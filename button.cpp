#include "button.h"

void Button::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(shape);
	target.draw(text);
}

Button::Button(string str, Vector2f pos)
{
	shape.setPosition(pos);
	shape.setSize(Vector2f(200.f, 50.f));
	shape.setFillColor(Color(0, 0, 0, 150));

	font.loadFromFile("resources/fonts/relica_regular.ttf");
	text.setFont(font);
	text.setCharacterSize(30);
	text.setString(str);
	text.setPosition(Vector2f(
		shape.getPosition().x + (shape.getLocalBounds().width / 2.f - text.getLocalBounds().width / 2.f),
		shape.getPosition().y + (shape.getLocalBounds().height / 1.75f - text.getLocalBounds().height)));
	pressed = false;
}

Button::~Button() {}

void Button::setPosition(float x, float y)
{
	shape.setPosition(x, y);
	text.setPosition(shape.getPosition().x + 10.f, shape.getPosition().y + 10.f);
}

bool Button::mouseCheck(Vector2f mouse)
{
	if (shape.getGlobalBounds().left <= mouse.x &&
		mouse.x <= (shape.getGlobalBounds().left + shape.getGlobalBounds().width) &&
		shape.getGlobalBounds().top <= mouse.y &&
		mouse.y <= (shape.getGlobalBounds().top + shape.getGlobalBounds().height))
	{
		shape.setFillColor(Color(0, 90, 170, 180));
		return true;
	}

	shape.setFillColor(Color(0, 0, 0, 150));
	return false;
}

void Button::updateEvent(bool& gameStarted, bool& gamePaused, bool& gameEnded, Vector2f mouse, Event event)
{
	if (!gameStarted || gamePaused || gameEnded)
	{
		if (event.mouseButton.button == Mouse::Left && mouseCheck(mouse))
		{
			if (event.type == Event::MouseButtonPressed) pressed = true;
			if (event.type == Event::MouseButtonReleased) pressed = false;
		}
	}
	else pressed = false;
}

void Button::update(bool& gameStarted, bool& gamePaused, bool& gameEnded, Vector2f mouse, Event event)
{
	mouseCheck(mouse);
	updateEvent(gameStarted, gamePaused, gameEnded, mouse, event);
}