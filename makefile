TARGET = game

build:
	g++ -lraylib -lX11 main.cpp -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: build run clean

