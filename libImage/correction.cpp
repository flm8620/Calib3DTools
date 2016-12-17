#include "correction.h"

#include <cmath>
#include <vector>
#include <assert.h>

using std::vector;

Vector2D undistortPixel(const Bi<vector<double> >& params, const Vector2D& distort)
{

	const double *xcoeff = params.x.data(), *ycoeff = params.y.data();
	const std::size_t xsize = params.x.size(), ysize = params.y.size();
	unsigned xDegree = (isqrt(8 * xsize + 1) - 1) / 2 - 1, yDegree, maxOrder;

	assert(xsize == (xDegree + 1)*(xDegree + 2) / 2);

	if (ysize == xsize)
		yDegree = maxOrder = xDegree;
	else
	{
		yDegree = (isqrt(8 * ysize + 1) - 1) / 2 - 1;
		assert(ysize == (yDegree + 1)*(yDegree + 2) / 2);

		maxOrder = yDegree > xDegree ? yDegree : xDegree;
	}


	//prepare power values per bit, that's x**0, **1, **2, **4...y**0, y**1...etc.
	const static int MAX_ORDER_BITS = std::log2(MAX_POLYNOME_ORDER) + 1;
	vector<double> bitPowerX(MAX_ORDER_BITS + 1), bitPowerY(MAX_ORDER_BITS + 1);
	double bpx, bpy;
	bitPowerX[0] = bitPowerY[0] = 1.;
	bpx = distort.x, bpy = distort.y;
	for (unsigned mask = UINT_MAX, i = 1; maxOrder & mask; mask <<= 1, i++, bpx *= bpx, bpy *= bpy) {
		bitPowerX[i] = bpx; bitPowerY[i] = bpy;
	}

	//calculate the values of the polynomials
	Vector2D result = { *(xcoeff++), *(ycoeff++) };
	for (int degree = 1; degree <= maxOrder; degree++)
		for (int i = degree, j = 0; i >= 0; i--, j++) {
			//calculate indeterminate = x**i * y**j
			double indeterminate = 1.;
			for (unsigned mask = UINT_MAX, bit = 1, bitmask = 1;
				(i | j) & mask;
				mask <<= 1, bitmask <<= 1, bit++) {
				if (bitmask&i) indeterminate *= bitPowerX[bit];
				if (bitmask&j) indeterminate *= bitPowerY[bit];
			}

			//add current term, coefficient * x**i * y**j , to results.
			if (degree <= xDegree) result.x += *(xcoeff++)*indeterminate;
			if (degree <= yDegree) result.y += *(ycoeff++)*indeterminate;
		}
	return result;
}

