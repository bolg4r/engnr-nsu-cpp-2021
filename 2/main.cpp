#include <iostream>
#include <fstream>
#include "comm.h"

void help(std::ostream &ty, const char *text = "."){
    ty<<text<<std::endl;
    ty<< "Usage: ./Calculator <filepath> or ./Calculator"<<std::endl;
    ty<<"Commands: #, POP, PUSH <number>, PUSH <varname>, PEEK <varname>, ABS, PLUS, MINUS, MUL, DIV, PRINT, READ"<<std::endl;
}

int main(int argnum, char *argv[]){
    try {
        std::stringstream test_s;
        std::ifstream ty;
        if (argnum > 2) {
            help(std::cerr);
            return 1;
        }
        if (argnum == 2) {

            ty.open(argv[1]);
            if (!ty.is_open()) {
                help(std::cerr, "Can't find file");
                return 1;
            }
            if (ty.peek() == EOF) {
                return 0;
            }
        }
    procces(test_s,ty,argnum);
    } catch (MainException &e){
        help(std::cerr);
        std::cerr << e.what() << std::endl;
        return 1;
    }
    catch (SafeIntException &) {
        std::cerr << "Overflow exception";
        return 1;
    }
}