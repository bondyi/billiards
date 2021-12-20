#include "game.h"

void Game::initWindow()
{
	settings.antialiasingLevel = 8;
	window = new RenderWindow(VideoMode(1024, 768), "Billiards", Style::Titlebar, settings);
}

void Game::initGame()
{
	restartGame = false;
	gui = new Gui();
	board = new Board();
	blackBall = new Ball(0);
	for (unsigned short i = 1; i != 16; ++i)
	{
		Ball* newBall = new Ball(i);
		whiteBalls.push_back(newBall);
	}
	dragged = false;
	move = false;
	goal = false;
}

Game::Game()
{
	initWindow();
	initGame();
}

Game::~Game()
{
	delete blackBall;
	whiteBalls.clear();
	delete draggedBall;
	delete board;
	delete direction;
	delete gui;
	delete window;
}

const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while (window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
		case Event::KeyPressed:
			if (sfmlEvent.key.code == Keyboard::Escape)
				if(gui->gameStarted && !gui->gameEnded)
					gui->gamePaused ? gui->gamePaused = false : gui->gamePaused = true;


		case Event::MouseButtonPressed:
			if (sfmlEvent.mouseButton.button == Mouse::Right)
			{
				draggedBall = nullptr;
				dragged = false;
			}

			if (sfmlEvent.mouseButton.button == Mouse::Left)
			{
				if (!move)
				{
					if (gui->gameStarted && !gui->gamePaused & !gui->gameEnded)
					{
						if (blackBall->checkCollisionPoint(mMouse))
						{
							draggedBall = blackBall;
							dragged = true;
						}
						for (auto whiteBall : whiteBalls)
						{
							if (whiteBall->checkCollisionPoint(mMouse))
							{
								draggedBall = whiteBall;
								dragged = true;
							}
						}
					}
				}
			}
			break;

		case Event::MouseButtonReleased:
			if (sfmlEvent.mouseButton.button == Mouse::Left && dragged)
			{
				Vector2f startVelocity = Vector2f(((draggedBall->getPosition().x - mMouse.x) * 1.5),
												  ((draggedBall->getPosition().y - mMouse.y) * 1.5));

				draggedBall->setVelocity(startVelocity);

				draggedBall->move = true;
				dragged = false;
				move = true;
			}
			break;

		case Event::MouseMoved:
			mMouse.x = sfmlEvent.mouseMove.x;
			mMouse.y = sfmlEvent.mouseMove.y;
		}
	}
}

void Game::collisionCircleLine(Ball* ball, Line* line)
{
	Vector2f p = ball->getPosition();				//центр шара
	Vector2f s = line->getPoints()[0].position;		//точка начала линии
	Vector2f e = line->getPoints()[1].position;		//точка конца линии

	Vector2f ps = p - s;	//расстояние между центром шара и точкой начала линии	
	Vector2f se = e - s;	//длина линии

	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);	//длина линии

	float t = ((ps.x * se.x) + (ps.y * se.y)) / lengthLine;		//точка нормали линии

	Vector2f st;
	st.x = s.x + t * se.x;
	st.y = s.y + t * se.y;

	Vector2f distance = p - st;

	float distanceBetween = sqrtf((distance.x * distance.x) + (distance.y * distance.y));

	Vector2f normal = distance / distanceBetween;
	Vector2f tangential = Vector2f(-normal.y, normal.x);

	float dotProductNormal = ball->getVelocity().x * normal.x +
							 ball->getVelocity().y * normal.y;


	float dotProductTangential = ball->getVelocity().x * tangential.x +
								 ball->getVelocity().y * tangential.y;

	float overlap = distanceBetween - RADIUS;

	if (distanceBetween <= RADIUS && (t > -0.f && t < 1.f))
	{
		ball->setPosition(p.x - distance.x * overlap / distanceBetween,
						  p.y - distance.y * overlap / distanceBetween);

		ball->setVelocity(Vector2f(-normal.x * dotProductNormal + tangential.x * dotProductTangential,
								   -normal.y * dotProductNormal + tangential.y * dotProductTangential));
	}
}

