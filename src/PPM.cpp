#include "PPM.h"
#include "Image.h"
#include "image_menu.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>

PPM::PPM()
: Image(), mMaxColorValue(1) {
}

PPM::PPM(const int& height, const int& width): 
	Image(height, width), mMaxColorValue(1) {
	}


int PPM::getMaxColorValue() const {
	return mMaxColorValue;
}

bool PPM::valueValid(const int& value) const {
	return value <= mMaxColorValue && value >= 0;
}
void PPM::setMaxColorValue(const int& max_color_value) {
	if (max_color_value > 0 && max_color_value <= 255) {
		mMaxColorValue = max_color_value;
	}
}

void PPM::setChannel(const int& row, const int& column, const int& channel, const int& value) {
	if (valueValid(value) == true) {
		Image::setChannel(row, column, channel, value);
	}
}

void PPM::setPixel(const int& row, const int& column, const int& red, const int& green, const int& blue) {
	if (valueValid(red) == true) {
		setChannel(row, column, 0, red);
	}
	if (valueValid(green) == true) {
		setChannel(row, column, 1, green);
	}
	if (valueValid(blue) == true) {
		setChannel(row, column, 2, blue);
	}
}

void PPM::writeStream(std::ostream& os) const {
	os << "P6" << " " << getWidth() << " " << getHeight() << " " << mMaxColorValue << "\n";
	int row, col, max_row, max_col, channel;
	unsigned char value;
	max_row = getHeight();
	max_col = getWidth();
	for (row = 0; row < max_row; row += 1) {
		for (col = 0; col < max_col; col += 1) {
			for (channel = 0; channel <= 2; channel += 1){
				value = getChannel(row, col, channel);
				os.write((char*) &value, sizeof(value));
			}
		}
	}
}

void PPM::readStream(std::istream& is) {
	int row, col, max_row, max_col, channel, max_color_value;
	std::string word;
	unsigned char c, value;
	is >> word >> max_col >> max_row >> max_color_value;
	is.read((char*) &c, 1);
	setMaxColorValue(max_color_value);
	setHeight(max_row);
	setWidth(max_col);
	for (row = 0; row < max_row; row += 1) {
		for (col = 0; col < max_col; col += 1) {
			for (channel = 0; channel <= 2; channel += 1){
				is.read((char*) &value, 1);
				setChannel(row, col, channel, value);
			}
		}
	}
}

void PPM::grayFromChannel(PPM& dst, const int& src_channel) const{
	int row, col, max_row, max_col, max_color, value;
	max_row = this->getHeight();
	max_col = this->getWidth();
	max_color = this->getMaxColorValue();
	dst.setMaxColorValue(max_color);
	dst.setHeight(max_row);
	dst.setWidth(max_col);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			value = this->getChannel(row, col, src_channel);
			dst.setPixel(row, col, value, value, value);
		} 
	}
}

void PPM::grayFromRed(PPM& dst) const {
	grayFromChannel(dst, 0);
}

void PPM::grayFromGreen(PPM& dst) const{
	grayFromChannel(dst, 1);
}

void PPM::grayFromBlue(PPM& dst) const{
	grayFromChannel(dst, 2);
}

double PPM::linearColorimetricPixelValue(const int& row, const int& column) const{
	return ((0.2126 * this->getChannel(row, column, 0)) + (0.7152 * this->getChannel(row, column, 1)) + (0.0722 * this->getChannel(row, column, 2)));
}

void PPM::grayFromLinearColorimetric(PPM& dst) const {
	int row, col, max_row, max_col, max_color;
	double brightness;
	max_row = this->getHeight();
	max_col = this->getWidth();
	max_color = this->getMaxColorValue();
	dst.setWidth(max_col);
	dst.setHeight(max_row);
	dst.setMaxColorValue(max_color);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			brightness = linearColorimetricPixelValue(row, col);
			dst.setPixel(row, col, brightness, brightness, brightness);
		} 
	}
}

