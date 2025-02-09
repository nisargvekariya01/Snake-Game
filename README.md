# Snake Game


## 📌 Introduction  
The Snake Game is a classic arcade game where the player controls a snake to collect food while avoiding collisions with walls or its own tail. This C++ implementation is customizable with difficulty levels, smooth rendering, real-time input handling, and dynamic score tracking.


---


## 🎮 Features  
- Runs smoothly on *Windows* terminals. (It can not run on iOS, because some of the functions that we have used in our code is not directly available on iOS libraries. So it makes task complicated for us to make 
  platform independent.) 
- *Smooth Rendering*: Uses GoToXY() for flicker-free screen updates by directly manipulating the console cursor.  
- *Customizable Difficulty*: 25 difficulty levels to control the snake’s speed.  
- *Score Tracking*: Tracks current score and highest score.  
- *Colorful Interface*: ANSI color codes for vibrant visuals.  
- *Pause/Resume*: Pause with ESC; resume by pressing any key (except X). Directional keys during pause immediately change the snake’s direction.  
- *Dynamic Food Spawning*: Food respawns randomly, avoiding the snake’s body.  


---


## 🛠 Class Descriptions  
### 🍎 Food Class (Food)  
Handles food spawning and collision checks.  
*Attributes*:
```
int x, y - Food coordinates.  
int width, height - Game board dimensions.
```


*Methods*:  
```
void Respawn(...); // Spawns food avoiding the snake’s tail  
int GetX()/GetY(); // Returns food coordinates
```
  


### 🐍 Snake Class (Snake)  
Manages movement, growth, collisions, and scoring.  
*Attributes*: 
```
deque<int> tailX, tailY - Stores tail coordinates.  
snakesDirection dir - Current direction (enum: Left, Right, Up, Down, Stop).  
lli currentScore, highestScore - Score tracking.  
```


*Methods*:  
```
void ChangeDirection(...); // Updates direction (prevents 180° turns)  
void Update(); // Moves snake, checks collisions  
void Grow(); // Increases tail length and score  
bool IsGameOver(); // Checks wall/self-collision
```
  


### 🎮 GameBoard Class (GameBoard)  
Handles rendering, difficulty selection, and game-over screens.  
*Methods*:  
```
void Render(...); // Draws game board, snake, food, and scores  
static lli SetDifficulty(); // Sets speed based on player input (1-25)  
void ShowGameOver(...); // Displays final stats
```
  


---


## 🚀 How to Run the Game  
1. *Compile the code*:  
   ``` 
   g++ t.cpp -o snake_game
   ```
     
2. *Run the executable*:  
   ```
   ./snake_game      # macOS/Linux  
   snake_game.exe    # Windows
   ```
     
3. *Follow prompts* to enter your name and select difficulty.  


---


## 🕹 Controls  
- ```W```/⬆️ : Arrow*: Move Up  
- ```S```/⬇️ : Arrow*: Move Down  
- ```A```/⬅️ : Move Left  
- ```D```/➡️ : Move Right  
- ```ESC```: Pause the game. Press **any key (except X)* to resume.  
  - If a *directional key* is pressed during pause, the snake starts moving in that direction immediately.  
- ```X```: Exit the game anytime.  


---


## 📊 Data Structure Analysis  
1. *Deque (Double-Ended Queue)*:  
   - *Usage*: Stores the snake’s tail coordinates (tailX and tailY).  
   - *Why?*: Efficient O(1) insertion at the front (new head position) and removal from the back (old tail position). Perfect for the snake’s dynamic body.  


2. **Enumeration (snakesDirection):  
   - *Usage*: Tracks the snake’s current direction (Left, Right, Up, Down, Stop).  
   - *Why?*: Ensures type-safe and readable direction checks.  


3. *Classes*:  
   - *Snake Class*: Encapsulates movement logic, collision detection, and score tracking.  
   - *Food Class*: Manages food spawning with collision avoidance.  
   - *GameBoard Class*: Centralizes rendering, difficulty settings, and UI interactions.  


4. *ANSI Escape Codes*:  
   - *Usage*: GoToXY(), SetColor(), and hideCursor() for smooth terminal manipulation.  
   - *Why?*: Direct cursor control eliminates flickering and enables dynamic updates.  


---


## 📜 Game Rules  
- Collect food (*) to grow the snake and increase your score.  
- Avoid collisions with walls or the snake’s own tail.  
- Difficulty increases with higher levels (snake moves faster).  


---


## 🎯 Conclusion  
This Snake Game offers a seamless terminal experience with cross-platform compatibility, smooth rendering, and intuitive controls. Challenge yourself to beat your high score while mastering the dynamic difficulty levels!  
