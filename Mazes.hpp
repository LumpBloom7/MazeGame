// Class created to handle xy coordinates in a more practical manner.
class Coord {
public:
  Coord( const int &X, const int &Y ) : x( X ), y( Y ) {}
  Coord() {}

  // Since the maze reads maze coordinates from the top left, it is pointless to compare reverse scenarios.
  bool operator>( const Coord &b ) {
    if ( ( this->x > b.x ) && ( this->y > b.y ) ) {
      return true;
    } else {
      return false;
    }
  }
  bool operator>=( const Coord &b ) {
    if ( ( this->x >= b.x ) && ( this->y >= b.y ) ) {
      return true;
    } else {
      return false;
    }
  }
  bool operator<( const Coord &b ) {
    if ( ( this->x < b.x ) && ( this->y < b.y ) ) {
      return true;
    } else {
      return false;
    }
  }
  bool operator<=( const Coord &b ) {
    if ( ( this->x <= b.x ) && ( this->y <= b.y ) ) {
      return true;
    } else {
      return false;
    }
  }
  bool operator==( const Coord &b ) {
    if ( ( this->x == b.x ) && ( this->y == b.y ) ) {
      return true;
    } else {
      return false;
    }
  }
  Coord operator-( const Coord &b ) {
    Coord temp;
    temp.x = this->x - b.x;
    temp.y = this->x - b.y;
    return temp;
  }
  Coord operator-( const int b ) {
    Coord temp;
    temp.x = this->x - b;
    temp.y = this->x - b;
    return temp;
  }
  Coord operator+( const Coord &b ) {
    Coord temp;
    temp.x = this->x + b.x;
    temp.y = this->x + b.y;
    return temp;
  }
  Coord operator+( const int b ) {
    Coord temp;
    temp.x = this->x + b;
    temp.y = this->x + b;
    return temp;
  }
  Coord operator++() {
    Coord temp;
    temp.x = this->x + 1;
    temp.y = this->y + 1;
    return temp;
  }
  Coord operator--() {
    Coord temp;
    temp.x = this->x + 1;
    temp.y = this->y + 1;
    return temp;
  }
  int x, y;
};
enum ObstacleType { wall = 0, spike = 1, enemy = 2 };
enum TriggerType { destroy = 0, create = 1, deactivate = 2, activate = 3, kill = 4 };

// Class to represent Special triggers used in the maze, for stuff like opening/closing doors, moving walls etc.
class Trigger {
public:
  // Constructors
  Trigger( const TriggerType &triggerType, const Coord &start, const Coord &end, const Coord &targetStart,
           const Coord &targetEnd )
      : type( triggerType ), triggerCoordStart( start ), triggerCoordEnd( end ), targetCoordStart( targetStart ),
        targetCoordEnd( targetEnd ) {}
  Trigger( const TriggerType &triggerType, const Coord &start, const Coord &end, const Coord &targetStart,
           const Coord &targetEnd, const bool &pushActivation )
      : type( triggerType ), triggerCoordStart( start ), triggerCoordEnd( end ), targetCoordStart( targetStart ),
        targetCoordEnd( targetEnd ), pushToActivate( pushActivation ) {}
  Trigger( const TriggerType &triggerType, const Coord &start, const Coord &end, const Coord &targetStart,
           const Coord &targetEnd, const bool &pushActivation, const bool &toggleable )
      : type( triggerType ), triggerCoordStart( start ), triggerCoordEnd( end ), targetCoordStart( targetStart ),
        targetCoordEnd( targetEnd ), pushToActivate( pushActivation ), toggle( toggleable ) {}
  Trigger( const TriggerType &triggerType, const Coord &start, const Coord &end, const Coord &targetStart,
           const Coord &targetEnd, const ObstacleType &create )
      : type( triggerType ), triggerCoordStart( start ), triggerCoordEnd( end ), targetCoordStart( targetStart ),
        targetCoordEnd( targetEnd ), creationObject( create ) {}
  Trigger( const TriggerType &triggerType, const Coord &start, const Coord &end, const Coord &targetStart,
           const Coord &targetEnd, const ObstacleType &create, const bool &pushActivation )
      : type( triggerType ), triggerCoordStart( start ), triggerCoordEnd( end ), targetCoordStart( targetStart ),
        targetCoordEnd( targetEnd ), creationObject( create ), pushToActivate( pushActivation ) {}
  Trigger( const TriggerType &triggerType, const Coord &start, const Coord &end, const Coord &targetStart,
           const Coord &targetEnd, const ObstacleType &create, const bool &pushActivation, const bool &toggleable )
      : type( triggerType ), triggerCoordStart( start ), triggerCoordEnd( end ), targetCoordStart( targetStart ),
        targetCoordEnd( targetEnd ), creationObject( create ), pushToActivate( pushActivation ), toggle( toggleable ) {}

