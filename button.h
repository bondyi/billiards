#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button : public Drawable
{
private:
	RectangleShape shape;		//прямоугольник, т.е. сама кнопка
	Text text;					//наименование кнопки
	Font font;					//шрифт текста

	void draw(RenderTarget& target, RenderStates states) const;		//отрисовка объекта в окне
public:
	Button(string str, Vector2f pos);	//конструктор кнопки
	~Button();		//деструктор кнопки

	void setPosition(float x, float y);		//установка позиции кнопки

	bool mouseCheck(Vector2f mouse);	//true - курсор на кнопке, false - нет
	void updateEvent(bool& gameStarted, bool& gamePaused, bool& gameEnded, Vector2f mouse, Event event);	//обновление событий для кнопки
	void update(bool& gameStarted, bool& gamePaused, bool& gameEnded, Vector2f mouse, Event event);			//обновление кнопки

	bool pressed;	//кнопка нажата

	//ключи для каждой кнопки
	enum btnType
	{
		PLAY,
		CONTINUE,
		NEW_GAME,
		EXIT
	};
};