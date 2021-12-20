#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Line: public Drawable, Transformable
{
private:
	//координаты начала и конца линии
	VertexArray points;
	//цвет линии
	Color color;

	//функция отрисовки объекта в окне
	void draw(RenderTarget& target, RenderStates states) const;
public:
	//конструктор линии
	Line(float x1, float y1, float x2, float y2, Color color = Color::White);
	//деструктор линии
	~Line();

	//функция возвращает координаты начала и конца линии
	VertexArray getPoints();
};
