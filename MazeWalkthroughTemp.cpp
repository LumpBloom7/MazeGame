Coord moveUp( const Coord &playerPos, int length ) {
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
Coord moveDown( const Coord &playerPos, int length ) {
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
Coord moveLeft( const Coord &playerPos, int length ) {
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
Coord moveRight( const Coord &playerPos, int length ) {
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
