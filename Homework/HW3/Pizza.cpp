#include "Pizza.h"

Pizza::Pizza(Shape * pizza_shape)
:pizza_shape(pizza_shape)
{
    
}

double Pizza::price(void)
{
    return 1*pizza_shape->area()                               // dough
           + 2*(pizza_shape->area() - pizza_shape->annulus(1)) // sauce + cheese
           + 0.5*pizza_shape->annulus(1);                      // stuffed crust
}