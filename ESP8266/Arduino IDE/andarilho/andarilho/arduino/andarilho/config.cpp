#include "config.h"

bool cabec(Stream &port) {
  port.println();
  port.println("   ___   _  _____  ___   ___  ______   __ ______ ");
  port.println("  / _ | / |/ / _ \\/ _ | / _ \\/  _/ /  / // / __ \\");
  port.println(" / __ |/    / // / __ |/ , _// // /__/ _  / /_/ /");
  port.println("/_/ |_/_/|_/____/_/ |_/_/|_/___/____/_//_/\\____/ ");
  port.println(" Engenharia de Computação - Sistemas Embarcados  ");
  port.println();
  return true;
}

JSONVar createActions(Source source, String payload) {
  JSONVar actions = JSON.parse(payload);
  if (JSON.typeof(actions) != "undefined") {
    Serial.print(source == MQTT ? "action MQTT -> " : "action BT -> ");
    Serial.print(actions["speed"]);
    Serial.print(" - ");
    Serial.println(actions["action"]);
  } else {
    Serial.println(payload);
  }
  return actions;
}
