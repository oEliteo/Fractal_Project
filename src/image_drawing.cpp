#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include "image_menu.h"
#include "Image.h"
#include "PPM.h"
#include "MenuData.h"
#include "JuliaSet.h"
#include "ComplexFractal.h"

void diagonalQuadPattern(ActionData& action_data ) {
	PPM& image = action_data.getInputImage1();
	image.setHeight(getInteger(action_data, "Image height? "));
	image.setWidth(getInteger(action_data, "Image width? "));
	int row;
	int col;
	int max_col;
	int max_row;
	max_row = image.getHeight();
	max_col = image.getWidth();
	image.setMaxColorValue(255);
	for (row = 0; row < max_row; row += 1) {
		for (col = 0; col < max_col; col += 1) {
			if (row < max_row / 2 && col < max_col / 2) {
				//Set Red Channel For Top Left Quarter of image
				image.setChannel(row, col, 0, 0);
				//Set Green Channel For Top Left Quarter of image
				image.setChannel(row, col, 1, ( 2*row + 2*col ) % 256);
				//Set Blue Channel For Top Left Quarter of Image
				image.setChannel(row, col, 2, 0);
			}
			else if (row < max_row / 2 && col >= max_col / 2) {
				//Set Red Channel For Top Right Quarter of Image
				image.setChannel(row, col, 0, 0);
				//Set Green Channel For Top Right Quarter of Image
				image.setChannel(row, col, 1, ( 2*row + 2*col ) % 256);
				//Set Blue Channel For Top Right Quarter of Image
				image.setChannel(row, col, 2, 255);
			}
			else if (row >= max_row / 2 && col < max_col / 2) {
				//Set Red Channel For Bottom Left Quarter of Image
				image.setChannel(row, col, 0, 255);
				//Set Green Channel For Bottom Left Quarter Of Image
				image.setChannel(row, col, 1, ( 2*row + 2*col ) % 256);
				//Set Blue Channel For Bottom Left Quarter of Image
				image.setChannel(row, col, 2, 0);
			}
			else if (row >= max_row / 2 && col >= max_col / 2) {
				//Set Red Channel For Bottom Right Quarter of Image
				image.setChannel(row, col, 0, 255);
				//Set Green Channel For Bottom Right Quarter of Image
				image.setChannel(row, col, 1, ( 2*row + 2*col ) % 256);
				//Set Blue Channel For Bottom Right Quarter of Image
				image.setChannel(row, col, 2, 255);
			}
		}
	}
}

void stripedDiagonalPattern(ActionData& action_data ) {
	PPM& p = action_data.getInputImage1();
	p.setHeight(getInteger(action_data, "Image height? "));
	p.setWidth(getInteger(action_data, "Image width? "));
	int row, col, max_row, max_col, max, min;
	max = (p.getHeight() + p.getWidth()) / 3;
	max_row = p.getHeight();
	max_col = p.getWidth();
	min = 0;

	if (max > 255) {
		max = 255;
	}

	else if (max <= 0) {
		max = 1;
	}

	p.setMaxColorValue(max);

	for (row = 0; row < max_row; row += 1) {

		for (col = 0; col < max_col; col += 1) {

			if (row < (max_row / 2) && col < row) {
				p.setPixel(row, col, min, (row + p.getWidth() - col - 1) % (max + 1), min);
			}

			else if (row < (max_row / 2) && col >= row) {
				p.setPixel(row, col, min, (row + p.getWidth() - col - 1) % (max + 1), max);
			}

			else if (row >= (max_row / 2) && col < row) {

				if (row % 3 == 0) {
					p.setPixel(row, col, min, (row + p.getWidth() - col - 1) % (max + 1), min);
				}

				else {
					p.setPixel(row, col, max, (row + p.getWidth() - col - 1) % (max + 1), min);
				}
			}

			else if (row >= (max_row / 2) && col >= row) {

				if (row % 3 == 0) {
					p.setPixel(row, col, min, (row + p.getWidth() - col - 1) % (max + 1), max);
				}

				else {
					p.setPixel(row, col, max, (row + p.getWidth() - col - 1) % (max + 1), max);
				}
			} 
		}
	}
}

