from smbus import SMBus
from hsc_trustability import HSC
import time

i2c = SMBus(1)

#Initialise HSC sensors
Pt_bellmouth = HSC(i2c, '1.6BA', 40) #0x28
Ps_bellmouth = HSC(i2c, '100MD', 72) #0x48

print("Pt ready:")
print(Pt_bellmouth.isready())
print(Pt_bellmouth.count)

time.sleep(1)

print("Pt measure:")
print(Pt_bellmouth.get_pressure())
print(Pt_bellmouth.count)

print("Ps ready:")
print(Ps_bellmouth.isready())
print(Ps_bellmouth.count)

time.sleep(1)

print("Ps measure:")
print(Ps_bellmouth.get_pressure())
print(Ps_bellmouth.count)