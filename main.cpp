#include <iostream> // For IO functionality
#include <vector>   // For Vector functionality
#include <memory>   // For memory management, includes std::shared_ptr and std::unique_ptr
#include <string>   // For string variable

#include "termcolor.hpp" // This header contains the functionality of adding colors to 'std::cout'.
#include "player.hpp"    // This header contains the namespace used to store player data and progress.
#include "core.cpp"      // This header contains the core functionality of the game engine.
#include "Mazes.cpp"

void newGame(), continueGame(), showInstructions(), workInProgress(), errorMessage(), debugMode(), aboutText();
int main() {
  std::vector<std::string> a{"1. New game", "2. Continue", "3. Instruction", "4. Geocache URL",
                             "5. About",    "6. Quit",     "7. Debug"};
  int response = core::createMenu( "Main menu", a, false );
  switch ( response ) {
  case 0: newGame(); break;
  case 1: continueGame(); break;
  case 2: showInstructions(); break;
  case 3: workInProgress(); break;
  case 4: aboutText(); break;
  case 5: exit( 0 ); break;
  case 6: debugMode(); break;
  default: errorMessage(); break;
  }
}
void workInProgress() {
  std::cout << termcolor::cyan << "Sorry, but this area is still a work in progress. Please check back soon. :)"
            << std::endl;
  core::pause();
  main();
}
void newGame() {
  workInProgress();
  core::pause();
}
void continueGame() {
  // Execute gameplay, but put them back where they left off.
  workInProgress();
  core::pause();
}
void showInstructions() {
  core::clear();
  std::cout << termcolor::underline << "Instructions" << termcolor::reset << std::endl
            << "The goal of this game is to find the hidden box within the maze thats given." << std::endl
            << "There are 10 mazes total, each one increasing the difficulty level." << std::endl
            << std::endl
            << "To make things harder, you're field of vision is limited." << std::endl
            << "On the first level you get to see an area with a radius of 25." << std::endl
            << "And for every level after, the radius is reduced by 2 units" << std::endl
            << std::endl
            << "You may encounter bonus items in the maze. " << std::endl
            << "Some of these bonus items may give you an advantage depending on its usage." << std::endl
            << "Timing is crucial when using the bonuses or you may not benefit from it. " << std::endl
            << "Picking up bonus items WILL overwrite any bonus items in storage." << std::endl
            << std::endl
            << "After completing all the levels, you will be able to unlock the next challenge." << std::endl
            << "Good luck and have fun. :)" << std::endl
            << termcolor::reset;
  core::pause();
  main();
}
void aboutText() {
  core::clear();
  std::cout << "About" << std::endl
            << "Software created by: Derrick Timmermans" << std::endl
            << "Mazes designed by: Loong Yuk Hou && Derrick Timmermans" << std::endl
            << "This software is under the MIT License" << std::endl
            << "Source code can be found at https://github.com/LumpBloom7/MazeGame" << std::endl;
  core::pause();
  main();
}
void errorMessage() {
  std::cout << termcolor::blink << termcolor::red << "Sorry. The developer has screwed up." << std::endl
            << "Please contact the Geocache owner with details of this incident." << std::endl
            << "Thank you for your cooperation." << termcolor::reset << std::endl;
  core::pause();
  main();
}
void debugMode() {
  core::clear();
  Maze test = Maze( 10000, 10000, Coord( 0, 0 ), Coord( 3, 6 ) );
  test.addObstacle( 'w', Coord( 1, 2 ), Coord( 1, 4 ) );
  test.addObstacle( 'w', Coord( 4, 0 ), Coord( 4, 4 ) );
  test.addObstacle( 'w', Coord( 3, 2 ), Coord( 3, 3 ) );
  test.addObstacle( 't', Coord( 1, 2 ), Coord( 1, 2 ), Coord( 5, 5 ) );
  mazeParser( test );
  mazeGame();
  core::pause();
  std::cout << termcolor::reset;
  main();
}
