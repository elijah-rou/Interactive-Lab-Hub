from flask import Flask, render_template, Response
from flask_socketio import SocketIO, emit
import serial
import time
from threading import Thread, Lock
import paho.mqtt.client as mqtt
from imutils.video import VideoStream
from imutils import resize
import cv2

# Flask Webserver
app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

# Arduino communication
ser = serial.Serial('/dev/ttyUSB0', 9600)
def read_from_port(ser):
    while True:
        reading = ser.readline().decode().strip()
        print(reading)
        socketio.emit('server-msg', reading)

thread = Thread(target=read_from_port, args=[ser])
thread.start()

# Video Stream
outputFrame = None
lock = Lock()
vs = VideoStream(src=0).start()
time.sleep(2)

def generate():
    # grab global references to the output frame and lock variables
    global outputFrame, lock
    # loop over frames from the output stream
    while True:
        # wait until the lock is acquired
        with lock:
            # check if the output frame is available, otherwise skip
            # the iteration of the loop
            if outputFrame is None:
                continue
            # encode the frame in JPEG format
            (flag, encodedImage) = cv2.imencode(".jpg", outputFrame)
            # ensure the frame was successfully encoded
            if not flag:
                continue
        # yield the output frame in the byte format
        yield(b'--frame\r\n' b'Content-Type: image/jpeg\r\n\r\n' + bytearray(encodedImage) + b'\r\n')

# MQTT client
client = mqtt.Client()
broker = "mqtt.eclipse.org"
topic = "ixe"

# Message functions
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    client.subscribe(topic)
def on_message(client, userdata, msg):
    receivedMessage = str(msg.payload.decode("utf-8"))
    print("received message = "+receivedMessage)
    if receivedMessage == "red":
        ser.write(b'R')
    elif receivedMessage == "blue":
        ser.write(b'B')
    elif receivedMessage == "green":
        ser.write(b'G')
    elif receivedMessage == "off":
        ser.write(b'L')

client.on_connect = on_connect
client.on_message = on_message
client.connect(broker, 1883, 60)
client.loop_start()

@app.route('/')
def index():
    return render_template('index.html')

@app.route("/video_feed")
def video_feed():
	# return the response generated along with the specific media
	# type (mime type)
	return Response(generate(),
		mimetype = "multipart/x-mixed-replace; boundary=frame")

@socketio.on('connect')
def test_connect():
    print('Client connected')
    emit('my response', {'data': 'Connected'})

@socketio.on('disconnect')
def test_disconnect():
    print('Client disconnected')


# Handle the LED messages
@socketio.on('ledBLUE')
def led_blue():
    print("Turn the LED blue!")
    client.publish(topic, "blue")

@socketio.on('ledRED')
def led_red():
    print("Turn the LED red!")
    client.publish(topic, "red")

@socketio.on('ledGREEN')
def led_green():
    print("Turn the LED green!")
    client.publish(topic, "green")

@socketio.on('ledOFF')
def led_off():
    print("Turn the LED off!")
    client.publish(topic, "off")

def stream_video():
    global outputFrame, vs, lock
    while True:
        frame = vs.read()
        with lock:
            outputFrame = resize(frame, width=400).copy()


def main():
    t = Thread(target=stream_video)
    t.daemon = True
    t.start()
    app.run(host='0.0.0.0', threaded=True)
    socketio.run(app)
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        ser.close()
        client.disconnect()
        client.loop_stop()
        vs.stop()
        print ("done")


if __name__ == '__main__':
    main()