void fourSquarePattern(ActionData& action_data ) {
	int size, row, col, max_row, max_col, max;
	PPM& p = action_data.getInputImage1();
	size = getInteger(action_data, "Image size? ");
	max = 100;
	p.setMaxColorValue(max);
	p.setHeight(size);
	p.setWidth(size);
	max_row = p.getHeight();
	max_col = p.getWidth();
	for (row = 0; row < max_row; row += 1) {
		for (col = 0; col < max_col; col += 1) {
			if (row < max_row / 2 && col < max_col / 2) {
				p.setPixel(row, col, 100, 0, 66);
			}
			else if (row < max_row / 2 && col >= max_col / 2) {
				p.setPixel(row, col, 0, 100, 33);
			}
			else if (row >= max_row / 2 && col < max_col / 2) {
				p.setPixel(row, col, 66, 33, 100);
			}
			else if (row >= max_row / 2 && col >= max_col / 2) {
				p.setPixel(row, col, 33, 66, 0);
			}
		}
	}
}

void simpleSquaresPattern(ActionData& action_data) {
	int size, row, col, max_row, max_col;
	Image& image = action_data.getInputImage1();
	size = getInteger(action_data, "Image size? ");
	image.setHeight(size);
	image.setWidth(size);
	max_row = image.getHeight();
	max_col = image.getWidth();
	for (row = 0; row < max_row; row += 1) {
		for (col = 0; col < max_col; col += 1) {
			if (row < max_row / 2 && col < max_col / 2) {
				//Set Red Channel For Top Left Quarter of image
				image.setChannel(row, col, 0, 127);
				//Set Green Channel For Top Left Quarter of image
				image.setChannel(row, col, 1, 0);
				//Set Blue Channel For Top Left Quarter of Image
				image.setChannel(row, col, 2, 255);
			}
			else if (row < max_row / 2 && col >= max_col / 2) {
				//Set Red Channel For Top Left Quarter of image
				image.setChannel(row, col, 0, 127);
				//Set Green Channel For Top Left Quarter of image
				image.setChannel(row, col, 1, 255);
				//Set Blue Channel For Top Left Quarter of Image
				image.setChannel(row, col, 2, 255);
			}
			else if (row >= max_row / 2 && col < max_col / 2) {
				//Set Red Channel For Top Left Quarter of image
				image.setChannel(row, col, 0, 255);
				//Set Green Channel For Top Left Quarter of image
				image.setChannel(row, col, 1, 0);
				//Set Blue Channel For Top Left Quarter of Image
				image.setChannel(row, col, 2, 255);			}
			else if (row >= max_row / 2 && col >= max_col / 2) {
				//Set Red Channel For Top Left Quarter of image
				image.setChannel(row, col, 0, 255);
				//Set Green Channel For Top Left Quarter of image
				image.setChannel(row, col, 1, 255);
				//Set Blue Channel For Top Left Quarter of Image
				image.setChannel(row, col, 2, 255);			}
		}
	}
}

void setSize(ActionData& action_data) {
	int height, width;
	height = getInteger(action_data, "Height? ");
	width = getInteger(action_data, "Width? ");
	action_data.getInputImage1().setHeight(height);
	action_data.getInputImage1().setWidth(width);
}

void setMaxColorValue(ActionData& action_data) {
	int max_color_value;
	max_color_value = getInteger(action_data, "Max color value? ");
	action_data.getInputImage1().setMaxColorValue(max_color_value);
}

void setChannel(ActionData& action_data) {
	int row, col, channel, value;
	row = getInteger(action_data, "Row? ");
	col = getInteger(action_data, "Column? ");
	channel = getInteger(action_data, "Channel? ");
	value = getInteger(action_data, "Value? ");
	action_data.getInputImage1().setChannel(row, col, channel, value);
}

void setPixel(ActionData& action_data) {
	int row, col, red, green, blue;
	row = getInteger(action_data, "Row? ");
	col = getInteger(action_data, "Column? ");
	red = getInteger(action_data, "Red? ");
	green = getInteger(action_data, "Green? ");
	blue = getInteger(action_data, "Blue? ");
	action_data.getInputImage1().setPixel(row, col, red, green, blue);
}

void clearAll(ActionData& action_data) {
	int row, col, max_row, max_col, channel;
	max_row = action_data.getInputImage1().getHeight();
	max_col = action_data.getInputImage1().getWidth();
	for(row = 0; row < max_row; row += 1) {
		for(col = 0; col < max_col; col += 1){
			for(channel = 0; channel <= 2; channel += 1) {
				action_data.getInputImage1().setChannel(row, col, channel, 0);
			}
		}
	}
}

