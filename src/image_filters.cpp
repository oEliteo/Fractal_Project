#include<iostream>
#include <string>
#include "image_menu.h"
#include "PPM.h"
#include "Image.h"
#include "ActionData.h"
#include "MenuData.h"

void plusEquals( ActionData& action_data ) {
	action_data.getInputImage1() += action_data.getInputImage2();
}

void minusEquals( ActionData& action_data ) {
	action_data.getInputImage1() -= action_data.getInputImage2();
}

void timesEquals( ActionData& action_data ) {
	double value;
	value = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() *= value;
}

void divideEquals( ActionData& action_data ){
	double value;
	value = getDouble(action_data, "Factor? ");
	action_data.getInputImage1() /= value;
}

void plus( ActionData& action_data ){
	action_data.getOutputImage() = action_data.getInputImage1() + action_data.getInputImage2();
}

void minus( ActionData& action_data ){
	action_data.getOutputImage() = action_data.getInputImage1() - action_data.getInputImage2();
}

void times( ActionData& action_data ) {
	double value;
	value = getDouble(action_data, "Factor? ");
	action_data.getOutputImage() = action_data.getInputImage1() * value;
}

void divide( ActionData& action_data ){
	double value;
	value = getDouble(action_data, "Factor? ");
	action_data.getOutputImage() = action_data.getInputImage1() / value;
}

void grayFromRed(ActionData& action_data){
	action_data.getInputImage1().grayFromRed(action_data.getOutputImage());	
}

void grayFromGreen(ActionData& action_data){
	action_data.getInputImage1().grayFromGreen(action_data.getOutputImage());		
}

void grayFromBlue(ActionData& action_data){
	action_data.getInputImage1().grayFromBlue(action_data.getOutputImage());		
}

void grayFromLinearColorimetric(ActionData& action_data){
	action_data.getInputImage1().grayFromLinearColorimetric(action_data.getOutputImage());
}

void orangeFilter(ActionData& action_data){
	action_data.getInputImage1().orangeFilter(action_data.getOutputImage());
}

void antiAliasFilter(ActionData& action_data){
	int reduction;
	reduction = getInteger(action_data, "Reduction count? ");
	action_data.getInputImage1().antiAlias(reduction,action_data.getOutputImage());
}