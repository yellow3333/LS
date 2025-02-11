#include "../../src/include/TextUI.h"
#include "gtest/gtest.h"
// #include "gmock/gmock.h"  // Google Mock
#include <sstream>

// InputDigit : 0~9 are valid
TEST(TextUITest, InputDigitValid) {
    TextUI ui;
    std::istringstream input("5\n");
    std::cin.rdbuf(input.rdbuf());  // 模擬 cin 輸入
    EXPECT_EQ(ui.inputDigit(), 5);
}

TEST(TextUITest, InputDigitInvalidString) {
    TextUI ui;
    std::istringstream input("abc\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(ui.inputDigit(), -1);
}

TEST(TextUITest, InputDigitInvalidNotDigit) {
    TextUI ui;
    std::istringstream input("10\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(ui.inputDigit(), -1);
}

// InputServe : Command 1~4 are valid
TEST(TextUITest, InputServeCommandValid) {
    TextUI ui;
    std::istringstream input("2\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(ui.inputServe(0), 2);  
}

TEST(TextUITest, InputServeCommandInvalid) {
    TextUI ui;
    std::istringstream input("0\n5\n2\n"); 
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(ui.inputServe(0), 2);  
}

// InputServe : input Pin 0/1 are valid
TEST(TextUITest, InputServePinValid) {
    TextUI ui;
    std::istringstream input("1\n");
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(ui.inputServe(1, 0), 1);  
}

TEST(TextUITest, InputServePinInvalid) {
    TextUI ui;
    std::istringstream input("2\n0\n"); 
    std::cin.rdbuf(input.rdbuf());
    EXPECT_EQ(ui.inputServe(1, 0), 0);  
}

// DisplayMenuOutput
TEST(TextUITest, DisplayMenuOutput) {
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());  // 改變 cout 流向

    TextUI ui;
    ui.displayMenu(); 

    std::cout.rdbuf(oldCout);  // 還原 cout

    std::string expected = "1. Load logic circuit file\n"
                           "2. Simulation\n"
                           "3. Display truth table\n"
                           "4. Exit\n";
    EXPECT_EQ(output.str(), expected);
}

// Process Command 1
TEST(TextUITest, ProcessCommandLoadInvalidFilel){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf()); 

    std::istringstream input("1\nInvalidFile.lcf\n");
    std::cin.rdbuf(input.rdbuf());

    TextUI ui;
    bool success = ui.processCommand();

    std::cout.rdbuf(oldCout);

    std::string expected =  "Command:"
                            "Please key in a file path : "
                            "File not found or file format error!!\n\n";
    EXPECT_EQ(output.str(), expected);
    EXPECT_TRUE(success);
}

//Process Command 2
TEST(TextUITest, ProcessCommandFailSimulation){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf()); 

    std::istringstream input("2\n");
    std::cin.rdbuf(input.rdbuf());

    TextUI ui;
    bool success = ui.processCommand();

    std::cout.rdbuf(oldCout);

    std::string expected =  "Command:"
                            "Please load an lcf file, before using this operation.\n\n";
    EXPECT_EQ(output.str(), expected);
    EXPECT_TRUE(success);
}

//Process Command 3
TEST(TextUITest, ProcessCommandFailDisplayTruthTable){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf()); 

    std::istringstream input("3\n");
    std::cin.rdbuf(input.rdbuf());

    TextUI ui;
    bool success = ui.processCommand();

    std::cout.rdbuf(oldCout);

    std::string expected =  "Command:"
                            "Please load an lcf file, before using this operation.\n\n";
    EXPECT_EQ(output.str(), expected);
    EXPECT_TRUE(success);
}

//Process Command 4
TEST(TextUITest, ProcessCommandExit){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf()); 

    std::istringstream input("4\n");
    std::cin.rdbuf(input.rdbuf());

    TextUI ui;
    bool success = ui.processCommand();

    std::cout.rdbuf(oldCout);

    std::string expected =  "Command:"
                            "Goodbye, thanks for using LS.";
    EXPECT_EQ(output.str(), expected);
    EXPECT_FALSE(success);
}