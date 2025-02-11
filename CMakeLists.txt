cmake_minimum_required(VERSION 3.10)
project(TestProject)

# 啟用測試功能
enable_testing()

# 加入必要的子目錄
add_subdirectory(src)
add_subdirectory(unitTest/testCase)
add_subdirectory(unitTest/googletest)
