#include "Server.h"
#include <Arduino.h>

Server::Server(int buzzer_pin, int led_pin, int client_port_1, int client_port_2)
{
    m_buzzer_pin = buzzer_pin;
    m_led_pin = led_pin;
    m_client_port[0] = client_port_1;
    m_client_port[1] = client_port_2;

    pinMode(OUTPUT, m_buzzer_pin);
    pinMode(OUTPUT, m_led_pin);
}

Server::~Server()
{

}

bool Server::is_connected_to_client(int client_id)
{

}

int Server::recieve_data_from_client(int client_id)
{

}

int Server::send_data_to_client(int client_id, int data)
{

}

void Server::play_sound(int frequency, int duracy)
{
    /* Limitations about tone

    - You can’t use tone() while also using analogWrite() on pins 3 or 11.
    - You cannot generate a tone lower than 31 HZ.
    - The tone() function cannot be used by two separate pins at the same time.
    */

    tone(m_buzzer_pin, frequency, duracy);
}

void Server::turn_on_led_panel(int duracy, char color)
{

}
