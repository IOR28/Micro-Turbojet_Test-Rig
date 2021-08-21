from struct import unpack

T_cmd = 0x54 #'T' = 0x54
F_cmd = 0x46 #'F' = 0x46

Pt3_cmd = 0x63 #'P' = 0x50, total: +0x10, phase 3: +0x03
Pt4_cmd = 0x64 #'P' = 0x50, total: +0x10, phase 4: +0x04
Pt9_cmd = 0x69 #'P' = 0x50, total: +0x10, phase 9: +0x09
P9_cmd = 0x60 #'P' = 0x50, static: +0x08, phase 9: +0x09

Tt1_cmd = 0x55 #'T' = 0x54, total: +0 (there is no static), phase 1: +0x01
Tt3_cmd = 0x57 #'T' = 0x54, total: +0, phase 3: +0x03
Tt4_cmd = 0x58 #'T' = 0x54, total: +0, phase 4: +0x04
Tt5_cmd = 0x59 #'T' = 0x54, total: +0, phase 5: +0x05

class ATtiny1627:
	def __init__(self, bus, addr):
		self.i2c = bus
		self.i2c_addr = addr
	
	def isready(self):
		try:
			temp = self.i2c.read_byte_data(self.i2c_addr, 0) #cmd = 0, slave answers with its address
			if (temp == self.i2c_addr):
				return True
			else:
				return False
		except:
			return False
	
	def __read_float(self, cmd):
		raw = self.i2c.read_i2c_block_data(self.i2c_addr, cmd, 4) #float is 32bits = 4 bytes
		[Result] = unpack('f', bytearray(raw))
		
		return Result
		
	def get_Thrust(self):
		Thrust = self.__read_float(T_cmd)
		return round(Thrust, 2)
	
	def get_Flow(self):
		Flow = self.__read_float(F_cmd)
		return round(Flow, 4)
		
	def get_Pt3(self):
		Pt3 = self.__read_float(Pt3_cmd)
		return round(Pt3, 0)
	
	def get_Pt4(self):
		Pt4 = self.__read_float(Pt4_cmd)
		return round(Pt4, 0)
	
	def get_Pt9(self):
		Pt9 = self.__read_float(Pt9_cmd)
		return round(Pt9, 0)
	
	def get_P9(self):
		P9 = self.__read_float(P9_cmd)
		return round(P9, 0)
	
	def get_Tt1(self):
		Tt1 = self.__read_float(Tt1_cmd)
		return Tt1 #don't round, compute AirFlow
	
	def get_Tt3(self):
		Tt3 = self.__read_float(Tt3_cmd)
		return round(Tt3, 2) #if RTD: give more resolution!!
		
	def get_Tt4(self):
		Tt4 = self.__read_float(Tt4_cmd)
		return round(Tt4, 2)
		
	def get_Tt5(self):
		Tt5 = self.__read_float(Tt5_cmd)
		return round(Tt5, 2)
