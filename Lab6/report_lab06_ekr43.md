# GreetingBot

## Try some Python code on the Pi

**How do you know what the shell script is doing?**
We can `cat` the script to see what commands are being executed by bash.

**How do we use ``vosk`` to recognize words and phrases?**
We load a model for ``vosk`` to use and then specify in code what words the model should look for in a string"

**Include the output of vosk recognizing phrases you taught it to look for.**
```sh
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : "pi likes"
}
{
  "partial" : "pi likes"
}
{
  "partial" : "pi likes"
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : "eddie"
}
{
  "partial" : "eddie"
}
{
  "partial" : "eddie"
}
{
  "partial" : "eddie likes"
}
{
  "partial" : "eddie likes"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "partial" : "eddie likes pi"
}
{
  "result" : [{
      "conf" : 1.000000,
      "end" : 2.970000,
      "start" : 2.700000,
      "word" : "eddie"
    }, {
      "conf" : 1.000000,
      "end" : 3.240000,
      "start" : 2.970000,
      "word" : "likes"
    }, {
      "conf" : 1.000000,
      "end" : 3.660000,
      "start" : 3.240000,
      "word" : "pi"
    }],
  "text" : "eddie likes pi"
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "partial" : ""
}
{
  "result" : [{
      "conf" : 0.985111,
      "end" : 4.620000,
      "start" : 4.560000,
      "word" : "pi"
    }],
  "text" : "pi"
}
```

**Include the listing for a shell script and model files that you use to get vosk to recognize these phrases.**
See speech2text/

## Connect the Arduino and the RPi

### Hello Pi, Hello Arduino

**What would you change to make sayHelloPi say something else?**
Change the message in the arduino sketch.

**How could you make it so that the Pi would only say something if the lights came on in the room?**
We could add a photocell to the arduino attached to the analog inputs and conditionally send the message depending on the analog reading.

**How could you make it so that the Pi would say different things based on different sensor values read by the Arduino?**
As with the previous question, we could threshold the readings from all the sensors and create a decision tree for which message to send to the pi.

**Next, try out ``HelloArduino``. First have ``HelloArduino.ino`` listen for messages from ``HelloArduino.py``. Next, use ``morse_code_translator.ino``. What happens differently?**
With `HelloArduinio`, the arduino will just blink if it receives a message. However, `morse_code_translator` will blink the arduino LED a specific amounnt of times depending on which character is sent by the pi. The amount of times is determined by the morse encoding of the character.

## Your own voice agent 

**Record someone trying out your design**
See `media/anakin_no.MOV`
**Submit your code to Github**
See `anakin_no/`

