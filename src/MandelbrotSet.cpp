#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include <iostream>
#include <cmath>
#include "MandelbrotSet.h"

MandelbrotSet::MandelbrotSet():ComplexFractal(){
}

MandelbrotSet::MandelbrotSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y):
ComplexFractal(height, width, min_x, max_x, min_y, max_y){
}

MandelbrotSet::~MandelbrotSet(){
	(void)0;
}

void MandelbrotSet::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const{
	x1 = x0 * x0 - y0 * y0 + a;
	y1 = 2 * x0 * y0 + b;
}

int MandelbrotSet::calculatePlaneEscapeCount( const double& a, const double& b ) const{
	double x1, y1, x0, y0, x2, y2, dist;
	x0 = 0.0;
	y0 = 0.0;
	int i;
	calculateNextPoint(x0, y0, a, b, x1, y1);
	dist = std::sqrt((x0 -a) * (x0 - a) + (y0 - b) * (y0 - b));
	i = 0;
	if(dist <= 2.0){
		while(i < getMaxNumber() && !(dist > 2.0)){
			x2 = x1;
			y2 = y1;
			calculateNextPoint(x2, y2, a, b, x1, y1);	
			dist = std::sqrt((x1 - 0.0) * (x1 - 0.0) + (y1 - 0.0) * (y1 - 0.0));	
			i += 1;
		}
		return i;
	}
	else{
		return 0;
	}
}

int MandelbrotSet::calculateNumber(const int& row, const int& column) const{
	double x, y;
	if(indexValid(row, column)){
		calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
		return calculatePlaneEscapeCount(x,y);
	}
	else{
		return -1;
	}
}

// MandelbrotPower::MandelbrotPower():MandelbrotSet(), mD(2.0){
// }

// MandelbrotPower::~MandelbrotPower(){
// 	(void)0;
// }

// double MandelbrotPower::getPower() const{
// 	return mD;
// }

// void MandelbrotPower::setPower(const double& power){
// 	mD = power;
// }

// void MandelbrotPower::calculateNextPoint( const double x0, const double y0, const double& a, const double& b, double& x1, double &y1 ) const{
// 	double r, theta;
// 	r = std::sqrt(x0 * x0 + y0 * y0);
// 	theta = std::atan2(b, x0);
// 	x1 = (std::pow(r, getPower())) * cos(getPower() * theta) + a;
// 	y1 = (std::pow(r, getPower())) * sin(getPower() * theta) + b;
// } 