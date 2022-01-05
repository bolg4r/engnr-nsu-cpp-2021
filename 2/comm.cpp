//
// Created by Ростислав on 03.01.2022.
//

#include "comm.h"
#include <iostream>
#include <fstream>


/*Pop::Pop(std::string &args) : Comm(args) {}

void Pop::comm(ContextExecution &context_execution) {
    if (!context_execution.stack.empty()) {
        context_execution.stack.pop();
    } else {
        throw PopException();
    }
}
*/
bool is_number(const std::string &str) {
        for (char const &c : str) {
            if (std::isdigit(c) == 0) return false;
        }
        return true;
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


/*Push::Push(std::string &args) : Comm(args) {}

void Push::comm(ContextExecution &context_execution) {
    if (is_number(params)) {
        int64_t result{}; //delete nahui
        auto[ptr, ec]{std::from_chars(params.data(), params.data() + params.size(), result)};
        if (ec == std::errc::result_out_of_range) { //если ошибка
            throw OverflowException();
        }
        context_execution.stack.push(result);
    } else {
        auto elem = context_execution.variables.find(params); //хуета
        if (elem == context_execution.variables.end()) {
            throw PushException();
        } else context_execution.stack.push(elem->second);
    }
}*/

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
        SafeInt<int64_t> a = context.vals.top();
        context.vals.pop();
        SafeInt<int64_t> b = context.vals.top();
        SafeInt<int64_t> res = a + b;
        context.vals.pop();
        context.vals.push(res);
    }
}


void Minus::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw MinusException();
    } else {
        SafeInt<int64_t> a = context.vals.top();
        context.vals.pop();
        SafeInt<int64_t> b = context.vals.top();
        SafeInt<int64_t> res = a - b;
        context.vals.pop();
        context.vals.push(res);
    }
}

void Div::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw DivException();
    } else {
        SafeInt<int64_t> a = context.vals.top();
        context.vals.pop();
        if (a==0) {throw ZeroException();}
        SafeInt<int64_t> b = context.vals.top();
        SafeInt<int64_t> res = b/a;
        context.vals.pop();
        context.vals.push(res);
    }
}

void Mul::act(ContextExecution &context, std::vector<std::string> str) {
    if (context.vals.size()<2) {
        throw MulException();
    } else {
        SafeInt<int64_t> a = context.vals.top();
        context.vals.pop();
        SafeInt<int64_t> b = context.vals.top();
        SafeInt<int64_t> res = b*a;
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

void procces(std::stringstream &test_s, std::ifstream &ty, int argnum) {
    std::string command_line;
    std::vector<std::string> ph;
    Comm *calc_command;
    Obrer proccessor;
    ContextExecution data;
    if (argnum == 2){
        while (getline(ty, command_line)) {
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

    if (argnum == 1){
        while (std::getline(std::cin,command_line)) {
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













