#pragma once

#include <ArduinoJson.h>
#include "sd_card.h"

struct SettingsData
{
    SettingsData(DynamicJsonDocument doc) noexcept;
    DynamicJsonDocument get_dynamic_json_document() noexcept;

    // --- Data --- //

    uint32_t timeout_sleep;

    // --- Data --- //
};

struct SettingsManager
{
    SettingsManager(SDCard &storage, const String& filename_for_settings = "settings.json") noexcept : _storage(storage), _filename_for_settings(filename_for_settings) {};

    bool serialize(SettingsData data) noexcept;

    SettingsData deserialize(bool& status) noexcept;

private:
    SDCard &_storage;
    const String& _filename_for_settings;
};
