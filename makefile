TARGET = game

ifeq ($(OS),Windows_NT)
	TG = $(TARGET).exe
else
	TG = $(TARGET)
endif

CXXFLAGS = -std=c++20 -O0 -g -Wall -Wextra -Wpedantic

build:
ifeq ($(OS),Windows_NT)
	zig c++ $(CXXFLAGS) -o $(TG) main.cpp \
		-I"C:\raylib\include" "C:\raylib\lib\libraylib.a" \
		-lopengl32 -lgdi32 -lwinmm
else
	zig c++ $(CXXFLAGS) -fsanitize=address,undefined \
		-D_GLIBCXX_ASSERTIONS \
		main.cpp -o $(TG) -lraylib -lX11 -lpthread -ldl -lm
endif

run: build
	./$(TG)

clean:
	rm -f $(TG) $(TG).exe

.PHONY: build run clean
