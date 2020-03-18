/*
** Assouline Yohann, 2020
** WSFF
** sketch_client
*/

const int BUTTON_PIN = 12;
const int LED_PIN = 14;

void setup()
{
    pinMode(BUTTON_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    Serial.begin(9600);
    Serial.println("Booting !");
}

void loop()
{
    int button_state = digitalRead(BUTTON_PIN);
    if (button_state) {
        digitalWrite(LED_PIN, HIGH);
    }
    digitalWrite(LED_PIN, LOW);
}
