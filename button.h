#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Button : public Drawable
{
private:
	RectangleShape shape;		//�������������, �.�. ���� ������
	Text text;					//������������ ������
	Font font;					//����� ������

	void draw(RenderTarget& target, RenderStates states) const;		//��������� ������� � ����
public:
	Button(string str, Vector2f pos);	//����������� ������
	~Button();		//���������� ������

	void setPosition(float x, float y);		//��������� ������� ������

	bool mouseCheck(Vector2f mouse);	//true - ������ �� ������, false - ���
	void updateEvent(bool& gameStarted, bool& gamePaused, bool& gameEnded, Vector2f mouse, Event event);	//���������� ������� ��� ������
	void update(bool& gameStarted, bool& gamePaused, bool& gameEnded, Vector2f mouse, Event event);			//���������� ������

	bool pressed;	//������ ������

	//����� ��� ������ ������
	enum btnType
	{
		PLAY,
		CONTINUE,
		NEW_GAME,
		EXIT
	};
};