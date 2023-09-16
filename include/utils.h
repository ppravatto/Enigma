#include <stdexcept>
#include <exception>

#ifndef UTILS_H
#define UTILS_H

// Check that the given charater is an uppercase alphabet letter
void check_char(char letter){
    if(int(letter) < 65 || int(letter) > 90){
        throw std::runtime_error("The given char is not an uppercase alphabet letter");
    }
}

// Obtain the index of a given letter in the alphabet
int to_index(char letter){  
    check_char(letter);
    return int(letter) - 65;
}

// Obtain the character from the index of the letter in the alphabet
char to_char(int index){
    return char(index + 65);
}

// Adjust an idex to make if fall in the range 0-25
int adjust_index(int index){
    if(index >= 0) return index%26;
    else{
        int value = index;
        while(value<0) value += 26;
        return value;
    }
}

#endif