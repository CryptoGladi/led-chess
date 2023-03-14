#include "sd_card.h"

SDCard::SDCard(SdCsPin_t cs_pin) noexcept {
  assert(this->_sd.begin(cs_pin));
}

void SDCard::raw_open_file(const String& filename, oflag_t mode) noexcept {
  if (!this->raw_file_is_opened()) {
    this->_file = _sd.open(filename, mode);
    assert(this->_file);
  }
}

void SDCard::raw_close_file() noexcept {
  if (this->raw_file_is_opened())
    assert(this->_file.close());
}

void SDCard::read_file(const String& filename, String& buffer) noexcept {
  if (!this->raw_file_is_opened())
    this->raw_open_file(filename);

  
  for (;;) {
    auto result = this->_file.read();

    if (result == -1) {
      break;
    }

    buffer += String(static_cast<char>(result));
  }

  buffer.trim();
  this->raw_close_file();
}

void SDCard::overwrite_file(const String& filename,
                            const String& data) noexcept {
  this->raw_close_file();
  this->_sd.remove(filename);

  this->raw_open_file(filename);
  this->_file.print(data);
  this->raw_close_file();
}

bool SDCard::raw_file_is_opened() noexcept {
  return this->_file;
}

File32& SDCard::get_raw_file() noexcept {
  return this->_file;
}