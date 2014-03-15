#include "ulog.hh"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  ulog::ulog<> logger;

  logger.log(1, "hi");

  return 0;
}
