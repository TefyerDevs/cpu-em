#include <iostream>
#include <chrono>
#include <thread>
#include "cpu.h"
#include "rom.h"

uint8_t second_wait = 1;

int main(){
    ROM rom("rom.bin");
    CPU cpu(&rom);
    while(cpu.getPointer() <= ROM_SIZE){

        cpu.process();

        cpu.addPointer(1);

        std::this_thread::sleep_for(std::chrono::seconds(second_wait));
    }
    return 0;
} 