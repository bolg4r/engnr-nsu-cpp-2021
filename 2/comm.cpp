//
// Created by Ростислав on 03.01.2022.
//

#include "comm.h"
#include <iostream>
#include <fstream>



bool is_number(const std::string &s) {
    return !s.empty() && (std::all_of(s.begin(), s.end(), [](char c) { return ::isdigit(c); }) ||
                          (s[0] == '-' && std::all_of(s.begin() + 1, s.end(), [](char c) { return ::isdigit(c); })));
}

void Pop::act(ContextExecution &context, std::vector<std::string> str) {
    if (!context.vals.empty()) {
        context.vals.pop();
    } else
        throw PopException();
}

PopException::PopException(std::string exc) {
    text = exc;
}


void Push::act(ContextExecution &context, std::vector<std::string> str) {
    if (is_number(str[1])) {
        context.vals.push(std::stoll(str[1]));
    } else {
        context.vals.push(context.vars[str[1]]);  //add exception(?)
    }
}

void Peek::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.empty() or str.size() < 2) {
        throw PeekException();
    } else
        context.vars[str[1]] = context.vals.top();
}

void Abs::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.empty()) {
        throw AbsException();
    } else {
        SafeInt<int64_t> a = context.vals.top();
        if (a < 0) {
            a = -1*a;
        }
        context.vals.pop();
        context.vals.push(a);
    }
}

void Plus::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw PlusException();
    } else {
        int64_t a = context.vals.top();
        context.vals.pop();
        int64_t b = context.vals.top();
        int64_t res;
        SafeAdd(a,b,res);
        context.vals.pop();
        context.vals.push(res);
    }
}


void Minus::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw MinusException();
    } else {
        int64_t a = context.vals.top();
        context.vals.pop();
        int64_t b = context.vals.top();
        int64_t res;
        SafeSubtract(b,a,res);
        context.vals.pop();
        context.vals.push(res);
    }
}

void Div::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw DivException();
    } else {
        int64_t a = context.vals.top();
        context.vals.pop();
        if (a==0) {throw ZeroException();}
        int64_t b = context.vals.top();
        int64_t res ;
        SafeDivide(b,a,res);
        context.vals.pop();
        context.vals.push(res);
    }
}

void Mul::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw MulException();
    } else {
        int64_t a = context.vals.top();
        context.vals.pop();
        int64_t b = context.vals.top();
        int64_t res;
        SafeMultiply(a,b,res);
        context.vals.pop();
        context.vals.push(res);
    }
}

void Print::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.empty()){
        throw PrintException();
    } else{
        std::cout<<std::to_string((int64_t) context.vals.top()) << std::endl;
    }
}


void Read::act(ContextExecution &context, std::vector<std::string> str) {
    if (str.size()<2) {
        throw ReadException();
    }
    if (!is_number(str[1])) {
        throw ReadException();
    }
    context.vals.push(std::stoll(str[1]));
}



Comm *Obrer::obr(std::vector<std::string> commands) {
    if (commands[0] == "#") {return nullptr;}
    if (commands[0] == "POP") {return new Pop();}
    if (commands[0] == "PUSH") {return new Push();}
    if (commands[0] == "PEEK") {return new Peek();}
    if (commands[0] == "ABS") {return new Abs();}
    if (commands[0] == "PLUS") {return new Plus();}
    if (commands[0] == "MINUS") {return new Minus();}
    if (commands[0] == "DIV") {return new Div();}
    if (commands[0] == "MUL") {return new Mul();}
    if (commands[0] == "PRINT") {return new Print();}
    if (commands[0] == "READ") {return new Read();}
    else {throw NoCommandException() ;}

}

void procces(std::stringstream &test_s, std::ifstream& ty, int kind) {
    std::string command_line;
    std::vector<std::string> ph;
    Comm *calc_command;
    Obrer proccessor;
    ContextExecution data;





    if (kind == 2){
        while (getline(ty, command_line)) {
            if (command_line.empty()){
                continue;
            }
            std::stringstream str_new(command_line);
            std::vector<std::string> command; //empty lines(?)
            std::stringstream str(command_line);
            std::string com;
            while (getline(str,com,' ')){
                ph.push_back(com);
            }
            calc_command = proccessor.obr(ph);
            calc_command->act(data,ph);
            ph.clear();
            delete calc_command;

        }
    }

    if (kind == 1){
        while (std::getline(std::cin,command_line)) {
            if (command_line.empty()){
                continue;
            }
            std::stringstream str_new(command_line);
            std::vector<std::string> command; //empty lines(?)
            std::stringstream str(command_line);
            std::string com;
            while (getline(str,com,' ')){
                ph.push_back(com);
            }
            calc_command = proccessor.obr(ph);
            calc_command->act(data,ph);
            ph.clear();
            delete calc_command;

        }
    }
    if (kind == 3){
        while (std::getline(test_s,command_line)) {
            if (command_line.empty()){
                continue;
            }
            std::stringstream str_new(command_line);
            std::vector<std::string> command; //empty lines(?)
            std::stringstream str(command_line);
            std::string com;
            while (getline(str,com,' ')){
                ph.push_back(com);
            }
            calc_command = proccessor.obr(ph);
            calc_command->act(data,ph);
            ph.clear();
            delete calc_command;

        }

    }
}













