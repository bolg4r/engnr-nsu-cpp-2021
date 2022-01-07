//
// Created by Ростислав on 06.01.2022.
//

#include <sstream>
#include <fstream>
#include "../comm.h"


TEST(two_plus_two, test_1) {
std::string test = "#Nikita Provotorov the best\n"
                   "PUSH 2\n"
                   "PUSH 2\n"
                   "PLUS\n"
                   "PRINT";
testing::internal::CaptureStdout();
std::stringstream in_s(test);
std::ifstream in;
std::string result = "4\n";
procces(in_s, in, 3);
std::string output = testing::internal::GetCapturedStdout();
std::cout << output;
EXPECT_EQ(output, result);
}

TEST(medium, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH 2\n"
                       "PUSH 10\n"
                       "PEEK var\n" //10
                       "DIV\n" //5
                       "PUSH var\n"
                       "PUSH 8\n"
                       "MUL\n" //40
                       "PUSH var"
                       "MINUS" //-35
                       "ABS"
                       "PRINT";



    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;
    std::string result = "70\n";
    procces(in_s, in, 3);
    std::string output = testing::internal::GetCapturedStdout();
    std::cout << output;
    EXPECT_EQ(output, result);
}

TEST(Plus_exc, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH 2\n"
                       "PLUS\n"
                       "PRINT\n";
    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;

    EXPECT_THROW(procces(in_s, in, 3), PlusException);
}

TEST(Some_exc, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH 2\n"
                       "Push 4\n"
                       "NikitaTheBest\n"
                       "MUL\n";
    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;
    std::string result = "4\n";
    procces(in_s, in, 3);
    EXPECT_THROW(procces(in_s, in, 3), NoCommandException);

}

TEST(Really_big, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH 942493935452545479986\n"
                       "PUSH 8996979999759659569755\n"
                       "PLUS\n";
    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;

    EXPECT_THROW(procces(in_s, in, 3), PushException);
}

TEST(Push_exc, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH \n"
                       "Pop\n"
                       "MUL\n";
    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;
    procces(in_s, in, 3);
    EXPECT_THROW(procces(in_s, in, 3), PushException);

}

TEST(Over_exc, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH 853373436854\n"
                       "PUSH 20898131\n"
                       "MUL\n"
                       "PRINT\n";
    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;
    procces(in_s, in, 3);
    EXPECT_THROW(procces(in_s, in, 3), OverException);

}

TEST(Over_exc1, test_1) {
    std::string test = "#Nikita Provotorov the best\n"
                       "PUSH -9223372036854775808\n"
                       "ABS\n"
                       "PRINT\n";
    testing::internal::CaptureStdout();
    std::stringstream in_s(test);
    std::ifstream in;
    procces(in_s, in, 3);
    EXPECT_THROW(procces(in_s, in, 3), OverException);

}

