#include "sd_card.h"

SDCard::SDCard(uint8_t cs_pin) noexcept {
  SD.begin(cs_pin);
}

void SDCard::raw_open_file(const String& filename, uint8_t mode) noexcept {
  if (!this->raw_file_is_opened()) {
    this->_file = SD.open(filename, mode);
    assert(this->_file && "error open file");
  }
}

void SDCard::raw_close_file() noexcept {
  if (this->raw_file_is_opened())
    this->_file.close();
}

void SDCard::read_file(const String& filename, String& buffer) noexcept {
  this->raw_open_file(filename, O_READ);

  buffer = String(this->_file.read());

  this->raw_close_file();
}

void SDCard::overwrite_file(const String& filename,
                            const String& data) noexcept {
  this->raw_close_file();
  SD.remove(filename);

  this->raw_open_file(filename, FILE_WRITE);
  this->_file.println(data);
  this->raw_close_file();
}

bool SDCard::raw_file_is_opened() noexcept {
  return this->_file;
}

File& SDCard::get_raw_file() noexcept {
  return this->_file;
}