void showMenu(MenuData& menu_data, ActionData& action_data) {
	int sizeOfNames, i;
	sizeOfNames = menu_data.getNames().size();
	for(i = 0; i < sizeOfNames; i += 1) {
		action_data.getOS() << menu_data.getNames()[i] << ") " << menu_data.getDescription(menu_data.getNames()[i]) << "\n";
	}

}

void takeAction(const std::string& choice, MenuData& menu_data, ActionData& action_data) {
	ActionFunctionType function = menu_data.getFunction(choice);
	if (function != 0) {
		function(action_data);
	}
	else if (choice == "menu") {
		showMenu(menu_data, action_data);
	}
	else if (choice != "menu" && function == 0) {
		action_data.getOS() << "Unknown action \'" << choice << "\'.\n";
	}
}

void configureMenu(MenuData& menu_data) {
	menu_data.addAction("draw-ascii", *drawAsciiImage, "Write output image to terminal as ASCII art.");
	menu_data.addAction("write", *writeUserImage,"Write output image to file.");
	menu_data.addAction("copy", *copyImage, "Copy input image 1 to output image.");
	menu_data.addAction("read1", *readUserImage1, "Read file into input image 1.");
	menu_data.addAction("#", *commentLine, "Comment to end of line.");
	menu_data.addAction("size", *setSize, "Set the size of input image 1.");
	menu_data.addAction("max-color-value", *setMaxColorValue, "Set the max color value of input image 1.");
	menu_data.addAction("channel", *setChannel, "Set a channel value in input image 1.");
	menu_data.addAction("pixel", *setPixel, "Set a pixel's 3 values in input image 1.");
	menu_data.addAction("clear", *clearAll, "Set all pixels to 0,0,0 in input image 1.");
	menu_data.addAction("quit", *quit, "Quit.");
	menu_data.addAction("read2", *readUserImage2, "Read file into input image 2.");
	menu_data.addAction("+", *plus, "Set output image from sum of input image 1 and input image 2.");
	menu_data.addAction("+=", *plusEquals, "Set input image 1 by adding in input image 2.");
	menu_data.addAction("-", *minus, "Set output image from difference of input image 1 and input image 2.");
	menu_data.addAction("-=", *minusEquals, "Set input image 1 by subtracting input image 2.");
	menu_data.addAction("*", *times, "Set output image from input image 1 multiplied by a number.");
	menu_data.addAction("*=", *timesEquals, "Set input image 1 by multiplying by a number.");
	menu_data.addAction("/", *divide, "Set output image from input image 1 divided by a number.");
	menu_data.addAction("/=", *divideEquals, "Set input image 1 by dividing by a number.");
	menu_data.addAction("red-gray", *grayFromRed, "Set output image by grayscale from red on input image 1.");
	menu_data.addAction("green-gray", *grayFromGreen, "Set output image by grayscale from green on input image 1.");
	menu_data.addAction("blue-gray", *grayFromBlue, "Set output image by grayscale from blue on input image 1.");
	menu_data.addAction("linear-gray", *grayFromLinearColorimetric, "Set output image by linear colorimetric grayscale on input image 1.");
	menu_data.addAction("circle", *drawCircle, "Draw a circle shape in input image 1.");
	menu_data.addAction("box", *drawBox, "Draw a box shape in input image 1.");
	menu_data.addAction("orange", *orangeFilter, "Set output image from orange filter on input image 1.");
	menu_data.addAction("square", *drawSquare, "Draw a square shape in input image 1.");
	menu_data.addAction("grid", *configureGrid, "Configure the grid.");
	menu_data.addAction("grid-set", *setGrid, "Set a single value in the grid.");
	menu_data.addAction("grid-apply", *applyGrid, "Use the grid values to set colors in the output image.");
	menu_data.addAction("set-color-table-size", *setColorTableSize, "Change the number of slots in the color table.");
	menu_data.addAction("set-color", *setColor, "Set the RGB values for one slot in the color table.");
	menu_data.addAction("set-random-color", *setRandomColor, "Randomly set the RGB values for one slot in the color table.");
	menu_data.addAction("set-color-gradient", *setColorGradient, "Smoothly set the RGB values for a range of slots in the color table.");
	menu_data.addAction("grid-apply-color-table", *applyGridColorTable, "Use the grid values to set colors in the output image using the color table.");
	menu_data.addAction("fractal-plane-size", *setFractalPlaneSize, "Set the dimensions of the grid in the complex plane.");
	menu_data.addAction("fractal-calculate", *calculateFractal, "Calculate the escape values for the fractal, multi-thread.");
	menu_data.addAction("fractal-calculate-single-thread", *calculateFractalSingleThread, "Calculate the escape values for the fractal, single-thread.");
	menu_data.addAction("julia-parameters", *setJuliaParameters, "Set the parameters of the Julia Set function.");
	menu_data.addAction("complex-fractal", *setComplexFractal, "Choose to make a complex plane.");
	menu_data.addAction("julia", *setJuliaFractal, "Choose to make a Julia set.");
	menu_data.addAction("mandelbrot", *setMandelbrotFractal, "Choose to make a Mandelbrot set.");
	menu_data.addAction("anti-alias", *antiAliasFilter, "Set output image from Anti-alias filter on input image 1.");
	menu_data.addAction("copyo1", *copyOutputImageToImage1, "Copy output image to input image 1.");
	// menu_data.addAction("mandelbrot-power", *setMandelbrotFractal, "Choose to make a Mandelbrot set with the power function.");
	// menu_data.addAction("set-mandelbrot-power", *setMandelbrotPower, "Choose a power for the Mandelbrot power function.");
	// menu_data.addAction("julia-four", *setJuliaFourFractal, "Choose to make a Julia set with the fourth power function.");
}

