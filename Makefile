# --- My Sweet Home (MSH) Ultimate Makefile ---
# Standard: C++98
# System: Windows (w64devkit)

CXX      := g++
# Include klasorlerini buraya ekliyoruz ki "No such file" hatasi almayalim
CXXFLAGS := -std=c++98 -Wall -Wextra -Iinclude -Iinclude/Logic -Iinclude/UI -Iinclude/Devices -Iinclude/Utils

# Hedef Dosya
TARGET   := bin/msh_app

# --- KAYNAK DOSYALARIN BULUNMASI ---
# wildcard komutu ile tum klasorlerdeki .cpp dosyalarini otomatik buluyoruz
SRCS     := src/main.cpp \
            src/SystemController.cpp \
            $(wildcard src/Logic/*.cpp) \
            $(wildcard src/UI/*.cpp) \
            $(wildcard src/Devices/*.cpp) \
            $(wildcard src/Utils/*.cpp)

# --- NESNE DOSYALARI ---
# .cpp listesini .o listesine ceviriyoruz (build/ klasoru altina)
OBJS     := $(SRCS:src/%.cpp=build/%.o)

# --- KURALLAR ---

all: $(TARGET)

# Linkleme (Birlestirme)
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	@echo "Linking objects..."
	$(CXX) $(OBJS) -o $@
	@echo "SUCCESS! Calistirmak icin: make run"

# Derleme (Compiling)
# src altindaki her dosyayi build altina ayni klasor yapisiyla derle
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizlik
clean:
	@rm -rf build bin
	@echo "Cleaned."

# Calistir
run: all
	@./$(TARGET)

.PHONY: all clean run