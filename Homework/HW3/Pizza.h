#ifndef __PIZZA_H
#define __PIZZA_H

#include "Pizza.h"
#include "Shape.h"

class Pizza
{
public:
    Pizza(Shape * pizza_shape);
    double price(void);
private:
    Shape * pizza_shape;
};

#endif //__TRIANGLE_H