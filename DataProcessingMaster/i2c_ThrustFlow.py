from smbus import SMBus
from struct import unpack
import time

i2c = SMBus(1)

for i in range(20):
#address: 0x0A, command: 0x54, get 4bytes
	raw = i2c.read_i2c_block_data(0x0A, 0x54, 4)
	[result] = unpack('f', bytearray(raw))
	print(result)
	time.sleep(.15)
	
