"""
server.py

Author: Nikolas Martelaro (nmartelaro@gmail.com) & Wendy Ju (wendyju@cornell.edu)

Purpose: This is the server that runs the web application and the serial
communication with the microcontroller. Messaging to the microcontroller is done
using serial. Messaging to the webapp is done using SocketIO.

Usage: python3 server.py

Notes: You will need to specify what port you would like the web app to be
served from. You will also need to include the serial port address as a command
line input.
"""

from flask import Flask, render_template
from flask_socketio import SocketIO, emit
import serial
import time
from threading import Thread

# Arduino communication
ser = serial.Serial('/dev/ttyUSB0', 9600)
def read_from_port(ser):
	while True:
		reading = ser.readline().decode().strip()
		print(reading)
		socketio.emit('server-msg', reading)

thread = Thread(target=read_from_port, args=[ser])
thread.start()

# Flask Webserver
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

@app.route('/')
def index():
    return render_template('index.html')

@socketio.on('connect')
def test_connect():
    print('Client connected')
    emit('my response', {'data': 'Connected'})

@socketio.on('disconnect')
def test_disconnect():
    print('Client disconnected')


# Handle the LED messages
@socketio.on('ledON')
def led_on():
    print("Turn the LED on!")
    ser.write(b'H') 

@socketio.on('ledOFF')
def led_off():
    print("Turn the LED off!")
    ser.write(b'L') 


if __name__ == '__main__':
    app.run(host='0.0.0.0', threaded=True)
    socketio.run(app)
