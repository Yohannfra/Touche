#ifndef SERVER_H
#define SERVER_H

class Server
{
    public:
        int m_buzzer_pin;
        int m_led_pin;
        int m_client_port[2];

        Server(int buzzer_pin, int led_pin, int client_port_1, int client_port_2);
        ~Server();

        //  Check if the connection to a client is still up
        bool is_connected_to_client(int client_id);

        // read data send by the client
        int recieve_data_from_client(int client_id);

        // send data to client
        int send_data_to_client(int client_id, int data);

        // play a sound through the buzzer
        void play_sound(int frequency, int duracy);

        // turn on the led panel for a certain duracy
        //  color : g -> green
        //          r -> red
        void turn_on_led_panel(int duracy, char color);
};

#endif
