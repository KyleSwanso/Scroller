//NodePi Scroller version 0.91
//Kyle Swanson


//Libraries.
var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var jsonParser = bodyParser.json();
var gpio = require('rpi-gpio');
var urlencodedParser = bodyParser.urlencoded({
    extended: false
});
var Particle = require('particle-api-js');
var particle = new Particle();

//Twilio credentials. Global variables.
var accountSid = 'ACCOUNT SID';
var authToken = "AUTH TOKEN";
var client = require('twilio')(accountSid, authToken);

//Particle credentials. Global variables.
var d_id = 'DEVICE ID';
var p_token = "PARTICLE TOKEN";


app.get('/', function(req, res) {
    res.send('Hello World!');
});


app.post('/', urlencodedParser, function(req, res) {
	console.log(req.body);

	//Register an event stream in the Particle cloud with publishEvent
	var publishEventPr = particle.publishEvent({ name: 'msg_event', data: req.body.Body, auth: p_token });

	   publishEventPr.then(
  		function(data) {
    			if (data.body.ok) { console.log("Event published succesfully") }
  		},
  	   function(err) {
    		console.log("Failed to publish event: " + err)
  	   }
	);


	//Reply functionality was removed for this version.

	//What's a twiml?
	var twiml = '<?xml version="1.0" encoding="UTF-8" ?><Response></Response>';
	res.send(twiml, {
		'Content-Type': 'text/xml'
    	}, 200);
});

app.listen(3000, function() {
	console.log('Example app listening on port 3000!');
});
