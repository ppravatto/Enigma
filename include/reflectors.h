#include <string>
#include <stdexcept>
#include <exception>

#include "utils.h"

#ifndef ENIGMA_REFLECTORS_H
#define ENIGMA_REFLECTORS_H

namespace enigma{

    class Reflector{

        private:
            std::string wiring;         // Internal wiring of the reflector
            
        public:
            Reflector(std::string);     // Class constructor
            ~Reflector();               // Class destructor

            char reflect(char);         // Function to encode the reflection of the incoming signals
    };


    // Reflector class constructor
    Reflector::Reflector(std::string _wiring){
        wiring = _wiring;
        if(wiring.length() != 26) throw std::runtime_error("The wiring string must have 26 characters");
        for(std::string::iterator it = wiring.begin(); it != wiring.end(); it++) check_char(*it);
    }

    // Reflector class destructor
    Reflector::~Reflector(){}

    // Function to encode the reflection of the incoming signals
    char Reflector::reflect(char letter){
        int index = to_index(letter);
        return wiring[index];
    }

}

#endif