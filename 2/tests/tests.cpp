//
// Created by Ростислав on 06.01.2022.
//

#include <sstream>
#include <fstream>
#include "../comm.h"


TEST(test1, two_plus_two) {
std::string test = "PUSH 2\n"
                   "PUSH 2\n"
                   "PLUS\n"
                   "PRINT\n";
testing::internal::CaptureStdout();
std::stringstream in_s(test);
std::ifstream in;
std::string result = "4\n";
procces(in_s, in, 3);
std::string output = testing::internal::GetCapturedStdout();
std::cout << output;
EXPECT_EQ(output, result);
}

TEST(test2, mid) {
    std::string test = "PUSH 2\n"
                       "PUSH 10\n"
                       "PEEK var\n" //10
                       "DIV\n" //0
                       "PUSH var\n"
                       "PUSH 8\n"
                       "MUL\n" //0
                       "PUSH var\n"
                       "MINUS\n" //70
                       "ABS\n"
                       "PRINT\n";



    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;
    std::string result = "70\n";
    procces(in_s, in, 3);
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output;
    EXPECT_EQ(output, result);
}

TEST(test3, PlusException) {
    std::string test = "PUSH 2\n"
                       "PLUS\n"
                       "PRINT\n";
    std::stringstream in_s(test);
    std::ifstream in;
    EXPECT_THROW(procces(in_s, in, 3), PlusException);
}

TEST(test4, NoCommandException) {
    std::string test = "PUSH 2\n"
                       "PUSH 4\n"
                       "NikitaTheBest\n"
                       "MUL\n";
    std::stringstream in_s(test);
    std::ifstream in;
    EXPECT_THROW(procces(in_s, in, 3), NoCommandException);

}



TEST(test5, PushException) {
    std::string test = "PUSH\n";

    std::stringstream in_s(test);
    std::ifstream in;
    EXPECT_THROW(procces(in_s, in, 3), PushException);

}

TEST(test6, OverException) {
    std::string test = "PUSH 853373436854\n"
                       "PUSH 20898131\n"
                       "MUL\n"
                       "PRINT\n";
    std::stringstream in_s(test);
    std::ifstream in;
    EXPECT_THROW(procces(in_s, in, 3), OverException);

}

TEST(test7, OverException) {
    std::string test ="PUSH -9223372036854775808\n"
                       "ABS\n"
                       "PRINT\n";
    std::stringstream in_s(test);
    std::ifstream in;
    EXPECT_THROW(procces(in_s, in, 3), OverException);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
