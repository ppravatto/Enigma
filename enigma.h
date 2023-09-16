#include <iostream>
#include <string>
#include <vector>
#include "utils.h"

#ifndef ROTORS_H
#define ROTORS_H

namespace enigma{

    class Rotor{

        protected:
            int position;
            std::string wiring;
            std::vector<char> notches;
            
        public:
            Rotor(std::string, std::vector<char>);
            ~Rotor();
            
            void set_position(char);
            void rotate();
            bool is_notch();
            char foreward(char);
            char backward(char);
            char left_output(char);
            char right_output(char);

    };

    Rotor::Rotor(std::string _wiring, std::vector<char> _notches){

        notches = _notches;
        for(std::vector<char>::iterator it = notches.begin(); it != notches.end(); it++) check_char(*it);
        
        wiring = _wiring;
        if(wiring.length() != 26) throw std::runtime_error("The wiring string must have 26 characters");
        for(std::string::iterator it = wiring.begin(); it != wiring.end(); it++) check_char(*it);

        position = 0;
    }

    Rotor::~Rotor(){}

    void Rotor::set_position(char start){
        position = to_index(start);
    }

    void Rotor::rotate(){
        position++;
        if(position >= 26) position = 0;
    }

    bool Rotor::is_notch(){
        for(std::vector<char>::iterator it = notches.begin(); it != notches.end(); it++){
            if(to_char(position) == *it) return true;
        }
        return false;
    }

    char Rotor::foreward(char letter){
        int index = to_index(letter) + position;
        return wiring[index%26];
    }

    char Rotor::left_output(char letter){
        char encoded = foreward(letter);
        int index = to_index(encoded) - position;
        return (index<0)? to_char(index+26) : to_char(index);
    }

    char Rotor::backward(char letter){
        int index = wiring.find(letter) - position;
        return (index < 0)? to_char(index) + 26 : to_char(index);
    }

    char Rotor::right_output(char letter){
        int index = (to_index(letter) + position) % 26;
        char new_letter = to_char(index);
        char encoded = backward(new_letter);
        return encoded;        
    }


    class Reflector{

        protected:
            std::string wiring;
            
        public:
            Reflector(std::string);
            ~Reflector();

            char foreward(char);
            char backward(char);
    };

    Reflector::Reflector(std::string _wiring){
        wiring = _wiring;
        if(wiring.length() != 26) throw std::runtime_error("The wiring string must have 26 characters");
        for(std::string::iterator it = wiring.begin(); it != wiring.end(); it++) check_char(*it);
    }

    Reflector::~Reflector(){}


    char Reflector::foreward(char letter){
        int index = to_index(letter);
        return wiring[index];
    }

    char Reflector::backward(char letter){
        int index = wiring.find(letter);
        return to_char(index);
    }


    class Plugboard{

        private:
            std::vector<std::string> connections = {};
        
        public:
            Plugboard();
            bool is_connected(char);
            void check_connection(std::string);
            void clear();
            void add(std::string);
            void add(std::vector<std::string>);
            char swap(char);
            
    };

    Plugboard::Plugboard(){}

    bool Plugboard::is_connected(char letter){
        for(std::vector<std::string>::iterator pit = connections.begin(); pit != connections.end(); pit++){
            for(std::string::iterator sit = (*pit).begin(); sit != (*pit).end(); sit++){
                if(char(*sit) == letter) return true;
            }
        }
        return false;
    }

    void Plugboard::check_connection(std::string connection){
        if(connection.length() != 2) throw std::runtime_error("A plugboard connection must be composed by two characters");
        if(connection[0] == connection[1]) throw std::runtime_error("A plugboard connection must be made between different characters");
        for(std::string::iterator it = connection.begin(); it != connection.end(); it++){
            check_char(*it);
            if(is_connected(*it) == true) throw std::runtime_error("One of the letters is already in use");
        }
    }

    void Plugboard::clear(){
        connections.clear();
    }

    void Plugboard::add(std::string connection){
        check_connection(connection);
        connections.push_back(connection);
    }

    void Plugboard::add(std::vector<std::string> connections){
        for(std::vector<std::string>::iterator it = connections.begin(); it != connections.end(); it++) add(*it);
    }

    char Plugboard::swap(char letter){
        if(is_connected(letter) == false) return letter;
        
        for(std::vector<std::string>::iterator pit = connections.begin(); pit != connections.end(); pit++){
            if(letter == (*pit)[0]) return (*pit)[1];
            if(letter == (*pit)[1]) return (*pit)[0];
        }

        throw std::runtime_error("Undefined behavior in plugboard");
    }


    class Enigma{

        private:
            std::vector<Rotor> rotors;
            Reflector reflector;
            Plugboard plugboard;

        public:
            Enigma(std::vector<Rotor>, Reflector);

            void set_positions(std::vector<char>);
            void set_plugboard(std::vector<std::string>);
            char transform(char);
            void rotate();
            std::string encode(std::string);

    };

    Enigma::Enigma(std::vector<Rotor> _rotors, Reflector _reflector) : rotors(_rotors), reflector(_reflector) {}

    void Enigma::set_positions(std::vector<char> positions){
        if(positions.size() != rotors.size()) throw std::runtime_error("The number of position must match the number of rotors");
        for(int i=0; i<positions.size(); i++) rotors[i].set_position(positions[i]);
    }

    void Enigma::set_plugboard(std::vector<std::string> connections){
        plugboard.clear();
        plugboard.add(connections);
    }

    char Enigma::transform(char letter){
        check_char(letter);
        char out = plugboard.swap(letter);
        for(int i = rotors.size()-1; i >= 0; i--) out = rotors[i].left_output(out);
        out = reflector.foreward(out);
        for(int i = 0; i < rotors.size(); i++) out = rotors[i].right_output(out);
        out = plugboard.swap(out);
        return out;
    }

    void Enigma::rotate(){
        for(int i = rotors.size()-1; i>=0; i--){
            bool notch_reached = rotors[i].is_notch();
            rotors[i].rotate();
            if(notch_reached == false) break;
        }
    }
    
    std::string Enigma::encode(std::string message){
        std::string output = "";
        for(std::string::iterator sit = message.begin(); sit != message.end(); sit++){
            rotate();
            char letter = transform(*sit);
            output += letter;
        }
        return output;
    }


    namespace components{

        Rotor Rotor_I("EKMFLGDQVZNTOWYHXUSPAIBRCJ", {'Q'});
        Rotor Rotor_II("AJDKSIRUXBLHWTMCQGZNPYFVOE", {'E'});
        Rotor Rotor_III("BDFHJLCPRTXVZNYEIWGAKMUSQO", {'V'});
        Rotor Rotor_IV("ESOVPZJAYQUIRHXLNFTGKDCMWB", {'J'});
        Rotor Rotor_V("VZBRGITYUPSDNHLXAWMJQOFECK", {'Z'});
        Rotor Rotor_VI("JPGVOUMFYQBENHZRDKASXLICTW", {'Z', 'M'});
        Rotor Rotor_VII("NZJHGRCXMYSWBOUFAIVLPEKQDT", {'Z', 'M'});
        Rotor Rotor_VIII("FKQHTLXOCBJSPDZRAMEWNIUYGV", {'Z', 'M'});

        Reflector Reflector_A("EJMZALYXVBWFCRQUONTSPIKHGD");
        Reflector Reflector_B("YRUHQSLDPXNGOKMIEBFZCWVJAT");
        Reflector Reflector_C("FVPJIAOYEDRZXWGCTKUQSBNMHL");

    }
    
}

#endif