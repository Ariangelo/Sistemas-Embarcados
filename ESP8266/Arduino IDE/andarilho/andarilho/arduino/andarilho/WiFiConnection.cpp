#include "config.h"

Ticker ticker;

void tick() {
  //toggle state
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));     // set pin to the opposite state
}

void configuracaoCallback(WiFiManager *gerenciadorWiFi) {
  Serial.println("Modo de configuração ativado");
  Serial.println(WiFi.softAPIP());
  Serial.println(gerenciadorWiFi->getConfigPortalSSID());
  //Modo de configuracao ativado led pisca rapido
  ticker.attach(0.2, tick);
}

bool wifiConnect() {
  // Forca o modo para STA+AP
  WiFi.mode(WIFI_STA);
  //WiFiManager
  //Depois de configurado a primeira vez o acesso ao WiFi e automatico
  WiFiManager gerenciadorWiFi;

  // set dark theme
  gerenciadorWiFi.setClass("invert");
  gerenciadorWiFi.setConfigPortalTimeout(30); // auto close configportal after n seconds
  gerenciadorWiFi.setAPClientCheck(true); // avoid timeout if client connected to softap
  gerenciadorWiFi.setBreakAfterConfig(true);   // always exit configportal even if wifi save fails

  //No caso de revogar o acesso ao WiFi
  //gerenciadorWiFi.resetSettings();
  gerenciadorWiFi.setDebugOutput(false);
  gerenciadorWiFi.setAPCallback(configuracaoCallback);

  if (!gerenciadorWiFi.autoConnect("AutoConnectAP")) {
    Serial.println("Falha na conexão com a WiFi");
    //reseta o ESP e tenta novamente
    //ESP.restart();
    delay(1000);
  } else {
    // Mostra IP do servidor
    Serial.println();
    Serial.println("WiFi conectado.");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
    Serial.println("Use este endereço para conectar ao dispositivo");
    Serial.println();
    ticker.attach(2.0, tick);
  }
  return WiFi.status() == WL_CONNECTED;
}