void drawCircle(ActionData& action_data) {
	int row, col, max_row, max_col, centerRow, centerCol, radius, redValue, greenValue, blueValue;
	double distance;
	max_row = action_data.getInputImage1().getHeight();
	max_col = action_data.getInputImage1().getWidth();
	centerRow = getInteger(action_data, "Center Row? ");
	centerCol = getInteger(action_data, "Center Column? ");
	radius = getInteger(action_data, "Radius? ");
	redValue = getInteger(action_data, "Red? ");
	greenValue = getInteger(action_data, "Green? ");
	blueValue = getInteger(action_data, "Blue? ");
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			distance = std::sqrt(((centerRow - row) * (centerRow - row)) + (centerCol - col) * (centerCol - col));
			if(distance <= radius){
				action_data.getInputImage1().setPixel(row, col, redValue, greenValue, blueValue);
			}
		}
	}
}

void drawBox(ActionData& action_data){
	int row, col, max_row, max_col, left_col, top_row, bottom_row, right_col, redValue, greenValue, blueValue;
	max_row = action_data.getInputImage1().getHeight();
	max_col = action_data.getInputImage1().getWidth();
	top_row = getInteger(action_data, "Top Row? ");
	left_col = getInteger(action_data, "Left Column? ");
	bottom_row = getInteger(action_data, "Bottom Row? ");
	right_col = getInteger(action_data, "Right Column? ");
	redValue = getInteger(action_data, "Red? ");
	greenValue = getInteger(action_data, "Green? ");
	blueValue = getInteger(action_data, "Blue? ");
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			if((row >= top_row && col >= left_col) && (row <= bottom_row && col <= right_col)){
				action_data.getInputImage1().setPixel(row, col, redValue, greenValue, blueValue);
			}
		}
	}
}

void drawSquare(ActionData& action_data){
	int centerRow, centerCol, row, col, max_row, max_col, size, red, green, blue, top_row, left_col, bottom_row, right_col;
	centerRow = getInteger(action_data, "Row? ");
	centerCol = getInteger(action_data, "Column? ");
	size = getInteger(action_data, "Size? ");
	red = getInteger(action_data, "Red? ");
	green = getInteger(action_data, "Green? ");
	blue = getInteger(action_data, "Blue? ");
	max_row = action_data.getInputImage1().getHeight();
	max_col = action_data.getInputImage1().getWidth();
	top_row = centerRow - (size / 2 );
	bottom_row = centerRow + (size / 2);
	left_col = centerCol - (size / 2 );
	right_col = centerCol + (size / 2 );

	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			if((row >= top_row && col >= left_col) && (row <= bottom_row && col <= right_col)){
				action_data.getInputImage1().setPixel(row, col, red, green, blue);
			}
		}
	}
}

void configureGrid(ActionData& action_data){
	int gridHeight, gridWidth, maxNumber;
	gridHeight = getInteger(action_data, "Grid Height? ");
	gridWidth = getInteger(action_data, "Grid Width? ");
	maxNumber = getInteger(action_data, "Grid Max Value? ");
	action_data.getGrid().setGridSize(gridHeight, gridWidth);
	action_data.getGrid().setMaxNumber(maxNumber);
}

