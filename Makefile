# --- w64devkit Uyumlu Makefile ---
CXX      = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Iinclude

# Hedef
TARGET   = bin/msh_app

# Kaynak Dosyalar
SRCS     = src/main.cpp

# Derleme Kurali
all:
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)
	@echo "SUCCESS! Run with: make run"

run: all
	@./$(TARGET)

clean:
	@rm -rf bin
	@echo "Cleaned."