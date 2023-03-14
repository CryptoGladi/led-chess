#pragma once

#include <ArduinoJson.h>
#include "sd_card.h"

/// @brief Сколько можно потрать памяти на аллокацию
static constexpr int SETTINGS_MAX_MEMORY_ALLOCATION = 1024;
#define SETTINGS_FILENAME "settings.json"

struct SettingsData {
  SettingsData(DynamicJsonDocument doc) noexcept;

  SettingsData() noexcept = default;

  DynamicJsonDocument get_dynamic_json_document() noexcept;

  // --- Информация --- //
  // ВНИМАНИЕ! ЕСЛИ ВЫ ИЗМЕНИЛИ ЭТОТ БЛОК КОДА, ТО
  // ВАМ НУЖНО ИЗМЕНИТЬ ЭТИ МЕТОДЫ:
  // 1) SettingsManager::serialize
  // 2) SettingsManager::deserialize

  /// @brief Время на переход в спящий режим
  uint32_t timeout_sleep;

  /// @brief Название точки доступа для подключение
  String ssid_wifi;

  /// @brief Пароль от точки доступа
  /// @warning Он в сыром виде!
  String raw_password;

  // --- Информация --- //
};

struct SettingsManager {
  /// @brief Инцилизация настроек
  /// @param storage Куда сохранять наши настройки
  /// @param filename_for_settings Имя файла где будут храниться настройки
  SettingsManager(
      SDCard& storage) noexcept
      : _storage(storage){};

  /// @brief Сохранить настройки
  /// @param data Наши новые настройки
  void serialize(SettingsData data) noexcept;

  /// @brief Загрузить настройки
  /// @return Настройки
  SettingsData deserialize() noexcept;

 private:
  SDCard& _storage;
};
