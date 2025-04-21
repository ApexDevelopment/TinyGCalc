#define _USE_MATH_DEFINES
#include "types.h"

#include <math.h>
#include <stdbool.h>

extern bool angle_mode_deg;

// Forward trig (input in degrees if angle_mode_deg)
double sin_override(double x)
{
	if (angle_mode_deg) x *= M_PI / 180.0;
	return sin(x);
}

double cos_override(double x)
{
	if (angle_mode_deg) x *= M_PI / 180.0;
	return cos(x);
}

double tan_override(double x)
{
	if (angle_mode_deg) x *= M_PI / 180.0;
	return tan(x);
}

// Inverse trig (output in degrees if angle_mode_deg)
double asin_override(double x)
{
	double r = asin(x);
	return angle_mode_deg ? r * 180.0 / M_PI : r;
}

double acos_override(double x)
{
	double r = acos(x);
	return angle_mode_deg ? r * 180.0 / M_PI : r;
}

double atan_override(double x)
{
	double r = atan(x);
	return angle_mode_deg ? r * 180.0 / M_PI : r;
}

double atan2_override(double y, double x)
{
	double r = atan2(y, x);
	return angle_mode_deg ? r * 180.0 / M_PI : r;
}
