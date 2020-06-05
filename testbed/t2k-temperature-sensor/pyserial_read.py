#!/usr/bin/env python

from datetime import datetime
import serial, sys
import time

sr = serial.Serial(
    port='COM1',
    baudrate=115200,
    parity=serial.PARITY_NONE,
    bytesize=serial.EIGHTBITS,
    timeout=None
)

if not sr.isOpen():
    print('Fail to connect to RS232.')
    sys.exit()

# Issue command to start reading.
run_cmd = 'run 1\r'
sr.write(run_cmd.encode())
# Flush the buffer
rb = sr.readline().decode()

print('Enter your commands below.\r\nInsert "exit" to leave the application or carrier return to retrieve readings.')

_input=1
while 1 :
    # get keyboard input
    _input = input(">> ")

    if _input == 'exit':
        sr.close()
        exit()
    else:

        rb = sr.readline().decode()
        while 'run 1' in rb:
            rb = sr.readline().decode()
        print(datetime.now().strftime('%Y/%m/%d %H:%M:%S'))
        print(rb)