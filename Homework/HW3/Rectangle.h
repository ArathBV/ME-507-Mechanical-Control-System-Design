#ifndef __RECTANGLE_H
#define __RECTANGLE_H

#include "Shape.h"

/*Rectangle class, child of Shape Class*/
class Rectangle: public Shape{
    public:
        Rectangle(double, double);
        double length;
        double width;
        double area(void) override;
        double annulus(double) override;
};

#endif