cmake_minimum_required(VERSION 3.10)

project(TinyJsonParser)

set(CMAKE_CXX_STANDARD 17)

# 添加源文件
add_executable(TinyJsonParser
    src/main.cpp
    src/Lexer.cpp
    src/Parser.cpp

)

# 包含头文件目录
target_include_directories(TinyJsonParser PRIVATE src)