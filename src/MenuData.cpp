#include "MenuData.h"

MenuData::MenuData() {
}

void MenuData::addAction(const std::string& name, ActionFunctionType func, const std::string& description) {
	mName_function_map[name] = func;
	mName_description_map[name] = description;
	mCommands.push_back(name);
}

const std::vector<std::string>& MenuData::getNames() const {
	return mCommands;
}

ActionFunctionType MenuData::getFunction(const std::string& name) {
	if (mName_function_map.find(name) != mName_function_map.end()) {
		return mName_function_map[name];
	}
	else{
		return 0;
	}
}

const std::string& MenuData::getDescription(const std::string& name) {
	if (mName_description_map.find(name) != mName_description_map.end()) {
		return mName_description_map[name];
	}
	else{
		static std::string empty;
		empty = "";
		return empty;
	}
}