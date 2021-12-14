#include "pipe_networking.h"
#include <unistd.h>
#include <ctype.h>

void processing(int to_client, int from_client) {
  char msg[100];
  read(from_client, msg, sizeof(msg));

  int i = 0;
  while (msg[i]) {
    msg[i] = toupper(msg[i]);
    i++;
  }

  write(to_client, msg, sizeof(msg));
  processing(to_client, from_client);
}

int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  processing(to_client, from_client);  
}
