Geocaching Maze
===============

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6bfb6b47b30a47c29c33a4481190848e)](https://www.codacy.com/app/LumpBloom7/MazeGame?utm_source=github.com&utm_medium=referral&utm_content=LumpBloom7/MazeGame&utm_campaign=badger)

This is a game created as the first challenge for a cache in Geocaching. It is a maze game where the goal is to find the Geocache in the maze while avoiding obstacles and difficulties. There are a total of 10 mazes and a code will be given afterwards for the second challenge.


Latest update
==========

#### 24/07/2017
 * [+] ```core::createMenu()``` now uses switch cases to get key input and do the appropriate stuff.
 * [+] ```getArrowInput()``` had now been renamed to ```getKeyInput()``` to accurately match its actual function.
 * [+] The ```ArrowKeys``` enumerator has been renamed to ```Keys``` because it does not only contain arrowKeys.
 * [+] Fixed ```Trigger::type``` not being initialized in constructors.
 * [+] Fixed up minor code styling inconsistencies.

#### 22/07/2017
 * [+] Made maze controls use the new ```getArrowInput()``` function.

#### 21/07/2017
 * [+] Tidied up core.cpp. All OS specific calls are now in their own independent code files and is appropriately called during compilation.
 * [+] Menus should now work on Linux since the Linux code to get arrow key input is implemented.
 * [+] Arrow key input is now handled by ```core::getArrowInput()```.

 Full changelogs can be found in CHANGELOGS.md
