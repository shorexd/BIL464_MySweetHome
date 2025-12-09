cmake_minimum_required(VERSION 3.10)

# Proje adi
project(MSH_Mode_System)

# Döküman gereksinimi: C++98 Standardi
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header (.h) dosyalarinin oldugu klasoru tanitiyoruz
include_directories(include)

# src klasöründeki tüm .cpp dosyalarini ve main.cpp'yi bul
file(GLOB SOURCES "src/*.cpp" "main.cpp")

# Bulunan dosyalardan calistirilabilir (exe) dosyayi olustur
add_executable(MSH_Mode_App ${SOURCES})