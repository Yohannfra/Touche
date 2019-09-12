#ifndef CLIENT_H
#define CLIENT_H

class Client
{
    public:
        int m_buzzer_pin;
        int m_sword_pin;
        int m_server_port;

        Client(int buzzer_pin, int sword_pin);
        ~Client();

        // Check if the connection to the server is still up
        bool is_connected_to_server(void);

        // init the connection to the server
        void connect_to_server(int port);

        // Check if the button of the sword is pressed
        bool sword_button_pressed();

        // play a sound through the buzzer
        void play_sound(int frequency, int duracy);

        // read data send by the server
        int recieve_data_from_server();

        // send data to server
        int send_data_to_server(int data);
};

#endif
