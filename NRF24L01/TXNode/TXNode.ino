/*
 Name:		TXNode.ino
 Created:	1/6/2018 9:54:39 PM
 Author:	Dr. -Ing. Ahmad Kamal Nasir (dringakn@gmail.com, http://web.lums.edu.pk/~akn/)
 License:	This Library is licensed under a GPLv3 License
 Purpose:	The purpose of this test program is to implement a basic transmitter node using
 NRF24L01 transciever.
 */

#include <RF24.h>
bool radioNumber = 0;
bool role = 1;		//  0=Rx, 1=Tx
RF24 radio(48, 53);	// (CE, CS) Pins
byte addresses[][6] = { "1Node","2Node" };

void setup() {
	Serial.begin(115200);
	Serial.println(F("RF24/examples/GettingStarted"));
	Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
	radio.begin();
	radio.setAutoAck(true);
	radio.setChannel(120);
	radio.setCRCLength(RF24_CRC_16);
	radio.setDataRate(RF24_250KBPS);
	radio.setPALevel(RF24_PA_LOW);
	//radio.enableDynamicPayloads();
	radio.setRetries(40, 100);
	if (radioNumber) {
		radio.openWritingPipe(addresses[1]);
		radio.openReadingPipe(1, addresses[0]);
	}
	else {
		radio.openWritingPipe(addresses[0]);
		radio.openReadingPipe(1, addresses[1]);
	}

	radio.startListening();

}

void loop() {
	if (role == 1) {
		radio.stopListening();                                    // First, stop listening so we can talk.
		Serial.println(F("Now sending"));
		unsigned long start_time = micros();                             // Take the time, and send it.  This will block until complete
		if (!radio.write(&start_time, sizeof(unsigned long))) {
			Serial.println(F("failed"));
		}
		radio.startListening();                                    // Now, continue listening
		unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
		boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not
		while (!radio.available()) {                             // While nothing is received
			if (micros() - started_waiting_at > 1000000) {            // If waited longer than 200ms, indicate timeout and exit while loop
				timeout = true;
				break;
			}
		}

		if (timeout) {                                             // Describe the results
			Serial.println(F("Failed, response timed out."));
		}
		else {
			unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
			radio.read(&got_time, sizeof(unsigned long));
			unsigned long end_time = millis();

			// Spew it
			Serial.print(F("Sent:"));
			Serial.print(start_time);
			Serial.print(F(", Got:"));
			Serial.print(got_time);
			Serial.print(F(", Round-trip:"));
			Serial.print(end_time - start_time);
			Serial.println(F(" mSec"));
		}
		delay(1000);
	}

	if (role == 0)
	{
		unsigned long got_time;

		if (radio.available()) {
			// Variable for the received timestamp
			while (radio.available()) {                                   // While there is data ready
				radio.read(&got_time, sizeof(unsigned long));             // Get the payload
			}

			radio.stopListening();                                        // First, stop listening so we can talk   
			radio.write(&got_time, sizeof(unsigned long));              // Send the final one back.      
			radio.startListening();                                       // Now, resume listening so we catch the next packets.     
			Serial.print(F("Sent:"));
			Serial.println(got_time);
		}
	}

	if (Serial.available())
	{
		char c = toupper(Serial.read());
		if (c == 'T') {
			Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
			role = 1;                  // Become the primary transmitter (ping out)
		}
		else
			if (c == 'R') {
				Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
				role = 0;                // Become the primary receiver (pong back)
				radio.startListening();
			}
	}

}

