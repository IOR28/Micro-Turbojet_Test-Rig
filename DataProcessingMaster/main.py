import time, subprocess, os
from multiprocessing import Process, Pipe
from control import Control
from DB_controller import DB_controller
from export_file import export_CSV, export_XLSX

##########------FUNCTIONS------##########
def decode_strings(byt):
	str = byt.decode('utf-8')
	str = str.rstrip('\n')
	str = str.split('\t')

	return str

def decode_floats(str):	
	if 'nan' in str:
		val = ()
		#print("data has null...")
		for i in range(len(str)):
			if str[i] != 'nan':
				val += (float(str[i]),)
			else:
				val += (None,)
	else:
		val = tuple(float(i) for i in str)

	return val


##########------INITIALIZATION------##########
print("Initializing...")
#set the global variables
#sampling period should be greater than exec_time to work properly, try >300ms
#if synchronism loss: increase T_data, if lots of nulls: increase T_data
T_data = .5 #standard: 500ms

#where to send data? can be both or none
toDB = False
toConsole = True

if (toDB):
	#set the saving period: save every x second, T_DB/T_data samples
	T_DB = 5 #standard: 5s -> 5/0.5 = 10 samples
	
	#after saving to DB, send the data elsewhere? can be both or none
	to_CSV = True
	to_XLSX = True

ctrl = Control() #initilize control class, red LED on = main still initializing

try: #check if devices are available, run initialize_i2c script and retrieve exceptions
	cmd = 'sudo python3 initialize_i2c.py'
	init = subprocess.check_call(cmd, stdout=subprocess.PIPE, shell=True)
except subprocess.CalledProcessError:
	print('Initialization Failed')
	#Enter a infinite loop with red LED blinking
	while(True):
		ctrl.error() #red LED flashing = init error


##########------MULTIPROCESSING------##########
if (toDB):
	main_conn, DB_conn = Pipe(True)
	db = Process(target=DB_controller, args=(DB_conn,))
	db.daemon = True
	db.start()
	main_conn.send(DB_conn.fileno())
	main_conn.send(T_data)
	main_conn.send(T_DB)
	
	print('Waiting for DB...')
	#retrieve the name of the table for post-processing
	name_table = main_conn.recv()
	
	DB_ready = main_conn.recv()
	if (DB_ready == 'ready'):
		print('DB is ready')

#initialization passed


##########------MEASUREMENTS------##########
print("Measuring...")
if (toConsole): #print header
	data = ('Thrust', 'FuelFlow', 'Tt0', 'Pt0', 'AirFlow', 'Tt3', 'Pt3', 'Tt4', 'Pt4', 'Tt5', 'Pt5', 'P9')
	row_format = '{:^15}' * (len(data))
	print('-'*185)
	print(row_format.format(*data))
	print('-'*185)

#Begin measuring
ctrl.measuring() #green LED on = measuring

reminder = 0 #in case of lost of synchronization
t = float(0) #t=0 for first sample, increases T_data
while ctrl.Ongoing_test:
	starttime = time.time()
	
	#gather data, not the cleanest way to do it, but the only way that works
	cmd = 'sudo python3 gather_data.py'
	gd = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
	out, err = gd.communicate()	
	
	strgs = decode_strings(out)
	exec_time = time.time() - starttime
	if ('nan' in strgs) and (exec_time < .5*T_data): #data missing, try again
		time.sleep(.7*T_data-exec_time) #sleep a bit so micros recover
		#repeat
		cmd = 'sudo python3 gather_data.py'
		gd = subprocess.Popen(cmd, stdout=subprocess.PIPE, shell=True)
		out, err = gd.communicate()
		strgs = decode_strings(out)

	
	#process data
	if (toConsole): #print them on console
		print(row_format.format(*strgs))
	if (toDB): #send data through pipe, DB_controller will pick them
		values = decode_floats(strgs) #strings to floats
		main_conn.send((t,) + values) #time stamp it before sending to DB
	t += T_data
	
	#check total execution time and periodicity
	exec_time = time.time() - starttime
	#print("gather_data execution time: ", exec_time)
	if (T_data > (exec_time+reminder)):
		time.sleep(T_data-exec_time-reminder) #sleep until next sample
		reminder = 0
	else:
	#something went wrong, perform the next sample slightly earlier
	#to regain synchronism
		reminder += (exec_time-T_data)
		if (reminder > .5*T_data): #synchronism is too bad at this point
			print("Lost sincronization!!")
			#Enter a infinite loop with red LED blinking
			while(True):
				ctrl.error() #red LED flashing = error

#measurements ended


##########------EXITING PROGRAM------##########
ctrl.exiting() #Set red LED, test complete, last saves
if (toDB):
	
	#exit through CTRL+C = !!!ERROR!!!, delete DB table
	if (ctrl.Signal_interrupt):
		from database import TurbojetDB
		TurbojetDB(name_table).drop_table()
		print("Table " + name_table +  " deleted")
	
	else: #normal rutine
		#send test finished flag to DB_controller
		print("Test finished, final saves...")
		main_conn.send('finished')
		db.join() #join threads with DB
		#wait for DB to save all data
		
		#close all DB connections
		DB_done = main_conn.recv()
		if (DB_done == 'done'):
			db.close()
			main_conn.close()
			DB_conn.close()
		

	##########------EXPORTING FILES------##########
		#export to file
		if (to_CSV):
			csv_file = export_CSV(name_table, "test") #timestamp=True
			print("Exported: ", csv_file)
		if (to_XLSX):
			xlsx_file = export_XLSX(name_table, "test") #timestamp=True
			print("Exported: ", xlsx_file)

print("Exiting program")
print("Bye.")
#Clean control
ctrl.off()

#if (ctrl.Signal_interrupt):
#	sys.exit(0)
#else:
#	os.system('sudo shutdown -h now')

