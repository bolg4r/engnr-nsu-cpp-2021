//
// Created by Ростислав on 02.01.2022.
//

#include "Hash.h"
#include <iostream>
#include <cstdint>

uint32_t adler32( std::istream &file ){
    uint32_t s1 = 1;
    uint32_t s2 = 0;
    unsigned char sig;
    while( file.read((char *)(&sig), sizeof(unsigned char)) ){
        s1 = ( s1 + sig ) % 65521;
        s2 = ( s2 + s1 ) % 65521;
    }
    return ( s2 << 16 ) | s1;
}

uint64_t sum64( std::istream &file ){
    uint64_t sum = 0, point = 0, result = 0;
    unsigned char sig;
    while (file.read((char*)&sig, sizeof(unsigned char))){
        if(point == 8){
            sum = sum + result;
            result = 0;
            point = 0;
        }
        result = result << 8;
        result = result + sig;
        point++;
    }

    return sum + result;
}

