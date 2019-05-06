#include <string>
#include "Engine.h"

using namespace std;

int main() {
	string filePath = "./Assets/Config/config.xml";
	Engine* engine = new Engine(filePath);
	while(engine->run()) {}

	return 0;
}