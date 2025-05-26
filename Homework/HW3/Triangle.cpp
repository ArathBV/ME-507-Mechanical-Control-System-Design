#include <iostream>
#include "Triangle.h"
#include <cmath>

/*
!@brief Triangle Constructor that takes in a parameter of base and height
!@return None
*/
Triangle::Triangle(double bs, double ht)
:base(bs), height(ht), side1(3), side2(3){
}

/*
!@brief Calculates and return the area of the triangle
!@return double
*/    
double Triangle::area(){
    return 0.5 * base * height;
}

/*
!@brief Calculates and return the annular area of the triangle with the given thickness
!@return double
*/  
double Triangle::annulus(double t){
    return area() - (perimeter() * t) + (M_PI * pow(t, 2));
}

/*
!@brief Calculates and return the perimeter of the triangle
!@return double
*/  
double Triangle::perimeter(){
    return base + side1 + side2;
}