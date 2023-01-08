CXXFLAGS += -O3 -DNDEBUG

release:
	g++ $(CXXFLAGS) ./src/*.cpp -o ./bin/chip8 -lsfml-graphics -lsfml-window -lsfml-system

debug:
	g++ -g ./src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system