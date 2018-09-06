//Libraries.
#include "Particle.h"
#include "neopixel.h"
#include "neomatrix.h"
#include "Adafruit_GFX.h"
#include <string>

// IMPORTANT: Set pixel PIN and TYPE
#define PIXEL_PIN D2
#define PIXEL_TYPE SK6812RGBW

//NeoMatrix Constructor (TILED)
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(98,1,1,8, PIXEL_PIN,
  NEO_TILE_TOP   + NEO_TILE_LEFT   + NEO_TILE_ROWS   + NEO_TILE_ZIGZAG +
  NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  PIXEL_TYPE);

//An array of 16-bit integer colors. RGB565? The colors of the text.
const uint16_t colors[] = {
  matrix.Color(255, 196, 64), matrix.Color(64, 255, 196), matrix.Color(196, 64, 255) };

//Global variables.
String message = "Default Message.";
int  pixelPerChar = 6;  //8 x 6 pixels.
int maxDisplacement;

//Setup runs once.
void setup() {
  //Declare a Particle Cloud function called msg_receiver.
  Particle.function("msg_receiver",msg_receiver);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(30);
  matrix.setTextColor(matrix.Color(0,0,0));
}

//Loop runs over and over again.
void loop() {

	draw();
	delay(500);
}


//This is our cloud function.
// Cloud functions must return int and take one String.
int msg_receiver(String incoming) {
	//handle incoming messages.
	message = incoming;
  return 1;
}

//Drawing on the LED matrix.
void draw () {

	int maxDisplacement = strlen(message) * pixelPerChar + matrix.width();

	for (int sweep = 0; sweep <= 3; sweep++) {
		matrix.setTextColor(colors[sweep]);

		for (int x = matrix.width(); x >= -maxDisplacement; x--) {
			matrix.fillScreen(0);
			matrix.setCursor(x, 0);
			matrix.print(F(message));
			matrix.show();
  			delay(50);		
		}

		
	}
}
