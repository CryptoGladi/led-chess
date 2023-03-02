#pragma once

#include <ArduinoJson.h>
#include "sd_card.h"

static constexpr int SETTINGS_MAX_MEMORY_ALLOCATION = 1024;
#define SETTINGS_FILE_NAME "settings.json"

struct SettingsData {
  SettingsData(DynamicJsonDocument doc) noexcept;

  SettingsData() noexcept = default;

  DynamicJsonDocument get_dynamic_json_document() noexcept;

  // --- Информация --- //
  // ВНИМАНИЕ! ЕСЛИ ВЫ ИЗМЕНИЛИ ЭТОТ БЛОК КОДА, ТО
  // ВАМ НУЖНО ИЗМЕНИТЬ ЭТИ МЕТОДЫ:
  // 1) SettingsManager::serialize
  // 2) SettingsManager::deserialize

  uint32_t timeout_sleep;
  String ssid_wifi;
  String raw_password;

  // --- Информация --- //
};

struct SettingsManager {
  SettingsManager(
      SDCard& storage,
      const String& filename_for_settings = "settings.json") noexcept
      : _storage(storage), _filename_for_settings(filename_for_settings){};

  bool serialize(SettingsData data) noexcept;

  SettingsData deserialize(bool& status) noexcept;

 private:
  SDCard& _storage;
  const String& _filename_for_settings;
};
