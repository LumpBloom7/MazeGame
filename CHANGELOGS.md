Geocaching Maze changelogs
===========================

#### 02/07/2017
 * [+] Redone code formatting to closely match LLVM style
 * [+] Made it so that the ```Build64.bat``` file also outputs the file with the same name.

#### 23/06/2017
 * [+] Code style improvements.

#### 22/06/2017
 * [+] Teleporter mechanics added. Teleporters can be added to the maze via ```MazeObstacle``` class when the type is set to ```'t'```. Maze creators must also specify the teleportLocation in order for the teleporter to function correctly.
 * [+] ```Coord``` class now have basic operators for comparisons and simple maths.
 * [+] Partial implementation of maze triggers, used for buttons or automation within the maze. The implementation can be found in ```Trigger``` class.
 * [+] Functions will now accept arguments as constant references rather than copying the variable.
 * [+] Added a few comments to help explain the use of each function.


#### 27/05/2017
 * [+] First test maze added. This could be accessed from ```Main menu > Debug mode```
 * [+] Basic controls added.
 * [+] Maze renderer added. This outputs the current state of the maze into the console. Currently uses letters to correspond maze elements.
 * [+] Maze parser added. This parses the ```Maze``` class into a 2D vector for gameplay. 
 * [+] Added the maze framework. The ```Maze``` class is implented in a way which it'll only require the size of the maze and where the obstacles are instead of hard-coding an array for the maze. 

#### 08/05/2017
 * Initial commit