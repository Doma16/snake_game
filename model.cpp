#include<deque>
#include<utility>
#include<vector>
#include<cstdlib>
#include<iostream>
#include<ctime>
#include<set>
using namespace std;

class SnakeGame {
public:
    int width;
    int height;
    deque<pair<int,int>> snake;
    vector<int> grid;
    pair<int,int> apple;

    SnakeGame(int width, int height) {
        for (int i = 0; i < width * height; ++i) {
            grid.push_back(0);
        }

        this->width = width;
        this->height = height;

        std::srand(std::time(nullptr));

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

    void update() {
        if (snake[0] == apple) {
        }
    }

    

};

int main(void) {

    SnakeGame sg(8, 8);

    sg.appleGen();
    
    return 0;
}