#include "Client.h"
#include <Arduino.h>

Client::Client(int buzzer_pin, int sword_pin)
{
    m_buzzer_pin = buzzer_pin;
    m_sword_pin = sword_pin;

    pinMode(OUTPUT, m_buzzer_pin);
    pinMode(INPUT, m_sword_pin);
}

Client::~Client()
{

}

bool Client::is_connected_to_server()
{

}

void Client::connect_to_server(int port)
{

}

bool Client::is_sword_button_pressed()
{
    int state = digitalRead(m_sword_pin);

    return state == HIGH;
}

void Client::play_sound(int frequency, int duracy)
{
    tone(m_buzzer_pin, frequency, duracy);
}

int Client::recieve_data_from_server()
{

}

int Client::send_data_to_server(int data)
{

}