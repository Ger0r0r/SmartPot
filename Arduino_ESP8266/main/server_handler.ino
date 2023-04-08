void server_talk(WiFiClient * client, char * command, int * status, int * temp, int * level, int * ntemp){
	while (client.available() > 0) { // client send something
    server_read(client, command);
    server_parcer(client, command, status, temp, level, ntemp);
  }
}

void server_read(WiFiClient * client, char * command){
	int i = 0;
    char c = client.read(); // read byte of message
    while (c != -1){ // read
      command[i] = c;
      i++;
      c = client.read();
    } // read complete
}

void server_parcer(WiFiClient * client, char * command, int * status, int * temp, int * level, int * ntemp){

  char first[4] = command.substring(0,3);
  // RECIEVE
  // "info" - send information
  // "stop" - break heat, stay wait
  // "heat" - to hit water over MAX_HEAT_TEMP(default=90)
  // "keep XX" - keep XX tempreture (heat if it needed)

  // SEND
  // *all information* - by recieving "info"
  // "ok" - if task is accepted
  // "done" - if task is done
  // "Not enouth water" - water level is too low
  // "Too much water" - water level is too high
  // "already" - if current task is the same as recieved task
  if (first == "info"){ // send information
    client.print("tempreture ");
    client.println(temp);
    client.print("water "); 
    client.println(level);
    client.print("status ");
    client.println(status);
    client.print("aim ");
    client.println(ntemp);
  }
  if (first == "stop"){
    status = 0;
    client.println("ok");
    client.println("done");
  }
  if (first == "heat"){
    if (status == 1){
      client.println("already");
    }
    if ((status == 0) || (status == 2)){
      if (temp <= MAX_HEAT_TEMP){
        if ((level >= WATER_LOW_BORDER) && (level <= WATER_HIGH_BORDER)){
          status = 1;
          client.pritnln("ok");
        } else {
          if (level < WATER_LOW_BORDER){
            client.println("Not enouth water");
          } else {
            client.println("Too much water");
          }
        }
      } else {
        client.println("done")
      }
    }
  }
  if (){
    
  }
}