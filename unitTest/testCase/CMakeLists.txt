# 建立測試執行檔案
add_executable(LogicSimulatorTest LogicSimulatorTest.cpp)
add_executable(TextUITest TextUITest.cpp)
add_executable(DeviceTest DeviceTest.cpp)

# 連結 Google Test 和 LogicSimulator 函式庫
target_link_libraries(LogicSimulatorTest gtest gtest_main LSLibrary)
target_link_libraries(TextUITest gtest gtest_main LSLibrary)
target_link_libraries(DeviceTest gtest gtest_main LSLibrary)

# 註冊測試
add_test(NAME LogicSimulatorTest COMMAND LogicSimulatorTest)
add_test(NAME TextUITest COMMAND TextUITest)
add_test(NAME DeviceTest COMMAND DeviceTest)