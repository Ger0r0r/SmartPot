void work(WiFiServer * wifiServer){
  int status = 0;   // 0 - wait, 1 - heat, 2 - keep 
  int temp = 0;     // current tempreture
  int level = 0;    // current water level
  int ntemp = 0;    // needed tempeture

	WiFiClient client = wifiServer.available();
  char command[32] = {0};
  // "stop" - break heat, stay wait
  // "heat" - to hit water over MAXTEMP(default=90)
  // "info" - send information
  // "keep XX" - keep XX tempreture (heat if it needed)

  if (client) { // client is exist
    while (client.connected()) { // client is connected
      server_talk(client, command, status, temp, level, ntemp);
    }
    client.stop();
  }
}