void Game::collisionCircles(Ball* ball1, Ball* ball2)
{
	if (ball1 != ball2)
	{
		Vector2f distance = ball1->getPosition() - ball2->getPosition();

		float distanceBetween = (sqrtf((distance.x * distance.x) + (distance.y * distance.y)));

		if (distanceBetween < (RADIUS + RADIUS))
		{
			ball1->move = true;
			ball2->move = true;

			ball1->collisionCircle_Circle = true;
			ball2->collisionCircle_Circle = true;

			float overlap = (distanceBetween - (RADIUS + RADIUS)) / 2.f;

			float moveX = (overlap * (ball1->getPosition().x - ball2->getPosition().x) / distanceBetween);
			float moveY = (overlap * (ball1->getPosition().y - ball2->getPosition().y) / distanceBetween);

			ball1->setPosition(ball1->getPosition().x - moveX, ball1->getPosition().y - moveY);
			ball2->setPosition(ball2->getPosition().x + moveX, ball2->getPosition().y + moveY);

			Vector2f normal;
			normal.x = distance.x / distanceBetween;
			normal.y = distance.y / distanceBetween;

			Vector2f tangential;
			tangential.x = -normal.y;
			tangential.y = normal.x;

			float dotProductTangential1 = ball1->getVelocity().x * tangential.x +
										  ball1->getVelocity().y * tangential.y;

			float dotProductTangential2 = ball2->getVelocity().x * tangential.x +
										  ball2->getVelocity().y * tangential.y;

			float dotProductNormal1 = ball1->getVelocity().x * normal.x + ball1->getVelocity().y * normal.y;
			float dotProductNormal2 = ball2->getVelocity().x * normal.x + ball2->getVelocity().y * normal.y;

			float m1 = (2.f * MASS * dotProductNormal2 + dotProductNormal1) / (MASS + MASS);
			float m2 = (2.f * MASS * dotProductNormal1 + dotProductNormal2) / (MASS + MASS);

			ball1->setVelocity(dotProductTangential1 * tangential + m1 * normal);
			ball2->setVelocity(dotProductTangential2 * tangential + m2 * normal);
		}
	}
}

void Game::collisionCircleHole(Ball* ball, Line* hole)
{
	Vector2f p = ball->getPosition();
	Vector2f s = hole->getPoints()[0].position;
	Vector2f e = hole->getPoints()[1].position;

	Vector2f ps = p - s;
	Vector2f se = e - s;

	float lengthLine = (e.x - s.x) * (e.x - s.x) + (e.y - s.y) * (e.y - s.y);

	float t = ((ps.x * se.x) + (ps.y * se.y)) / lengthLine;

	Vector2f st;
	st.x = s.x + t * se.x;
	st.y = s.y + t * se.y;

	Vector2f distance = p - st;
	float distanceBetween = sqrtf(distance.x * distance.x + distance.y * distance.y);

	if (distanceBetween <= RADIUS && (t > -0.f && t < 1.f))
	{
		if(ball->collisionCircle_Circle) goal = true;
		ball->collisionCircle_Circle = false;
		ball->setGoaled();
		ball->setVelocity(Vector2f(0.f, 0.f));
		ball->move = false;
		ball->setPosition(RADIUS, RADIUS);
	}
}

void Game::updateDirectionLine()
{
	if (dragged)
	{
		Vector2f distance = mMouse - draggedBall->getPosition();
		float distanceBetween = sqrt(distance.x * distance.x + distance.y * distance.y);
		Vector2f invert = distance / distanceBetween;

		Color directionColor = Color(255, (255 - ((int)distanceBetween / 2) % 255), 0);
		if (distanceBetween > 510) directionColor = Color::Red;

		direction = new Line(draggedBall->getPosition().x, draggedBall->getPosition().y,
							 draggedBall->getPosition().x - distanceBetween * invert.x,
							 draggedBall->getPosition().y - distanceBetween * invert.y, directionColor);
	}
}

