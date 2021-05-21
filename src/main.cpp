#include <getopt.h>
#include <iostream>
#include <string>
#include <utility>
#include "simulation.hpp"
#include "global.hpp"


using namespace std;

int main(int argc, char **argv) {
  Simulation simulator(false);
  simulator.run();
  exit(EXIT_SUCCESS);
}
