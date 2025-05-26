#include "Rectangle.h"
#include <iostream>
#include <cmath>

/*
!@brief Rectangle Constructor that takes in a parameters of length and width
!@return None
*/
Rectangle::Rectangle(double len, double wdth)
:length(len), width(wdth){

}

/*
!@brief Calculates and return the area of the rectangle
!@return double
*/    
double Rectangle::area(){
    return length * width;
}

/*
!@brief Calculates and return the annular area of the rectangle with the given thickness
!@return double
*/    
double Rectangle::annulus(double t){
    return area() - ((length - t) * (width - t));
}