#include "menu.h"

Menu::Menu()
{
	menuStarted = false;
	menuPaused = false;
	menuEnded = false;

	background.setSize(Vector2f(1024.f, 768.f));
	background.setPosition(0.f, 0.f);
	background.setFillColor(Color(0, 0, 0, 100));

	Button* btnPlay = new Button("PLAY!", Vector2f(412.f, 425.f));
	Button* btnContinue = new Button("CONTINUE", Vector2f(412.f, 325.f));
	Button* btnNewGame = new Button("NEW GAME", Vector2f(412.f, 425.f));
	Button* btnExit = new Button("EXIT", Vector2f(412.f, 525.f));

	buttons.insert(pair<Button::btnType, Button*>(Button::PLAY, btnPlay));
	buttons.insert(pair<Button::btnType, Button*>(Button::CONTINUE, btnContinue));
	buttons.insert(pair<Button::btnType, Button*>(Button::NEW_GAME, btnNewGame));
	buttons.insert(pair<Button::btnType, Button*>(Button::EXIT, btnExit));
}

Menu::~Menu()
{
	buttons.clear();
}

void Menu::update(RenderWindow* window, bool& gameStarted, bool& gamePaused, bool& restartGame, bool& gameEnded, Vector2f mouse, Event event)
{
	menuStarted = gameStarted;
	menuPaused = gamePaused;
	menuEnded = gameEnded;

	for (auto btn : buttons)
	{
		if (btn.second->pressed)
		{
			if(!menuStarted && btn.first == Button::PLAY) gameStarted = true;

			if (menuPaused)
			{
				switch (btn.first)
				{
				case Button::CONTINUE: gamePaused = false; break;
				case Button::NEW_GAME: restartGame = true; break;
				case Button::EXIT: window->close();
				}
			}

			if (menuEnded)
			{
				if (btn.first == Button::NEW_GAME) restartGame = true;
				if (btn.first == Button::EXIT) window->close();
			}
		}
		btn.second->update(gameStarted, gamePaused, gameEnded, mouse, event);
	}
}

void Menu::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(background);
	for (auto btn : buttons)
	{
		if (!menuStarted && btn.first == Button::PLAY) target.draw(*btn.second);

		if (menuPaused)
		{
			switch (btn.first)
			{
			case Button::CONTINUE: target.draw(*btn.second); break;
			case Button::NEW_GAME: target.draw(*btn.second); break;
			case Button::EXIT: target.draw(*btn.second); break;
			}
		}

		if (menuEnded)
		{
			if (btn.first == Button::NEW_GAME) target.draw(*btn.second);
			if (btn.first == Button::EXIT) target.draw(*btn.second);
		}
	}
}