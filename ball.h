#pragma once

#include <iostream>
#include <cmath>

#include "line.h"

using namespace std;

const float RADIUS = 8.f;		//������
const float MASS = 160.f;		//�����
const float FRICTION = 0.5f;	//����������� ������ ������� "��� - ���������� ����"

class Ball
{
private:

	CircleShape shape;			//����������
	Color color;				//����

	Vector2f mVelocity;			//������ ��������
	Vector2f mAcceleration;		//������ ���������
	float mAngle;				//���� ��������

	void initVariables();		//������������� ����������

public:
	Ball(unsigned short i);		//����������� ����

	bool move;						//��� ��������
	bool collisionCircle_Circle;	//��� ���������� � ������ ����� � ������� ����
	bool goaled;					//��� �����

	void setPosition(float x, float y);				//������������ ���������
	void setAcceleration(Vector2f acceleration);	//������������ ���������
	void setVelocity(Vector2f velocity);			//������������ ��������

	Vector2f getPosition();			//���������� ���������
	Vector2f getVelocity() const;	//���������� ��������

	//���������� ��������
	void updateVelocity(float deltaTime);

	//�������� �� ����������� ������� � ����
	bool checkCollisionPoint(const Vector2f& mouse);

	void setGoaled();	//��� �����
	bool isGoaled();	//true - ��� �����, false - ���

	void render(RenderTarget* target);	//��������� ������� � ����
};