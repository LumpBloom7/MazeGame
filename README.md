Geocaching Maze
===============

This is a game created as the first challenge for a cache in Geocaching. It is a maze game where the goal is to find the Geocache in the maze while avoiding obstacles and difficulties. There are a total of 10 mazes and a code will be given afterwards for the second challenge.


Latest update
==========
Full changelogs can be found in CHANGELOGS.md
#### 23/06/2017
 * [+] Code style improvements.

#### 22/06/2017
 * [+] Teleporter mechanics added. Teleporters can be added to the maze via ```MazeObstacle``` class when the type is set to ```'t'```. Maze creators must also specify the teleportLocation in order for the teleporter to function correctly.
 * [+] ```Coord``` class now have basic operators for comparisons and simple maths.
 * [+] Partial implementation of maze triggers, used for buttons or automation within the maze. The implementation can be found in ```Trigger``` class.
 * [+] Added a few comments to help explain the use of each function.
