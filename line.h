#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Line: public Drawable, Transformable
{
private:
	//���������� ������ � ����� �����
	VertexArray points;
	//���� �����
	Color color;

	//������� ��������� ������� � ����
	void draw(RenderTarget& target, RenderStates states) const;
public:
	//����������� �����
	Line(float x1, float y1, float x2, float y2, Color color = Color::White);
	//���������� �����
	~Line();

	//������� ���������� ���������� ������ � ����� �����
	VertexArray getPoints();
};
