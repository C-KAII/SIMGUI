// main.cpp
#include "App.h"

int main(int argc, char* argv[]) {
  App app;

  if (app.init()) {
    app.run();
  }

  return 0;
}