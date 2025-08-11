#include <IRremote.hpp>
#include <Arduino.h>

const int RECV_PIN = 2;

// Define a struct for button mapping
struct Button {
  uint64_t code;
  const char* name;
};

// List your buttons here
Button buttons[] = {
  {0xF906FF00, "Ok"},
  {0xF807FF00, "Right"},
  {0xE51AFF00,   "Up"},
  {0xB748FF00, "Down"},
  {0xB847FF00, "Left"},
  {0xB44BFF00, "vol_up"},
  {0xB04FFF00, "vol_down"},
  // Add or remove buttons easily here
};

const int numButtons = sizeof(buttons) / sizeof(buttons[0]);

void setup() {
  delay(2000);
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("IR Receiver started");
}

void loop() {
  if (IrReceiver.decode()) {
    uint64_t value = IrReceiver.decodedIRData.decodedRawData;

    if (value != 0 && value != 0xFFFFFFFF) {
      Serial.print("IR code: 0x");
      Serial.println((unsigned long)value, HEX);

      bool found = false;
      for (int i = 0; i < numButtons; i++) {
        if (value == buttons[i].code) {
          Serial.print("Button pressed: ");
          Serial.println(buttons[i].name);
          found = true;
          break;
        }
      }
      if (!found) {
        Serial.println("Unknown command");
      }
    }

    IrReceiver.resume();
  }
}

