#include "rotors.h"
#include "reflectors.h"

#ifndef ENIGMA_COMPONENTS_H
#define ENIGMA_COMPONENTS_H

namespace enigma{

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

#endif
