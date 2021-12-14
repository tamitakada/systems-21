#include "pipe_networking.h"
#include <unistd.h>
#include <ctype.h>

void processing(int to_client, int from_client) {
  char msg[100];
  int n = read(from_client, msg, sizeof(msg));
  if (n) {
    int i = 0;
    while (msg[i]) {
      msg[i] = toupper(msg[i]);
      i++;
    }

    write(to_client, msg, sizeof(msg));
    processing(to_client, from_client);
  }
}

void handshake_loop() {
    int to_client;
    int from_client;

    from_client = server_handshake( &to_client );

    processing(to_client, from_client);
    handshake_loop();
}

int main() {
  handshake_loop();
}
