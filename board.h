#pragma once

#include <iostream>
#include <vector>

#include "line.h"

using namespace std;

class Board
{
private:
	//�������� ����������� �����
	Texture boardTexture;

	//������ ����������� �����
	Sprite boardSprite;

	//�������, ��������� �� ������ � ���
	vector<Line> lines;
	vector<Line> holes;

	//������������� ����������� �����
	void initBoard();

	//������������� �����
	void initLines();

public:
	//����������� ����������� �����
	Board();

	//���������� ����������� �����
	~Board();

	//������� ���������� ������ ������ ��� ���
	vector<Line> getBorderLines();
	vector<Line> getHolesLines();

	//��������� ������� � ����
	void render(RenderTarget* target);
};