#include "Square.h"

class Palette : public Square{
private:
    int coord;
public:
    Palette(int indice);

    const int getCoord();

    void setCoord(int);

    
};