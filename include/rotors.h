#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

#include "utils.h"

#ifndef ENIGMA_ROTORS_H
#define ENIGMA_ROTORS_H

namespace enigma{

    class Rotor{

        private:
            int position;                           // Current position of the rotor
            std::string wiring;                     // Internal wiring of the rotor
            std::vector<char> notches;              // Vector encoding the position of the notches turning the next rotor
            
        public:
            Rotor(std::string, std::vector<char>);  // Class constructor
            ~Rotor();                               // Class destructor
            
            void set_position(char);                // Function to set the starting position of the rotor
            void rotate();                          // Function to advance the rotor by one step
            bool is_notch();                        // Function to check if the notch has been reached
            char left_to_right(char);               // Function encoding a left to right pass taking into account rotor position
            char right_to_left(char);               // Function encoding a right to left pass taking into account rotor position

    };

    // Rotor class constructor
    Rotor::Rotor(std::string _wiring, std::vector<char> _notches){

        notches = _notches;
        for(std::vector<char>::iterator it = notches.begin(); it != notches.end(); it++) check_char(*it);
        
        wiring = _wiring;
        if(wiring.length() != 26) throw std::runtime_error("The wiring string must have 26 characters");
        for(std::string::iterator it = wiring.begin(); it != wiring.end(); it++) check_char(*it);

        position = 0;
    }

    // Rotor class destructor
    Rotor::~Rotor(){}

    // Function to set the position of the rotor
    void Rotor::set_position(char start){
        position = to_index(start);
    }

    // Function advancing the rotor by one step
    void Rotor::rotate(){
        position++;
        if(position >= 26) position = 0;
    }

    // Function to check if a notch has been reached
    bool Rotor::is_notch(){
        for(std::vector<char>::iterator it = notches.begin(); it != notches.end(); it++){
            if(to_char(position) == *it) return true;
        }
        return false;
    }

    // Function encoding a left to right pass taking into account rotor position
    char Rotor::left_to_right(char letter){
        int index = to_index(letter) + position;                // Compue the entry point based on letter and position of the rotor
        index = adjust_index(index);                            // Adjust the index to fit within the valid char range
        char new_letter = wiring[index];                        // Compute the output letter based on rotor wiring
        int new_index = to_index(new_letter) - position;        // Shift the letters to adjust for the rotor position
        new_index = adjust_index(new_index);                    // Adjust the index to fit within the valid char range
        return to_char(new_index);                              // Convert the index in char format
    }

    // Function encoding a right to left pass taking into account rotor position
    char Rotor::right_to_left(char letter){
        int index = to_index(letter) + position;                // Compue the entry point based on letter and position of the rotor
        index = adjust_index(index);                            // Adjust the index to fit within the valid char range
        char new_letter = to_char(index);                       // Compute the input letter based on rotor position
        int new_index = wiring.find(new_letter) - position;         // Compute the output index based on wiring and rotor position
        new_index = adjust_index(new_index);                    // Adjust the index to fit within the valid char range
        return to_char(new_index);                              // Convert the index in char format   
    }

}

#endif