#include "board.h"

void Board::initBoard()
{
	//загрузка изображения бильярдного стола из файла "boardTexture.png"
	boardTexture.loadFromFile("resources/images/boardTexture.png");

	//добавление текстуры в спрайт
	boardSprite.setTexture(boardTexture);

	//изменение центра спрайта
	boardSprite.setOrigin(425.f, 227.5f);

	//перемещение спрайта
	boardSprite.setPosition(512.f, 453.5f);
}

void Board::initLines()
{
	////////////////////БОРДЮРЫ//////////////////////

	Line topLeftL		(117.f, 269.f, 102.f, 254.f);
	Line topLeftR		(115.f, 241.f, 130.f, 256.f);

	Line topLongL		(130.f, 256.f, 495.f, 256.f);

	Line topMidL		(494.f, 256.f, 502.f, 245.f);
	Line topMidR		(521.f, 245.f, 529.f, 256.f);

	Line topLongR		(528.f, 256.f, 894.f, 256.f);

	Line topRightL		(894.f, 256.f, 908.f, 241.f);
	Line topRightR		(921.f, 254.f, 906.f, 269.f);

	Line midLongR		(906.f, 268.f, 906.f, 638.f);

	Line downRightR		(906.f, 637.f, 921.f, 652.f);
	Line downRightL		(908.f, 665.f, 893.f, 650.f);

	Line downLongR		(894.f, 650.f, 527.f, 650.f);

	Line downMidR		(528.f, 650.f, 521.f, 662.f);
	Line downMidL		(502.f, 662.f, 495.f, 650.f);

	Line downLongL		(496.f, 650.f, 130.f, 650.f);

	Line downLeftR		(130.f, 650.f, 115.f, 665.f);
	Line downLeftL		(102.f, 652.f, 117.f, 636.f);

	Line midLongL		(117.f, 637.f, 117.f, 268.f);

	lines.push_back(topLeftL);
	lines.push_back(topLeftR);
	lines.push_back(topLongL);
	lines.push_back(topMidL);
	lines.push_back(topMidR);
	lines.push_back(topLongR);
	lines.push_back(topRightL);
	lines.push_back(topRightR);
	lines.push_back(midLongR);
	lines.push_back(downRightR);
	lines.push_back(downRightL);
	lines.push_back(downLongR);
	lines.push_back(downMidR);
	lines.push_back(downMidL);
	lines.push_back(downLongL);
	lines.push_back(downLeftR);
	lines.push_back(downLeftL);
	lines.push_back(midLongL);

	///////////////////////ЛУЗЫ///////////////////////

	Line topLeftHole	(102.f, 254.f, 115.f, 241.f);
	Line topMidHole		(502.f, 247.5f, 521.f, 247.5f);
	Line topRightHole	(908.f, 241.f, 921.f, 254.f);
	Line downRightHole	(921.f, 652.f, 908.f, 665.f);
	Line downMidHole	(521.f, 659.5f, 502.f, 659.5f);
	Line downLeftHole	(115.f, 665.f, 102.f, 652.f);

	holes.push_back(topLeftHole);
	holes.push_back(topMidHole);
	holes.push_back(topRightHole);
	holes.push_back(downRightHole);
	holes.push_back(downMidHole);
	holes.push_back(downLeftHole);
}

Board::Board()
{
	initBoard();
	initLines();
}

Board::~Board()
{
	lines.clear();
	holes.clear();
}

vector<Line> Board::getBorderLines()
{
	return lines;
}

vector<Line> Board::getHolesLines()
{
	return holes;
}

void Board::render(RenderTarget* target)
{
	target->draw(boardSprite);
	for (auto i : lines) target->draw(i);
	for (auto i : holes) target->draw(i);
}