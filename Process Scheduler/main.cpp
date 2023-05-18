#include <iostream>
#include "Scheduler.h"
using namespace std;
int main() {
	Scheduler scheduler("");
	scheduler.loadFromFile(""); //Name of the input file
	scheduler.Simulate();
}