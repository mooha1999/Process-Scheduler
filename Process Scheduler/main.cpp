#include <iostream>
#include "Scheduler.h"
using namespace std;
int main() {
	Scheduler scheduler("");
	scheduler.loadFromFile("input.txt"); //Name of the input file
	scheduler.Simulate();
}