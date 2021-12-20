#pragma once

#include "menu.h"

struct Player
{
	Text numberText;	//��� ������
	Text pointsText;	//���� ������

	unsigned short number;	//����� ������
	unsigned short points;	//���� ������

	bool goaled;	//����� ����� ���
};

class Gui : public Drawable
{
private:
	Font font;	//����� ������

	Text gameVersion;	//������ ����
	Text rules;			//����� ������
	Text winner;		//����������
	Text score;			//����� "score" (��� �������)

	//������� ��������� Player
	Player player1;
	Player player2;
	Player currentPlayer;

	Menu menu;		//������ ������ Menu

	//��������� �������� � ����
	void draw(RenderTarget& target, RenderStates states) const;
public:
	Gui();		//����������� ����������
	~Gui();		//���������� ����������

	void setCurrentPlayer(Player player);			//������� ������
	void setCurrentPlayer(unsigned short number);	//������� ����� ������	

	//���������� �������
	Player getPlayer1();
	Player getPlayer2();
	Player getCurrentPlayer();

	void addPoints(Player player);	//���������� 1 ���� ������������� ������
	void setGoal(Player player);	//��������� ���� ������������� ������

	bool gameStarted;		//���� ��������
	bool gamePaused;		//���� �� �����
	bool gameEnded;			//���� �����������

	void restart();			//���������� ����

	//���������� ����������
	void update(RenderWindow* window, bool& restartGame, Vector2f mouse, Event event);
};