#ifndef __SHAPE_H
#define __SHAPE_H

class Shape
{
public:
    virtual double area(void)         = 0;
    virtual double annulus(double t)  = 0;
};

/*Circle class, child of Shape Class*/
class Circle : public Shape {
}


/*Triangle class, child of Shape Class*/
class Triangle: public Shape{
}


/*Rectangle class, child of Shape Class*/
class Rectangle: public Shape{
}

#endif //__SHAPE_H