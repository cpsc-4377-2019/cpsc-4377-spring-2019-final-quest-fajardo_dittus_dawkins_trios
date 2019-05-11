#include <string>
#include <vector>
#include "Engine.h"

using namespace std;

int main() {
	vector<string> levelPaths = { "./Assets/Config/config.xml", "./Assets/Config/config2.xml" };
	Engine* engine = new Engine(levelPaths);
	while(engine->run()) {}

	return 0;
}