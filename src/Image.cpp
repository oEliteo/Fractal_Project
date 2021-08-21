#include <vector>
#include <iostream>
#include "Image.h"

Image::Image()
: mHeight(0), mWidth(0) {
	mData.resize(mHeight * (mWidth * 3));
}
Image::Image(const int& height, const int& width)
  : mHeight(height), mWidth(width) {
  	mData.resize(mHeight * (mWidth * 3));
  }

int Image::getHeight() const {
	return mHeight;
}

int Image::getWidth() const {
	return mWidth;
}

bool Image::indexValid(const int& row, const int& column, const int& channel) const {
	bool flag;
	flag = true;
	unsigned long int vectorSize = mData.size();
	unsigned long int indexValue = index(row, column, channel);
	if (channel < 0 || channel > 2) {
		flag = false;
	}
	else if (row > mHeight - 1 || row < 0){
		flag = false;
	}
	else if (column > mWidth - 1 || column < 0){
		flag = false;
	}
	else if (indexValue > vectorSize){
		flag = false;
	}
	else if (vectorSize < 1){
		flag = false;
	}
	return flag;
}

int Image::index(const int& row, const int& column, const int& channel) const {
	return ((row * mWidth * 3) + (column * 3)) + channel;
}

int Image::getChannel( const int& row, const int& column, const int& channel ) const {
	int x;
	if(indexValid(row, column, channel) == true) {
		x = mData[(row * mWidth * 3 + column * 3) + channel];
	}
	else {
		x = -1;
	}
	return x;
}

void Image::setHeight( const int& height ) {
	if (height >= 0) {
		mHeight = height;
		mData.resize(mHeight * (mWidth * 3));
	}
	else {
		mHeight = mHeight;
	}
}

void Image::setWidth( const int& width ) {
	if (width >= 0) {
		mWidth = width;
		mData.resize(mHeight * (mWidth * 3));
	}
	else {
		mWidth = mWidth;
	}
}

void Image::setChannel( const int& row, const int& column, const int& channel, const int& value ) {
	if (indexValid(row, column, channel)) {
		mData[index(row, column, channel)] = value;
	}
}

