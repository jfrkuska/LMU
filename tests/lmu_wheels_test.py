#!/usr/bin/env python
'''

It should be noted that the client can also be used with
the guard construct that is available in python 2.5 and up::

    with ModbusClient('127.0.0.1') as client:
        result = client.read_coils(1,10)
        print result
'''
import sys, getopt
from pymodbus.client.sync import ModbusSerialClient as ModbusClient

try:
	opts, args = getopt.getopt(sys.argv[1:],"t:o:")
except getopt.GetoptError:
	print sys.argv[0], '-t <chassis throttle> -o <chassis orientation>'
	sys.exit(2)
for opt, arg in opts:
	if opt == '-t':
		throttle = int(arg)
	elif opt == '-o':
		orientation = int(arg)

def enum(**enums):
	return type('Enum', (), enums)

LMUOrientation = {	'STP':0,
			'FWD':1,
			'BAK':2,
			'CW':3,
			'CCW':4,
		}

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
devport = '/dev/ttyACM0'
client = ModbusClient(method='rtu', port=devport, parity='N', stopbits=1, bytesize=8, baudrate=115200, timeout=0.148, uid=1)

client.connect()

rq = client.write_registers(LMURegs['FB_START'], [throttle, orientation])
rr = client.read_holding_registers(LMURegs['FB_START'],
	2,
	unit=1)
print(rr.registers)

client.close()
