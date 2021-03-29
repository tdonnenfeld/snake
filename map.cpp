#include "common.h"
#include "matrix.h"
#include <iostream>
#include "map.h"
#include <time.h>
#include <vector>

Map::Map() : Map(15, 15) {};
Map::Map(int size) : Map(size, size) {};
Map::Map(int rows, int columns) : rows(rows), columns(columns), matrix(Matrix(rows, columns, MapObject::Empty)) {
    Position initialPosition = Position(rows/2, columns/2);
    matrix.set(initialPosition, MapObject::Snake);
    this->snake = {initialPosition};
    this->spawnApple();
    this->direction = Direction::Right;
    this->lastDirection = Direction::Right;
};

void Map::spawnApple(void) {
    srand (time(NULL));
    Position applePosition = Position(rand()%rows, rand()%columns);
    this->applePosition = applePosition;
    matrix.set(applePosition, MapObject::Apple);
}

void Map::display(void) {
    for(int i=0; i<rows; i++){
        for(int j=0; j<columns; j++){
            std::cout << (int)matrix(i,j);
        }
        std::cout << "\n";
    }
    std::cout << "\n\n";
}

void Map::iterateTick(void) {
    Position nextPosition = this->getNextPosition();
    this->moveSnake(nextPosition);
    this->lastDirection = this->direction;
    this->checkEatsHimself();
    this->refreshMap();
}

void Map::checkEatsHimself(void) {
    for(std::size_t i = 0; i < this->snake.size(); ++i) {    
        for(std::size_t j = 0; j < this->snake.size(); ++j) {
            if(i!=j){
                if(snake[i] == snake[j]) {
                    this->gameLost = true;
                }
            }
        }
    }
}

void Map::moveSnake(Position nextPosition) { 
    if (nextPosition == this->applePosition) {
        this->snake.insert(this->snake.begin(), nextPosition);
        this->spawnApple();
    } else {
        std::vector<Position> oldSnake = this->snake;
        for(std::size_t i = 0; i < this->snake.size(); ++i) {
            if(i==0) {
                this->snake[i] = nextPosition; 
            } else {
                this->snake[i] = oldSnake[i-1];
            }
        }
    }
}

void Map::refreshMap(void) {
    for(int x=0; x<this->rows; x++) {
        for(int y=0; y<this->columns; y++) {
            matrix.set(Position(x,y), MapObject::Empty);            
        }
    }
    for(std::size_t i = 0; i < this->snake.size(); ++i) {
        matrix.set(this->snake[i], MapObject::Snake);
    }
    matrix.set(applePosition, MapObject::Apple);
}

Position Map::getNextPosition(void) {
    Position nextPosition = this->snake[0];
    switch(this->direction) {
        case Direction::Up : nextPosition.x = this->snake[0].x - 1;
            break;       
        case Direction::Down : nextPosition.x = this->snake[0].x + 1;
            break;       
        case Direction::Left : nextPosition.y = this->snake[0].y - 1;
            break;       
        case Direction::Right : nextPosition.y = this->snake[0].y + 1;
            break;       
    } 
    if (nextPosition.x < 0 || nextPosition.x >= this->rows || nextPosition.y < 0 || nextPosition.y >= this->columns) {
       this->gameLost = true; 
    }
    return nextPosition;
}

void Map::setDirection(Direction direction) {
    if( direction == Direction::Right && lastDirection != Direction::Left) {
        this->direction = direction;
    } else if( direction == Direction::Left && lastDirection != Direction::Right) {
        this->direction = direction;
    } else if( direction == Direction::Up && lastDirection != Direction::Down) {
        this->direction = direction;
    } else if( direction == Direction::Down && lastDirection != Direction::Up) {
        this->direction = direction;
    }
}

Direction Map::getDirection() {
    return this->direction;
}
        

