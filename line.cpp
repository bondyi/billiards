#include "line.h"

Line::Line(float x1, float y1, float x2, float y2, Color color)
{
	this->color = color;

	//координаты начала линии
	Vertex start = Vertex(Vector2f(x1, y1), this->color);

	//координаты конца линии
	Vertex end = Vertex(Vector2f(x2, y2), this->color);

	//рисует линию между точками
	points.setPrimitiveType(LineStrip);
	
	//добавление координат в массив 
	points.append(start);
	points.append(end);
}

Line::~Line() 
{ 
	//очистка массива
	points.clear();
}

VertexArray Line::getPoints() 
{
	return points;
}

void Line::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(points);
}