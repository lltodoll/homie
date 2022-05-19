#include <Homie.h>

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t RX   = 3;
static const uint8_t TX   = 1;


#define firmwareVersion "1.0.0"

static const uint8_t PIN_RELAY = D0;

HomieNode lightNode("light", "Light", "switch");

bool lightOnHandler(const HomieRange& range, const String& value) {
  if (value != "true" && value != "false") return false;

    bool on = (value == "true");
    digitalWrite(PIN_RELAY, on ? HIGH : LOW);
    lightNode.setProperty("on").send(value);
    Homie.getLogger() << "Light is " << (on ? "on" : "off") << endl;

    return true;
}

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;

  pinMode(PIN_RELAY, OUTPUT);
  digitalWrite(PIN_RELAY, LOW);

  Homie_setFirmware("awesome-relay", firmwareVersion);

  lightNode.advertise("on").setName("On").setDatatype("boolean").settable(lightOnHandler);

  Homie.setup();
}

void loop() {
  Homie.loop();
}