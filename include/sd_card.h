#pragma once

#include <SPI.h>
#include <SD.h>

struct SDCard
{
    SDCard(uint8_t cs_pin) : cs_pin(cs_pin) {
        SD.begin(this->cs_pin);
    };
    
    bool read_file(const String &filename, String& buffer);

    bool overwrite_file(const String &filename, const String &data);

    bool file_is_opened();

private:
    bool open_file(const String &filename, uint8_t mode=O_READ);

    File file;
    uint8_t cs_pin;
};
