#pragma once

#include <SD.h>
#include <SPI.h>

struct SDCard {
  explicit SDCard(uint8_t cs_pin) noexcept;

  bool read_file(const String& filename, String& buffer) noexcept;

  bool overwrite_file(const String& filename, const String& data) noexcept;

  bool file_is_opened() noexcept;

  bool raw_open_file(const String& filename, uint8_t mode = O_READ) noexcept;

  bool raw_close_file() noexcept;

  File& get_raw_file() noexcept;

 private:
  File _file;
};
