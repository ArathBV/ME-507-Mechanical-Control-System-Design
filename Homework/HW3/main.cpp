#include <iostream>
#include "Triangle.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Pizza.h"

Triangle my_triangle = Triangle(2, 3);
Circle circ = Circle(2);
Rectangle rect = Rectangle(2, 1);

Pizza my_pizza = Pizza(&my_triangle);
Pizza pizza2 = Pizza(&circ);
Pizza pizza3 = Pizza(&rect);

int main()
{
    std::cout << "The pizza costs " << my_pizza.price() << "$" << std::endl;
    std::cout << "The pizza costs " << pizza2.price() << "$" << std::endl;
    std::cout << "The pizza costs " << pizza3.price() << "$" << std::endl;

    return 0;
}