#!/usr/bin/env python
'''

It should be noted that the client can also be used with
the guard construct that is available in python 2.5 and up::

    with ModbusClient('127.0.0.1') as client:
        result = client.read_coils(1,10)
        print result
'''
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from pymodbus.client.sync import ModbusSerialClient as ModbusClient

def enum(**enums):
	return type('Enum', (), enums)

LMURegs = {'MTR_IDX':0,
		'MTR_DIR':1,
		'MTR_THROTTLE':2,
		'SW_IDX':3,
		'SW_STATE':4,
		'SENSR_IDX':5,
		'SENSR_REG':6,
		'SENSR_DATA':7,
		'FB_START':8,
		'FB_0':0,
		'FB_1':1,
		'FB_2':2,
		'FB_3':4,
		'FB_4':5,
		'FB_DELTA_T':6,
		'FB_END':14
		}
#---------------------------------------------------------------------------# 
# configure the client logging
#---------------------------------------------------------------------------# 
#import logging
#logging.basicConfig()
#log = logging.getLogger()
#log.setLevel(logging.DEBUG)
#devport = '/dev/ttyUSB0'
devport = '/dev/ttyACM3'
client = ModbusClient(method='rtu', port=devport, parity='N', stopbits=1, bytesize=8, baudrate=115200, timeout=0.050, uid=1)

client.connect()

#fig, ax = plt.subplots()
sample_cnt = 300
sample_rate = 15 
time_sec = sample_cnt / sample_rate
fig = plt.figure()
ax = plt.axes(xlim=(-time_sec, 0), ylim=(-0.5,0.5))
xline, = ax.plot([], [])
yline, = ax.plot([], [])
zline, = ax.plot([], [])

t = np.linspace(-time_sec, 0, sample_cnt)
x = [0] * sample_cnt
y = [0] * sample_cnt
z = [0] * sample_cnt
v = (x, y, z)
 
value = [0] * 3


def data_gen():
	while True:
		## update FB registers 
		rr = client.read_holding_registers(10,
			4,
			unit=1)
		print(rr.registers)
		for i in range(0, 3):
			value[i]=rr.registers[i]
			if (value[i] > 32000):
				value[i] -= 65535
                	value[i]=float(value[i])/1024
		#print(value)
		x.append(value[0])
		y.append(value[1])
		z.append(value[2])
		del x[0]
		del y[0]
		del z[0]
		
		## operate switches

		## set motors

		yield v

def update(data):
	xline.set_ydata(data[0])
	yline.set_ydata(data[1])
	zline.set_ydata(data[2])
	#xline.set_data(t, data[0])
	#yline.set_data(t, data[1])
	#zline.set_data(t, data[2])
	return (xline, yline, zline) 
	
def init():
	xline.set_data(t, x)
	yline.set_data(t, y)
	zline.set_data(t, z)
	return (xline, yline, zline)

ani = animation.FuncAnimation(fig, update, frames=data_gen, init_func=init, interval=(1000/sample_rate), blit=True)
plt.show()

client.close()
