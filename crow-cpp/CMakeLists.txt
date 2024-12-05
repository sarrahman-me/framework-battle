cmake_minimum_required(VERSION 3.12)
project(books-api)

# Set standar C++ yang akan digunakan
set(CMAKE_CXX_STANDARD 11)

# Menambahkan direktori include untuk Crow dan Asio
# Homebrew menginstal Asio dan Crow di /opt/homebrew/include
include_directories(/opt/homebrew/include)

# Menambahkan file sumber utama
add_executable(books-api main.cpp)

# Menautkan library pthread (untuk multithreading)
target_link_libraries(books-api pthread)
