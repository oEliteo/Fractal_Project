#include "image_menu.h"
#include <cstdlib>
#include <ctime>

int main() {
	std::srand(std::time(0));
	return imageMenu(std::cin, std::cout);
}