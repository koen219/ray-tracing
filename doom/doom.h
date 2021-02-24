#pragma once

#include <SFML/Graphics.hpp>
#include "moveable.h";
#include <iostream>
#include <vector>
class Doom
{
private:
	const int ScreenHeight = 512;
	const int ScreenWidth = 512*2;
	const int Height = 16;
	const int Width = 16;
	const int tileSize = 32;
	char bord[16][16] = {
		{'0','0','0','0','0','0','w','0','0','0','0','0','0','0','0','0'},
		{'0','0','0','0','0','0','w','0','0','w','0','0','0','0','0','0'},
		{'0','0','0','0','0','0','w','0','0','w','0','0','0','0','0','0'},
		{'0','0','0','0','0','0','w','w','w','0','0','0','0','0','0','0'},
		{'0','0','0','0','0','0','w','0','0','0','0','0','0','0','0','0'},
		{'w','w','w','w','w','w','w','w','w','w','w','w','w','w','w','w'},
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','0','0','0','0','p','0','0','0','0','0','w','0','0'},
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','w','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','w','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','w','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','w','0','0','0','0','0','0','0','0','0','w','0','0'},
		{'0','0','0','0','0','0','0','0','0','0','0','0','0','w','0','0'},
	};
	bool gameOver;
	sf::RenderWindow* window;
	void draw();
	void handleEvents();
	void playerMove();
	void drawFOV();
	moveable* Player;
	std::vector<moveable*> drawAbles; 
	std::vector<sf::RectangleShape> walls;
	std::vector<sf::RectangleShape> air3D;
	std::vector<sf::RectangleShape> walls3D;
	std::vector<sf::RectangleShape> ground3D;
	int FOV = 40;
	double getLengthToWall(double);
public:
	inline Doom() { 
		gameOver = false; 
		window = new sf::RenderWindow(sf::VideoMode(ScreenWidth, ScreenHeight), "SFML works!");
		Player = new moveable;
		drawAbles.push_back(Player);
		Player->Type = 'P';
		for (int i = 0; i<Height; i++)
			for (int j = 0; j < Width; j++) {
				if (bord[i][j] == 'p')
					Player->Position = vector2D(tileSize*j, tileSize*i);
			}
		for (int i = 0; i < Height; i++)
			for (int j = 0; j < Width; j++)
				if (bord[i][j] == 'w') {
					sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
					rect.setPosition(j * tileSize, i * tileSize);
					rect.setFillColor(sf::Color::Red);
					walls.push_back(rect);
					
				}
		for (int i = 0; i < FOV; i++) {
			sf::RectangleShape wall;
			sf::RectangleShape air;
			sf::RectangleShape ground;
			walls3D.push_back(wall);
			air3D.push_back(air);
			ground3D.push_back(ground);
		}
	}
	inline ~Doom() {
		delete Player;
		delete window;
	}
	void gameLoop();
};

