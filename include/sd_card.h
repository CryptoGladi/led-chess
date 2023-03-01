#pragma once

#include <SPI.h>
#include <SD.h>

struct SDCard
{
    SDCard(uint8_t cs_pin) noexcept : cs_pin(cs_pin) {
        SD.begin(this->cs_pin);
    };
    
    bool read_file(const String &filename, String& buffer) noexcept;

    bool overwrite_file(const String &filename, const String &data) noexcept;

    bool file_is_opened() noexcept;

private:
    bool open_file(const String &filename, uint8_t mode=O_READ) noexcept;

    File file;
    uint8_t cs_pin;
};
