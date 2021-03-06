#include "Mazes.hpp"
Coord playerPos = Coord( 0, 0 );
Coord endPos{};
Coord finishPos{};
std::vector<std::vector<char>> parsedMaze;
std::vector<MazeObstacle> teleporters;
std::vector<Direction> record;

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
    parsedMaze[ a ][ 0 ] = 'w';
    parsedMaze[ a ][ input.getWidth() + 1 ] = 'w';
  }
  for ( int a = 0; a < input.getWidth() + 2; a++ ) {
    parsedMaze[ 0 ][ a ] = 'w';
    parsedMaze[ input.getHeight() + 1 ][ a ] = 'w';
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
void renderMaze() { // New experimental render system. So far renders one extra
		    // line on 1366x768 resolution
  core::clear();
  // Prepare int with console height and width so we do not call the function everytime.
  int halfHeight = core::console::getConsoleHeight() / 2;
  int halfWidth = core::console::getConsoleWidth() / 2;

  // Used to trim off excess areas that exceed the left and top boundaries of console.
  int cutX = 0, cutY = 0;
  if ( playerPos.y / ( halfHeight ) > 0 ) {
    cutY = ( ( halfHeight ) * ( playerPos.y / halfHeight ) ) - ( ( halfHeight ) - ( playerPos.y % halfHeight ) );
  }
  if ( playerPos.x / ( halfWidth ) > 0 ) {
    cutX = ( ( halfWidth ) * ( playerPos.x / halfWidth ) ) - ( ( halfWidth ) - ( playerPos.x % halfWidth ) );
  }

  // Render maze with player being at the center of the console
  for ( int o = 0; o < (halfHeight)-playerPos.y; o++ ) { std::cout << std::endl; }
  for ( int y = 0 + cutY; y < parsedMaze.size() && y < ( halfHeight ) + playerPos.y; y++ ) {

    for ( int o = 0; o < (halfWidth)-playerPos.x; o++ ) { std::cout << ' ' << std::flush; }
    for ( int x = 0 + cutX; x < parsedMaze[ y ].size() && x < ( halfWidth ) + playerPos.x - 1; x++ ) {
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
void demoPlayback() {
  renderMaze();
  if ( core::filesystem::fileExists( "demo.json" ) ) {
    std::ifstream is( "demo.json" );
    cereal::JSONInputArchive archive( is );
    archive( record );
    for ( int a = 0; a < record.size(); a++ ) {
      core::sleep( std::chrono::milliseconds( 100 ) );
      if ( record[ a ] == Direction::up ) {
        playerPos = moveUp( playerPos );
        renderMaze();
        if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
          std::cout << termcolor::green << "You win!!!" << std::endl;
          break;
        }
      } else if ( record[ a ] == Direction::down ) {
        playerPos = moveDown( playerPos );
        renderMaze();
        if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
          std::cout << termcolor::green << "You win!!!" << std::endl;
          break;
        }
      } else if ( record[ a ] == Direction::left ) {
        playerPos = moveLeft( playerPos );
        renderMaze();
        if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
          std::cout << termcolor::green << "You win!!!" << std::endl;
          break;
        }
      } else if ( record[ a ] == Direction::right ) {
        playerPos = moveRight( playerPos );
        renderMaze();
        if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
          std::cout << termcolor::green << "You win!!!" << std::endl;
          break;
        }
      }

      if ( a == record.size() - 1 ) {
        std::cout << "Demo playback complete" << std::endl;
        core::pause();
      }
    }
  }
}
int mazeGame() {
  record = {};
  renderMaze();
  bool failcheck{};
  while ( true ) {
    core::Keys input = core::getKeyInput();
    if ( input == core::Keys::up && failcheck ) {
      record.push_back( Direction::up );
      playerPos = moveUp( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    } else if ( input == core::Keys::down && failcheck ) {
      record.push_back( Direction::down );
      playerPos = moveDown( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    } else if ( input == core::Keys::left && failcheck ) {
      record.push_back( Direction::left );
      playerPos = moveLeft( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    } else if ( input == core::Keys::right && failcheck ) {
      record.push_back( Direction::right );
      playerPos = moveRight( playerPos );
      renderMaze();
      if ( parsedMaze[ playerPos.y ][ playerPos.x ] == 'e' ) {
        std::cout << termcolor::green << "You win!!!" << std::endl;
        break;
      }
    }
    failcheck = true;
  }
  std::vector<std::string> a{"Yes", "No"};
  int demo = core::createMenu( "Save demo?", a, false );
  if ( demo == 0 ) {
    std::ofstream os( ( "demo.json" ) );
    cereal::JSONOutputArchive archive( os );
    archive( CEREAL_NVP( record ) ); // Names the output the same as the variable name6
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
