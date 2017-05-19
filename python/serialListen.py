import time
import serial
import webbrowser

# configure the serial connections (the parameters differs on the device you are connecting to)
ser = serial.Serial(
    port='COM10',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)

ser.isOpen()

while 1 :
        out = ''
        while ser.inWaiting() > 0:
            out += ser.read(1)

        if out != '':
			url = 'http://127.0.0.1:8000/?'
			webbrowser.open_new_tab(url + out)
			print ">>" + out