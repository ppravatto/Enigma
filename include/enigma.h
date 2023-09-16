#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

#include "utils.h"
#include "rotors.h"
#include "reflectors.h"
#include "plugboard.h"

#ifndef ENIGMA_H
#define ENIGMA_H

namespace enigma{

    class Enigma{

        private:
            std::vector<Rotor> rotors;                          // Vector encoding the selected rotors in order
            Reflector reflector;                                // Selected Reflector
            Plugboard plugboard;                                // Plugboard configuration

        public:
            Enigma(std::vector<Rotor>, Reflector);              // Class constructor
            ~Enigma();                                          // Class destructor

            void set_positions(std::vector<char>);              // Function to set the starting position of the rotors
            void set_plugboard(std::vector<std::string>);       // Function to set the plugboard based on user selection
            char transform(char);                               // Perform the transformation of a character (no rotor movement)
            void rotate();                                      // Update the position of the rotors
            std::string encode(std::string);                    // Encode a given string using the current configuaration

    };

    // Class constructor
    Enigma::Enigma(std::vector<Rotor> _rotors, Reflector _reflector) : rotors(_rotors), reflector(_reflector) {}

    // Class destructor
    Enigma::~Enigma(){}

    // Function to set the starting position of the rotors
    void Enigma::set_positions(std::vector<char> positions){
        if(positions.size() != rotors.size()) throw std::runtime_error("The number of position must match the number of rotors");
        for(int i=0; i<positions.size(); i++) rotors[i].set_position(positions[i]);
    }

    // Function to set the plugboard based on user selection
    void Enigma::set_plugboard(std::vector<std::string> connections){
        plugboard.clear();
        plugboard.add(connections);
    }

    // Perform the transformation of a character (no rotor movement)
    char Enigma::transform(char letter){
        check_char(letter);
        char out = plugboard.swap(letter);
        for(int i = rotors.size()-1; i >= 0; i--) out = rotors[i].left_to_right(out);
        out = reflector.reflect(out);
        for(int i = 0; i < rotors.size(); i++) out = rotors[i].right_to_left(out);
        out = plugboard.swap(out);
        return out;
    }

    // Update the position of the rotors
    void Enigma::rotate(){
        for(int i = rotors.size()-1; i>=0; i--){
            bool notch_reached = rotors[i].is_notch();
            rotors[i].rotate();
            if(notch_reached == false) break;
        }
    }
    
    // Encode a given string using the current configuaration
    std::string Enigma::encode(std::string message){
        std::string output = "";
        for(std::string::iterator sit = message.begin(); sit != message.end(); sit++){
            rotate();
            char letter = transform(*sit);
            output += letter;
        }
        return output;
    }

}

#endif