void PPM::orangeFilter(PPM& dst) const {
	int row, col, max_row, max_col, max_color, new_red, new_green, new_blue;
	max_row = this->getHeight();
	max_col = this->getWidth();
	max_color = this->getMaxColorValue();
	dst.setWidth(max_col);
	dst.setHeight(max_row);
	dst.setMaxColorValue(max_color);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			new_red = (2 * ((2 * this->getChannel(row, col, 0)) + this->getChannel(row, col, 1))) / 3;
			new_green = (2 * ((2 * (this->getChannel(row, col, 0))) + this->getChannel(row, col, 1))) / 6;
			new_blue = this->getChannel(row, col, 2) / 2;
			if(new_red > max_color){
				new_red = max_color;
			}
			else if(new_red < 0){
				new_red = 0;
			}

			if(new_green > max_color){
				new_green = max_color;
			}
			else if(new_green < 0){
				new_green = 0;
			}

			if(new_blue > max_color){
				new_blue = max_color;
			}
			else if(new_blue < 0){
				new_blue = 0;
			}
			dst.setPixel(row, col, new_red, new_green, new_blue);
		}
	}
}

bool PPM::operator==(const PPM& rhs) const{
	bool flag;
	flag = false;
	int thisPixels, rhsPixels;
	thisPixels = this->getHeight() * (this->getWidth() * 3);
	rhsPixels = rhs.getHeight() * (rhs.getWidth() * 3);

	if (thisPixels == rhsPixels){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

bool PPM::operator!=(const PPM& rhs) const{
	bool flag;
	flag = false;
	int thisPixels, rhsPixels;
	thisPixels = this->getHeight() * (this->getWidth() * 3);
	rhsPixels = rhs.getHeight() * (rhs.getWidth() * 3);

	if(thisPixels != rhsPixels){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

bool PPM::operator<(const PPM& rhs) const{
	bool flag;
	flag = false;
	int thisPixels, rhsPixels;
	thisPixels = this->getHeight() * (this->getWidth() * 3);
	rhsPixels = rhs.getHeight() * (rhs.getWidth() * 3);

	if(thisPixels < rhsPixels){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

bool PPM::operator<=(const PPM& rhs) const{
	bool flag;
	flag = false;
	int thisPixels, rhsPixels;
	thisPixels = this->getHeight() * (this->getWidth() * 3);
	rhsPixels = rhs.getHeight() * (rhs.getWidth() * 3);

	if(thisPixels <= rhsPixels){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

bool PPM::operator>(const PPM& rhs) const{
	bool flag;
	flag = false;
	int thisPixels, rhsPixels;
	thisPixels = this->getHeight() * (this->getWidth() * 3);
	rhsPixels = rhs.getHeight() * (rhs.getWidth() * 3);

	if(thisPixels > rhsPixels){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

bool PPM::operator>=(const PPM& rhs) const{
	bool flag;
	flag = false;
	int thisPixels, rhsPixels;
	thisPixels = this->getHeight() * (this->getWidth() * 3);
	rhsPixels = rhs.getHeight() * (rhs.getWidth() * 3);

	if(thisPixels >= rhsPixels){
		flag = true;
	}
	else{
		flag = false;
	}

	return flag;
}

PPM& PPM::operator+=(const PPM& rhs){
	int row, col, channel, max_row, max_col, v1, v2, v3;
	max_col = this->getWidth();
	max_row = this->getHeight();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v2 = rhs.getChannel(row, col, channel);
				v3 = v1 + v2;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				else if(v3 < 0) {
					v3 = 0;
				}
				this->setChannel(row, col, channel, v3);
			}
		}
	}
	return (*this);
}

PPM& PPM::operator-=(const PPM& rhs){
	int row, col, channel, max_row, max_col, v1, v2, v3;
	max_col = this->getWidth();
	max_row = this->getHeight();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v2 = rhs.getChannel(row, col, channel);
				v3 = v1 - v2;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				else if(v3 < 0) {
					v3 = 0;
				}
				this->setChannel(row, col, channel, v3);
			}
		}
	}
	return (*this);
}

PPM& PPM::operator*=(const double& rhs){
	int row, col, channel, max_row, max_col, v1, v3;
	max_col = this->getWidth();
	max_row = this->getHeight();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v3 = v1 * rhs;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				else if(v3 < 0) {
					v3 = 0;
				}
				this->setChannel(row, col, channel, v3);
			}
		}
	}
	return (*this);
}

PPM& PPM::operator/=(const double& rhs){
	int row, col, channel, max_row, max_col, v1, v3;
	max_col = this->getWidth();
	max_row = this->getHeight();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v3 = v1 / rhs;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				else if(v3 < 0) {
					v3 = 0;
				}
				this->setChannel(row, col, channel, v3);
			}
		}
	}
	return (*this);
}

