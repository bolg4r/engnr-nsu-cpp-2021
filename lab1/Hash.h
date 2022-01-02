//
// Created by Ростислав on 02.01.2022.
//

#ifndef PLUSS_WORKINGHARD_HASH_H
#define PLUSS_WORKINGHARD_HASH_H

#include <fstream>
#include <cstdint>
#include <iostream>

uint32_t adler32( std::istream &file );
uint64_t sum64( std::istream &file );


#endif //PLUSS_WORKINGHARD_HASH_H
