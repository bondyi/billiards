#pragma once

#include <iostream>
#include <vector>

#include "line.h"

using namespace std;

class Board
{
private:
	//текстура биль€рдного стола
	Texture boardTexture;

	//спрайт биль€рдного стола
	Sprite boardSprite;

	//вектора, состо€щие из бордюр и луз
	vector<Line> lines;
	vector<Line> holes;

	//инициализаци€ биль€рдного стола
	void initBoard();

	//инициализаци€ линий
	void initLines();

public:
	//конструктор биль€рдного стола
	Board();

	//деструктор биль€рдного стола
	~Board();

	//функции возвращают вектор бордюр или луз
	vector<Line> getBorderLines();
	vector<Line> getHolesLines();

	//отрисовка объекта в окне
	void render(RenderTarget* target);
};