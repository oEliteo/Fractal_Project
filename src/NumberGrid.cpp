#include <vector>
#include "NumberGrid.h"
#include "PPM.h"
#include "ColorTable.h"

NumberGrid::NumberGrid() :
mHeight(300), mWidth(400), mMax_val(255) {
	mGrid.resize(mHeight * mWidth);
	int row, col, max_col, max_row;
	max_row = mHeight;
	max_col = mWidth;
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			setNumber(row, col, 0);
		}
	}
}

NumberGrid::NumberGrid(const int& height, const int& width) :
mHeight(height), mWidth(width), mMax_val(255) {
	mGrid.resize(mHeight * mWidth);
	int row, col, max_col, max_row;
	max_row = this->getHeight();
	max_col = this->getWidth();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			setNumber(row, col, 0);
		}
	}
}

int NumberGrid::getWidth() const{
	return this->mWidth;
}

int NumberGrid::getHeight() const{
	return this->mHeight;
}

int NumberGrid::getMaxNumber() const{
	return this->mMax_val;
}

void NumberGrid::setGridSize(const int& height, const int& width){
	if(height >= 2 && width >= 2){
		this->mHeight = height;
		this->mWidth = width;
		this->mGrid.resize(mHeight * mWidth);
	}
}

void NumberGrid::setMaxNumber(const int& number){
	if(number >= 0){
		this->mMax_val = number;
	}
}

const std::vector<int>& NumberGrid::getNumbers() const{
	return this->mGrid;
}

int NumberGrid::index(const int& row, const int& column) const{
	return (row * this->mWidth) + column;
}

bool NumberGrid::indexValid(const int& row, const int& column) const{
	bool flag;
	flag = true;
	if (row > mHeight - 1 || row < 0){
		flag = false;
	}
	else if (column > mWidth - 1 || column < 0){
		flag = false;
	}
	else if (mGrid.size() < 1){
		flag = false;
	}
	return flag;
}

bool NumberGrid::numberValid(const int& number) const{
	bool flag;
	flag = false;
	if(number >= 0 && number <= this->getMaxNumber()){
		flag = true;
	}
	else{
		flag = false;
	}
	return flag;
}

int NumberGrid::getNumber(const int& row, const int& column) const{
	int value;
	value = -1;
	if(indexValid(row, column)){
		value = mGrid[index(row, column)];
	}
	else{
		value = -1;
	}
	return value;
}

void NumberGrid::setNumber(const int& row, const int& column, const int& number){
	if(indexValid(row, column) && numberValid(number)){
		mGrid[index(row, column)] = number;
	}
}

void NumberGrid::setPPM(PPM& ppm) const{
	ppm.setHeight(mHeight);
	ppm.setWidth(mWidth);
	ppm.setMaxColorValue(63);
	int row, col, max_row, max_col;
	max_row = this->getHeight();
	max_col = this->getWidth();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){

			if(getNumber(row, col) == 0){
				ppm.setPixel(row, col, 0, 0, 0);
			}
			else if(getNumber(row, col) == this->getMaxNumber()){
				ppm.setPixel(row, col, 63,31,31);
			}
			else if(getNumber(row, col) % 8 == 0){
				ppm.setPixel(row, col, 63,63,63);
			}
			else if(getNumber(row, col) % 8 == 1){
				ppm.setPixel(row, col, 63,31,31);
			}
			else if(getNumber(row, col) % 8 == 2){
				ppm.setPixel(row, col, 63,63,31);
			}
			else if(getNumber(row, col) % 8 == 3){
				ppm.setPixel(row, col, 31,63,31);
			}
			else if(getNumber(row, col) % 8 == 4){
				ppm.setPixel(row, col, 0,0,0);
			}
			else if(getNumber(row, col) % 8 == 5){
				ppm.setPixel(row, col, 31,63,63);
			}
			else if(getNumber(row, col) % 8 == 6){
				ppm.setPixel(row, col, 31,31,63);
			}
			else if(getNumber(row, col) % 8 == 7){
				ppm.setPixel(row, col, 63,31,63);
			}
		}
	}
}

void NumberGrid::setPPM(PPM& ppm, const ColorTable& colors) const{
	if(colors.getNumberOfColors() < 2){
		(void)0;
	}
	else if(colors.getNumberOfColors() >= 2){
		ppm.setHeight(mHeight);
		ppm.setWidth(mWidth);
		ppm.setMaxColorValue(colors.getMaxChannelValue());
		int row, col, max_row, max_col, max_num;
		max_num = getMaxNumber();
		Color color;
		max_row = this->getHeight();
		max_col = this->getWidth();
		for(row = 0; row < max_row; row += 1){
			for(col = 0; col < max_col; col += 1){
				if(getNumber(row, col) == max_num){
					color = colors[colors.getNumberOfColors() - 1];
					ppm.setPixel(row, col, color.getRed(), color.getGreen(), color.getBlue());
				}
				else{
					color = colors[getNumber(row,col) % colors.getNumberOfColors()];
					ppm.setPixel(row, col, color.getRed(), color.getGreen(), color.getBlue());
				}
			}
		}
	}
}

NumberGrid::~NumberGrid(){
	(void)0;
}

void NumberGrid::calculateAllNumbers(){
	int row, col, max_row, max_col;
	max_row = this->getHeight();
	max_col = this->getWidth();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			setNumber(row, col, calculateNumber(row, col));
		}
	}
}