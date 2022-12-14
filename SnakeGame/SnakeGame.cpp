#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <windows.h>

const short WEIGHT = 11;
const short HEIGHT = 13;

void Greetings() {
    std::cout << "Игра 'Змейка' - поглощайте сердца, чтобы расти.\n"
        << "Управление производится клавишами W,A,S,D.\n\n";
}

class SnakeGame {
private:
    std::string board[WEIGHT][HEIGHT];
    std::vector <short> snake_tors;
    char difficulty,
        direction;
    short vin_lenght,
        snake_lenght,
        head_X,
        head_Y,
        random_value;
    void SetDifficulty() {
        std::cout << "Выберите уровень сложности!\n"
            << "1 - Легкий\n2 - Средний\n3 - Тяжёлый\n";
        std::string temp;
        for (;;) {
            std::cin >> temp;
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
                std::cout << "Ошибка! Повторите ввод!\n";
            }
        }
    }
    bool CreateGame() {
        bool the_end = 0;
        short count = 1;
        MoveSnake();                //направления змейки
        CreateEdges(count);         //создание краёв поля
        CreateTors(count);          //создание тела
        CreateHead(count, the_end); //создание головы
        CreateHearts(count);        //создание сердец на поле
        DrawBoard();                //визуальное отображение
        DrawStatus();               //вывод игровой статистики
        return the_end;
    }
    void MoveSnake() {
        if (direction == '1') { --head_X; }
        else if (direction == '2') { --head_Y; }
        else if (direction == '3') { ++head_X; }
        else if (direction == '4') { ++head_Y; }
    }
    void CreateEdges(short count) {
        for (int i = 0; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j, ++count) {
                if (i == 0 || i == WEIGHT - 1 || j == 0 || j == HEIGHT - 1) {
                    board[i][j] = '*';
                    --count;
                }
                else if (board[i][j][0] != char(3)) {
                    board[i][j] = std::to_string(count);
                }
            }
        }
    }
    void CreateTors(short count) {
        for (int i = 1; i < WEIGHT - 1; ++i) {
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
    void CreateHead(short count, bool& the_end) {
        for (int i = 0; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                if (i == head_X && j == head_Y) {                           //голова
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
                        SetRandomValue();
                    }
                    board[i][j] = 'O';
                }
                if (board[i][j][0] != '*') {
                    ++count;
                }
            }
        }
    }
    void CreateHearts(short count) {
        if (snake_lenght != vin_lenght) {
            for (int i = 1; i < WEIGHT - 1; ++i) {
                for (int j = 1; j < HEIGHT - 1; ++j, ++count) {
                    if (count == random_value && board[i][j][0] != 'o' && board[i][j][0] != 'O') {
                        board[i][j] = char(3);
                    }
                    else if (count == random_value && (board[i][j][0] == 'o' || board[i][j][0] == 'O')) {
                        i = 0;
                        j = 1;
                        count = 1;
                        SetRandomValue();
                        break;
                    }
                }
            }
        }
    }
    short SetRandomValue() {
        return random_value = rand() % ((WEIGHT - 2) * (HEIGHT - 2)) + 1;
    }
    void DrawBoard() {
        for (int i = 0; i < WEIGHT; ++i) {
            for (int j = 0; j < HEIGHT; ++j) {
                if (board[i][j][0] >= '1' && board[i][j][0] <= '9') {
                    std::cout << "  ";
                }
                else {
                    std::cout << board[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
    }
    void DrawStatus() {
        std::cout << "Длина змейкм - " << snake_lenght + 1
            << "\nОсталось поглотить - " << vin_lenght - snake_lenght << " сердец.\n";
        if (snake_lenght <= 2) {
            std::cout << "Ты - Головастик. Покушай малыш!\n\n";
        }
        else if (snake_lenght > 2 && snake_lenght <= 8) {
            std::cout << "Ты - Маленькая змейка. Ещё чуть-чуть пупсик!\n\n";
        }
        else if (snake_lenght > 8 && snake_lenght <= 15) {
            std::cout << "Ты - Обычная змейка. Обыкновенность на кончиках пальцев!\n\n";
        }
        else if (snake_lenght > 15 && snake_lenght <= 21) {
            std::cout << "Ты - Жирная змейка. Кто то в последнее время навернул немало фастфуда!\n\n";
        }
        else if (snake_lenght > 21) {
            std::cout << "Ты - Отожраный червос. Смотри не лопни!\n\n";
        }
    }
public:
    SnakeGame() {
        difficulty = {};
        direction = '0';
        vin_lenght = 0;
        snake_lenght = 0;
        head_X = WEIGHT / 2;
        head_Y = HEIGHT / 2;
        random_value = SetRandomValue();
        restart = {};
    }
    char restart;
    void StartGame() {
        SetDifficulty();
        for (;;) {
            if (_kbhit()) {
                char key = _getch();
                if (key == 'w' || key == 'W' || key == -26 || key == -106) { direction = '1'; }
                else if (key == 'a' || key == 'A' || key == -28 || key == -108) { direction = '2'; }
                else if (key == 's' || key == 'S' || key == -21 || key == -101) { direction = '3'; }
                else if (key == 'd' || key == 'D' || key == -94 || key == -126) { direction = '4'; }
            }
            system("cls");      //Очистка экрана
            if (CreateGame() || snake_lenght == vin_lenght) { break; }
            if (difficulty == '1') { Sleep(400); }
            else if (difficulty == '2') { Sleep(300); }
            else if (difficulty == '3') { Sleep(200); }
        }
        if (snake_lenght < vin_lenght) {
            std::cout << "Игра окончена - Поражение!\nЖелаете начать заново?\nНажмите 'Y/y' - если хотите или любую другую, чтобы закончить - ";
        }
        else {
            std::cout << "Игра окончена - Победа!\nЖелаете начать заново?\nНажмите 'Y/y' - если хотите или любую другую, чтобы закончить - ";
        }
        std::cin >> restart;
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
        system("cls");
        goto RESTART;
    }
    return 0;
}