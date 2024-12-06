cmake_minimum_required(VERSION 3.10)
project(BooksAPI)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(books-api main.cpp)