#include "Circle.h"
#include <iostream>
#include <cmath>

/*
!@brief Circle Constructor that takes in a parameter of radius and sets it to the radius var
!@return None
*/
Circle::Circle(double rad)
:radius(rad){

}

/*
!@brief Calculates and return the area of the circle with the given radius
!@return double
*/    
double Circle::area() {
    return M_PI * (pow(radius, 2));
}   

/*
!@brief Calculates and return the annular area of the circle with the given thickness
!@return double
*/    
double Circle::annulus(double t){
    return area() - (M_PI * pow((radius - (t)), 2));
}
