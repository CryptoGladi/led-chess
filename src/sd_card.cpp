#include "sd_card.h"

bool SDCard::open_file(const String &filename, uint8_t mode) {
    this->file = SD.open(filename, mode);
    return this->file_is_opened();
}

bool SDCard::read_file(const String &filename, String &buffer) {
    if (!this->open_file(filename, O_READ))
        return false;

    if (!this->file_is_opened())
        return false;

    buffer = String(this->file.read());
    return true;
}

bool SDCard::overwrite_file(const String &filename, const String &data) {
    if (!SD.remove(filename)) 
        return false;

    if (!this->open_file(filename, O_WRITE))
        return false;

    this->file.println(data);
    return true;   
}

bool SDCard::file_is_opened() {
    return (this->file && this->file.available());
}