void Game::restart()
{
	restartGame = false;
	dragged = false;
	move = false;
	goal = false;

	gui->restart();

	blackBall->setPosition(300.f, 453.f);
	blackBall->setVelocity(Vector2f(0.f, 0.f));
	blackBall->move = false;
	blackBall->goaled = false;

	for (unsigned short i = 0; i != 15; ++i)
	{
		switch (i)
		{
		case 0:		{ whiteBalls[i]->setPosition(700.f, 453.f); break; }

		case 1:		{ whiteBalls[i]->setPosition(715.f, 444.f); break; }
		case 2:		{ whiteBalls[i]->setPosition(715.f, 462.f); break; }

		case 3:		{ whiteBalls[i]->setPosition(730.f, 435.f); break; }
		case 4:		{ whiteBalls[i]->setPosition(730.f, 453.f); break; }
		case 5:		{ whiteBalls[i]->setPosition(730.f, 471.f); break; }

		case 6:		{ whiteBalls[i]->setPosition(745.f, 426.f); break; }
		case 7:		{ whiteBalls[i]->setPosition(745.f, 444.f); break; }
		case 8:		{ whiteBalls[i]->setPosition(745.f, 462.f); break; }
		case 9:		{ whiteBalls[i]->setPosition(745.f, 480.f); break; }

		case 10:	{ whiteBalls[i]->setPosition(760.f, 417.f); break; }
		case 11:	{ whiteBalls[i]->setPosition(760.f, 435.f); break; }
		case 12:	{ whiteBalls[i]->setPosition(760.f, 453.f); break; }
		case 13:	{ whiteBalls[i]->setPosition(760.f, 471.f); break; }
		case 14:	{ whiteBalls[i]->setPosition(760.f, 489.f); break; }
		}
		whiteBalls[i]->setVelocity(Vector2f(0.f, 0.f));
		whiteBalls[i]->move = false;
		whiteBalls[i]->goaled = false;
	}
}

void Game::updateAllCollisions()
{
	for (auto whiteBall : whiteBalls)
	{
		if (whiteBall->move || blackBall->move)
		{
			for (Line line : board->getBorderLines())
			{
				if (!whiteBall->isGoaled())
					collisionCircleLine(whiteBall, &line);

				if (!blackBall->isGoaled())
					collisionCircleLine(blackBall, &line);
			}


			for (auto whiteBall2 : whiteBalls)
			{
				if (!whiteBall->isGoaled() && !whiteBall2->isGoaled())
					collisionCircles(whiteBall, whiteBall2);
			}

			if (!blackBall->isGoaled() && !whiteBall->isGoaled())
				collisionCircles(blackBall, whiteBall);


			for (auto hole : board->getHolesLines())
			{
				if (!blackBall->isGoaled())
					collisionCircleHole(blackBall, &hole);

				if (!whiteBall->isGoaled())
					collisionCircleHole(whiteBall, &hole);
			}
		}
	}
}

void Game::updateGameLogic()
{
	bool blackBallStopped = false;
	unsigned short countOfStoppedWhiteBalls = 0;
	unsigned short countOfGoaledBalls = 0;

	if (move && blackBall->getVelocity() == Vector2f(0.f, 0.f)) blackBallStopped = true;

	for (auto ball : whiteBalls) 
		if (move && ball->getVelocity() == Vector2f(0.f, 0.f)) ++countOfStoppedWhiteBalls;

	if (blackBallStopped && countOfStoppedWhiteBalls == 15)
	{
		move = false;

		blackBall->collisionCircle_Circle = false;
		for (auto ball : whiteBalls) ball->collisionCircle_Circle = false;

		if (goal)
		{
			gui->addPoints(gui->getCurrentPlayer());
			goal = false;
		}
		else gui->setCurrentPlayer(1 - gui->getCurrentPlayer().number);

		if (blackBall->isGoaled()) ++countOfGoaledBalls;
		for (auto ball : whiteBalls) if (ball->isGoaled()) ++countOfGoaledBalls;

		if (gui->getPlayer1().points == 8 ||
		gui->getPlayer2().points == 8 ||
		countOfGoaledBalls == 15)
		gui->gameEnded = true;

	}
}

void Game::update()
{
	float deltaTime = 0.f;
	deltaTime = clock.restart().asSeconds();

	pollEvents();

	updateDirectionLine();

	gui->update(window, restartGame, mMouse, sfmlEvent);

	updateGameLogic();

	if (gui->gameStarted && !gui->gamePaused && !gui->gameEnded && move)
	{
		blackBall->updateVelocity(deltaTime);
		for (auto whiteBall : whiteBalls) whiteBall->updateVelocity(deltaTime);

		updateAllCollisions();
	}

	if (restartGame) restart();
}

void Game::render()
{
	window->clear(Color(32, 32, 32));		//графитовый фон

	board->render(window);				//отрисовка бильярдного стола

	if (!blackBall->isGoaled()) 
		blackBall->render(window);		//отрисовка чёрного шара

	for (auto ball : whiteBalls) 
		if (!ball->isGoaled()) 
			ball->render(window);		//отрисовка белых шаров

	window->draw(*gui);							//отрисовка интерфейса

	if (dragged) window->draw(*direction);		//отрисовка направления шара после удара

	window->display();							//отображение объектов в окне
}