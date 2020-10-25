import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)
while True:
    try:
        ser.write(b'sos') #arbitrary message
        time.sleep(1.25)
    except KeyboardInterrupt:
        ser.close();
        break
