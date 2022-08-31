#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>
using namespace std;

const short WEIGHT = 11;
const short HEIGHT = 13;

class SnakeGame {
private:
    string board[WEIGHT][HEIGHT];
    vector <short> snakeTors;
    char difficulty = {},
        direction = '0';
    short vinLenght = 0,
        snakeLenght = 0,
        headX = WEIGHT / 2,
        headY = HEIGHT / 2,
        randomValue = getRandomValue();

    void setDifficulty() {
        cout << "Выберите уровень сложности!\n"s
            << "1 - Легкий\n2 - Средний\n3 - Тяжёлый\n"s;
        string temp;
        for (;;) {
            cin >> temp;
            if (temp.size() == 1 && temp[0] == '1') {
                difficulty = temp[0];
                vinLenght = 24;
                break;
            }
            else if (temp.size() == 1 && temp[0] == '2') {
                difficulty = temp[0];
                vinLenght = 29;
                break;
            }
            else if (temp.size() == 1 && temp[0] == '3') {
                difficulty = temp[0];
                vinLenght = 34;
                break;
            }
            else {
                cout << "Ошибка! Повторите ввод!\n"s;
            }
        }
    }
    bool createGame() {
        short count = 1;
        bool theEnd = 0;
        moveSnake(headX, headY);    //направления змейки
        createEdges(count);         //создание краёв поля
        createTors(count);          //создание тела
        createHead(count, theEnd);  //создание головы
        createHearts(count);        //создание сердец на поле
        drawBoard();                //визуальное отображение
        drawStatus();               //вывод игровой статистики
        return theEnd;
    }
    void moveSnake(short& headX, short& headY) {
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
    void createEdges(short& count) {
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
    void createTors(short& count) {
        for (int i = 1, count = 1; i < WEIGHT - 1; ++i) {
            for (int j = 1; j < HEIGHT - 1; ++j, ++count) {
                if (snakeLenght > 0) {
                    for (const auto& x : snakeTors) {
                        if (count == x) {
                            board[i][j] = 'o';
                        }
                    }
                }
            }
        }
    }
    void createHead(short& count, bool& theEnd) {
        for (int i = 0, count = 1; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                if (i == headX && j == headY) {                             //голова
                    if (board[i][j][0] == '*' || board[i][j][0] == 'o') {   //поражение-победа
                        theEnd = 1;
                        board[i][j] = 'X';
                        break;
                    }
                    else if (snakeLenght == vinLenght) {
                        theEnd = 1;
                    }
                    if (snakeLenght > 0) {                                  //обработка тела
                        reverse(snakeTors.begin(), snakeTors.end());
                        snakeTors.pop_back();
                        reverse(snakeTors.begin(), snakeTors.end());
                        snakeTors.push_back(count);
                    }
                    if (board[i][j][0] == char(3)) {                        //сердца-генерация после поглощения
                        ++snakeLenght;
                        snakeTors.push_back(randomValue);
                        getRandomValue();
                    }
                    board[i][j] = 'O';
                }
                if (board[i][j][0] != '*') {
                    ++count;
                }
            }
        }
    }
    void createHearts(short& count) {
        if (snakeLenght != vinLenght) {
            for (int i = 1, count = 1; i < WEIGHT - 1; ++i) {
                for (int j = 1; j < HEIGHT - 1; ++j, ++count) {
                    if (count == randomValue && board[i][j][0] != 'o' && board[i][j][0] != 'O') {
                        board[i][j] = char(3);
                    }
                    else if (count == randomValue && (board[i][j][0] == 'o' || board[i][j][0] == 'O')) {
                        i = 0;
                        j = 1;
                        count = 1;
                        getRandomValue();
                        break;
                    }
                }
            }
        }
    }
    short getRandomValue() {
        return randomValue = rand() % ((WEIGHT - 2) * (HEIGHT - 2)) + 1;
    }
    void drawBoard() {
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
    void drawStatus() {
        cout << "Длина змейкм - "s << snakeLenght + 1
            << "\nОсталось поглотить - "s << vinLenght - snakeLenght << " сердец.\n"s;
        if (snakeLenght <= 2) {
            cout << "Ты - Головастик. Покушай малыш!\n\n"s;
        }
        else if (snakeLenght > 2 && snakeLenght <= 8) {
            cout << "Ты - Маленькая змейка. Ещё чуть-чуть пупсик!\n\n"s;
        }
        else if (snakeLenght > 8 && snakeLenght <= 15) {
            cout << "Ты - Обычная змейка. Обыкновенность на кончиках пальцев!\n\n"s;
        }
        else if (snakeLenght > 15 && snakeLenght <= 21) {
            cout << "Ты - Жирная змейка. Кто то в последнее время навернул немало фастфуда!\n\n"s;
        }
        else if (snakeLenght > 21) {
            cout << "Ты - Отожраный червос. Смотри не лопни!\n\n"s;
        }
    }
public:
    char restart = {};
    void greetings() {
        cout << "Игра 'Змейка' - поглощайте сердца, чтобы расти.\n"s
            << "Управление производится клавишами W,A,S,D.\n\n"s;
    }
    void startGame() {
        setDifficulty();
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
            if (createGame()) {
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
        if (snakeLenght < vinLenght) {
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
    SnakeGame game;
    game.greetings();
RESTART:
    game.startGame();
    if (game.restart == 'Y' || game.restart == 'y') {
        goto RESTART;
    }
    return 0;
}