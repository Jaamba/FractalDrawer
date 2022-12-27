#include "Utilities.h"

//faster way to compute a square root
float fastSquareRoot(float n) {
	long i;
	float x2, y;
	const float threeHalfs = 1.5f;

	x2 = n * 0.5f;
	y = n;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;

	y = y * (threeHalfs - (x2 * y * y));
	y = y * (threeHalfs - (x2 * y * y));

	return y * n;
}