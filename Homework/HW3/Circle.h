#ifndef __CIRCLE_H
#define __CIRCLE_H

#include "Shape.h"

/*Circle class, child of Shape Class*/
class Circle : public Shape {
    public:
        Circle(double);
        double radius;
        double area(void) override;
        double annulus(double) override;
    
};

#endif