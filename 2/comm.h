//
// Created by Ростислав on 03.01.2022.
//

#ifndef PLUSS_2_2_COMM
#define PLUSS_2_2_COMM

#include <string>
#include "libs/SafeInt/SafeInt.hpp"
#include <stack>
#include <map>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include "libs/googletest/googletest/include/gtest/gtest.h"




bool is_number(const std::string &str);

struct ContextExecution {
    std::stack<SafeInt<int64_t>> vals;
    std::map<std::string, SafeInt<int64_t>> vars;
};

class Comm {
public:
    virtual void act(ContextExecution &context_execution, std::vector<std::string> str) = 0;
    virtual ~Comm() = default;
};


class MainException : public std::exception {
protected:
    std::string text = " ERROR ";
public:
    virtual std::string what() = 0;
};


class Pop final: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

/*class Pop : public Comm {
public:
    explicit Pop(std::string &args);

    void comm(ContextExecution &context_execution) override;

};*/


class PopException : public MainException {
public:
    PopException() {
        text += "pop exception";
    }
    PopException(std::string text_);
    std::string what() override{
        return text;
    }
};


/*class Push : public Comm {
public:
    explicit Push(std::string &args);
    void
    comm(ContextExecution &context_execution) override;
};*/

class Push: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};


class PushException : public MainException {
public:
    PushException() {
        text += "pop exception";
    }
    PushException(std::string text_);
    std::string what() override{
        return text;
    }
};

class Peek: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class PeekException : public MainException {
public:
    PeekException() {
        text += "peek exception";
    }
    PeekException(std::string text_);
    std::string what() override{
        return text;
    }
};

class Abs: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class AbsException : public MainException {
public:
    AbsException() {
        text += "abs exception";
    }
    AbsException(std::string text_);
    std::string what() override{
        return text;
    }
};

class Plus: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class PlusException : public MainException {
public:
    PlusException() {
        text += "Plus exception";
    }
    PlusException(std::string text_);
    std::string what() override{
        return text;
    }
};

class Minus: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class MinusException : public MainException {
public:
    MinusException() {
        text += "Minus exception";
    }
    MinusException(std::string text_);
    std::string what() override{
        return text;
    }
};


class Div: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class DivException : public MainException {
public:
    DivException() {
        text += "Div exception";
    }
    DivException(std::string text_);
    std::string what() override{
        return text;
    }
};


class ZeroException : public MainException {
public:
    ZeroException() {
        text += "ZeroException";
    }
    ZeroException(std::string text_);
    std::string what() override{
        return text;
    }
};

class Mul: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};


class MulException : public MainException {
public:
    MulException() {
        text += "Mul exception";
    }
    MulException(std::string text_);
    std::string what() override{
        return text;
    }
};

class Print: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class Read: public Comm{
    void act(ContextExecution& context,  std::vector<std::string> str) override;
};

class ReadException : public MainException {
public:
    ReadException() {
        text += "Read exception";
    }
    ReadException(std::string text_);
    std::string what() override{
        return text;
    }
};


class PrintException : public MainException {
public:
    PrintException() {
        text += "Print exception";
    }
    PrintException(std::string text_);
    std::string what() override{
        return text;
    }
};

class NoCommandException : public MainException {
public:
    NoCommandException() {
        text += "NoCommand exception";
    }
    NoCommandException(std::string text_);
    std::string what() override{
        return text;
    }
};


class Calc {
public:

    Calc() = default;

    virtual Comm *obr(std::vector<std::string> commands) = 0;

};


class Obrer : Calc {
public:
    Comm *obr( std::vector<std::string> commands) override;
};



void procces(std::stringstream &test_s, std::ifstream &ty, int argnum);



#endif //PLUSS_2_2_COMM
