
### Transfer function for HSC sensor:
## Output(% of 2^14 counts) = 80%/(Pmax-Pmin) * (P-Pmin) + 10%
## P-Pmin = (Output-10%) * (Pmax-Pmin)/80%
## P = (Output-10%) * (Pmax-Pmin)/80% + Pmin

output_10 = int(0.1 * 2**14)
output_80 = int(0.8 * 2**14)

## units
bar = 100000 #Pa

class HSC:
	def __init__(self, bus, model, addr):
		if model == '1.6BA':
			self.Pmin = 0
			self.Pmax = 1.6
			self.units = bar
		
		elif model == '100MD':
			self.Pmin = -0.100
			self.Pmax = 0.100
			self.units = bar
		
		else:
			print('Device not available')
			self.Pmin = 0
			self.Pmax = 0
			self.units = 0
		
		self.i2c = bus
		self.i2c_addr = addr
	
	def _get_raw(self):
		#read 2 bytes, pressure output:
		raw = self.i2c.read_i2c_block_data(self.i2c_addr, 0x00, 4) #the device will ignore the register
		
		self.count = raw
		#status: 00 ok, 01 command mode, 10 stale data, 11 fault
		self.status = (raw[0] & 0xc0) >> 6
		
		#command mode will never happen (need to access the device during the 3ms initialization)
		#stale data: use the last captured data, do nothing
		#fault: bad reading
		if (self.status != 4):
			#14 bit pressure
			self.P_counts = ((raw[0] & 0x3f) << 8) + raw[1]
			#11 bit temperature
			self.T_counts = (raw[2] << 8) + ((raw[3] & 0xe0) >> 5)
		else:
			self.P_counts = 0
			self.T_counts = 0
		
	def isready(self):
		self._get_raw()
		if (self.status != 4):
			return True
		else:
			return False
	
	def get_pressure(self):
		self._get_raw()
		
		pressure = (self.P_counts-output_10) * (self.Pmax-self.Pmin)/output_80 + self.Pmin
		pressure *= self.units #convert to Pa
		
		return round(pressure, 0)
	
	def get_temperature(self):
		self._get_raw()
		
		temperature = (self.T_counts/2047 * 200) - 50
		return round(temperature, 2)
	
	