#ifndef __TRIANGLE_H
#define __TRIANGLE_H

#include "Shape.h"

/*Triangle class, child of Shape Class*/
class Triangle: public Shape{
    public:
        Triangle(double, double);
        double base;
        double height;
        double area(void) override;
        double annulus(double) override;
    private:
        double side1;
        double side2;
        double perimeter(void);
};

#endif