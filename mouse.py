import sys
import serial
ser = serial.Serial('/dev/tty.usbmodemfa131', 9600, timeout=10)
ser.write('b')

ser.close()
quit()
