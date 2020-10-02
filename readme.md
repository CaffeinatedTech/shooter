# shooter

Just a vertical shoot-em-up to learn C++ and SFML with.

The plan is to build the same game over and over and improve on 
code style and features with each iteration.

### Iteration 2
This iteration is in progress

### Plan
#### Engine
* Function for setting up initial game state and resetting for
new game
* Use an enum to handle state like `state::RUNNING` or `state::INTERMISSION`
* GUI Text - Create a text generator function to tidy up the constructor
* Debug Text - On-screen in game
* Update - Break into separate functions
* Sound effects
* High Score - Save to a file
* XML Handler
* Control Handler
  * Load/Save control scheme to XML file

#### Enemies
* Load all XML files in the assets/enemies directory
* Sort by difficulty

#### Player
* Load random XML file from the assets/player directory

### Features

#### Controls
* Movement
    * Keyboard - Arrow keys
    * Joystick 0 - D-Pad
* Firing
    * Keyboard - Space (hold for continuous fire)
    * Joystick - Button 0 (hold for continuous fire)
* Other
    * P or PAUSE to pause the game
    * ENTER to start a new game on the game-over screen

#### Gameplay
* Complete increasingly difficult waves of enemies (12 each wave)
* Each wave increases difficulty by shifting the weighted enemy spawn chances
* Three enemy types with different sprites, health and score
* Random enemy spawn locations and timing
* Enemy shooting - Some enemies are able to shoot, either straight down, or at the player
* Collisions - If you crash your ship into an enemy, you will destroy it and get the
destroy score, but you will damage your ship.  Be careful.
* Health regen - Stop shooting for a second to begin ship repairs.
* One life - You only get one ship, look after it.


#### Game World
* Game field is wider than the window.  The camera keeps the 
player ship centered horizontally until the edge of the field.
* Continuously scrolling background
* Wave score and kills are shown between waves
* Game Over screen shows total score and allows you to start a new game

### Build
You'll need a cpp compiler like gcc, cmake and SFML, and boost installed  
`cmake .` to configure the build  
`cmake --build .` to build the project  
Or just build it in your IDE