#ifndef __SHAPE_H
#define __SHAPE_H

class Shape
{
public:
    virtual double area(void)         = 0;
    virtual double annulus(double t)  = 0;
};

#endif //__SHAPE_H