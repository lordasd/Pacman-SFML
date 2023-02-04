OOP 1 - Project - Super Pacman(SFML)
-------------------
Name: David Zaydenberg
ID: 319323721
-------------------
Summary:

Super Pacman game built in C++ using SFML.
A game controlled via keyboard arrow keys.
3 levels to pass to win the game.
4 bonuses to pick up on the way:
SuperBonus - Being invincible for 10 seconds and be able to
"kill"(Freeze) ghosts for 4 seconds
(50 points for Super, 20 points for killing ghost).
LifeBonus - Gives one life
TimeBonus - Gives 15 seconds bonus
TimeFreeze - Freezes ghosts for 5 seconds
Avoid ghosts and pick up all cookies(10 points each) to finish a level.

-------------------
Files:

main.cpp - Creating the controller and running it the game.
Controller.cpp/h - Controlls the flow of the game. Run func runs while true and
checks all the gamestates and chooses to run the apropriate function(loop).

GameState.cpp/h -  Has all game state :  Menu, Play, Lost, Win, Exit.
Has a func to return int from enum.

Ui.cpp/h - Has all the UI drawings (Life, Time, Points, Level). Draws them in the 
bottom of the window.

Display.cpp/h - Returns sf::RenderWindow(sf::VideoMode()) of different GameStates
as explained above.

GameObjectFactory.cpp/h - A class that is responsible in it's function to return
a unique pointer to the base class of the character that's provided from the level map.
for each object, it passes a unique texture, calibrates the position on the map and passes it.
Has a static member for door and key id.

GameBoard.cpp/h - Handles opening the files, creating UI object and loading all objects from
the map into an vector of GameObject(Base class). GameBoard prints all the objects on the map.
Any events that are sent from Controller are passed through GameBoard class.

GameObject.cpp.h - Base class of all MovingObjects and StaticObjects.
Has pure virtual functions for handling collisions with objects.
Has 2 constructors: 1) Single sprites(staticobjects), 2) vector of sprites for Movingobjects.
it has the ability the change from normal to scared sprites for the ghosts and back.
Setting colors for the pacman when super and returning to original.

MainMenu.cpp/h - Creates the menu for the game
and loads menuitems(Buttons) to MenuItem class member.
Handles mouse hover above buttons and highlighting them.

MenuItem.cpp/h - Contains the sprite of the item(button)

TextureManager.cpp/h - Singelton class. Loads textures into sf::Texture members and return them
as needed. Holds vectors of moving sprites

SoundManager.cpp/h - Singelton class. Loads sounds for the game and holds them as sf::SoundBuffer.

MovingObjects.cpp/h - Base class for all moving objects like pacman and ghost and has the move 
pure virtual func and the direction of each moving object.

GameCharacter.cpp/h - Has basic information about characters like pacman and ghost(HP)
and apropriate functions for it like die, addlife and decrease life.

Direction.cpp/h - Controlls the direction of the moving object. and has function like
getting the direction and converting direction to vector to move the objects.

Pacman.cpp/h - Is the player. has move override function, draw override function and all 
the functionallity that the player/movingobject should have like collisions with all
objects(Getting bonuses, killing/dying from a ghost...).

PacmanState.h - enum class for the state of pacman (Normal, Super, Dead).

BonusState.h - enum class for the bonus state that is picked up and yet to be activated.
(Super, Life, Time, TimeFreeze, None).

Ghost.cpp/h - Exactly as pacman explaine, but it's controlled by the computer algorithms.
Has all the movement and collision functions. Holding a unique pointer for Behavior class.
Each time the behavior changes, it creates a new unique pointer for the behavior.

Behavior.cpp/h - Base class for behaviors like patrol, chase and frightened. has pure
virtual functions like update and getDirection. It holds the position of pacman and 
current position of the ghost for calculations of the algorithms.

PatrolBehavior.cpp/h - Updates the behavior with patrolling in different random directions
that are changed every between 3-6 seconds.

ChaseBehavior.cpp/h - Chase behavior for chasing pacman when he's near enough (< 200 pixels(4 blocks))
and stop chsing after >= 200 pixels.

FrightenedBehavior.cpp/h - Frightened while pacman is in Super mode. they run away using the same
algorithm for chasing but in the opposite direciton.

StaticObjects.cpp/h - Base class for all staticobjects and they get the apropriate sprite from it.
It has and override getSprite function.

Blank.cpp/h - Just get's created and sends the sprite up to the baseclass GameObject. has draw func.

Wall.cpp/h - Has collision functions and calls the handlecollision of the other objects(Ghost&pacman).

Key.cpp/h - Has unique id for the door it belongs. handleCollision function that unshows the key in the window.
If picked up, a door is opened.

Door.cpp/h - The same as the key, has and id for the key, and if the door is collided with super pacman,
the door is destroyed and the key is dispeard.

Cookie.cpp/h - Pacman collects cookies and the disapear on collision.

Bonus.cpp/h - Has BonusType to controll what bonus it is.

BonusType.h - enum class of bonus types that Bonus class could hold (Super, Life, Time, TimeFreeze)

-------------------
Database:
MovingObject sprites are held in std::vector<sf::Sprite> so each cell is a different direction
(0 - up, 1 - down, 2 - right, 3 - left, 4 - stay)

