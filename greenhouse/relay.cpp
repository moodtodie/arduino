#include "relay.hh"

void relayOn() {
  digitalWrite(RELAY_PIN, HIGH);
}

void relayOff() {
  digitalWrite(RELAY_PIN, LOW);
}
