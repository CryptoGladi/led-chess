#include "sd_card.h"

SDCard::SDCard(uint8_t cs_pin) noexcept {
  SD.begin(cs_pin);
}

bool SDCard::raw_open_file(const String& filename, uint8_t mode) noexcept {
  this->_file = SD.open(filename, mode);
  return this->file_is_opened();
}

bool SDCard::raw_close_file() noexcept {
  if (!this->file_is_opened())
    return false;

  this->_file.close();
  return true;
}

bool SDCard::read_file(const String& filename, String& buffer) noexcept {
  if (!this->raw_open_file(filename, O_READ))
    return false;

  if (!this->file_is_opened())
    return false;

  buffer = String(this->_file.read());
  this->_file.close();
  return true;
}

bool SDCard::overwrite_file(const String& filename,
                            const String& data) noexcept {
  SD.remove(filename);

  if (!this->raw_open_file(filename, O_WRITE))
    return false;

  this->_file.println(data);
  this->_file.close();
  return true;
}

bool SDCard::file_is_opened() noexcept {
  return (this->_file && this->_file.available());
}

File& SDCard::get_raw_file() noexcept {
  return this->_file;
}