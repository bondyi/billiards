#pragma once

#include <iostream>
#include <cmath>

#include "line.h"

using namespace std;

const float RADIUS = 8.f;		//радиус
const float MASS = 160.f;		//масса
const float FRICTION = 0.5f;	//коэффициент трения системы "шар - бильярдный стол"

class Ball
{
private:

	CircleShape shape;			//окружность
	Color color;				//цвет

	Vector2f mVelocity;			//вектор скорости
	Vector2f mAcceleration;		//вектор ускорения
	float mAngle;				//угол поворота

	void initVariables();		//инициализиция переменных

public:
	Ball(unsigned short i);		//конструктор шара

	bool move;						//шар движется
	bool collisionCircle_Circle;	//шар столкнулся с другим шаром в текущем ходе
	bool goaled;					//шар забит

	void setPosition(float x, float y);				//присваивание положения
	void setAcceleration(Vector2f acceleration);	//присваивание ускорения
	void setVelocity(Vector2f velocity);			//присваивание скорости

	Vector2f getPosition();			//возвращает положение
	Vector2f getVelocity() const;	//возвращает скорость

	//обновление скорости
	void updateVelocity(float deltaTime);

	//проверка на пересечение курсора и шара
	bool checkCollisionPoint(const Vector2f& mouse);

	void setGoaled();	//шар забит
	bool isGoaled();	//true - шар забит, false - нет

	void render(RenderTarget* target);	//отрисовка объекта в окне
};