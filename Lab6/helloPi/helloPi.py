# HelloPi by Wendy Ju
#
# June 25, 2020
# to use the ACT LED, you must first run $ echo none | sudo tee /sys/class/leds/led0/trigger from the command line
# to restore the ACT LED, reboot, or run echo mmc0 | sudo tee /sys/class/leds/led0/trigger

import warnings
import serial
import time
from gpiozero import LED, PinNonPhysical
from subprocess import call

# This disables the PinNonPhysical warning for the rest of the script
warnings.simplefilter('ignore', category=PinNonPhysical)


ser=serial.Serial("/dev/ttyUSB0",9600)  #change ACM number as found from ls /dev/tty/ACM*
ser.baudrate=9600
actled = LED(29)


while True:
   try:
      message=ser.readline()
      print(message)
      actled.blink()
      time.sleep(1.25)
   except KeyboardInterrupt:
      ser.close()
      break
