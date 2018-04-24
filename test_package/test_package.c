#include <stdio.h>
#include <stdlib.h>
#include "dyad.h"

/* Connects to a daytime server and prints the response */

static void onConnect(dyad_Event *e) {
  printf("connected: %s\n", e->msg);
}

static void onError(dyad_Event *e) {
  printf("error: %s\n", e->msg);
  exit(EXIT_FAILURE);
}

static void onData(dyad_Event *e) {
  printf("%s", e->data);
}


int main(void) {
  dyad_Stream *s;
  dyad_init();

  s = dyad_newStream();
  dyad_addListener(s, DYAD_EVENT_CONNECT, onConnect, NULL);
  dyad_addListener(s, DYAD_EVENT_ERROR,   onError,   NULL);
  dyad_addListener(s, DYAD_EVENT_DATA,    onData,    NULL);
  dyad_connect(s, "time.is", 80);

  dyad_getStreamCount();
  dyad_update();
  dyad_shutdown();
  return EXIT_SUCCESS;
}
