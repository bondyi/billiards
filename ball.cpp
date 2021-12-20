#include "ball.h"

void Ball::initVariables()
{
	mVelocity = Vector2f(0.f, 0.f);
	mAcceleration = Vector2f(0.f, 0.f);
	move = false;
	collisionCircle_Circle = false;
	goaled = false;
}

Ball::Ball(unsigned short i)
{
	initVariables();
	i ? shape.setFillColor(Color::White) : shape.setFillColor(Color::Black);
	shape.setRadius(RADIUS);
	shape.setOrigin(RADIUS, RADIUS);
	switch (i)
	{
	case 0:		{ shape.setPosition(300.f, 453.f); break; }

	case 1:		{ shape.setPosition(700.f, 453.f); break; }

	case 2:		{ shape.setPosition(715.f, 444.f); break; }
	case 3:		{ shape.setPosition(715.f, 462.f); break; }

	case 4:		{ shape.setPosition(730.f, 435.f); break; }
	case 5:		{ shape.setPosition(730.f, 453.f); break; }
	case 6:		{ shape.setPosition(730.f, 471.f); break; }

	case 7:		{ shape.setPosition(745.f, 426.f); break; }
	case 8:		{ shape.setPosition(745.f, 444.f); break; }
	case 9:		{ shape.setPosition(745.f, 462.f); break; }
	case 10:	{ shape.setPosition(745.f, 480.f); break; }

	case 11:	{ shape.setPosition(760.f, 417.f); break; }
	case 12:	{ shape.setPosition(760.f, 435.f); break; }
	case 13:	{ shape.setPosition(760.f, 453.f); break; }
	case 14:	{ shape.setPosition(760.f, 471.f); break; }
	case 15:	{ shape.setPosition(760.f, 489.f); break; }
	}
}

void Ball::setPosition(float x, float y)
{
	shape.setPosition(x, y);
}

void Ball::setAcceleration(Vector2f acceleration)
{
	mAcceleration = acceleration;
}

void Ball::setVelocity(Vector2f velocity)
{
	mVelocity = velocity;
}

Vector2f Ball::getPosition()
{
	return shape.getPosition();
}

Vector2f Ball::getVelocity() const
{
	return mVelocity;
}

void Ball::updateVelocity(float deltaTime)
{
	mAcceleration = -mVelocity * FRICTION;
	mVelocity += mAcceleration * deltaTime;

	shape.setPosition(shape.getPosition().x + mVelocity.x * deltaTime, 
					  shape.getPosition().y + mVelocity.y * deltaTime);

	//если скорость крайне мала, шар останавливается
	if (abs(mVelocity.x) < 2.5f && abs(mVelocity.y) < 2.5f)
	{
		mVelocity = Vector2f(0.f, 0.f);
		move = false;
	}
}

bool Ball::checkCollisionPoint(const Vector2f& mouse)
{
	if (pow((mouse.x - shape.getPosition().x), 2) + 
		pow((mouse.y - shape.getPosition().y), 2) <= 
		pow(RADIUS, 2))
		return true;
	else return false;
}

void Ball::setGoaled()
{
	goaled = true;
}

bool Ball::isGoaled()
{
	return goaled;
}

void Ball::render(RenderTarget* target)
{ 
	target->draw(shape);
}