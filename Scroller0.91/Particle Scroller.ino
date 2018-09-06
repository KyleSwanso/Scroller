//Particle Scroller version 0.91
//Kyle Swanson


//Libraries.
#include "Particle.h"
#include "neopixel.h"
#include "neomatrix.h"
#include "Adafruit_GFX.h"
#undef swap
#include <deque>
#include <string>
#include <cmath>


// IMPORTANT: Set pixel PIN and TYPE.
#define PIXEL_PIN D2
#define PIXEL_TYPE SK6812RGBW


//NeoMatrix Constructor (TILED).
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(98,1,1,8, PIXEL_PIN,
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_ZIGZAG +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  PIXEL_TYPE);


//Global variables.
std::deque<String> messageQueue; //A deque of Strings to store text messages.
std::deque<String> messageQueue2; //A deque of Strings to store text messages.
std::deque<String> messageQueue3; //A deque of Strings to store text messages.
int pixelPerChar = 6;  //8 x 6 pixels.
bool discoMode = 0;


//Setup runs once.
void setup() {

  //Subscribe to a Particle Event.
  Particle.subscribe("msg_event", msgHandler);

  //Setup the LED Matrix.
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(50); //Careful this will change your power draw.
  matrix.setTextColor(matrix.Color(0,0,0));

  //Test message
  messageQueue.push_back("Test Message");
}


//Loop runs over and over again.
void loop() {

  checkClear();
  checkDisco();
	shiftDown();

	if (!messageQueue.empty()) {
    tasteColors();
	  draw();
	  messageQueue.pop_front();
	}

	delay(50); //Just because.
}


//This is our Particle Event handler.
void msgHandler(const char *event, const char *data) {

  messageQueue.push_back(data);
  messageQueue2.push_back(data);
  messageQueue3.push_back(data);
}


//Drawing on the LED matrix.
void draw () {

	String message = messageQueue.at(0);
	int cursorDisplacement = strlen(message) * pixelPerChar + matrix.width();

	for (int sweep = 0; sweep < 3; sweep++) {

		for (int x = matrix.width(); x >= -cursorDisplacement; x--) {
		  matrix.fillScreen(0);
			matrix.setCursor(x, 0);
			matrix.print(F(message));
			matrix.show();
  		delay(40); //Speed of text scroll.

      if (discoMode) {
          matrix.setTextColor(matrix.Color(rand()%255,rand()%255,rand()%255));
      }

		}

	}

}


//Shifts the messages down through the messageQueue's.
void shiftDown () {

  if (messageQueue2.empty() && !messageQueue3.empty()) {
	  messageQueue2.push_back(messageQueue3.at(0));
	  messageQueue3.pop_front();
  }

  if (messageQueue.empty() && !messageQueue2.empty()) {
	  messageQueue.push_back(messageQueue2.at(0));
	  messageQueue2.pop_front();
  }

}


//Make and set text color based on first three characters of the message.
void tasteColors () {

  std::string tempString = static_cast<std::string>(messageQueue.at(0));

	uint16_t Red = tempString[0];
	uint16_t Green = tempString[1];
	uint16_t Blue = tempString[2];

	matrix.setTextColor(matrix.Color(Red,Green,Blue));
}


//Check for command codes.
void checkClear () {

	std::string tempString = static_cast<std::string>(messageQueue.back());
	std::size_t found = tempString.find("ALLCLEAR");

  if (found != std::string::npos) {
	   messageQueue.clear();
		 messageQueue2.clear();
		 messageQueue3.clear();
	}

}


void checkDisco () {

  std::string tempString = static_cast<std::string>(messageQueue.back());
	std::size_t found = tempString.find("DISCO");

  if (found != std::string::npos) {
	   discoMode = 1;
	}

  else {
     discoMode = 0;
  }

}
