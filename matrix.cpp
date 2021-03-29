#include "common.h"
#include "matrix.h"
#include "position.h"
#include <SFML/Graphics.hpp>
#include "iostream"
Matrix::Matrix() : Matrix(1, 1) {};

Matrix::Matrix(int size) : Matrix(size, size) {};

Matrix::Matrix(int rows, int columns) : Matrix(rows, columns, MapObject::Empty) {};

Matrix::Matrix(int rows, int columns, MapObject value) : rows(rows), columns(columns) {
    _storage.assign(rows * columns, value); 
};

MapObject& Matrix::operator()(int const x, int const y) {
    return _storage[x * rows + y];
}

void Matrix::set(Position position, MapObject value) {
    _storage[position.x * rows + position.y] = value;
}


int Matrix::getRows() {
    return this->rows;
}

int Matrix::getColumns() {
    return this->columns;
}
