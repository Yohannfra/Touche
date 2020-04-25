#ifndef ESPNOW_HPP
#define ESPNOW_HPP

esp_err_t setup_esp_now();

void send_message(const message_t *message);

#endif // ESPNOW_HPP
