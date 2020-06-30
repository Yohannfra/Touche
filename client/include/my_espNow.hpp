#ifndef ESPNOW_HPP
#define ESPNOW_HPP

esp_err_t setupEspNow();

esp_err_t sendMessage(const message_t *message);

#endif // ESPNOW_HPP
