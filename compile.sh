#!/bin/bash

g++ -IC:/SFML/include -c src/main.cpp -o bin/main.o
g++ -IC:/SFML/include -c src/boid.cpp -o bin/boid.o
g++ -LC:/SFML/lib -o bin/app.exe bin/main.o bin/boid.o -lmingw32 -lm -lsfml-system -lsfml-window -lsfml-graphics -lsfml-main

