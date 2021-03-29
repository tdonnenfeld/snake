#ifndef _POSITION_H_
#define _POSITION_H_

class Position {
    public:
        Position(int x, int y) : x(x), y(y) {};
        int x{0};
        int y{0};
        bool operator==(Position &b) {
            return this->isEqual(b);
        };
        bool operator!=(Position &b) {
            return !(*this==b);
        }
        bool isEqual(Position &b) {
            return (x == b.x && y == b.y);
        };
}; 

#endif
