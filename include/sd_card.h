#pragma once

#include <SD.h>
#include <SPI.h>

struct SDCard {
  /// @brief Инцилизация
  /// @param cs_pin Пин для работы с sd картой
  explicit SDCard(uint8_t cs_pin) noexcept;

  /// @brief Прочитать файл
  /// @param filename Имя файла
  /// @param buffer Куда сохранить текст из файла
  /// @warning Автомотически открывает файл и закрывает его
  void read_file(const String& filename, String& buffer) noexcept;

  /// @brief Переписать файл
  /// @param filename Имя файла
  /// @param data Информацию которую нужно записать в файл
  /// @return true - если успешно
  /// @warning Автомотически открывает файл и закрывает его
  void overwrite_file(const String& filename, const String& data) noexcept;

  /// @brief Файл открыт?
  /// @warning Лучше использовать эти методы overwrite_file и read_file
  bool raw_file_is_opened() noexcept;

  /// @brief Открыть файл
  /// @param filename Имя файла
  /// @param mode Его режим (чтение или запись)
  /// @return true - если успешно
  /// @warning Лучше использовать эти методы overwrite_file и read_file
  void raw_open_file(const String& filename, uint8_t mode = O_READ) noexcept;

  /// @brief Закрыть файл
  /// @return true - если успешно
  /// @warning Лучше использовать эти методы overwrite_file и read_file
  void raw_close_file() noexcept;

  /// @brief Получить ссылку на File
  /// @warning Лучше использовать эти методы overwrite_file и read_file
  File& get_raw_file() noexcept;

 private:
  File _file;
};
