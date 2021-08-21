#ifndef _MENUDATA_H_
#define _MENUDATA_H_
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ActionData.h"

typedef void (*ActionFunctionType)(ActionData& action_data);
class MenuData {
  public:
  	MenuData();
  	void addAction(const std::string& name, ActionFunctionType func, const std::string& description);
  	const std::vector<std::string>& getNames() const;
  	ActionFunctionType getFunction(const std::string& name);
  	const std::string& getDescription(const std::string& name);
  private:
  	std::vector<std::string> mCommands;
  	std::map<std::string,ActionFunctionType> mName_function_map;
  	std::map<std::string,std::string> mName_description_map;
};

#endif //_MENUDATA_H_