// Class created to handle xy coordinates in a more practical manner.
class Coord {
	public:
		Coord(const int &X,const int &Y): x(X), y(Y) {}
		Coord() {}
		int x, y;

		// Since the maze reads maze coordinates from the top left, it is pointless to compare reverse scenarios.
		bool operator>(const Coord &b)
		{
			if((this->x > b.x) && (this->y > b.y)) {
				return true;
			} else {
				return false;
			}
		}
		bool operator>=(const Coord &b)
		{
			if((this->x >= b.x) && (this->y >= b.y)) {
				return true;
			} else {
				return false;
			}
		}
		bool operator<(const Coord &b)
		{
			if((this->x < b.x) && (this->y < b.y)) {
				return true;
			} else {
				return false;
			}
		}
		bool operator<=(const Coord &b)
		{
			if((this->x <= b.x) && (this->y <= b.y)) {
				return true;
			} else {
				return false;
			}
		}
		bool operator==(const Coord &b)
		{
			if((this->x == b.x) && (this->y == b.y)) {
				return true;
			} else {
				return false;
			}
		}
		Coord operator-(const Coord &b)
		{
			Coord temp;
			temp.x = this->x - b.x;
			temp.y = this->x - b.y;
			return temp;
		}
		Coord operator-(const int b)
		{
			Coord temp;
			temp.x = this->x - b;
			temp.y = this->x - b;
			return temp;
		}
		Coord operator+(const Coord &b)
		{
			Coord temp;
			temp.x = this->x + b.x;
			temp.y = this->x + b.y;
			return temp;
		}
		Coord operator+(const int b)
		{
			Coord temp;
			temp.x = this->x + b;
			temp.y = this->x + b;
			return temp;
		}

};

enum TriggerType {
	destroy = 0,
	create = 1,
	deactivate = 2,
	activate = 3,
	kill = 4
};

// Class to represent Special triggers used in the maze, for stuff like opening/closing doors, moving walls etc.
class Trigger {
		// Constructors
		Trigger(const Coord &start, const Coord &end, const Coord &targetStart, const Coord &targetEnd) : triggerCoordStart(start), triggerCoordEnd(end), targetCoordStart(targetStart), targetCoordEnd(targetEnd) {}
		Trigger(const Coord &start, const Coord &end, const Coord &targetStart, const Coord &targetEnd, const bool &pushActivation) : triggerCoordStart(start), triggerCoordEnd(end), targetCoordStart(targetStart), targetCoordEnd(targetEnd), pushToActivate(pushActivation) {}
		Trigger(const Coord &start, const Coord &end, const Coord &targetStart, const Coord &targetEnd, const bool &pushActivation, const bool &toggleable) : triggerCoordStart(start), triggerCoordEnd(end), targetCoordStart(targetStart), targetCoordEnd(targetEnd), pushToActivate(pushActivation), toggle(toggleable) {}

		Coord getTriggerStart()
		{
			return triggerCoordStart;
		}
		Coord getTriggerEnd()
		{
			return triggerCoordEnd;
		}
		Coord getTargetStart()
		{
			return targetCoordStart;
		}
		Coord getTargetEnd()
		{
			return targetCoordEnd;
		}
		TriggerType getType()
		{
			return type;
		}
		bool isPushActivate()
		{
			return pushToActivate;
		}
		bool isToggleable()
		{
			return toggle;
		}
		bool isActivated()
		{
			return activated;
		}
	private:
		TriggerType type;
		Coord targetCoordStart, targetCoordEnd;
		Coord triggerCoordStart, triggerCoordEnd;
		bool pushToActivate;
		bool toggle;
		bool activated;
};

// Class to represent obstacles that can be encountered in the maze, like walls, traps etc. Does not include entities like monsters and items.
class MazeObstacle {
	public:
		// Constructors
		MazeObstacle(const char &Type, const Coord &Start, const Coord &End) : start(Start), end(End), type(Type) {}
		MazeObstacle(const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation) : start(Start), end(End), type(Type), telLoc(teleportLocation) {}
		MazeObstacle(const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation, const bool &oneTimeUse) : start(Start), end(End), type(Type), telLoc(teleportLocation), singleUse(oneTimeUse) {}

		char getType()
		{
			return type;
		}
		Coord getStart()
		{
			return start;
		}
		Coord getEnd()
		{
			return end;
		}
		Coord getTeleportLocation()
		{
			return telLoc;
		}
	private:
		char type; // Could be a wall, trap or something.

		Coord start, end;
		bool singleUse = false;
		Coord telLoc;
};

//Class to handle the maze.
class Maze {
	private:
		int width, height;
		Coord startPos;
		Coord endPos;
		std::vector<MazeObstacle> mazeInfo{};
	public:
		// Constructors
		Maze(): width(10), height(10), startPos(Coord(0, 0)) {}
		Maze(const int &Width, const int &Height, const Coord &playerStart, const Coord &playerEnd) : width(Width), height(Height), startPos(playerStart), endPos(playerEnd) {}

		// Add generic obstacle to maze
		void addObstacle(const char &Type, const Coord &Start, const Coord &End)
		{
			mazeInfo.push_back(MazeObstacle(Type, Start, End));
		}
		void addObstacle(const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation)
		{
			mazeInfo.push_back(MazeObstacle(Type, Start, End, teleportLocation));
		}
		void addObstacle(const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation, const bool &oneTimeUse)
		{
			mazeInfo.push_back(MazeObstacle(Type, Start, End, teleportLocation, oneTimeUse));
		}
		int getWidth()
		{
			return width;
		}
		int getHeight()
		{
			return height;
		}
		Coord getStartPos()
		{
			return startPos;
		}
		Coord getEndPos()
		{
			return endPos;
		}
		std::vector<MazeObstacle> getMazeInfo()
		{
			return mazeInfo;
		}

};

void optimizeMaze();

void renderMaze(); // Prints the maze generated.

void mazeParser(Maze &input); // Used to turn maze infomation from human readable to machine readable format.

int mazeGame(); // Main handler for user activities.

Coord moveUp(const Coord &playerPos);

Coord moveDown(const Coord &playerPos);

Coord moveLeft(const Coord &playerPos);

Coord moveRight(const Coord &playerPos);