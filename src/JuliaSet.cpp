#include "JuliaSet.h"
#include "ComplexFractal.h"
#include "NumberGrid.h"
#include <cmath>
#include <iostream>

JuliaSet::JuliaSet(): ComplexFractal(), mA(-0.650492), mB(-0.478235){
}

JuliaSet::JuliaSet(const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y, const double& a, const double& b):
ComplexFractal(height, width, min_x, max_x, min_y, max_y), mA(a), mB(b){
}

JuliaSet::~JuliaSet(){
	(void)0;
}

double JuliaSet::getA() const{
	return mA;
}

double JuliaSet::getB() const{
	return mB;
}

void JuliaSet::setParameters(const double& a, const double& b){
	if((a >= -2.0 && a <= 2.0) && (b >= -2.0 && b <= 2.0)){
		this->mA = a;
		this->mB = b;
	}
}

void JuliaSet::calculateNextPoint(const double& x0, const double& y0, double& x1, double& y1) const{
	x1 = x0 * x0 - y0 * y0 + getA();
	y1 = 2 * x0 * y0 + getB();
}

int JuliaSet::calculatePlaneEscapeCount(const double& x0, const double& y0) const{
	double x1, y1, x2, y2, dist;
	int i;
	dist = std::sqrt((x0 - 0.0) * (x0 - 0.0) + (y0 - 0.0) * (y0 - 0.0));
	calculateNextPoint(x0, y0, x1, y1);
	i = 0;
	if(dist <= 2.0){
		while(i < getMaxNumber() && !(dist > 2.0)){
			x2 = x1;
			y2 = y1;
			dist = std::sqrt((x1 - 0.0) * (x1 - 0.0) + (y1 - 0.0) * (y1 - 0.0));
			calculateNextPoint(x2, y2, x1, y1);		
			i += 1;
		}
		return i;
	}
	else{
		return 0;
	}
}

int JuliaSet::calculateNumber(const int& row, const int& column) const{
	double x, y;
	if(indexValid(row, column)){
		calculatePlaneCoordinatesFromPixelCoordinates(row, column, x, y);
		return calculatePlaneEscapeCount(x,y);
	}
	else{
		return -1;
	}
}


// JuliaSetFour::JuliaSetFour():JuliaSet(){
// }
// JuliaSetFour::~JuliaSetFour(){
// 	(void)0;
// }
// void JuliaSetFour::calculateNextPoint(const double x0, const double y0, double& x1, double& y1) const{
// 	x1 = (x0 * x0 * x0 * x0) - 6 * (x0 * x0) * (y0 * y0) + (y0 * y0 * y0 * y0) + getA();
// 	y1 = 4 * (x0 * x0 * x0) * (y0) - 4 * x0 * (y0 * y0 * y0) + getB();
// }