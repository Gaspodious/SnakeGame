#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

const short WEIGHT = 11;
const short HEIGHT = 13;

void Greetings() {
    cout << "Игра 'Змейка' - поглощайте сердца, чтобы расти.\n"s
        << "Управление производится клавишами W,A,S,D.\n\n"s;
}

class SnakeGame {
private:
    string board[WEIGHT][HEIGHT];
    vector <short> snake_tors;
    char difficulty = {},
        direction = '0';
    short vin_lenght = 0,
        snake_lenght = 0,
        headX = WEIGHT / 2,
        headY = HEIGHT / 2,
        random_value = GetRandomValue();
    void SetDifficulty() {
        cout << "Выберите уровень сложности!\n"s
            << "1 - Легкий\n2 - Средний\n3 - Тяжёлый\n"s;
        string temp;
        for (;;) {
            cin >> temp;
            if (temp.size() == 1 && temp[0] == '1') {
                difficulty = temp[0];
                vin_lenght = 24;
                break;
            }
            else if (temp.size() == 1 && temp[0] == '2') {
                difficulty = temp[0];
                vin_lenght = 29;
                break;
            }
            else if (temp.size() == 1 && temp[0] == '3') {
                difficulty = temp[0];
                vin_lenght = 34;
                break;
            }
            else {
                cout << "Ошибка! Повторите ввод!\n"s;
            }
        }
    }
    bool CreateGame() {
        short count = 1;
        bool the_end = 0;
        MoveSnake(headX, headY);    //направления змейки
        CreateEdges(count);         //создание краёв поля
        CreateTors(count);          //создание тела
        CreateHead(count, the_end);  //создание головы
        CreateHearts(count);        //создание сердец на поле
        DrawBoard();                //визуальное отображение
        DrawStatus();               //вывод игровой статистики
        return the_end;
    }
    void MoveSnake(short& headX, short& headY) {
        if (direction == '1') {
            --headX;
        }
        else if (direction == '2') {
            --headY;
        }
        else if (direction == '3') {
            ++headX;
        }
        else if (direction == '4') {
            ++headY;
        }
    }
    void CreateEdges(short& count) {
        for (int i = 0, count = 1; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j, ++count) {
                if (i == 0 || i == WEIGHT - 1 || j == 0 || j == HEIGHT - 1) {
                    board[i][j] = '*';
                    --count;
                }
                else if (board[i][j][0] != char(3)) {
                    board[i][j] = to_string(count);
                }
            }
        }
    }
    void CreateTors(short& count) {
        for (int i = 1, count = 1; i < WEIGHT - 1; ++i) {
            for (int j = 1; j < HEIGHT - 1; ++j, ++count) {
                if (snake_lenght > 0) {
                    for (const auto& x : snake_tors) {
                        if (count == x) {
                            board[i][j] = 'o';
                        }
                    }
                }
            }
        }
    }
    void CreateHead(short& count, bool& the_end) {
        for (int i = 0, count = 1; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                if (i == headX && j == headY) {                             //голова
                    if (board[i][j][0] == '*' || board[i][j][0] == 'o') {   //поражение-победа
                        the_end = 1;
                        board[i][j] = 'X';
                        break;
                    }
                    else if (snake_lenght == vin_lenght) {
                        the_end = 1;
                    }
                    if (snake_lenght > 0) {                                  //обработка тела
                        reverse(snake_tors.begin(), snake_tors.end());
                        snake_tors.pop_back();
                        reverse(snake_tors.begin(), snake_tors.end());
                        snake_tors.push_back(count);
                    }
                    if (board[i][j][0] == char(3)) {                        //сердца-генерация после поглощения
                        ++snake_lenght;
                        snake_tors.push_back(random_value);
                        GetRandomValue();
                    }
                    board[i][j] = 'O';
                }
                if (board[i][j][0] != '*') {
                    ++count;
                }
            }
        }
    }
    void CreateHearts(short& count) {
        if (snake_lenght != vin_lenght) {
            for (int i = 1, count = 1; i < WEIGHT - 1; ++i) {
                for (int j = 1; j < HEIGHT - 1; ++j, ++count) {
                    if (count == random_value && board[i][j][0] != 'o' && board[i][j][0] != 'O') {
                        board[i][j] = char(3);
                    }
                    else if (count == random_value && (board[i][j][0] == 'o' || board[i][j][0] == 'O')) {
                        i = 0;
                        j = 1;
                        count = 1;
                        GetRandomValue();
                        break;
                    }
                }
            }
        }
    }
    short GetRandomValue() {
        return random_value = rand() % ((WEIGHT - 2) * (HEIGHT - 2)) + 1;
    }
    void DrawBoard() {
        for (int i = 0; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                if (board[i][j][0] >= '1' && board[i][j][0] <= '9') {
                    cout << "  ";
                }
                else {
                    cout << board[i][j] << " ";
                }
            }
            cout << "\n"s;
        }
    }
    void DrawStatus() {
        cout << "Длина змейкм - "s << snake_lenght + 1
            << "\nОсталось поглотить - "s << vin_lenght - snake_lenght << " сердец.\n"s;
        if (snake_lenght <= 2) {
            cout << "Ты - Головастик. Покушай малыш!\n\n"s;
        }
        else if (snake_lenght > 2 && snake_lenght <= 8) {
            cout << "Ты - Маленькая змейка. Ещё чуть-чуть пупсик!\n\n"s;
        }
        else if (snake_lenght > 8 && snake_lenght <= 15) {
            cout << "Ты - Обычная змейка. Обыкновенность на кончиках пальцев!\n\n"s;
        }
        else if (snake_lenght > 15 && snake_lenght <= 21) {
            cout << "Ты - Жирная змейка. Кто то в последнее время навернул немало фастфуда!\n\n"s;
        }
        else if (snake_lenght > 21) {
            cout << "Ты - Отожраный червос. Смотри не лопни!\n\n"s;
        }
    }
public:
    char restart = {};
    void StartGame() {
        SetDifficulty();
        for (;;) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'w' || key == 'W' || key == -26 || key == -106) {
                    direction = '1';
                }
                else if (key == 'a' || key == 'A' || key == -28 || key == -108) {
                    direction = '2';
                }
                else if (key == 's' || key == 'S' || key == -21 || key == -101) {
                    direction = '3';
                }
                else if (key == 'd' || key == 'D' || key == -94 || key == -126) {
                    direction = '4';
                }
                else if (key == 'x') {
                    cin >> direction;
                }
            }
            system("cls");                  //Очистка экрана
            if (CreateGame()) {
                break;
            }
            if (difficulty == '1') {
                Sleep(400);
            }
            else if (difficulty == '2') {
                Sleep(300);
            }
            else if (difficulty == '3') {
                Sleep(200);
            }
        }
        if (snake_lenght < vin_lenght) {
            cout << "Игра окончена - Поражение!\nЖелаете начать заново? Y/N - "s;
        }
        else {
            cout << "Игра окончена - Победа!\nЖелаете начать заново? Y/N - "s;
        }
        cin >> restart;
        system("cls");
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    Greetings();
RESTART:
    SnakeGame game;
    game.StartGame();
    if (game.restart == 'Y' || game.restart == 'y') {
        goto RESTART;
    }
    return 0;
}