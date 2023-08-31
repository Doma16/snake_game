#include<deque>
#include<utility>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<set>
#include<string>
#include<map>
using namespace std;

class SnakeGame {
public:
    int width;
    int height;
    deque<pair<int,int>> snake;
    vector<int> grid;
    pair<int,int> apple;

    bool finished = false;
    int direction = -1; // 0, 1, 2, 3

    SnakeGame(int width, int height) {
        for (int i = 0; i < width * height; ++i) {
            grid.push_back(0);
        }

        this->width = width;
        this->height = height;

        //std::srand(std::time(nullptr));

        int x = rand() % width;
        int y = rand() % height;
        pair<int,int> p(x,y);
        snake.push_back(p);

    }

    void appleGen() {
        set<pair<int,int>> check;
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; j++) {
                pair<int,int> tmp(i,j);
                check.insert(tmp);
            }
        }
        for (auto i = snake.begin(); i != snake.end(); ++i) {
            auto iter = check.find(*i);
            if (iter != check.end()) {
                check.erase(iter);
            }
        }

        int pos = rand() % check.size();
        auto iter = check.begin();
        advance(iter, pos);
        apple = *iter;
    }

    void checkFinished() {
        pair<int,int> head = snake.front();
        int x = head.first;
        int y = head.second;

        if (x < 0 or x >= width) {
            finished = true;
            return;
        }

        if (y < 0 or y >= height) {
            finished = true;
            return;
        }

        for(auto i = snake.begin(); i != snake.end(); ++i) {
            if (head == *i) {
                finished = true;
                return;
            }
        }
    }

    void update() {
        if (!finished && direction != -1) {
            pair<int, int> head; 
            head = snake.front();
            switch (direction)
            {
            case 0: /* up */
                head = move(head, 0, -1);
                break;
            case 1: /* right */
                head = move(head, 1, 0);
                break;
            case 2: /* down */
                head = move(head, 0, 1);
                break;
            case 3: /* left */
                head = move(head, -1, 0);
                break;
            default:
                /* no move */
                break;
            }

            if (apple == head) {
                appleGen();
            } else {
                snake.pop_back();
            }
            snake.push_front(head);
        }
    }

    void printSnake() {
        for(auto i = snake.begin(); i != snake.end(); ++i) {
            cout << i->first << ", " << i->second << endl;
        }
    }

    pair<int,int> move(pair<int,int> curr, int x, int y) {
        curr.first += x;
        curr.second += y;
        return curr;
    }

    void draw() {
        string out;
        string signs = "#os";
        for(int i = 0; i < width; ++i) {
            for(int j = 0; j < height; ++j) {
                out += signs.at(grid.at(j*width + i));
                out += " ";
            }
            out.append("\n");
        }
        
        string symbol(1, signs.at(1));
        out.replace(apple.first * 2 + apple.second * (2*width+1), 1, symbol);

        for (auto i = snake.begin(); i != snake.end(); ++i) {
            string sym(1,signs.at(2));
            out.replace(i->first * 2 + i->second * (2*width +1), 1, sym);
        }

        cout << out;
    }

    bool is_finished() {
        return finished;
    }

    void change(string to) {
        map<string, int> calc{{"up", 0},{"right", 1},{"down", 2},{"left", 3}};
        try
        {
            direction = calc.at(to);
        }
        catch(const std::exception& e)
        {
            direction = -1;
        }
    }
};

int main(void) {

    SnakeGame sg(6, 6);

    sg.appleGen();
    sg.draw();

    cout << endl;

    sg.update();
    sg.change("up");
    sg.update();   
    sg.draw();
    cout << endl;

    sg.update();
    sg.draw();

    cout << endl;
    sg.direction = 3;
    sg.update();
    sg.draw();

    cout << endl;
    sg.direction = 2;
    sg.update();
    sg.draw(); 
    cout << endl;

    sg.update();
    sg.draw(); 
    cout << endl;

    sg.update();
    sg.draw(); 
    cout << endl;

    sg.direction = 1;
    sg.update();
    sg.draw(); 
    cout << endl;

    sg.update();
    sg.draw(); 
    cout << endl;


    return 0;
}