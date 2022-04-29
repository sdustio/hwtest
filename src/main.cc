#include <chrono>
#include <iostream>
#include <thread>

#include "sdnova/spi.h"

int main(int argc, char** argv) {
  sdquadx::sensor::LegDatas legdatas;
  sdquadx::interface::LegCmds legcmds;

  // legcmds
  for (auto& cmd : legcmds) {
    cmd.kp = {1, 1, 1};
    cmd.kd = {1, 1, 1};
    cmd.q_des = {0.1, 0.1, 0.1};
    cmd.qd_des = {0, 0, 0};
    cmd.tau = {0, 0, 0};
  }

  std::cout << "Init spi dev!" << std::endl;
  if (!InitSpi("/dev/spidev2.0", "/dev/spidev2.1")) {
    std::cout << "Init failed!\n";
    return 1;
  }

  for (size_t i = 599'999; i < 600'000; i++) {
    WriteInFrom(legcmds);
    if (!RunSpi()) {
      std::cout << "Communication error\n";
      break;
    }

    ReadOutTo(legdatas);
    // legdatas
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  return 0;
}
