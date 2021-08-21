import time, queue
from multiprocessing import Pipe,connection
from database import TurbojetDB

##########------MULTIPROCESSING------##########
def DB_controller(child_conn):
	q = queue.Queue()
	to_main = connection.Connection(child_conn.recv())
	T_data = child_conn.recv()
	T_DB = child_conn.recv()
	n = int(T_DB/T_data) #save data to database every T_DB/T_data samples
	
	##########------INITIALIZATION------##########

	starttime = time.time()
	DB = TurbojetDB()
	DB.create_table()
	exectime = time.time() - starttime
	print("Execution time to initialize DB connection: ", exectime)
	
	to_main.send(DB.Table) #send the name of the DB to main
	to_main.send('ready') #database ready flag
	#initialization passed

	##########------DATA SAVING------##########
	while (True): 
		if (to_main.poll()): #check if main said anything
			msg = to_main.recv()
			if (msg == 'finished'): #test finished flag
				break
			else: #if it didn't finish: its a measurement, put it in queue
				q.put(msg)
		
		if (q.qsize() > n): #qsize reached, save data to DB
			measurements = []
			
			for x in range(n): #retrieve the n measurements
				measurements.append(q.get())
			
			#print(len(measurements))
			#print(*measurements, sep='\n')
			DB.add_measurements(measurements) #save them to DB
			print(n, "Measurements saved to DB")
		else:
			time.sleep(T_data/2) #wait for a measurements to be performed


	
	#test is done
	##########------LAST SAVE------##########
	measurements = []
	n = q.qsize()
	for i in range(n): #retrieve all missing measurements
		measurements.append(q.get())
	#print(len(measurements))
	#print(*measurements, sep='\n')
	print("Last ", n, "measurements saved to DB")
	DB.add_measurements(measurements) #save them to DB


	##########------EXIT------##########
	
	print("Exiting DB")
	to_main.send('done') #flag to signal all data is saved
	