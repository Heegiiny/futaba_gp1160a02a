#include <iostream>
#include <cstring>
#include <math.h>
#include "display.h"

Display::Display()
{
}

Display::clear()
{
    Serial.write("\x1b\x5b\x32\x4a");
}

// Команда входа в графический режим
const char *gfx_code = "\x1b\x5c\x3f\x4c\x47";

//Добавляет ANSII-код числа и ';' к строке
void concat_ansii_num(char *str, uint16_t num, bool semicolon = true)
{
    char *num_buffer = new char[3];
    itoa(num, num_buffer, 10);
    std::copy(num_buffer, num_buffer + strlen(num_buffer), str + strlen(str));
    if (semicolon)
    {
        str[strlen(str)] = ';';
    }
}
const uint8_t PREFIX_MAX_SIZE = 20;
Display::sendGraphics(uint16_t x, uint8_t y, uint8_t h, uint16_t w, const char *data)
{
    //char *message = new char[strlen(gfx_code) + (w * h / 8) + 1];
    // Префикс = команда входа + размер сообщения
    char *msg_prefix = new char[PREFIX_MAX_SIZE];
    memset(msg_prefix, 0, PREFIX_MAX_SIZE);
    std::copy(gfx_code, gfx_code + strlen(gfx_code), msg_prefix);

    concat_ansii_num(msg_prefix, x);
    concat_ansii_num(msg_prefix, y);
    concat_ansii_num(msg_prefix, h);
    concat_ansii_num(msg_prefix, w);

    std::cout << "Prefix: " << msg_prefix
              << "\n";

    //const uint16_t data_size = (w * h / 8);
    const uint8_t rows_in_bytes = (uint16_t)ceil(abs(w) / BYTE_SIZE);
    const uint16_t data_size = rows_in_bytes * abs(h);
    const uint8_t prefix_size = strlen(msg_prefix);
    const uint16_t message_size = prefix_size + data_size + 1;

    std::cout << "message_size: " << message_size
              << "\n";

    char *message = new char[message_size];
    memset(message, 0, message_size);
    std::copy(msg_prefix, msg_prefix + prefix_size, message);
    std::copy(data, data + data_size, message + prefix_size);
    //message = (char *)malloc(strlen(gfx_code) + (w * h / 8) + 1);
    //strcpy(message, gfx_code);
    //strcat(message, data);
    Serial.write(message, message_size);

    //Serial.write("\rq");

    std::cout << message
              << "\n";
}

// Команда установки режима текста
const char *screen_mode_code = "\x1b\x5c\x3f\x4c\x53";
Display::setScreenMode(uint8_t mode)
{
    char *code_buffer = new char[10];
    memset(code_buffer, 0, 10);
    std::copy(screen_mode_code, screen_mode_code + strlen(screen_mode_code), code_buffer);
    concat_ansii_num(code_buffer, mode, false);
    //itoa(mode, code_buffer + strlen(screen_mode_code), 10);
    std::cout << "code_buffer: " << code_buffer
              << "\n";
    Serial.write(code_buffer, strlen(code_buffer));
}

// Команда установки курсора
const char *set_cursor_code = "\x1b\x5b";
Display::setCursor(uint16_t x, uint8_t y)
{
    char *code_buffer = new char[10];
    memset(code_buffer, 0, 10);
    std::copy(set_cursor_code, set_cursor_code + strlen(set_cursor_code), code_buffer);
    concat_ansii_num(code_buffer, y);
    concat_ansii_num(code_buffer, x, false);
    code_buffer[strlen(code_buffer)] = 'H';
    std::cout << "code_buffer: " << code_buffer
              << "\n";
    Serial.write(code_buffer, strlen(code_buffer));
}

Display display;
