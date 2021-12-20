#pragma once

#include "menu.h"

struct Player
{
	Text numberText;	//имя игрока
	Text pointsText;	//очки игрока

	unsigned short number;	//номер игрока
	unsigned short points;	//очки игрока

	bool goaled;	//игрок забил шар
};

class Gui : public Drawable
{
private:
	Font font;	//шрифт текста

	Text gameVersion;	//версия игры
	Text rules;			//текст правил
	Text winner;		//победитель
	Text score;			//слово "score" (для красоты)

	//объекты структуры Player
	Player player1;
	Player player2;
	Player currentPlayer;

	Menu menu;		//объект класса Menu

	//отрисовка объектов в окне
	void draw(RenderTarget& target, RenderStates states) const;
public:
	Gui();		//конструктор интерфейса
	~Gui();		//деструктор интерфейса

	void setCurrentPlayer(Player player);			//сменить игрока
	void setCurrentPlayer(unsigned short number);	//сменить номер игрока	

	//возвращает игроков
	Player getPlayer1();
	Player getPlayer2();
	Player getCurrentPlayer();

	void addPoints(Player player);	//добавление 1 очка передаваемому игроку
	void setGoal(Player player);	//установка гола передаваемому игроку

	bool gameStarted;		//игра началась
	bool gamePaused;		//игра на паузе
	bool gameEnded;			//игра закончилась

	void restart();			//перезапуск игры

	//обновление интерфейса
	void update(RenderWindow* window, bool& restartGame, Vector2f mouse, Event event);
};