/*
 Name:		SRF04.ino
 Created:	12/12/2017 10:05:56 AM
 Author:	ahmad.kamal
*/

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	digitalWrite(LED_BUILTIN, HIGH);
	delay(1000);
	digitalWrite(LED_BUILTIN, LOW);
	delay(1000);
}
