# Scroller
##Scroller is a Node webserver paired with a Particle Photon to enable the display of text messages (SMS) on an LED matrix.

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
You will need a Raspberry Pi or similar with node.js + express, and body-parser installed.
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
You may need to add a port forward in your router settings.
```

**Suppliers:**
```
Everything can be found online at Adafruit or Amazon.
```

**Limitations:**
```
The program supports up to 255 character messages.
~100+ actively queued messages before RAM on the Particle Photon becomes an issue.
```

**TO-DO:**
```
Create website interface.
Multiple message queues without cloning messages.
Tweak displayed text color range.
Observe for bugs.
```
