#include "ComplexFractal.h"
#include "NumberGrid.h"
#include <cmath>

ComplexFractal::ComplexFractal():
ThreadedGrid(200, 300), mMin_x(-1.5), mMax_x(1.5), mMin_y(-1.0), mMax_y(1.0), mDeltaX(0.01), mDeltaY(0.01){
}

ComplexFractal::ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y ):
ThreadedGrid(height, width), mMin_x(min_x), mMax_x(max_x), mMin_y(min_y), mMax_y(max_y), mDeltaX(0.1), mDeltaY(0.1){
}

ComplexFractal::~ComplexFractal( ){
	(void)0;
}

double ComplexFractal::getMinX() const{
	return mMin_x;
}

double ComplexFractal::getMaxX() const{
	return mMax_x;
}

double ComplexFractal::getMinY() const{
	return mMin_y;
}

double ComplexFractal::getMaxY() const{
	return mMax_y;
}

void ComplexFractal::setGridSize(const int& height, const int& width){
	double dX, dY;
	if(height >= 2 && width >= 2){
		NumberGrid::setGridSize(height, width);
		dX = calculateDeltaX();
		dY = calculateDeltaY();
		setDeltas(dX, dY);
	}
}

void ComplexFractal::setPlaneSize(const double& min_x, const double& max_x, const double& min_y, const double& max_y){
	double place_holder;
	if(min_x >= -2.0 && min_x <= 2.0 && max_x >= -2.0 && max_x <= 2.0 && min_y >= -2.0 && min_y <= 2.0 && max_y >= -2.0 && max_y <= 2.0 && min_x != max_x && max_y != min_y){
		this->mMin_x = min_x;
		this->mMax_x = max_x;
		this->mMin_y = min_y;
		this->mMax_y = max_y;
		if(this->mMin_x > this->mMax_x){
			place_holder = this->mMin_x;
			this->mMin_x = this->mMax_x;
			this->mMax_x = place_holder;
		}
		if(this->mMin_y > this->mMax_y){
			place_holder = this->mMin_y;
			this->mMin_y = this->mMax_y;
			this->mMax_y = place_holder;
		}
		setDeltas(calculateDeltaX(), calculateDeltaY());
	}
}

double ComplexFractal::getDeltaX() const{
	return mDeltaX;
}

double ComplexFractal::getDeltaY() const{
	return mDeltaY;
}

void ComplexFractal::setDeltas(const double& delta_x, const double& delta_y){
	if(delta_x >= 0 && delta_y >= 0){
		mDeltaX = delta_x;
		mDeltaY = delta_y;
	}
}

double ComplexFractal::calculateDeltaY() const{
	return (mMax_y - mMin_y) / (getHeight() - 1);
}

double ComplexFractal::calculateDeltaX() const{
	return (mMax_x - mMin_x) / (getWidth() - 1);
}

double ComplexFractal::calculatePlaneXFromPixelColumn(const int& column) const{
	if(column < 0 || column >= getWidth()){
		return 0;
	}
	else{
		return (mMin_x + column * getDeltaX());
	}
}

double ComplexFractal::calculatePlaneYFromPixelRow(const int& row) const{
	if(row < 0 || row >= getHeight()){
		return 0;
	}
	else{
		return (mMax_y - row * getDeltaY());
	}
}

void ComplexFractal::calculatePlaneCoordinatesFromPixelCoordinates(const int& row, const int& column, double& x, double& y) const{
	if(row < 0 || row > getHeight()-1 || column > getWidth()-1 || column < 0){
		x = 0.0;
		y = 0.0;
	}
	else{
		x = calculatePlaneXFromPixelColumn(column);
		y = calculatePlaneYFromPixelRow(row);
	}
}

int ComplexFractal::calculateNumber(const int& row, const int& column) const{
	double x, y;

	if(indexValid(row, column)){
		x = calculatePlaneXFromPixelColumn(column);
		y = calculatePlaneYFromPixelRow(row);
		return (std::abs(getMaxNumber() * std::sin(10*x) * std::cos(10*y)));
	}
	else{
		return -1;
	}
}