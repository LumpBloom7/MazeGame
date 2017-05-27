class Coord {
	public:
		Coord(int X, int Y)
		{
			x = X;
			y = Y;
		}
		Coord()
		{
			x = 0 + 1;
			y = 0 + 1;
		}
		int x, y;
};
class MazeObstacle {
	public:
		MazeObstacle(char obstacleType, Coord Start, Coord End)
		{
			type = obstacleType;
			start = Start;
			end = End;
		}
		MazeObstacle(Coord Start, Coord End)
		{
			type = 'w';
			start = Start;
			end = End;
		}

		char type; // Could be a wall, trap or something.

		Coord start, end;
};
class Maze {
	public:
		Maze(int Width, int Height, Coord playerStart, Coord playerEnd)
		{
			width = Width;
			height = Height;
			startPos = playerStart;
			endPos = playerEnd;
		}
		Maze()
		{
			width = 10;
			height = 10;
			startPos = Coord(0, 0);
		}
		void addObstacle(char obstacleType, Coord Start, Coord End)
		{
			mazeInfo.push_back(MazeObstacle(obstacleType, Start, End));
		}
		void removeObstable(int obstacleNumber)
		{
		}
		int width, height;
		Coord startPos;
		Coord endPos;
		std::vector<MazeObstacle> mazeInfo{};
};

void optimizeMaze();

void renderMaze();

void mazeParser(Maze input);

int mazeGame(std::vector< std::vector<char> > maze);

Coord moveUp(Coord playerPos);

Coord moveDown(Coord playerPos);

Coord moveLeft(Coord playerPos);

Coord moveRight(Coord playerPos);
