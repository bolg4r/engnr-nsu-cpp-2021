#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "Hash.h"


void help(std::ostream &ty){
    ty<< "Usage: \n .hasher -h \n ./hasher -m <adler/sum64> <filename>"<<std::endl;
    ty<<"./hasher <filename> -m <adler/sum64>"<<std::endl;
}

int main(int num_arg, char *argv[]) {
    std::ifstream file;
    std::string mode, filename;

    if(num_arg != 4 && num_arg != 2){
        if(num_arg<4){
            std::cerr << "Error! Not enough arguments." << std::endl;
            help(std::cerr);
            return 1;
        }
        else {
            std::cerr << "Error! Too many arguments." << std::endl;
            help(std::cerr);
            return 1;
        }

    }

    if (num_arg == 2){
        if(!(strcmp(argv[1], "-h"))){
            help(std::cout);
        }
        else{
            std::cerr<<"Arguments are entered incorrectly";
            help(std::cerr);
            return 1;
        }
    }

    if (num_arg == 4){
        if (strcmp(argv[1],"-m")== 0 && (strcmp(argv[2],"adler32")==0 || strcmp(argv[2],"sum64")==0)){
            mode = argv[2];
            filename = argv[1];
        }
        if (strcmp(argv[2], "-m")== 0 && (strcmp(argv[3],"adler32")==0 || strcmp(argv[3],"sum64")==0)) {
            mode = argv[3];
            filename = argv[1];
        }
        else {
            std::cerr << "Error! Arguments are entered incorrectly." << std::endl;
            help(std::cerr);
            return 1;
        }
    }

    file.open(filename, std::ios::binary);

    if (file.is_open()){
        if(strcmp(mode,"adler32") == 0){
            std::cout << std::hex << adler32(file) << std::endl;
        }else {
            std::cout << std::hex << sum64(file) << std::endl;
        }
    }
    else {
        std::cerr << "Error! File is not found"<<std::endl;
        help(std::cerr);
        return 1;
    }


    return 0;
}
