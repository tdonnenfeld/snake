#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <vector>
#include "common.h"
#include "position.h"
#include <SFML/Graphics.hpp>

class Matrix {
    public: 
        Matrix();
        Matrix(int size);
        Matrix(int rows, int columns);
        Matrix(int rows, int columns, MapObject value); 
        Matrix(int rows, int columns, sf::RectangleShape); 
        MapObject& operator()(int const x, int const y);
        void set(Position position, MapObject value);
        int getColumns(void);
        int getRows(void);

    private:
        std::vector<MapObject> _storage; // Storage will contain matrix values, line by line.
        int rows, columns;
};

#endif
