#include "ColorTable.h"
#include <vector>
#include "image_menu.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Color::Color(): 
mRed(0), mGreen(0), mBlue(0) {

}

Color::Color(const int& red, const int& green, const int& blue):
mRed(red), mGreen(green), mBlue(blue) {

}

int Color::getRed() const {
	return mRed;
}

int Color::getGreen() const {
	return mGreen;
}

int Color::getBlue() const {
	return mBlue;
}

int Color::getChannel(const int& channel) const{
	if(channel == 0){
		return mRed;
	}
	else if(channel == 1){
		return mGreen;
	}
	else if(channel == 2){
		return mBlue;
	}
	else {
		return -1;
	}
}

void Color::setRed(const int& value) {
	if(value >= 0){
		mRed = value;
	}
}

void Color::setGreen(const int& value) {
	if(value >= 0){
		mGreen = value;
	}
}

void Color::setBlue(const int& value) {
	if(value >= 0){
		mBlue = value;
	}
}

void Color::setChannel(const int& channel, const int& value) {
	if(channel == 0){
		setRed(value);
	}
	else if(channel == 1){
		setGreen(value);
	}
	else if(channel == 2){
		setBlue(value);
	}
}

void Color::invert(const int& max_color_value) {
	if(max_color_value >= this->getRed() && max_color_value >= this->getGreen() && max_color_value >= this->getBlue()){
		this->setRed(max_color_value - this->getRed());
		this->setGreen(max_color_value - this->getGreen());
		this->setBlue(max_color_value - this->getBlue());
	}
}

bool Color::operator==(const Color& rhs) const {
	bool value;
	if(this->getRed() == rhs.getRed() && this->getGreen() == rhs.getGreen() && this->getBlue() == rhs.getBlue()){
		value = true;
	}
	else{
		value = false;
	}
	return value;
}

std::ostream& operator<<( std::ostream& os, const Color& color ){
	int red, green, blue;
	red = color.getRed();
	green = color.getGreen();
	blue = color.getBlue();
	os << red << ":" << green << ":" << blue;
	return os;
}

ColorTable::ColorTable(const int& num_color):
mColorTable(0) {
	mColorTable.resize(num_color);
}

int ColorTable::getNumberOfColors() const {
	return this->mColorTable.size();
}

void ColorTable::setNumberOfColors(const int& num_color ) {
	this->mColorTable.resize(num_color);
}

const Color& ColorTable::operator[]( const int& i ) const {
	static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
	if(i < 0){
		return c;
	}
	else if(i >= this->getNumberOfColors()){
		return c;
	}
	else{
		return mColorTable[i];
	}
}

Color& ColorTable::operator[]( const int& i ) {
	static Color ec( -1, -1, -1 );
    static Color c( -1, -1, -1 );
    c = ec;
	if(i < 0){
		return c;
	}
	else if(i >= this->getNumberOfColors()){
		return c;
	}
	else{
		return mColorTable[i];
	}
}

void ColorTable::setRandomColor( const int& max_color_value, const int& position) {
	int red, green, blue;
	if(max_color_value < 0){
		(void)0;
	}
	else if(position < 0){
		(void)0;
	}
	else if(position > getNumberOfColors()){
		(void)0;
	}
	else if(max_color_value > 0){
		red = (std::rand() % max_color_value);
		green = (std::rand() % max_color_value);
		blue = (std::rand() % max_color_value);
		mColorTable[position].setRed(red);
		mColorTable[position].setGreen(green);
		mColorTable[position].setBlue(blue);
	}
	else{
		red = 0;
		green = 0;
		blue = 0;
		mColorTable[position].setRed(red);
		mColorTable[position].setGreen(green);
		mColorTable[position].setBlue(blue);
	}
}

double ColorTable::gradientSlope(const double y1, const double y2, const double x1, const double x2) const {
	return (y2 - y1) / (x2 - x1);
}

double ColorTable::gradientValue(const double y1, const double x1, const double slope, const double x) const {
	return slope * (x - x1) + y1;
}

void ColorTable::insertGradient(const Color& color1, const Color& color2, const int& position1, const int& position2) {
	int i;
	double red_slope, green_slope, blue_slope;
	red_slope = gradientSlope(color1.getRed(), color2.getRed(), position1, position2);
	green_slope = gradientSlope(color1.getGreen(), color2.getGreen(), position1, position2);
	blue_slope = gradientSlope(color1.getBlue(), color2.getBlue(), position1, position2);

	if(position1 >= position2){
		(void)0;
	}
	else if(position1 < 0){
		(void)0;
	}
	else if(position1 >= getNumberOfColors()){
		(void)0;
	}
	else if(position2 < 0){
		(void)0;
	}
	else if(position2 >= getNumberOfColors()){
		(void)0;
	}
	else{
		for(i = position1; i <= position2; i += 1 ){
			mColorTable[i].setRed(gradientValue(color1.getRed(),position1,red_slope,i));
			mColorTable[i].setGreen(gradientValue(color1.getGreen(),position1,green_slope,i));
			mColorTable[i].setBlue(gradientValue(color1.getBlue(),position1,blue_slope,i));
		}
	}

}

int ColorTable::getMaxChannelValue() const {
	int i, max_value, num_colors;
	max_value = 0;
	num_colors = getNumberOfColors();
	Color color;
	for(i = 0; i < num_colors; i += 1){
		color = mColorTable[i];
		if(color.getRed() > max_value){
			max_value = color.getRed();
		}
		if(color.getGreen() > max_value){
			max_value = color.getGreen();
		}
		if(color.getBlue() > max_value){
			max_value = color.getBlue();
		}
	}
	return max_value;
}