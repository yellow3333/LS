# 定義邏輯模擬器函式庫
file(GLOB SRC_FILES *.cpp)

# 建立靜態函式庫 LogicSimulator
add_library(LSLibrary ${SRC_FILES})

# 添加 include 資料夾到 target
target_include_directories(LSLibrary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
