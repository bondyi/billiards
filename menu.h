#pragma once

#include <map>

#include "button.h"

class Menu : public Drawable
{
private:
	RectangleShape background;		//затемнение окна

	void draw(RenderTarget& target, RenderStates states) const;		//отрисовка объекта в окне
public:
	Menu();		//конструктор меню
	~Menu();	//деструктор меню

	bool menuStarted;	//меню старта игры
	bool menuPaused;	//меню паузы
	bool menuEnded;		//меню конца игры


	map <Button::btnType, Button*> buttons;		//контейнер, элементами которого €вл€ютс€ кнопки и их ключи

	//обновление объектов
	void update(RenderWindow* window, bool& gameStarted, bool& gamePaused, bool& restartGame, bool& gameEnded, Vector2f mouse, Event event);
};