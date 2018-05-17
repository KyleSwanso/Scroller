# Scroller
##Scroller is a node.js webserver paired with a Particle Photon to enable the display of text messages (SMS) on an LED matrix.

**Program flow:**
```
Send a text message (SMS) to your Twilio phone number.
Twilio webhook POSTS to the node.js webserver.
Node.js webserver calls Particle Cloud function with your text message body as the argument.
Particle cloud calls the corresponding function on the local Particle Photon.
Message is displayed to the LED matrix.
```

**Requirements:**
```
You will need a Twilio account (twilio.com) or similar SMS gateway.  
You will need a Particle IO account (particle.io) and a Particle Photon or similar.
An LED matrix of your choice.  We used Adafruit "neoPixel" brand LED strips to build a large matrix.
An LED power supply.  Please select one with enough current for your needs.
Level-Shifter (3.3v to 5v). We used a TXB0108 from Adafruit.
Bus-Bars (Optional).  They sure are handy if you're using LED strips to build your matrix.
Waterproof wiring connectors. 2-pin. (Optional).  Allows fast and easy removal of an entire strip. 
```

**Notes:**
```
Don't forget the 300 ohm resistor on your data input.  
Your Power supply should have a safety margin. Get more current than you need.
Don't be a neanderthal.  Use heat shrink tubing on your soldered wires.
```

**Suppliers:**
```
Everything can be found online at Adafruit or Amazon.
```

**Limitations:**
```
Currently the program only supports up to 63 character messages.
Future implementation will support up to 255 character messages.
```

**TO-DO:**
```
Switch from Particle Function to Particle Events.
Add message parsing to enable the addition of control codes.
Create a message queue.
```
