import RPi.GPIO as GPIO
import time, signal, sys

class Control:
	def __signal_handler(self, sig, frame):
		print("Exit through keyboard")
		if (self.Ongoing_test): #let it exit gracefully
			self.Ongoing_test = False
			self.Signal_interrupt = True
			
		else: #test has not begun, just exit
			time.sleep(1)
			sys.exit(0)

	def __button_callback(self, channel):
		self.Ongoing_test = False #finish flag
		print("Finish button pressed")

	def __init__(self):
		self.Green = 7
		self.Red = 11
		self.Button = 13
		self.Ongoing_test = False #still initializing
		self.Signal_interrupt = False #in case keyboard interrupt
		
		GPIO.setmode(GPIO.BOARD)
		GPIO.setwarnings(False)
		
		#Set red LED as program is still initializing
		GPIO.setup(self.Green, GPIO.OUT) #green LED
		GPIO.output(self.Green, False)
		GPIO.setup(self.Red, GPIO.OUT) #red LED
		GPIO.output(self.Red, True)
		
		GPIO.setup(self.Button, GPIO.IN, pull_up_down=GPIO.PUD_UP) #pull up the pin
		#detect the falling edge when pressing the button and call the function
		GPIO.add_event_detect(self.Button, GPIO.FALLING, callback=self.__button_callback, bouncetime=100)
		
		#configure the signal handler for CTRL+C exits
		signal.signal(signal.SIGINT, self.__signal_handler)

	def error(self):
		#red LED flashing
		time.sleep(.5)
		GPIO.output(self.Red, False)
		time.sleep(.5)
		GPIO.output(self.Red, True)

	def measuring(self):
		#Set green LED, initialization complete, start measuring
		self.Ongoing_test = True #start flag
		GPIO.output(self.Green, True)
		GPIO.output(self.Red, False)

	def exiting(self):
		#Set red LED, test complete, saving
		GPIO.output(self.Green, False)
		GPIO.output(self.Red, True)

	def off(self):
		GPIO.output(self.Green, False)
		GPIO.output(self.Red, False)
		GPIO.cleanup()