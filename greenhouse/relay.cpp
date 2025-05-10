#include "relay.hh"

bool isOn = false;

bool isActive() {
  return isOn;
}

void relayOn() {
  isOn = true;
  digitalWrite(RELAY_PIN, HIGH);
}

void relayOff() {
  isOn = false;
  digitalWrite(RELAY_PIN, LOW);
}
