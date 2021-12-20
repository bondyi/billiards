#pragma once

#include <map>

#include "button.h"

class Menu : public Drawable
{
private:
	RectangleShape background;		//���������� ����

	void draw(RenderTarget& target, RenderStates states) const;		//��������� ������� � ����
public:
	Menu();		//����������� ����
	~Menu();	//���������� ����

	bool menuStarted;	//���� ������ ����
	bool menuPaused;	//���� �����
	bool menuEnded;		//���� ����� ����


	map <Button::btnType, Button*> buttons;		//���������, ���������� �������� �������� ������ � �� �����

	//���������� ��������
	void update(RenderWindow* window, bool& gameStarted, bool& gamePaused, bool& restartGame, bool& gameEnded, Vector2f mouse, Event event);
};