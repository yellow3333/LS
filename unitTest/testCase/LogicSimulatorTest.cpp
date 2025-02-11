#include "../../src/include/LogicSimulator.h"
#include "gtest/gtest.h"

TEST(LogicSimulatorTest, Constructor) {
    LogicSimulator sim;
    EXPECT_EQ(sim.getInPinSize(), 0) << "Initial input pin size should be 0";
}

// Load
TEST(LogicSimulatorTest, LoadValidFile){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    LogicSimulator sim;
    bool success = sim.load("C:\\Users\\Ken\\Code\\HW\\src\\testLcf\\test.lcf"); // valid file

    std::cout.rdbuf(oldCout); 

    std::string expected = "Circuit: 4 input pins, 3 output pins and 5 gates\n";
    EXPECT_EQ(output.str(), expected);
    EXPECT_EQ(sim.getInPinSize(), 4);
    EXPECT_TRUE(success) << "Loading an invalid file should return ture";
}

TEST(LogicSimulatorTest, LoadInvalidFile) {
    LogicSimulator sim;
    bool success = sim.load("invalidFile.lcf");
    EXPECT_FALSE(success) << "Loading an invalid file should return false";
}

TEST(LogicSimulatorTest, LoadInvalidFormat) {
    LogicSimulator sim;
    bool success = sim.load("invalidFile.txt");
    EXPECT_FALSE(success) << "Loading an invalid file should return false";
}

// ClearLogic
TEST(LogicSimulatorTest, ClearLogicOnEmptyCircuit) {
    LogicSimulator sim;
    EXPECT_NO_THROW(sim.clearLogic());  
}

TEST(LogicSimulatorTest, ClearLogicAfterLoad) {
    LogicSimulator sim;
    sim.load("C:\\Users\\Ken\\Code\\HW\\src\\testLcf\\test.lcf");  
    sim.clearLogic();

    EXPECT_EQ(sim.getInPinSize(), 0);  // 檢查輸入腳位數是否清空
    EXPECT_NO_THROW(sim.clearLogic()); // 再次清理不應該導致崩潰
}

// outTalbeHead
TEST(LogicSimulatorTest, OutTableHead){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());  

    LogicSimulator sim;
    sim.load("C:\\Users\\Ken\\Code\\HW\\src\\testLcf\\test.lcf");  
    sim.outTalbeHead();

    std::cout.rdbuf(oldCout); 

    std::string expected = "Circuit: 4 input pins, 3 output pins and 5 gates\n"
                           "i i i i | o o o\n"
                           "1 2 3 4 | 1 2 3\n"
                           "--------+------\n";
    EXPECT_EQ(output.str(), expected);
}

// outTableItem
TEST(LogicSimulatorTest, OutTableItem){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());  

    LogicSimulator sim;
    sim.load("C:\\Users\\Ken\\Code\\HW\\src\\testLcf\\test.lcf");  
    vector<int>  iPin(sim.getInPinSize(),0);
    sim.outTableItem(iPin);

    std::cout.rdbuf(oldCout); 

    std::string expected =  "Circuit: 4 input pins, 3 output pins and 5 gates\n"
                            "0 0 0 0 | 1 0 1\n";
    EXPECT_EQ(output.str(), expected);
}

// getSimulationResult
TEST(LogicSimulatorTest, GetSimulationResult){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());  

    LogicSimulator sim;
    sim.load("C:\\Users\\Ken\\Code\\HW\\src\\testLcf\\test.lcf");  
    vector<int>  iPin(sim.getInPinSize(),0);
    sim.getSimulationResult(iPin);

    std::cout.rdbuf(oldCout); 

    std::string expected = "Circuit: 4 input pins, 3 output pins and 5 gates\n"
                           "Simulation Result: \n"
                           "i i i i | o o o\n"
                           "1 2 3 4 | 1 2 3\n"
                           "--------+------\n"
                           "0 0 0 0 | 1 0 1\n";
                           
    EXPECT_EQ(output.str(), expected);
}

// getTruthTable()
TEST(LogicSimulatorTest, GetTruthTable){
    std::ostringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());  

    LogicSimulator sim;
    sim.load("C:\\Users\\Ken\\Code\\HW\\src\\testLcf\\test.lcf");  
    sim.getTruthTable();

    std::cout.rdbuf(oldCout); 

    std::string expected = "Circuit: 4 input pins, 3 output pins and 5 gates\n"
                           "Truth table: \n"
                           "i i i i | o o o\n"
                           "1 2 3 4 | 1 2 3\n"
                           "--------+------\n"
                           "0 0 0 0 | 1 0 1\n"
                           "0 0 0 1 | 1 0 0\n"
                           "0 0 1 0 | 1 0 1\n"
                           "0 0 1 1 | 1 0 0\n"
                           "0 1 0 0 | 1 0 1\n"
                           "0 1 0 1 | 1 0 0\n"
                           "0 1 1 0 | 1 0 1\n"
                           "0 1 1 1 | 1 0 0\n"
                           "1 0 0 0 | 1 0 1\n"
                           "1 0 0 1 | 1 0 0\n"
                           "1 0 1 0 | 1 0 1\n"
                           "1 0 1 1 | 1 0 0\n"
                           "1 1 0 0 | 0 0 1\n"
                           "1 1 0 1 | 0 0 0\n"
                           "1 1 1 0 | 0 1 1\n"
                           "1 1 1 1 | 0 1 0\n";
                           
    EXPECT_EQ(output.str(), expected);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}