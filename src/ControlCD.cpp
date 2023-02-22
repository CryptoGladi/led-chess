#include "ControlCD.h"
#include <SPI.h>
#include "Backlight.h"
#include "Configuration.h"

CCD::CCD(String name) {  //конструктор класса
  nameFile = name;
}

void CCD::initializingCDcard(uint8_t pin) {  //функция проверки cd карты на её наличие
  bool status_cd_begin = SD.begin(pin);
  bool status_cd_open = static_cast<bool>(SD.open(nameFile));

  bool status_cd = status_cd_begin && status_cd_open;

  if (status_cd)
  {
    SidematrixLed.setPixelColor(1, SidematrixLed.Color(0, 250, 0));  // указываем зелёный цвет для первого пикселя
    SidematrixLed.setPixelColor(2, SidematrixLed.Color(0, 0, 0));    // отключаем красный цвет для второрго пикселя 
  }
  else
  {
    SidematrixLed.setPixelColor(1, SidematrixLed.Color(0, 0, 0));  // отлючаем  зелёный цвет для первого пикселя
    SidematrixLed.setPixelColor(2, SidematrixLed.Color(250, 0, 0));    // указываем красный цвет для второго пикселя
  }
}

//по итогу выполнения этих двух функций в statusCD будет информация о существовании старой конфигурации доски