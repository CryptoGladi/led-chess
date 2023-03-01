#include "settings.h"

SettingsData::SettingsData(DynamicJsonDocument doc) noexcept {
    this->timeout_sleep = doc["timeout_sleep"];
}

DynamicJsonDocument SettingsData::get_dynamic_json_document() noexcept {
    DynamicJsonDocument doc(1024);

    doc["timeout_sleep"] = this->timeout_sleep;

    return doc;
}

bool SettingsManager::serialize(SettingsData data) noexcept {
    auto doc = data.get_dynamic_json_document();
    
    //serializeJson(doc, Serial);
}