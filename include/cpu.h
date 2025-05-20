#pragma once

#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <cctype>
#include "rom.h"
#include "registers.h"

std::string toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::toupper(c); });
    return result;
}

std::map<std::string, std::string> commands_hex = {
    { "5F", "add" },
    { "5A", "sub" },
    { "43", "jmp" },
    { "A2", "ret" },
    { "58", "mov" },
    { "F2", "int" },
    { "F4", "hlt" },
    { "4C", "syscall"}
};


int hex_to_int(std::string hex){
    unsigned int x;   
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> x;
    return x;
}


bool isCommand(std::string hex){
    return commands_hex.find(toUpperCase(hex)) != commands_hex.end();
}  

std::string getCommand(std::string hex){
    return commands_hex.at(toUpperCase(hex));
}


template< typename T >
std::string int_to_hex( T i )
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)*2) 
         << std::hex << i;
  return stream.str();
}

void cpu_exit(int code){
    std::cout<< "cpu exit with code: " << code << std::endl;
    exit(0);
}

#define RAM_SIZE 64


class CPU {
public:
    CPU(ROM* rom){
        this->rom = rom;
    }
    
    void process(){
        std::string hex = rom->get(getPointer());
        if(isCommand(hex)){
            if(getCommand(hex) == "mov" ){
                int register_val = hex_to_int(rom->get(getPointer()+1));
                int value = hex_to_int(rom->get(getPointer()+2));
                
                if(register_val == 0x2F){
                    std::cout<< "moved: " << value << " to: " 
                    << "rax" << std::endl;
                }else if(register_val == 0x1F){
                    std::cout<< "moved: " << value << " to: " 
                    << "rdi" << std::endl;
                }else if(register_val == 0x3F){
                    std::cout<< "moved: " << value << " to: " 
                    << "rbp" << std::endl;
                }else{
                    std::cout<< "moved: " << value << " to: " 
                    << int_to_hex(register_val) << std::endl;
                }
                addPointer(2);

                return;
            }else if(getCommand(hex) == "syscall"){
                if(storage[0x1F] == hex_to_int("0x3C")){
                    cpu_exit(storage[0x2F]);
                }
            }else if(getCommand(hex) == "jmp"){
                int address = hex_to_int(rom->get(getPointer()+1));
                setPointer(address-1);
            }else {
            std::cout<< "processed command: " << getCommand(hex) << 
            "| with hex: " << hex << " | at address: " << int_to_hex(pointer) << std::endl;
            }
        }else{
            std::cout << "processed hex: " << hex << " | at address: " << int_to_hex(pointer) << std::endl;
        }

    }

    void setPointer(int i){
        this->pointer = i;
    }

    void addPointer(int i){
        setPointer(getPointer()+i);
    }

    int getPointer(){
        return this->pointer;
    }


    int pointer = 0;


    ROM* rom;
};