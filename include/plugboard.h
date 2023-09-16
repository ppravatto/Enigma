#include <vector>
#include <string>
#include <stdexcept>
#include <exception>

#include "utils.h"

#ifndef ENIGMA_PLUGBOARD_H
#define ENIGMA_PLUGBOARD_H

namespace enigma{

    class Plugboard{

        private:
            std::vector<std::string> connections = {};  // Vector encoding the pairs of connected letters
        
        public:
            Plugboard();                                // Class constructor
            ~Plugboard();                               // Class destructor

            bool is_connected(char);                    // Function to check if a given letter is connected to some other
            void check_connection(std::string);         // Function to validate if the user provided connection is valid
            void clear();                               // Function to clear all the connections in the plugboard
            void add(std::string);                      // Function to add a single connection
            void add(std::vector<std::string>);         // Function to add multiple connections
            char swap(char);                            // Function to perform a letter swap based on input character
            
    };

    // Plugboard class constructor
    Plugboard::Plugboard(){}

    // Plugboard class destructor
    Plugboard::~Plugboard(){}

    // Function to check if a given letter is connected to some other
    bool Plugboard::is_connected(char letter){
        for(std::vector<std::string>::iterator pit = connections.begin(); pit != connections.end(); pit++){
            for(std::string::iterator sit = (*pit).begin(); sit != (*pit).end(); sit++){
                if(char(*sit) == letter) return true;
            }
        }
        return false;
    }

    // Function to validate if the user provided connection is valid
    void Plugboard::check_connection(std::string connection){
        if(connection.length() != 2) throw std::runtime_error("A plugboard connection must be composed by two characters");
        if(connection[0] == connection[1]) throw std::runtime_error("A plugboard connection must be made between different characters");
        for(std::string::iterator it = connection.begin(); it != connection.end(); it++){
            check_char(*it);
            if(is_connected(*it) == true) throw std::runtime_error("One of the letters is already in use");
        }
    }

    // Function to clear all the connections in the plugboard
    void Plugboard::clear(){
        connections.clear();
    }

    // Function to add a single connection
    void Plugboard::add(std::string connection){
        check_connection(connection);
        connections.push_back(connection);
    }

    // Function to add multiple connections
    void Plugboard::add(std::vector<std::string> connections){
        for(std::vector<std::string>::iterator it = connections.begin(); it != connections.end(); it++) add(*it);
    }

    // Function to perform a letter swap based on input character
    char Plugboard::swap(char letter){
        if(is_connected(letter) == false) return letter;
        
        for(std::vector<std::string>::iterator pit = connections.begin(); pit != connections.end(); pit++){
            if(letter == (*pit)[0]) return (*pit)[1];
            if(letter == (*pit)[1]) return (*pit)[0];
        }

        throw std::runtime_error("Undefined behavior in plugboard");
    }

}

#endif