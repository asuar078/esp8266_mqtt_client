#ifndef FLOOR_LEDS_HPP
#define  FLOOR_LEDS_HPP

#include <Arduino.h>

#define ESP_FLOOR_1
// #define ESP_FLOOR_2
// #define ESP_FLOOR_3
// #define ESP_FLOOR_4
// #define ESP_FLOOR_5
// #define ESP_FLOOR_6
// #define ESP_FLOOR_7
// #define ESP_FLOOR_8

// A struct to represent a
class RoomLed {
public:
  String roomNum;
  const int ledNum;

  RoomLed(String p_roomNum, const int p_ledNum)
    : roomNum(p_roomNum), ledNum(p_ledNum) {}

  void begin() {
    pinMode(ledNum, OUTPUT);
    digitalWrite(ledNum, LOW);
  }

  void on() {
    digitalWrite(ledNum, HIGH);
  }

  void off() {
    digitalWrite(ledNum, LOW);
  }
};

// All gpio safe to use for LED
const int ledGPIO16 = 16; // D0
const int ledGPIO5 = 5;   // D1
const int ledGPIO4 = 4;   // D2
const int ledGPIO0 = 0;   // D3
const int ledGPIO2 = 2;   // D4
const int ledGPIO14 = 14; // D5
const int ledGPIO12 = 12; // D6
const int ledGPIO13 = 13; // D7
const int ledGPIO15 = 15; // D8

#if defined(ESP_FLOOR_1)
RoomLed roomGround{static_cast<String>("ground"), D0};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 1;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &roomGround
};
#elif defined(ESP_FLOOR_2)
RoomLed room201{static_cast<String>("201"), D0};
RoomLed room202{static_cast<String>("202"), D1};
RoomLed room203{static_cast<String>("203"), D2};
RoomLed roomFitness{static_cast<String>("fitness"), D3};
RoomLed roomLobby{static_cast<String>("lobby"), D4};
RoomLed roomGround{static_cast<String>("ground"), D5};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 6;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room201, &room202, &room203, &roomFitness, &roomLobby, &roomGround
};

#elif defined(ESP_FLOOR_3)
RoomLed room301{static_cast<String>("301"), D0};
RoomLed room302{static_cast<String>("302"), D1};
RoomLed room303{static_cast<String>("303"), D2};
RoomLed room304{static_cast<String>("304"), D3};
RoomLed room305{static_cast<String>("305"), D4};
RoomLed room306{static_cast<String>("306"), D5};
RoomLed room307{static_cast<String>("307"), D6};
RoomLed room308{static_cast<String>("308"), D7};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 8;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room301, &room302, &room303, &room304, &room305, &room306, &room307, &room308
};
#elif defined(ESP_FLOOR_4)
RoomLed room401{static_cast<String>("401"), D0};
RoomLed room402{static_cast<String>("402"), D1};
RoomLed room403{static_cast<String>("403"), D2};
RoomLed room404{static_cast<String>("404"), D3};
RoomLed room405{static_cast<String>("405"), D4};
RoomLed room406{static_cast<String>("406"), D5};
RoomLed room407{static_cast<String>("407"), D6};
RoomLed room408{static_cast<String>("408"), D7};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 8;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room401, &room402, &room403, &room404, &room405, &room406, &room407, &room408
};
#elif defined(ESP_FLOOR_5)
RoomLed room501{static_cast<String>("501"), D0};
RoomLed room502{static_cast<String>("502"), D1};
RoomLed room503{static_cast<String>("503"), D2};
RoomLed room504{static_cast<String>("504"), D3};
RoomLed room505{static_cast<String>("505"), D4};
RoomLed room506{static_cast<String>("506"), D5};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 6;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room501, &room502, &room503, &room504, &room505, &room506
};
#elif defined(ESP_FLOOR_6)
RoomLed room601{static_cast<String>("601"), D0};
RoomLed room602{static_cast<String>("602"), D1};
RoomLed room603{static_cast<String>("603"), D2};
RoomLed room604{static_cast<String>("604"), D3};
RoomLed room605{static_cast<String>("605"), D4};
RoomLed room606{static_cast<String>("606"), D5};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 6;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room601, &room602, &room603, &room604, &room605, &room606
};
#elif defined(ESP_FLOOR_7)
RoomLed room701{static_cast<String>("701"), D0};
RoomLed room702{static_cast<String>("702"), D1};
RoomLed room703{static_cast<String>("703"), D2};
RoomLed room704{static_cast<String>("704"), D3};
RoomLed room705{static_cast<String>("705"), D4};
RoomLed room706{static_cast<String>("706"), D5};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 6;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room701, &room702, &room703, &room704, &room705, &room706
};
#elif defined(ESP_FLOOR_8)
RoomLed room801{static_cast<String>("pha"), D0};
RoomLed room802{static_cast<String>("phb"), D1};
RoomLed room803{static_cast<String>("phc"), D2};
RoomLed room804{static_cast<String>("phd"), D3};

const size_t NUMBER_OF_ROOMS_ON_FLOOR = 4;
std::array<RoomLed*, NUMBER_OF_ROOMS_ON_FLOOR> floorLeds {
  &room801, &room802, &room803, &room804
};
#endif

#endif
