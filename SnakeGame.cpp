#include <conio.h>
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

#define fastio ios_base::sync_with_stdio(false);
typedef long long int lli;

enum snakesDirection { Stop = 0, Left, Right, Up, Down };

void SetColor(int color) {
    cout << "\033[" << color << "m";
}

void ResetColor() {
    cout << "\033[0m";
}

void GoToXY(int x, int y) {
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    cout << "\033[?25l";
}

void showCursor() {
    cout << "\033[?25h";
}

class Food {
private:
    int x, y;
    int width, height;

public:
    Food(int w, int h) {
        width = w;
        height = h;
    }

    void Respawn(const deque<int>& tailX, const deque<int>& tailY, int tailLen) {
        bool occupied;
        do {
            occupied = false;
            x = rand() % width;
            y = rand() % height;
            for(int i = 0; i < tailLen; ++i) {
                if(tailX[i] == x && tailY[i] == y) {
                    occupied = true;
                    break;
                }
            }
        } while(occupied);
    }

    int GetX() {
        return x;
    }

    int GetY(){
        return y;
    }
};

class Snake {
private:
    int x, y;
    int width, height;
    deque<int> tailX, tailY;
    int tailLen;
    snakesDirection dir;
    lli currentScore, highestScore;
    bool gameOver;

public:
    Snake(int w, int h) {
        width = w;
        height = h;
        currentScore = 0;
        highestScore = 0;
        gameOver = false;
    }

    void Initialize() {
        x = width/2;
        y = height/2;
        tailX.clear();
        tailY.clear();
        tailX.push_back(x);
        tailY.push_back(y + 1);
        tailX.push_back(x);
        tailY.push_back(y + 2);
        tailLen = tailX.size();
        dir = Up;
        gameOver = false;
        currentScore = 0;
    }

    void ChangeDirection(snakesDirection newDir) {
        if((dir == Left && newDir == Right) || (dir == Right && newDir == Left) || (dir == Up && newDir == Down) || (dir == Down && newDir == Up)) {
            return;
        }
        dir = newDir;
    }

    void Update() {
        tailX.push_front(x);
        tailY.push_front(y);
        if(tailX.size() > tailLen) {
            tailX.pop_back();
            tailY.pop_back();
        }

        switch(dir) {
            case Left:
                x--;
                break;
            case Right:
                x++;
                break;
            case Up:
                y--;
                break;
            case Down:
                y++;
                break;
            case Stop:
                break;
        }

        if(x < 0 || x >= width || y < 0 || y >= height) {
            gameOver = true;
        }
        for(int i = 0; i < tailLen; ++i) {
            if(tailX[i] == x && tailY[i] == y) {
                gameOver = true;
                break;
            }
        }
    }

    void Grow() {
        tailLen++;
        currentScore += 10;
        highestScore = max(highestScore, currentScore);
    }

    bool CheckFoodCollision(int foodX, int foodY) {
        return x == foodX && y == foodY;
    }

    bool IsGameOver() {
        return gameOver;
    }

    int GetX() {
        return x;
    }

    int GetY() {
        return y;
    }

    const deque<int>& GetTailX() {
        return tailX;
    }

    const deque<int>& GetTailY() {
        return tailY;
    }

    int GetTailLen() {
        return tailLen;
    }

    lli GetCurrentScore() {
        return currentScore;
    }

    lli GetHighestScore() {
        return highestScore;
    }
};

class GameBoard {
private:
    int width, height;

public:
    GameBoard(int w, int h) : width(w), height(h) {}

