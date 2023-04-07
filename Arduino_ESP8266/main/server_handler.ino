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
  // "info" - send information
  // "stop" - break heat, stay wait
  // "heat" - to hit water over MAXTEMP(default=90)
  // "keep XX" - keep XX tempreture (heat if it needed)
  if (command == "info"){ // send information
    client.print("tempreture ");
    client.println(temp);
    client.print("water "); 
    client.println(level);
    client.print("status ");
    client.println(status);
    client.print("aim ");
    client.println(ntemp);
  }
  if (command == "stop"){
    status = 0;
    client.println("ok");
  }
  if (command == "heat"){
    if (status == 1){
      client.println("already");
    }
    if ((status == 0) || (status == 2)){
      status = 1;
      client.pritnln("ok");
    }
  }
  if (){
    
  }
}