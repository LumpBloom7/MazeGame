#include "Mazes.hpp"
Coord playerPos = Coord( 0, 0 );
Coord endPos{};
Coord finishPos{};
std::vector<std::vector<char>> parsedMaze;
std::vector<MazeObstacle> teleporters;

void mazeParser( Maze &input ) {
  playerPos = Coord( input.getStartPos().x + 1, input.getStartPos().y + 1 );
  endPos = input.getEndPos();
  std::vector<std::vector<char>> temp;
  // Create play area. Including space for borders.
  for ( int a = 0; a < input.getWidth() + 2; a++ ) {
    std::vector<char> _1{};
    for ( int b = 0; b < input.getHeight() + 2; b++ ) { _1.push_back( ' ' ); }
    temp.push_back( _1 );
  }
  parsedMaze = temp;
  // Create borders.
  for ( int a = 0; a < input.getHeight() + 2; a++ ) {
    parsedMaze[ a ][ 0 ] = '|';
    parsedMaze[ a ][ input.getWidth() + 1 ] = '|';
  }
  for ( int a = 0; a < input.getWidth() + 2; a++ ) {
    parsedMaze[ 0 ][ a ] = '-';
    parsedMaze[ input.getHeight() + 1 ][ a ] = '-';
  }

  // Generate maze using data provided.
  for ( int a = 0; a < input.getMazeInfo().size(); a++ ) {
    for ( int x = input.getMazeInfo()[ a ].getStart().x + 1; x <= input.getMazeInfo()[ a ].getEnd().x + 1; x++ ) {
      for ( int y = input.getMazeInfo()[ a ].getStart().y + 1; y <= input.getMazeInfo()[ a ].getEnd().y + 1; y++ ) {
        if ( input.getMazeInfo()[ a ].getType() == 't' ) { teleporters.push_back( input.getMazeInfo()[ a ] ); }
        parsedMaze[ y ][ x ] = input.getMazeInfo()[ a ].getType();
      }
    }
  }
  // Mark end position
  parsedMaze[ endPos.y ][ endPos.x ] = 'e';
}
void optimizeMaze();
void renderMaze() { // New experimental render system.
  core::clear();
  // Prepare int with console height and width so we do not call the function everytime.
  int consoleHeight = core::console::getConsoleHeight();
  int consoleWidth = core::console::getConsoleWidth();

  // Used to trim off excess areas that exceed the left and top boundaries of console.
  int cutX = 0, cutY = 0;
  if ( playerPos.y / ( consoleHeight / 2 ) > 0 ) {
    cutY = ( ( consoleHeight ) * ( playerPos.y / ( consoleHeight / 2 ) ) ) -
           ( ( consoleHeight ) - ( playerPos.y % ( consoleHeight / 2 ) ) );
  }
  if ( playerPos.x / ( consoleWidth / 2 ) > 0 ) {
    cutX = ( ( consoleWidth / 2 ) * ( playerPos.x / ( consoleWidth / 2 ) ) ) -
           ( ( consoleWidth / 2 ) - ( playerPos.x % ( consoleWidth / 2 ) ) );
  }

  // Render maze with player being at the center of the console
  for ( int o = 0; o < ( consoleHeight / 2 ) - playerPos.y; o++ ) { std::cout << std::endl; }
  for ( int y = 0 + cutY; y < parsedMaze.size() && y < ( consoleHeight / 2 ) + playerPos.y; y++ ) {
    for ( int o = 0; o < ( consoleWidth / 2 ) - playerPos.x; o++ ) { std::cout << ' ' << std::flush; }
    for ( int x = 0 + cutX; x < parsedMaze[ y ].size() && x < ( consoleWidth / 2 ) + playerPos.x - 1; x++ ) {
      if ( playerPos.x == x && playerPos.y == y ) {
        std::cout << "@" << std::flush;
      } else if ( parsedMaze[ y ][ x ] == ' ' ) {
        std::cout << ' ' << std::flush;
      } else {
        std::cout << parsedMaze[ y ][ x ] << std::flush;
      }
    }
    std::cout << std::endl;
  }
}
void renderMaze2() { // Soon to be forgotten..
  core::clear();
  for ( int y = 0; y < parsedMaze.size(); y++ ) {
    for ( int x = 0; x < parsedMaze[ y ].size(); x++ ) {
      if ( playerPos.x == x && playerPos.y == y ) {
        std::cout << "@" << std::flush;
      } else if ( parsedMaze[ y ][ x ] == ' ' ) {
        std::cout << ' ' << std::flush;
      } else {
        std::cout << parsedMaze[ y ][ x ] << std::flush;
      }
    }
    std::cout << std::endl;
  }
}
int mazeGame() {
  renderMaze();
  bool failcheck{};
  while ( true ) {
    core::Keys input = core::getKeyInput();
    if ( input == core::Keys::up && failcheck ) {
      playerPos = moveUp( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }

    } else if ( input == core::Keys::down && failcheck ) {
      playerPos = moveDown( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    } else if ( input == core::Keys::left && failcheck ) {
      playerPos = moveLeft( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    } else if ( input == core::Keys::right && failcheck ) {
      playerPos = moveRight( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    }
    failcheck = true;
  }
}
Coord moveUp( const Coord &playerPos ) {
  if ( playerPos.y == 0 || parsedMaze[ playerPos.y - 1 ][ playerPos.x ] == 'w' ||
       parsedMaze[ playerPos.y - 1 ][ playerPos.x ] == '-' ) {
    return playerPos;
  } else {
    if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 't' ) {
      for ( int a = 0; a < teleporters.size(); a++ ) {
        if ( teleporters[ a ].getStart().x + 1 == playerPos.x && teleporters[ a ].getStart().y + 1 == playerPos.y ) {
          return Coord( teleporters[ a ].getTeleportLocation().x + 1, teleporters[ a ].getTeleportLocation().y + 1 );
        }
      }
    }
    return Coord( playerPos.x, playerPos.y - 1 );
  }
}
Coord moveDown( const Coord &playerPos ) {
  if ( playerPos.y == parsedMaze[ 0 ].size() - 1 || parsedMaze[ playerPos.y + 1 ][ playerPos.x ] == 'w' ||
       parsedMaze[ playerPos.y + 1 ][ playerPos.x ] == '-' ) {
    return playerPos;
  } else {
    if ( parsedMaze[ playerPos.y + 1 ][ playerPos.x ] == 't' ) {
      for ( int a = 0; a < teleporters.size(); a++ ) {
        if ( teleporters[ a ].getStart().x + 1 == playerPos.x &&
             teleporters[ a ].getStart().y + 1 == playerPos.y + 1 ) {
          return Coord( teleporters[ a ].getTeleportLocation().x + 1, teleporters[ a ].getTeleportLocation().y + 1 );
        }
      }
    }
    return Coord( playerPos.x, playerPos.y + 1 );
  }
}
Coord moveLeft( const Coord &playerPos ) {
  if ( playerPos.x == 0 || parsedMaze[ playerPos.y ][ playerPos.x - 1 ] == 'w' ||
       parsedMaze[ playerPos.y ][ playerPos.x - 1 ] == '|' ) {
    return playerPos;
  } else {
    if ( parsedMaze[ playerPos.y ][ playerPos.x - 1 ] == 't' ) {
      for ( int a = 0; a < teleporters.size(); a++ ) {
        if ( teleporters[ a ].getStart().x + 1 == playerPos.x - 1 &&
             teleporters[ a ].getStart().y + 1 == playerPos.y ) {
          return Coord( teleporters[ a ].getTeleportLocation().x + 1, teleporters[ a ].getTeleportLocation().y + 1 );
        }
      }
    }
    return Coord( playerPos.x - 1, playerPos.y );
  }
}
Coord moveRight( const Coord &playerPos ) {
  if ( playerPos.x == parsedMaze.size() - 1 || parsedMaze[ playerPos.y ][ playerPos.x + 1 ] == 'w' ||
       parsedMaze[ playerPos.y ][ playerPos.x + 1 ] == '|' ) {
    return playerPos;
  } else {
    if ( parsedMaze[ playerPos.y ][ playerPos.x + 1 ] == 't' ) {
      for ( int a = 0; a < teleporters.size(); a++ ) {
        if ( teleporters[ a ].getStart().x + 1 == playerPos.x + 1 &&
             teleporters[ a ].getStart().y + 1 == playerPos.y ) {
          return Coord( teleporters[ a ].getTeleportLocation().x + 1, teleporters[ a ].getTeleportLocation().y + 1 );
        }
      }
    }
    return Coord( playerPos.x + 1, playerPos.y );
  }
}
void triggerProcessor( Trigger &trigger ) {
  if ( trigger.getType() == TriggerType::destroy ) {
    for ( int a = trigger.getTargetStart().y + 1; a <= trigger.getTargetEnd().y + 1; a++ ) {
      for ( int b = trigger.getTargetStart().x + 1; b <= trigger.getTargetEnd().x + 1; b++ ) {
        parsedMaze[ a ][ b ] == ' ';
      }
    }
  } else if ( trigger.getType() == TriggerType::create ) {
    for ( int a = trigger.getTargetStart().y + 1; a <= trigger.getTargetEnd().y + 1; a++ ) {
      for ( int b = trigger.getTargetStart().x + 1; b <= trigger.getTargetEnd().x + 1; b++ ) {
        if ( trigger.getCreationObject() == ObstacleType::wall ) {
          parsedMaze[ a ][ b ] == 'w';
        } else if ( trigger.getCreationObject() == ObstacleType::spike ) {
          parsedMaze[ a ][ b ] == 's';
        } else if ( trigger.getCreationObject() == ObstacleType::enemy ) {
          // Add enemy entity.
        }
      }
    }
  } else if ( trigger.getType() == TriggerType::kill ) {
    // Kill target entity.
  }
}