  Coord getTriggerStart() { return triggerCoordStart; }
  Coord getTriggerEnd() { return triggerCoordEnd; }
  Coord getTargetStart() { return targetCoordStart; }
  Coord getTargetEnd() { return targetCoordEnd; }
  TriggerType getType() { return type; }
  ObstacleType getCreationObject() { return creationObject; }
  bool isPushActivate() { return pushToActivate; }
  bool isToggleable() { return toggle; }
  bool isActivated() { return activated; }

private:
  TriggerType type;
  ObstacleType creationObject;
  Coord targetCoordStart, targetCoordEnd;
  Coord triggerCoordStart, triggerCoordEnd;
  bool pushToActivate;
  bool toggle;
  bool activated;
};

// Class to represent obstacles that can be encountered in the maze, like walls, traps etc. Does not include entities
// like monsters and items.
class MazeObstacle {
public:
  // Constructors
  MazeObstacle( const char &Type, const Coord &Start, const Coord &End ) : start( Start ), end( End ), type( Type ) {}
  MazeObstacle( const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation )
      : start( Start ), end( End ), type( Type ), telLoc( teleportLocation ) {}
  MazeObstacle( const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation,
                const bool &oneTimeUse )
      : start( Start ), end( End ), type( Type ), telLoc( teleportLocation ), singleUse( oneTimeUse ) {}

  char getType() { return type; }
  Coord getStart() { return start; }
  Coord getEnd() { return end; }
  Coord getTeleportLocation() { return telLoc; }

private:
  char type; // Could be a wall, trap or something.

  Coord start, end;
  bool singleUse = false;
  Coord telLoc;
};

// Class to handle the maze.
class Maze {
private:
  int width, height;
  Coord startPos;
  Coord endPos;
  std::vector<MazeObstacle> mazeInfo{};

public:
  // Constructors
  Maze() : width( 10 ), height( 10 ), startPos( Coord( 0, 0 ) ) {}
  Maze( const int &Width, const int &Height, const Coord &playerStart, const Coord &playerEnd )
      : width( Width ), height( Height ), startPos( playerStart ), endPos( playerEnd ) {}

  // Add generic obstacle to maze
  void addObstacle( const char &Type, const Coord &Start, const Coord &End ) {
    mazeInfo.push_back( MazeObstacle( Type, Start, End ) );
  }
  void addObstacle( const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation ) {
    mazeInfo.push_back( MazeObstacle( Type, Start, End, teleportLocation ) );
  }
  void addObstacle( const char &Type, const Coord &Start, const Coord &End, const Coord &teleportLocation,
                    const bool &oneTimeUse ) {
    mazeInfo.push_back( MazeObstacle( Type, Start, End, teleportLocation, oneTimeUse ) );
  }
  int getWidth() { return width; }
  int getHeight() { return height; }
  Coord getStartPos() { return startPos; }
  Coord getEndPos() { return endPos; }
  std::vector<MazeObstacle> getMazeInfo() { return mazeInfo; }
  void showWalkthrough() {
    int a, b, c, d;
    // a = move
  }
};

class Enemy {
public:
  Enemy() : position( 0, 0 ) {}
  Enemy( Coord &Position ) : position( Position.x, Position.y ) {}
  Enemy( Coord &Position, int &Health ) : position( Position ), health( Health ) {}
  Enemy( Coord &Position, bool &playerSpotted ) : position( Position ), seenPlayer( playerSpotted ) {}
  Enemy( Coord &Position, int &Health, bool &playerSpotted )
      : position( Position ), health( Health ), seenPlayer( playerSpotted ) {}
  /*void solvemaze() { // Make the move (if it's wrong, we will backtrack later.
    Maze[ Y ][ X ] = SomeDude;

    // If you want progressive update, uncomment these lines...
    // PrintDaMaze();
    // Sleep(50);

    // Check if we have reached our goal.
    if ( X == EndingPoint.X && Y == EndingPoint.Y ) { return true; }

    // Recursively search for our goal.
    if ( X > 0 && Maze[ Y ][ X - 1 ] == Free && Solve( X - 1, Y ) ) { return true; }
    if ( X < MazeWidth && Maze[ Y ][ X + 1 ] == Free && Solve( X + 1, Y ) ) { return true; }
    if ( Y > 0 && Maze[ Y - 1 ][ X ] == Free && Solve( X, Y - 1 ) ) { return true; }
    if ( Y < MazeHeight && Maze[ Y + 1 ][ X ] == Free && Solve( X, Y + 1 ) ) { return true; }

    // Otherwise we need to backtrack and find another solution.
    Maze[ Y ][ X ] = Free;
    // If you want progressive update, uncomment these lines...
    // PrintDaMaze();
    // Sleep(50);
    return false;
  }*/

private:
  Coord position;
  int health = 100;
  int damageMultiplier = 1;
  int defenseMultiplier = 1;
  bool seenPlayer = false;
};
class PathfindingMap {};

void optimizeMaze();

void renderMaze(); // Prints the maze generated.

void mazeParser( Maze &input ); // Used to turn maze infomation from human readable to machine readable format.

int mazeGame(); // Main handler for user activities.

Coord moveUp( const Coord &playerPos );
Coord moveDown( const Coord &playerPos );
Coord moveLeft( const Coord &playerPos );
Coord moveRight( const Coord &playerPos );

void triggerProcessor( Trigger &trigger );
