#include <iostream>
#include <thread>
#include <chrono>

#include "sdnova/spi.h"


int main(int argc, char** argv) {
  sdquadx::sensor::LegDatas legdatas;
  sdquadx::interface::LegCmds legcmds;
  std::cout << "Init spi dev!" << std::endl;
  if (!InitSpi("/dev/spidev2.0", "/dev/spidev2.1")) {
    std::cout << "Init failed!\n";
    return 1;
  }

  for (size_t i = 599'999; i < 600'000; i++) {
    // legcmds
    WriteInFrom(legcmds);
    RunSpi();
    ReadOutTo(legdatas);
    // legdatas
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  return 0;
}
