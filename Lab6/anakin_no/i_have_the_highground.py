#!/usr/bin/env python3

from vosk import Model, KaldiRecognizer
import sys
import os
import wave
import json
from google_speech import Speech

if not os.path.exists("vosk_small"):
    print ("Please download the model from https://github.com/alphacep/vosk-api/blob/master/doc/models.md and unpack as 'model' in the current folder.")
    exit (1)

wf = wave.open(sys.argv[1], "rb")
if wf.getnchannels() != 1 or wf.getsampwidth() != 2 or wf.getcomptype() != "NONE":
    print ("Audio file must be WAV format mono PCM.")
    exit (1)

model = Model("vosk_small")
# You can also specify the possible word list
rec = KaldiRecognizer(model, wf.getframerate(), "i have the high ground [unk]")

while True:
    data = wf.readframes(4000)
    if len(data) == 0:
        break
    if rec.AcceptWaveform(data):
        text = json.loads(rec.Result())["text"]
        if "i have the high ground" in text:
            print("ANAKIN")
            speech = Speech("I hate you", "en")
            speech.play()
            break

