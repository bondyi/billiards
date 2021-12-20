#pragma once

#include "board.h"
#include "ball.h"
#include "gui.h"

class Game
{
private:
	RenderWindow* window;		//����
	ContextSettings settings;	//���������
	Event sfmlEvent;			//�������

	Vector2f mMouse;			//���������� �������

	void initWindow();			//������������� ����
	void initGame();			//������������� ����

public:
	Game();						//����������� ����
	~Game();					//���������� ����

	Clock clock;				//�����

	Gui* gui;					//������ "���������"
	Board* board;				//������ "����" (+ ����� (������� � ����))
	Ball* blackBall;			//������ "���" (������)
	vector<Ball*> whiteBalls;	//������, ��������� �� �������� "���" (�����)
	Ball* draggedBall;			//������ "��������� ���"

	Line* direction;			//������ "����������� ���� ����� �����"

	bool restartGame;			//���������� ����
	bool dragged;				//��� ������
	bool move;					//���� �������
	bool goal;					//��� ����� � ����

	const bool running() const;		//true - ���� �������, false - �������
	void pollEvents();				//�������

	void collisionCircleLine(Ball* ball, Line* line);		//����������� ������������ "��� - ������"
	void collisionCircles(Ball* ball1, Ball* ball2);		//����������� ������������ "��� - ���"
	void collisionCircleHole(Ball* ball, Line* hole);		//����������� ������������ "��� - ����"

	void updateDirectionLine();			//���������� ������� "����������� ���� ����� �����"
	void updateAllCollisions();			//���������� ����������� ������������
	void updateGameLogic();				//���������� ������ ����
	void restart();						//������� ����������� ����

	void update();						//����� ���� ������� ����������
	void render();						//��������� �������� � ����
};