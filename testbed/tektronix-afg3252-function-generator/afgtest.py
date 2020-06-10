from AFG3252 import * 
import time
import socket

fg = socket.gethostbyname('192.168.1.200')

print('Function generator on IP {0}...'.format(fg))
dev = AFG3252(fg)

dev.disableOutput(1)
dev.disableOutput(2)

dev.outputType('pulse')
dev.outputPolarity(1,'INVerted')
dev.setFrequency(7000)
#dev.setVoltage(1, "50mV")
dev.setVoltageHigh(1,"50mV")
dev.setVoltageLow(1,"0mV")
dev.setLeading(1, "4ns")
dev.setTrailing(1, "55us")

dev.enableOutput(1)
time.sleep(2)
dev.disableOutput(1)