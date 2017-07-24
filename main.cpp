#include <iostream> // For IO functionality
#include <vector>   // For Vector functionality
#include <memory>   // For memory management, includes std::shared_ptr and std::unique_ptr
#include <string>   // For string variable

#include "termcolor.hpp" // This header contains the functionality of adding colors to 'std::cout'.
#include "player.hpp"    // This header contains the namespace used to store player data and progress.
#include "core.cpp"      // This header contains the core functionality of the game engine.
#include "Mazes.cpp"

void newGame(), continueGame(), showInstructions(), workInProgress(), errorMessage(), debugMode();
int main() {
  std::vector<std::string> a{"1. New game", "2. Continue", "3. Instruction", "4. Geocache URL", "5. Quit", "6. Debug"};
  int response = core::createMenu( "Main menu", a, false );
  switch ( response ) {
  case 0: newGame(); break;
  case 1: continueGame(); break;
  case 2: showInstructions(); break;
  case 3:
    workInProgress();
    break; // Add webpage redirect here.
  case 4: exit( 0 ); break;
  case 5: debugMode(); break;
  default: errorMessage(); break;
  }
}
void workInProgress() {
  std::cout << termcolor::cyan << "Sorry, but this area is still a work in progress. Please check back soon. :)"
            << std::endl;
  std::cin.ignore();
  main();
}
void newGame() {
  // Execute gameplay
  workInProgress();
  std::cin.ignore();
}
void continueGame() {
  // Execute gameplay, but put them back where they left off.
  workInProgress();
  std::cin.ignore();
}
void showInstructions() {
  core::clear();
  std::cout << termcolor::underline << "Instructions" << termcolor::reset << std::endl
            << "The goal of this game is to find the hidden box within the maze thats given. There are 10 mazes total, "
               "each one increasing the difficulty level."
            << std::endl
            << "To make things harder, you're field of vision is limited. On the first level you get to see an area "
               "with a radius of 25, with your character being in the center. And for every level after, the radius is "
               "reduced by 2 units"
            << std::endl
            << "You may encounter bonus items which may give you an advantage depending on how you use it. Timing is "
               "crucial when using the bonuses or you will not benefit from it. You may only carry 1 bonus at a time "
               "and any bonus item you are carrying while passing over another will be overwritten."
            << std::endl
            << "After completing all the levels, you will get a 10 digit pin to unlock the next challenge. Good luck "
               "and have fun. :)"
            << std::endl;
  std::cin.ignore();
  main();
}

void errorMessage() {
  std::cout << termcolor::blink << termcolor::red
            << "Sorry. The developer has screwed up. Please contact the Geocache owner with details of this incident. "
               "Thank you for your cooperation."
            << termcolor::reset << std::endl;
  std::cin.ignore();
  main();
}
void debugMode() {
  core::clear();
  Maze test = Maze( 10, 10, Coord( 0, 0 ), Coord( 3, 6 ) );
  test.addObstacle( 'w', Coord( 1, 2 ), Coord( 1, 4 ) );
  test.addObstacle( 'w', Coord( 4, 0 ), Coord( 4, 4 ) );
  test.addObstacle( 'w', Coord( 3, 2 ), Coord( 3, 3 ) );
  test.addObstacle( 't', Coord( 1, 2 ), Coord( 1, 2 ), Coord( 5, 5 ) );
  mazeParser( test );
  mazeGame();
  std::cin.ignore();
  std::cin.ignore();
  std::cout << termcolor::reset;
  main();
}