std::vector<sf::Color> m_origColors - have original colors of pacman so when it changes back from
super to normal, it will have the colors for all the direction sprites

MovingObjects and StaticObjects (Base class - GameObject) are held in two different members:
std::vector<std::unique_ptr<GameObject>> m_staticObjects and m_movingObjects which is located
in GameBoard.

-------------------
Algorithms:

Collision with a wall/Door:
Each time we collide with a wall or a closed door, after detecting the collisions I move my sprite
1 pixel backwards and change the direction to stay, so it will not try going through the wall non-stop.

Slide into tight path algorithm:
We have objects of 50x50 and pacman is 49x49 as well as the ghost is
a bit smaller(30x40), and it's hard to squeeze into tight spaces when turning. So the algorithm calculates
how far are you from the end of the wall texture. If you are < 20 pixels far away it will move you sideways
towards the path, and it will make easy turn into the tight paths. Depending on the direction and where
is the wall(down, up, right, left to you). we calculate half of the sprite which is 25.f, and we add or
sub from the whole sprite and have the position of the space to go through. exactly the same we calculate 
for the pacman and then we do abs() for the sub and see how far is the pacman from the pathway.
The same algorithm is placed for the ghosts as well.

Ghost Behaviors:

Patrol Behavior - The ghost moves randomly while changing the direction each (3-6) seconds.

Chase Behavior - After ghost discovers pacman < 200 pixels away, it starts chasing him with an algorithm.
Every 0.7 seconds it's allowed to change direction to try and chase pacman.
We check if the x coordinates are equal, if yes, check y bigger than ghosts go down else up.
the same with if y coordinates are equal, check if x > ghosts.x, go right, else left.
If both statements are false, check if pacman.x > ghost.x. if yes, check if pacmans.y >= ghosts, if yes
he's right down/up from the ghost and take the longer route by calculating the distance:
abs(pacmanPos.x - ghostPos.x) > abs(pacmanPos.y - ghostPos.y) = go right, else down.
if the pacmans.y < ghosts, do the same but go Up for else statement.
The same is for the last outside statement(4th) if pacmanPos.x < ghostPos.x
Do the same calculations, but the pacman is now left down/up.
That way pacman is being chased almost perfectly.

Frightened Behavior - The same algorithm for chasing but reversed and movement is changing each second.
That way the are chasing the opposite way :).

-------------------
Design:

Controller controlls the workflow of the game and has the loops for all windows that may open.

GameBoard loads the level and holds all the objects of the level, like static and moving objects
as a vector of unique ptr. So GameBoard has the drawing function that draws all the objects.
Checks all the collisions for objecte between moving and moving and moving and static.
Each time gameboard goes over the board of the level, it sends the character to
GameObjectFactory class to get a uniqueptr return as a base class GameObject.
Display class is responsible for returning the correct window for the apropriate GameState.
GameObject has all handleCollision pure virtual functions so all the moving and static objects
could make use of them.

Each static object like wall, key, door, and bonus are drawn with a singlesprite, unlike
movingobjects which holds a vector of sprites in the base class(GameObject)
The pure virtual func of move is located in MovingObject class which pacman and ghost derives
from it. MovingObject has a member of Direction
(Which I took from an example in the moodle as an insperation) to tell the direction of the
moving object(Up, down, right, left).

Each staticobject or moving object gets it's own textures from a singelton TextureManager class
which sent by GameObjectFactory when creating the object.

Each class that should make a sound when it collides and something happens, they should get
the sound from a singelton class SoundManager in their own classes.

Pacman has a speed of 105.f, and ghost has 90.f so pacman is a bit faster and can run away
so ghost will loose the sight and stop "Chasing" pacman. It also helps in turns, because turns
can be also an enemy for you. Speed of ghosts are changed to 70.f while the are
frightened(Pacman is Super). and the are flickering 1.5 seconds away from being back to normal,
it means Super bonus is wearing off. Ghost is chasing pacman if dist < 200 and stoping chasing
when >= 200. If pacman gets "killed" by pacman while in super, ghost "dies" freezes for 4 seconds.
When TimeFreeze bonus is taken by pacman, ghosts are frozen for 5 seconds.

Each Static/Moving objects has it's own handleCollision, so pacman cannot go through walls and doors
unless when pacman is in Super, he can break the doors and the keys will disapear.
Ghosts also can't go through walls and doors, but when collided with pacman while he's not in super
mode, pacman loses one life point, and everyone resets to their own original positions.

Level is finished when all cookies are collected and controller changes the level number and the loop
runs again and creates a new GameBoard with the players info saved(Level, points).
Different music plays between each level.

At the end, after all levels are finished and you win, you get a window of win, and the points you 
collected.
If you lose, you get a lose window and can go back to main menu and start over.

-------------------
Bugs:

-------------------
Notes:

Game can be a bit challenging, but it's not impossible.
It can easely be beaten if you stay focused :) .

Adding a level:
1) Add a level file to /resources/levels/
2) Add to playlist file the name of the level
3) In the CMakeLists add the line "configure_file ("levelname.txt" ${CMAKE_BINARY_DIR} COPYONLY)"
-------------------