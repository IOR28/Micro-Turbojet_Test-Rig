import sys, math
from smbus import SMBus
from bmp280 import BMP280
from attiny1627 import ATtiny1627
from hsc_trustability import HSC

#for some reason, defining the bus and all devices on each execution performs better
i2c = SMBus(1)

#data from bmp280
bmp280 = BMP280(i2c_dev=i2c, i2c_addr=119) #0x77
tt0 = round(bmp280.get_temperature() + 273.15, 2)
pt0 = round(bmp280.get_pressure() * 100, 0)

#data from thrust&flow micro
T_F = ATtiny1627(i2c, 10) #0x0A
thrust = T_F.get_Thrust()
vol_fuelflow = T_F.get_Flow() #l/min

#compute fuel mass flow
ro_15 = 0.799 #kg/l at 15ºC
cf = -0.00093*tt0+1.26760 #density-temperature correction factor for kerosene, 1.00 at 15ºC
ro = ro_15 * cf
fuelflow = vol_fuelflow * ro / 60 #kg/s
fuelflow = round(fuelflow, 4)

#data from pressure micro
P = ATtiny1627(i2c, 11) #0x0B
pt3 = P.get_Pt3()
pt4 = P.get_Pt4()
pt9 = P.get_Pt9()
p9 = P.get_P9()

#data from temperature micro
T = ATtiny1627(i2c, 12) #0x0C
tt1 = T.get_Tt1()
tt3 = T.get_Tt3()
tt4 = T.get_Tt4()
tt5 = T.get_Tt5()

#data from HSC
Pt_bellmouth = HSC(i2c, '1.6BA', 40) #0x28
Ps_bellmouth = HSC(i2c, '100MD', 72) #0x48
pt1 = Pt_bellmouth.get_pressure()
p1 = pt1 - Ps_bellmouth.get_pressure()
if (p1 > pt1):
	p1 = pt1

#compute air mass flow
gamma = 1.4
r = 287.14

#M1 = math.sqrt(((pt1/p1)**((gamma-1)/gamma)-1)*2/(gamma-1))
#simplify: (gamma-1)/gamma = 2/7, 2/(gamma-1)=5
M1 = math.sqrt(((pt1/p1)**(2/7)-1)*5)

#mf_parameter = math.sqrt(gamma/r)*M1*(1+(gamma-1)/2*M1**2]**(-(gamma+1)/(2*(gamma-1)))
#simplify: (gamma-1)/2 = 0.2, (gamma+1)/(2*(gamma-1) = 3
mf_parameter = math.sqrt(gamma/r)*M1*(1+0.2*M1**2)**(-3)

#AirFlow = mf_paramenter*Pt1*A1/math.sqrt(Tt1)
A1 = math.pi*0.03**2 #Bellmouth, diameter 60mm
airflow = mf_parameter*pt1*A1/math.sqrt(tt1)

if (airflow <= 0.015):
	airflow = 0.0

airflow = round(airflow, 4)

#create tuple with all values
values = (thrust, fuelflow, tt0, pt0, airflow, tt3, pt3, tt4, pt4, tt5, pt9, p9)

print(*values, sep='\t')

