#pragma once

#include "board.h"
#include "ball.h"
#include "gui.h"

class Game
{
private:
	RenderWindow* window;		//окно
	ContextSettings settings;	//настройки
	Event sfmlEvent;			//событие

	Vector2f mMouse;			//координаты курсора

	void initWindow();			//инициализация окна
	void initGame();			//инициализация игры

public:
	Game();						//конструктор игры
	~Game();					//деструктор игры

	Clock clock;				//время

	Gui* gui;					//объект "интерфейс"
	Board* board;				//объект "стол" (+ линии (бордюры и лузы))
	Ball* blackBall;			//объект "шар" (чёрный)
	vector<Ball*> whiteBalls;	//вектор, состоящий из объектов "шар" (белые)
	Ball* draggedBall;			//объект "выбранный шар"

	Line* direction;			//объект "направление шара после удара"

	bool restartGame;			//перезапуск игры
	bool dragged;				//шар выбран
	bool move;					//шары катятся
	bool goal;					//шар попал в лузу

	const bool running() const;		//true - окно открыто, false - закрыто
	void pollEvents();				//события

	void collisionCircleLine(Ball* ball, Line* line);		//регистрация столкновения "шар - бордюр"
	void collisionCircles(Ball* ball1, Ball* ball2);		//регистрация столкновения "шар - шар"
	void collisionCircleHole(Ball* ball, Line* hole);		//регистрация столкновения "шар - луза"

	void updateDirectionLine();			//обновление объекта "направление шара после удара"
	void updateAllCollisions();			//обновление регистраций столкновения
	void updateGameLogic();				//обновление логики игры
	void restart();						//функция перезапуска игры

	void update();						//вызов всех функций обновления
	void render();						//отрисовка объектов в окне
};