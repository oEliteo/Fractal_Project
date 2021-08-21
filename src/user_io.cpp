#include <iostream>
#include <string>
#include "image_menu.h"
#include "ActionData.h"
//Timestamp Change

std::string getString( ActionData& action_data, const std::string& prompt ) {
	std::string result;
	action_data.getOS() << prompt;
	action_data.getIS() >> result;
	return result;
}

int getInteger( ActionData& action_data, const std::string& prompt ) {
	int result;
	action_data.getOS() << prompt;
	action_data.getIS() >> result;
	return result;
}

double getDouble( ActionData& action_data, const std::string& prompt ) {
	double result;
	action_data.getOS() << prompt;
	action_data.getIS() >> result;
	return result;
}

std::string getChoice( ActionData& action_data ) {
	return getString(action_data, "Choice? ");
}

void commentLine( ActionData& action_data ) {
	unsigned char x;
	x = 0;
	while (action_data.getIS().good() && x != '\n') {
		action_data.getIS().read((char*) &x, 1);
	}
}

void quit(ActionData& action_data) {
	action_data.setDone();
}

int askQuestions3(ActionData& action_data) {
	std::string color;
	color = getString(action_data, "What is your favorite color? ");

	int integer;
	integer = getInteger(action_data, "What is your favorite integer? ");

	double number;
	number = getDouble(action_data, "What is your favorite number? ");

	int i;
	for (i = 1; i <= integer; i += 1) {
		action_data.getOS() << i << ' ' << color << ' ' << number << std::endl;
	}

	return integer;
}
