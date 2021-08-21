#include <iostream>
#include "ActionData.h"
#include "ColorTable.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

ActionData::ActionData(std::istream& is, std::ostream& os): 
mIS(is), mOS(os), mDone(false), mGridPointer(0), mColorTable(16) {
	int position1, position2;
	Color color1, color2;
	color1 = Color(0,255,0);
	color2 = Color(255,0,255);
	position1 = 0;
	position2 = 15;
	mColorTable.insertGradient(color1, color2, position1, position2);
}

std::istream& ActionData::getIS() {
	return mIS;
}

std::ostream& ActionData::getOS() {
	return mOS;
}

PPM& ActionData::getInputImage1() {
	return mImageIn1;
}

PPM& ActionData::getInputImage2() {
	return mImageIn2;
}

PPM& ActionData::getOutputImage() {
	return mImageOut;
}

bool ActionData::getDone() const {
	return mDone;
}

void ActionData::setDone() {
	mDone = true;
}

NumberGrid& ActionData::getGrid(){
	return *mGridPointer;
}

void ActionData::setGrid(NumberGrid *grid){
	if(mGridPointer != 0){
		delete mGridPointer;
	}
	mGridPointer = grid;
}

ActionData::~ActionData() {
	if(mGridPointer != 0){
		delete mGridPointer;
		mGridPointer = 0;
	}
}

ColorTable& ActionData::getTable(){
	return mColorTable;
}