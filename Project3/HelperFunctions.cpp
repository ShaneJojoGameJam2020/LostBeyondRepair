#include "HelperFunctions.h"
#include <utility>
int getTaxiCabDistance(std::pair<int, int> pair1, std::pair<int, int> pair2) {
	int Xdistance = pair1.first - pair2.first;
	int Ydistance = pair1.second - pair2.second;
	if (Xdistance < 0) {
		Xdistance = Xdistance * (-1);
	}
	if (Ydistance < 0) {
		Ydistance = Ydistance * (-1);
	}
	return Xdistance + Ydistance;
}