#ifndef _MAP_H_
#define _MAP_H_

#include <iostream>
#include "matrix.h"
#include "common.h"
#include <vector>
#include "position.h"

class Map {
    public:
        Map();
        Map(int size);
        Map(int rows, int columns);
        void display(void);
        void spawnApple(void);
        void setDirection(Direction direction);
        Direction getDirection(void);
        bool gameLost{false};
        void iterateTick();
        void moveSnake(Position nextPosition);
        Position getNextPosition();
        Position applePosition = Position(1,1);
        std::vector<Position> snake;
        void refreshMap(void);
        void checkEatsHimself(void);
        Matrix matrix;
    private:
        int rows{ 15 };
        int columns{ 15 };
        Direction direction;
        Direction lastDirection;
};

#endif
