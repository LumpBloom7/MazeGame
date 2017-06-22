#include "Mazes.hpp"
Coord playerPos = Coord(0, 0);
Coord endPos{};
Coord finishPos{};
std::vector<std::vector<char>> parsedMaze;
std::vector<MazeObstacle> teleporters;

void mazeParser(Maze &input)
{
	playerPos = Coord(input.getStartPos().x + 1, input.getStartPos().y + 1);
	endPos = input.getEndPos();
	std::vector<std::vector<char>> temp;
	// Create play area. Including space for borders.
	for (int a = 0; a < input.getWidth() + 2; a++) {
		std::vector<char> _1{};
		for (int b = 0; b < input.getHeight() + 2; b++) {
			_1.push_back(' ');
		}
		temp.push_back(_1);
	}
	parsedMaze = temp;
	// Create borders.
	for (int a = 0; a < input.getHeight() + 2; a++) {
		parsedMaze[a][0] = '|';
		parsedMaze[a][input.getWidth() + 1] = '|';
	}
	for (int a = 0; a < input.getWidth() + 2; a++) {
		parsedMaze[0][a] = '-';
		parsedMaze[input.getHeight() + 1][a] = '-';
	}

	// Generate fancy maze

	// Generate maze using data provided.
	for (int a = 0; a < input.getMazeInfo().size(); a++) {
		for (int x = input.getMazeInfo()[a].getStart().x + 1; x <= input.getMazeInfo()[a].getEnd().x + 1; x++) {
			for (int y = input.getMazeInfo()[a].getStart().y + 1; y <= input.getMazeInfo()[a].getEnd().y + 1; y++) {
				if(input.getMazeInfo()[a].getType() == 't') {
					teleporters.push_back(input.getMazeInfo()[a]);
				}
				parsedMaze[y][x] = input.getMazeInfo()[a].getType();
			}
		}
	}
	// Mark end position
	parsedMaze[endPos.y][endPos.x] = 'e';
}
void optimizeMaze();
void renderMaze()
{
	core::clear();
	for (int y = 0; y < parsedMaze.size(); y++) {
		for (int x = 0; x < parsedMaze[y].size(); x++) {
			if(playerPos.x == x && playerPos.y == y) {
				std::cout << "@" << std::flush;
			} else if(parsedMaze[y][x] == ' ') {
				std::cout << ' ' << std::flush;
			} else {
				std::cout << parsedMaze[y][x] << std::flush;
			}
		}
		std::cout << std::endl;
	}
}
int mazeGame()
{
	renderMaze();
	bool failcheck{};
	while (true) {
		if ((GetAsyncKeyState(VK_UP) & SHRT_MAX) && failcheck) {
			playerPos = moveUp(playerPos);
			renderMaze();
			if (parsedMaze[playerPos.y][playerPos.x] == 'e') {
				std::cout << termcolor::green << "You win!!!" << std::endl;
				break;
			}

		} else if ((GetAsyncKeyState(VK_DOWN) & SHRT_MAX) && failcheck) {
			playerPos = moveDown(playerPos);
			renderMaze();
			if (parsedMaze[playerPos.y][playerPos.x] == 'e') {
				std::cout << termcolor::green << "You win!!!" << std::endl;
				break;
			}
		} else if ((GetAsyncKeyState(VK_LEFT) & SHRT_MAX) && failcheck) {
			playerPos = moveLeft(playerPos);
			renderMaze();
			if (parsedMaze[playerPos.y][playerPos.x] == 'e') {
				std::cout << termcolor::green << "You win!!!" << std::endl;
				break;
			}
		} else if (((GetAsyncKeyState(VK_RIGHT) & SHRT_MAX) && failcheck)) {
			playerPos = moveRight(playerPos);
			renderMaze();
			if (parsedMaze[playerPos.y][playerPos.x] == 'e') {
				std::cout << termcolor::green << "You win!!!" << std::endl;
				break;
			}
		}
		failcheck = true;
	}
}
Coord moveUp(const Coord &playerPos)
{
	if(playerPos.y == 0 || parsedMaze[playerPos.y-1][playerPos.x] == 'w'|| parsedMaze[playerPos.y-1][playerPos.x] == '-')
		return playerPos;
	else {
		if(parsedMaze[playerPos.y][playerPos.x] == 't')
			for (int a = 0; a < teleporters.size(); a++)
				if(teleporters[a].getStart().x+1 == playerPos.x && teleporters[a].getStart().y+1 == playerPos.y)
					return Coord(teleporters[a].getTeleportLocation().x+1, teleporters[a].getTeleportLocation().y+1);
		return Coord(playerPos.x, playerPos.y - 1);

	}
}
Coord moveDown(const Coord &playerPos)
{
	if(playerPos.y == parsedMaze[0].size()-1 || parsedMaze[playerPos.y + 1][playerPos.x] == 'w' || parsedMaze[playerPos.y + 1][playerPos.x] == '-')
		return playerPos;
	else {
		if(parsedMaze[playerPos.y+1][playerPos.x] == 't')
			for (int a = 0; a < teleporters.size(); a++)
				if(teleporters[a].getStart().x+1 == playerPos.x && teleporters[a].getStart().y+1 == playerPos.y+1)
					return Coord(teleporters[a].getTeleportLocation().x+1, teleporters[a].getTeleportLocation().y+1);
		return Coord(playerPos.x, playerPos.y + 1);
	}
}
Coord moveLeft(const Coord &playerPos)
{
	if(playerPos.x == 0 || parsedMaze[playerPos.y][playerPos.x -1] == 'w' || parsedMaze[playerPos.y][playerPos.x -1] == '|')
		return playerPos;
	else {
		if(parsedMaze[playerPos.y][playerPos.x-1] == 't')
			for (int a = 0; a < teleporters.size(); a++)
				if(teleporters[a].getStart().x+1 == playerPos.x-1 && teleporters[a].getStart().y+1 == playerPos.y)
					return Coord(teleporters[a].getTeleportLocation().x+1, teleporters[a].getTeleportLocation().y+1);
		return Coord(playerPos.x - 1, playerPos.y);
	}
}
Coord moveRight(const Coord &playerPos)
{
	if(playerPos.x == parsedMaze.size()-1 || parsedMaze[playerPos.y][playerPos.x +1 ] == 'w' || parsedMaze[playerPos.y][playerPos.x +1 ] == '|')
		return playerPos;
	else {
		if(parsedMaze[playerPos.y][playerPos.x+1] == 't')
			for (int a = 0; a < teleporters.size(); a++)
				if(teleporters[a].getStart().x+1 == playerPos.x+1 && teleporters[a].getStart().y+1 == playerPos.y)
					return Coord(teleporters[a].getTeleportLocation().x+1, teleporters[a].getTeleportLocation().y+1);
		return Coord(playerPos.x + 1, playerPos.y);
	}
}
