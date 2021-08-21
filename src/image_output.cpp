#include <iostream>
#include <vector>
#include "Image.h"
#include "image_menu.h"
#include <string>
#include <fstream>

void drawAsciiImage(ActionData& action_data) {
	int row;
	int col;
	int max_row;
	int max_col;
	std::string display;
	Image& image = action_data.getOutputImage();
	max_row = image.getHeight();
	max_col = image.getWidth();

	for (row = 0; row < max_row; row += 1) {
		for (col = 0; col < max_col; col += 1) {
			double strength;
			strength = (image.getChannel(row, col, 0) + image.getChannel(row, col, 1) + image.getChannel(row, col, 2)) / 765.0;
			if (strength >= 1.0) {
				display += '@';
			}
			else if (strength >= 0.9) {
				display += '#';
			}
			else if (strength >= 0.8) {
				display += '%';
			}
			else if (strength >= 0.7) {
				display += '*';
			}
			else if (strength >= 0.6) {
				display += '|';
			}
			else if (strength >= 0.5) {
				display += '+';
			}
			else if (strength >= 0.4) {
				display += ';';
			}
			else if (strength >= 0.3) {
				display += '~';
			}
			else if (strength >= 0.2) {
				display += '-';
			}
			else if (strength >= 0.1) {
				display += '.';
			}
			else if (strength >= 0.0) {
				display += ' ';
			}
		}
		display = display + '\n';
	}
	action_data.getOS() << display;
}

void writeUserImage( ActionData& action_data) {
	std::string outputFileName;
	PPM& p = action_data.getOutputImage();
	outputFileName = getString(action_data, "Output filename? ");
	std::ofstream file(outputFileName);
	p.writeStream(file);
	file.close();
}

void copyImage(ActionData& action_data) {
	action_data.getOutputImage() = action_data.getInputImage1();
}

void readUserImage1(ActionData& action_data) {
	std::string inputFileName;
	inputFileName = getString(action_data, "Input filename? ");
	std::ifstream file(inputFileName);
	action_data.getInputImage1().readStream(file);
	file.close();
}

void readUserImage2(ActionData& action_data) {
	std::string inputFileName;
	inputFileName = getString(action_data, "Input filename? ");
	std::ifstream file(inputFileName);
	action_data.getInputImage2().readStream(file);
	file.close();
}

void copyOutputImageToImage1(ActionData& action_data){
	action_data.getInputImage1() = action_data.getOutputImage();
}