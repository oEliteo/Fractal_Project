#include <iostream>
#include <string>
#include <vector>
#include "Image.h"
#include "image_menu.h"
#include "PPM.h"
#include "NumberGrid.h"
#include "ComplexFractal.h"
#include "JuliaSet.h"
#include "MandelbrotSet.h"

int assignment1 (std::istream& is, std::ostream& os) {
	ActionData x(is, os);
	return askQuestions3(x);
}

int assignment2(std::istream& is, std::ostream& os) {
	ActionData x(is, os);
	diagonalQuadPattern(x);
	x.getOutputImage() = x.getInputImage1();
	drawAsciiImage(x);
	return 0;
}

int assignment3(std::istream& is, std::ostream& os) {
	ActionData x(is, os);
	stripedDiagonalPattern(x);
	x.getOutputImage() = x.getInputImage1();
	writeUserImage(x);
	return 0;
}

int four_square( std::istream& is, std::ostream& os ) {
	ActionData x(is, os);
	fourSquarePattern(x);
	x.getOutputImage() = x.getInputImage1();
	writeUserImage(x);
	return 0;
}

int simple_squares_ascii(std::istream& is, std::ostream& os) {
	ActionData x(is, os);
	simpleSquaresPattern(x);
	x.getOutputImage() = x.getInputImage1();
	drawAsciiImage(x);
	return 0;
}

int imageMenu(std::istream& is, std::ostream& os) {
	ActionData x(is, os);
	ComplexFractal *grid;
	grid = new ComplexFractal;
	x.setGrid(grid);
	MenuData y;
	configureMenu(y);
	while (x.getDone() != true && x.getIS().good()) {
		takeAction(getChoice(x), y, x);
	}
	return 0;
}

void setComplexFractal( ActionData& action_data ){
	ComplexFractal *grid;
	grid = new ComplexFractal;
	action_data.setGrid(grid);
}

void setJuliaFractal( ActionData& action_data ){
	JuliaSet *grid;
	grid = new JuliaSet;
	action_data.setGrid(grid);
}

void setMandelbrotFractal( ActionData& action_data ){
	MandelbrotSet *grid;
	grid = new MandelbrotSet;
	action_data.setGrid(grid);
}

// void setMandelbrotPowerFractal( ActionData& action_data ){
// 	MandelbrotPower *grid;
// 	grid = new MandelbrotPower;
// 	action_data.setGrid(grid);
// }

// void setJuliaFourFractal(ActionData& action_data){
// 	JuliaSetFour * grid;
// 	grid = new JuliaSetFour;
// 	action_data.setGrid(grid);
// }