from contextlib import contextmanager
import mariadb
from datetime import datetime

@contextmanager
def connect_TurbojetTests():
	db = mariadb.connect( #connect to DB with predifined user
	  user="turbojet",
	  password="bench",
	  host="localhost",
	  database="TurbojetTests"
	)
	
	cursor = db.cursor()
	
	try:
		yield cursor
	except mariadb.Error as e:
		print(f"Error: {e}")
	finally:
		db.commit() #commit changes and close connection
		db.close()

class TurbojetDB:
	def __init__(self, t=datetime.now().strftime("%d%m%Y%H%M")):
		self.Table = t #default name generated as the current time
	
	def create_table(self):
	
		ex =('CREATE TABLE TurbojetTests.'+ self.Table + ' ('+ #set the name of the table as t0
			'Time FLOAT(2) PRIMARY KEY, '+ #start counting from t0, raspi gets data every T_data
			'Thrust FLOAT(2), '+ #Thrust [N] with res 2 decimals
			'FuelFlow FLOAT(4), '+ #Fuel Flow [kg/s] with res 4 decimals
			'Tt0 FLOAT(2), '+ #Temperature [K] has res 2 decimals
			'Pt0 FLOAT(0), '+ #Pressure [Pa] without decimals
			'AirFlow FLOAT(4), '+ #Air mass flow [kg/s] with res 4 decimals
			'Tt3 FLOAT(2), '+ #if RTD: give more resolution!!
			'Pt3 FLOAT(0), '+
			'Tt4 FLOAT(2), '+
			'Pt4 FLOAT(0), '+
			'Tt5 FLOAT(2), '+
			'Pt9 FLOAT(0), '+
			'P9 FLOAT(0)'+
			')')
		
		with connect_TurbojetTests() as cursor:
			cursor.execute(ex)

	def drop_table(self):
		drop = 'DROP TABLE TurbojetTests.' + self.Table + ';'
		
		with connect_TurbojetTests() as cursor:
			cursor.execute(drop)

	def add_measurements(self, values): #values can be as many rows of measurements as desired
		names = "(Time, Thrust, FuelFlow, Tt0, Pt0, AirFlow, Tt3, Pt3, Tt4, Pt4, Tt5, Pt9, P9)"
		format = "(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"
		ins = 'INSERT INTO TurbojetTests.' + self.Table + names + ' VALUES ' + format
		
		with connect_TurbojetTests() as cursor:
			cursor.execute(ins, values)

	def fetch_table(self): #return the table from the DB
		query = "SELECT * FROM TurbojetTests." + self.Table + ";"
		
		header, rows = [], []
		with connect_TurbojetTests() as cursor:
			cursor.execute(query)
			header = [row[0] for row in cursor.description]
			rows = cursor.fetchall()

		return header, rows


