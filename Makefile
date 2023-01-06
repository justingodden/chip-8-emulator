build:
	g++ ./src/*.cpp -o ./bin/main -lsfml-graphics -lsfml-window -lsfml-system

debug:
	g++ -g ./src/*.cpp -lsfml-graphics -lsfml-window -lsfml-system