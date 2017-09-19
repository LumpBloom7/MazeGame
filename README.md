Geocaching Maze
===============

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6bfb6b47b30a47c29c33a4481190848e)](https://www.codacy.com/app/LumpBloom7/MazeGame?utm_source=github.com&utm_medium=referral&utm_content=LumpBloom7/MazeGame&utm_campaign=badger)

This is a game created as the first challenge for a cache in Geocaching. It is a maze game where the goal is to find the Geocache in the maze while avoiding obstacles and difficulties. There are a total of 10 mazes and a code will be given afterwards for the second challenge.

Changelogs
==========

#### 19/09/2017
 * [+] Added demo recording and demo playback. Can be accessed in the new debug menu.

#### 22/08/2017
 * [+] Fix minor math issue in maze rendering system.

#### 18/08/2017
 * [+] Overhauled maze rendering system. Now it properly renders Mazes with a width and height larger than the console limits. It will also not draw excess areas that exceed console boundaries.
 * [+] Added ```sleep``` function in core.cpp. Used to pause the program for a period of time in seconds and milliseconds.
 * [+] Added about screen.
 * [-] Removed some unused functions in core.cpp
 * [-] Removed unneeded comments.

 Full changelogs can be found in CHANGELOGS.md