void setGrid(ActionData& action_data){
	int gridRow, gridCol, gridVal;
	gridRow = getInteger(action_data, "Grid Row? ");
	gridCol = getInteger(action_data, "Grid Column? ");
	gridVal = getInteger(action_data, "Grid Value? ");
	action_data.getGrid().setNumber(gridRow, gridCol, gridVal);
}

void applyGrid(ActionData& action_data){
	action_data.getGrid().setPPM(action_data.getOutputImage());
}

void setColorTableSize(ActionData& action_data){
	int size;
	size = getInteger(action_data, "Size? ");
	action_data.getTable().setNumberOfColors(size);
}

void setColor(ActionData& action_data){
	int position, red, green, blue;
	position = getInteger(action_data, "Position? ");
	red = getInteger(action_data, "Red? ");
	green = getInteger(action_data, "Green? ");
	blue = getInteger(action_data, "Blue? ");
	action_data.getTable()[position].setRed(red);
	action_data.getTable()[position].setGreen(green);
	action_data.getTable()[position].setBlue(blue);
}

void setRandomColor(ActionData& action_data){
	int position;
	position = getInteger(action_data, "Position? ");
	action_data.getTable().setRandomColor(255, position);
}

void setColorGradient(ActionData& action_data){
	int firstPosition, firstRed, firstGreen, firstBlue, secondPosition, secondRed, secondGreen, secondBlue;
	firstPosition = getInteger(action_data, "First position? ");
	firstRed = getInteger(action_data, "First red? ");
	firstGreen = getInteger(action_data, "First green? ");
	firstBlue = getInteger(action_data, "First blue? ");
	secondPosition = getInteger(action_data, "Second position? ");
	secondRed = getInteger(action_data, "Second red? ");
	secondGreen = getInteger(action_data, "Second green? ");
	secondBlue = getInteger(action_data, "Second blue? ");
	Color color1, color2;
	color1.setRed(firstRed);
	color1.setGreen(firstGreen);
	color1.setBlue(firstBlue);
	color2.setRed(secondRed);
	color2.setGreen(secondGreen);
	color2.setBlue(secondBlue);
	action_data.getTable().insertGradient(color1, color2, firstPosition, secondPosition);
}

void applyGridColorTable(ActionData& action_data){
	action_data.getGrid().setPPM(action_data.getOutputImage(), action_data.getTable());
}

void setFractalPlaneSize(ActionData& action_data){
	ComplexFractal *ptr = dynamic_cast<ComplexFractal*>(&action_data.getGrid());
  	if(ptr != 0){
  		double minX, maxX, minY, maxY;
		minX = getDouble(action_data, "Min X? ");
		maxX = getDouble(action_data, "Max X? ");
		minY = getDouble(action_data, "Min Y? ");
		maxY = getDouble(action_data, "Max Y? ");
		ptr->setPlaneSize(minX, maxX, minY, maxY);
  	}
  	else{
  		action_data.getOS() << "Not a ComplexFractal object. Can't set plane size.";
  	}
}

void calculateFractal(ActionData& action_data){
	int row, col, max_row, max_col;
	max_row = action_data.getGrid().getHeight();
	max_col = action_data.getGrid().getWidth();
	for(row = 0; row < max_row; row += 1){
		for(col = 0; col < max_col; col += 1){
			action_data.getGrid().setNumber(row, col, action_data.getGrid().calculateNumber(row, col));
		}
	}
}

void setJuliaParameters(ActionData& action_data){
	JuliaSet *ptr = dynamic_cast<JuliaSet*>(&action_data.getGrid());
	if(ptr != 0){
		double a, b;
		a = getDouble(action_data, "Parameter a? ");
		b = getDouble(action_data, "Parameter b? ");
		ptr->setParameters(a, b);
	}
	else{
		action_data.getOS() << "Not a JuliaSet object. Can’t set parameters.";
	}
}

void calculateFractalSingleThread(ActionData& action_data){
	action_data.getGrid().NumberGrid::calculateAllNumbers();
}

// void setMandelbrotPower( ActionData& action_data ){
// 	MandelbrotPower *ptr = dynamic_cast<MandelbrotPower*>(&action_data.getGrid());
// 	if(ptr != 0){
// 		double power;
// 		power = getDouble(action_data, "Power? ");
// 		ptr->setPower(power);
// 	}
// 	else{
// 		action_data.getOS() << "Not a MandelbrotPower object. Can’t set power.";
// 	}
// }