    void Render(Snake& snake, Food& food, string& playerName) {
        GoToXY(0, 0);
        SetColor(96);
        cout << "ssssssss  Nn    N      A      k  k  eeeeeee          gggggggg      A      Mm   mM  eeeeeee" << endl;
        cout << "S         N N   N     A A     k k   E                G            A A     M M M M  E      " << endl;
        cout << "Ssssssss  N  N  N    AaaaA    kK    Eeeeeee          G   GGGG    AaaaA    M  M  M  Eeeeeee" << endl;
        cout << "       S  N   N N   A     A   k k   E                G      g   A     A   M     M  E      " << endl;
        cout << "sssssssS  N    Nn  A       A  k  k  Eeeeeee          GGGGGGGG  A       A  M     M  Eeeeeee" << endl;

        GoToXY(0, 6);
        SetColor(97);
        for(int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl;

        for(int i = 0; i < height; i++) {
            GoToXY(0, i + 7);
            cout << "#";
            for(int j = 0; j < width; j++) {
                if(i == snake.GetY() && j == snake.GetX()) {
                    SetColor(96);
                    cout << "O";
                } else if(i == food.GetY() && j == food.GetX()) {
                    int randCol[] = {31, 32, 33, 34, 35, 36, 91, 92, 93, 94, 95, 96};
                    SetColor(randCol[rand() % 12]);
                    cout << "*";
                } else {
                    bool isTail = false;
                    const auto& tailX = snake.GetTailX();
                    const auto& tailY = snake.GetTailY();
                    for(int k = 0; k < snake.GetTailLen(); k++) {
                        if(tailX[k] == j && tailY[k] == i) {
                            SetColor(34);
                            cout << "o";
                            isTail = true;
                            break;
                        }
                    }
                    if(!isTail) {
                        cout << " ";
                    }
                }
            }
            SetColor(97);
            cout << "#" << endl;
        }

        for(int i = 0; i < width + 2; i++) {
            cout << "#";
        }
        cout << endl;
        cout << endl;

        GoToXY(0, height + 9);
        SetColor(34);
        cout << "Your score: ";
        SetColor(36);
        cout << snake.GetCurrentScore() << endl;

        GoToXY(0, height + 10);
        SetColor(34);
        cout << "High score: ";
        SetColor(36);
        cout << snake.GetHighestScore() << endl;
    }

    lli SetDifficulty() {
        system("cls");
        SetColor(93);
        cout << "Press 'X' to exit the game at any time.\n\nSet difficulty (1-25): ";
        int choice;
        ResetColor();
        cin >> choice;
        while(choice < 1 || choice > 25) {
            system("cls");
            SetColor(91);
            cout << "Invalid! Enter (1-25): ";
            ResetColor();
            cin >> choice;
        }
        return (30 - choice) * 10;
    }

    void ShowGameOver(string& playerName, lli score, lli highScore) {
        system("cls");
        SetColor(91);
        cout << "G A M E  O V E R\n\n";
        SetColor(34);
        cout << "Your score: ";
        SetColor(36);
        cout << score << endl;
        SetColor(34);
        cout << "High score: ";
        SetColor(36);
        cout << highScore << "\n\n";
        SetColor(32);
        cout << "Hii, " << playerName << "!!\n";
    }
};

int main() {
    fastio;
    hideCursor();

    const int width = 90;
    const int height = 30;
    GameBoard board(width, height);
    Snake snake(width, height);
    Food food(width, height);

    SetColor(92);
    cout << "Enter your name: ";
    ResetColor();
     string playerName;
    cin >> playerName;

    lli difficulty = board.SetDifficulty();
    snake.Initialize();
    food.Respawn(snake.GetTailX(), snake.GetTailY(), snake.GetTailLen());

    bool playAgain = true;
    while(playAgain) {
        while(!snake.IsGameOver()) {
            if(_kbhit()) {
                switch(_getch()) {
                    case 'w': 
                    case 'W': 
                    case 72 : 
                        snake.ChangeDirection(Up); 
                        break;
                    case 's': 
                    case 'S': 
                    case 80 : 
                        snake.ChangeDirection(Down); 
                        break;
                    case 'a': 
                    case 'A': 
                    case 75 : 
                        snake.ChangeDirection(Left); 
                        break;
                    case 'd':
                    case 'D': 
                    case 77 : 
                        snake.ChangeDirection(Right);
                        break;
                    case 'x': 
                    case 'X':
                        system("cls");
                        SetColor(34);
                        cout << "Your Score: ";
                        SetColor(36);
                        cout << snake.GetCurrentScore();
                        SetColor(34);
                        cout << "\nHighest Score: ";
                        SetColor(36);
                        cout << snake.GetHighestScore() << "\n\n";
                        ResetColor();
                        exit(0);
                    case 27: // Pause
                        switch (_getch()) {
                            case 'w': 
                            case 'W': 
                            case 72 : 
                                snake.ChangeDirection(Up); 
                                break;
                            case 's': 
                            case 'S': 
                            case 80 : 
                                snake.ChangeDirection(Down); 
                                break;
                            case 'a': 
                            case 'A': 
                            case 75 : 
                                snake.ChangeDirection(Left); 
                                break;
                            case 'd':
                            case 'D': 
                            case 77 : 
                                snake.ChangeDirection(Right);
                                break;
                            case 'x': 
                            case 'X':
                                system("cls");
                                SetColor(34);
                                SetColor(34);
                                cout << "Your Score: ";
                                SetColor(36);
                                cout << snake.GetCurrentScore();
                                SetColor(34);
                                cout << "\nHighest Score: ";
                                SetColor(36);
                                cout << snake.GetHighestScore() << "\n\n";
                                ResetColor();
                                showCursor();
                                exit(0);
                        }
                        break;
                }
            }

            snake.Update();
            if (snake.CheckFoodCollision(food.GetX(), food.GetY())) {
                snake.Grow();
                food.Respawn(snake.GetTailX(), snake.GetTailY(), snake.GetTailLen());
            }

            board.Render(snake, food, playerName);
            Sleep(difficulty);
        }

        board.ShowGameOver(playerName, snake.GetCurrentScore(), snake.GetHighestScore());
        SetColor(92);
        cout << "Play again? (Y/N): ";
        char choice;
        ResetColor();
        cin >> choice;
        playAgain = (toupper(choice) == 'Y');
        if(playAgain) {
            snake.Initialize();
            food.Respawn(snake.GetTailX(), snake.GetTailY(), snake.GetTailLen());
            difficulty = board.SetDifficulty();
        }
    }

    system("cls");
    ResetColor();
    showCursor();
    return 0;
}