PPM PPM::operator+(const PPM& rhs) const {
	int row, col, channel, max_row, max_col, max_val, v1, v2, v3;
	PPM p;
	max_col = this->getWidth();
	max_row = this->getHeight();
	max_val = this->getMaxColorValue();
	p.setHeight(max_row);
	p.setWidth(max_col);
	p.setMaxColorValue(max_val);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v2 = rhs.getChannel(row, col, channel);
				v3 = v1 + v2;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				p.setChannel(row, col, channel, v3);
			}
		}
	}
	return p;
}

PPM PPM::operator-(const PPM& rhs) const{
	int row, col, channel, max_row, max_col, max_val, v1, v2, v3;
	PPM p;
	max_col = this->getWidth();
	max_row = this->getHeight();
	max_val = this->getMaxColorValue();
	p.setHeight(max_row);
	p.setWidth(max_col);
	p.setMaxColorValue(max_val);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v2 = rhs.getChannel(row, col, channel);
				v3 = v1 - v2;
				if(v3 < 0){
					v3 = 0;
				}
				p.setChannel(row, col, channel, v3);
			}
		}
	}
	return p;
}

PPM PPM::operator*(const double& rhs) const{
	int row, col, channel, max_row, max_col, max_val, v1, v3;
	PPM p;
	max_col = this->getWidth();
	max_row = this->getHeight();
	max_val = this->getMaxColorValue();
	p.setHeight(max_row);
	p.setWidth(max_col);
	p.setMaxColorValue(max_val);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v3 = v1 * rhs;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				else if(v3 < 0){
					v3 = 0;
				}
				p.setChannel(row, col, channel, v3);
			}
		}
	}
	return p;
}

PPM PPM::operator/(const double& rhs) const{
	int row, col, channel, max_row, max_col, max_val, v1, v3;
	PPM p;
	max_col = this->getWidth();
	max_row = this->getHeight();
	max_val = this->getMaxColorValue();
	p.setHeight(max_row);
	p.setWidth(max_col);
	p.setMaxColorValue(max_val);
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				v1 = this->getChannel(row, col, channel);
				v3 = v1 / rhs;
				if(v3 > this->getMaxColorValue()){
					v3 = this->getMaxColorValue();
				}
				else if(v3 < 0){
					v3 = 0;
				}
				p.setChannel(row, col, channel, v3);
			}
		}
	}
	return p;
}

int PPM::antiAliasPixelValue(int n, int row, int column, int channel) const{
	int big_row, big_col, total_channel;
	total_channel = 0;
	for(big_row = n * row; big_row < (row + 1) * n; big_row += 1){
		for(big_col = column * n; big_col < (column + 1) * n; big_col += 1){
			total_channel += getChannel(big_row, big_col, channel);
		}
	}
	return total_channel / (n * n);
}

void PPM::antiAlias(const int& n, PPM& dst) const{
	int row, col, channel, value, max_row, max_col;
	dst.setHeight(this->getHeight() * 1/n);
	dst.setWidth(this->getWidth() * 1/n);
	dst.setMaxColorValue(this->getMaxColorValue());
	max_row = dst.getHeight();
	max_col = dst.getWidth();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1){
				value = antiAliasPixelValue(n, row, col, channel);
				dst.setChannel(row, col, channel, value);
			}
		}
	}
}