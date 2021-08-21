from bmp280 import BMP280
from smbus import SMBus
from attiny1627 import ATtiny1627
from hsc_trustability import HSC

i2c = SMBus(1)

# Initialise the BMP280
try:
	bmp280 = BMP280(i2c_dev=i2c, i2c_addr=119) #0x77
	temperature = bmp280.get_temperature()
	pressure = bmp280.get_pressure()
	#print('BMP280 found!')
except:
	raise Exception('BMP280 not found!')

#Initialise HSC sensors
Pt_bellmouth = HSC(i2c, '1.6BA', 40) #0x28
Ps_bellmouth = HSC(i2c, '100MD', 72) #0x48

if (Pt_bellmouth.isready() and Ps_bellmouth.isready()):
	#print('TruStability devices found!')
	pt1 = Pt_bellmouth.get_pressure()
	p1 = pt1 - Ps_bellmouth.get_pressure()
	if (p1 > pt1):
		p1 = pt1
else:
	raise Exception('Trustability devices not found!')


#Initialise the Thrust&Flow micro
T_F = ATtiny1627(i2c, 10) #0x0A
if (T_F.isready()):
	#print('Thrust&Flow device found!')
	thrust = T_F.get_Thrust()
	fuelflow = T_F.get_Flow()
else:
	raise Exception('Thrust&Flow device not found!')
	
#Initialise the Pressure micro
P = ATtiny1627(i2c, 11) #0x0B
if (P.isready()):
	#print('Pressure device found!')
	pt3 = P.get_Pt3()
	pt4 = P.get_Pt4()
	pt9 = P.get_Pt9()
	p9 = P.get_P9()
else:
	raise Exception('Pressure device not found!')
	
#Initialise the Temperature micro
T = ATtiny1627(i2c, 12) #0x0C
if (T.isready()):
	#print('Temperature device found!')
	tt1 = T.get_Tt1()
	tt3 = T.get_Tt3()
	tt4 = T.get_Tt4()
	tt5 = T.get_Tt5()
else:
	raise Exception('Temperature device not found!')

	
