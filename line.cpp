#include "line.h"

Line::Line(float x1, float y1, float x2, float y2, Color color)
{
	this->color = color;

	//���������� ������ �����
	Vertex start = Vertex(Vector2f(x1, y1), this->color);

	//���������� ����� �����
	Vertex end = Vertex(Vector2f(x2, y2), this->color);

	//������ ����� ����� �������
	points.setPrimitiveType(LineStrip);
	
	//���������� ��������� � ������ 
	points.append(start);
	points.append(end);
}

Line::~Line() 
{ 
	//������� �������
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