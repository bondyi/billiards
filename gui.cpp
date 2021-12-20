#include "gui.h"

void Gui::draw(RenderTarget& target, RenderStates states) const
{
	if (!gameStarted)
	{
		target.draw(menu);
		target.draw(rules);
	}
	else if (gamePaused) target.draw(menu);
	else if (gameEnded)
	{
		target.draw(menu);
		target.draw(winner);
	}
	else
	{
		target.draw(score);
		target.draw(player1.numberText);
		target.draw(player1.pointsText);
		target.draw(player2.numberText);
		target.draw(player2.pointsText);
	}
	target.draw(gameVersion);
}

Gui::Gui()
{
	font.loadFromFile("resources/fonts/relica_regular.ttf");

	gameVersion.setFont(font);
	gameVersion.setString("v1.1");
	gameVersion.setFillColor(Color::White);
	gameVersion.setPosition(0, 751);
	gameVersion.setCharacterSize(15);

	rules.setFont(font);
	rules.setString("Welcome to the Billiards game!\n\nTo win, you need to score more points than your opponent.\nA goal is scored only if a ball touches another ball.\n\nControls: to select a ball, hover over it with the cursor, then hold LMB to adjust direction and strength.\nTo hit the ball, release LMB.\nTo undo ball hit, press RMB.\n\nPress ESC to open menu.\n\nGood luck!");
	rules.setPosition(100, 6);
	rules.setCharacterSize(15);

	score.setFont(font);
	score.setString("score");
	score.setFillColor(Color::White);
	score.setPosition(480, 0);
	score.setCharacterSize(20);

	winner.setFont(font);
	winner.setPosition(0, 0);
	winner.setCharacterSize(30);

	player1.points = 0;
	player1.number = 0;
	player1.goaled = false;

	player1.numberText.setFont(font);
	player1.numberText.setString("PLAYER 1");
	player1.numberText.setPosition(275, 10);
	player1.numberText.setCharacterSize(30);

	player1.pointsText.setFont(font);
	player1.pointsText.setPosition(467, 20);
	player1.pointsText.setCharacterSize(50);

	player2.points = 0;
	player2.number = 1;
	player2.goaled = false;

	player2.numberText.setFont(font);
	player2.numberText.setString("PLAYER 2");
	player2.numberText.setPosition(595, 10);
	player2.numberText.setCharacterSize(30);

	player2.pointsText.setFont(font);
	player2.pointsText.setPosition(517, 20);
	player2.pointsText.setCharacterSize(50);

	currentPlayer = player1;

	gameStarted = false;
	gamePaused = false;
	gameEnded = false;
}

Gui::~Gui() {}

void Gui::setCurrentPlayer(Player player)
{
	currentPlayer = player;
}

void Gui::setCurrentPlayer(unsigned short number)
{
	!number ? currentPlayer = player1 : currentPlayer = player2;
}

Player Gui::getPlayer1()
{
	return player1;
}

Player Gui::getPlayer2()
{
	return player2;
}

Player Gui::getCurrentPlayer()
{
	return currentPlayer;
}

void Gui::addPoints(Player player)
{
	!player.number ? ++player1.points : ++player2.points;
}

void Gui::setGoal(Player player)
{
	player.goaled ? player.goaled = false : player.goaled = true;
}

void Gui::restart()
{
	gameEnded = false;
	gamePaused = false;
	gameStarted = true;
	player1.points = 0;
	player2.points = 0;
	currentPlayer = player1;
}

void Gui::update(RenderWindow* window, bool& restartGame, Vector2f mouse, Event event)
{
	player1.numberText.setFillColor(Color::White);
	player1.pointsText.setString(to_string(player1.points));

	player2.numberText.setFillColor(Color::White);
	player2.pointsText.setString(to_string(player2.points));

	if (!currentPlayer.number) player1.numberText.setFillColor(Color::Yellow);
	else player2.numberText.setFillColor(Color::Yellow);

	if (gameEnded)
	{
		player1.points > player2.points ?
			winner.setString("PLAYER 1 WIN!") :
			winner.setString("PLAYER 2 WIN!");

		if (player1.points == player2.points) winner.setString("DRAW!");

		winner.setOrigin(winner.getLocalBounds().width / 2.f, winner.getLocalBounds().height / 2.f);
		winner.setPosition(512, 300);
	}

	menu.update(window, gameStarted, gamePaused, restartGame, gameEnded, mouse, event);
}