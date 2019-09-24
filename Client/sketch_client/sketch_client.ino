int button = 16;

void setup()
{
	pinMode(button, INPUT);
	Serial.begin(9600);
}

void loop() {
	int button_state = digitalRead(button);

	if (button_state) {
		Serial.println("PRESSED !");
	}
}
