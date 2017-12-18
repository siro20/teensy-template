#include "WProgram.h"

extern "C" int main(void)
{
#ifdef USING_MAKEFILE

	// To use Teensy 3.0 without Arduino, simply put your code here.
	// For example:

	pinMode(13, OUTPUT);

	Serial2.begin(115200);
	EhciDebug.begin();
	Serial2.println("Teensy LC USB gadget starting...");
	size_t toggle1 = 0;
	size_t toggle2 = 0;
	size_t toggleLED = 0;
	size_t toggleLEDspeed = 0;

	elapsedMillis timer_blink;
	elapsedMillis timer_second;

	digitalWriteFast(13, HIGH);
	delay(500);

	while (1) {
		if (toggleLEDspeed > 0 && timer_blink > toggleLEDspeed) {
			timer_blink = 0;

			toggleLED ^= 1;
			digitalWriteFast(13, toggleLED);
		}
		if (timer_second > 1000) {
			timer_second = 0;
			if (toggle1 + toggle2 == 2) {
				toggleLEDspeed = 125;
			} else if (toggle1 + toggle2 == 1) {
				toggleLEDspeed = 250;
			} else {
				toggleLEDspeed = 0;
			}
			toggle1 = 0;
			toggle2 = 0;
		}

		if (Serial2.available()) {
			int c = Serial2.read();
			EhciDebug.write(c);
			toggle1 = 1;
		}
		if (EhciDebug.available()) {
			int c = EhciDebug.read();
			Serial2.write(c);
			toggle2 = 1;
		}
	}


#else
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		yield();
	}
#endif
}

