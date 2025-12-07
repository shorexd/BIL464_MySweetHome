cmake_minimum_required(VERSION 3.10)

project(MSH_System)

# C++98 Standardını zorunlu kılıyoruz
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include klasörünü tanıtıyoruz
include_directories(include)

# Kaynak dosyaları listeliyoruz
file(GLOB SOURCES "src/*.cpp" "main.cpp")

add_executable(MSH_App ${SOURCES})