#ifndef MATH_H
#define MATH_H

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

static float absf(float f)
{
	if(f < 0.f)
		return -f;
	return f;
}

static float modf(float x, int *integer)
{
	*integer = (int)x;
	return x - (int)x;
}

#ifndef MATH_EXTERNALLY_DEFINED
static float expf(float x)
{
	float result = 1.f;
	float term = 1.f;
	for(unsigned int i = 1; i < 16; ++i)
	{
		term *= x / (float)i;
		result += term;
	}
	return result;
}

static float logf(float x)
{
	if(x <= 0.f)
		return -1.f / 0.f;

	const float eps = 1e-6;
	const unsigned int N = 128;

	float x0 = x;
	for(unsigned int i = 0; i < N; ++i)
	{
		float g0 = expf(x0);
		float f0 = g0 - x;
		float x1 = x0 - f0 / g0;
		if(absf(x1 - x0) < eps)
			return x1;
		x0 = x1;
	}
	return x0;
}

static float powf(float base, float exp)
{
	if(base == 0)
		return (exp == 0) ? 1.f : 0.f;
	return expf(exp * logf(base));
}

static float factorial(float x)
{
	float total = 1.f;
	for(size_t i = 1; i <= x; i += 2)
	{
		if(i + 1 > x)
			total *= i;
		else
			total *= (i * (i + 1));
	}
	return total;
}

static float sinf(float x)
{
	float s = x;
	float n = 3;
	for(size_t i = 0; i < 32; ++i)
	{
		if(i % 2 == 0)
			s -= powf(x, n) / factorial(n);
		else
			s += powf(x, n) / factorial(n);
		n += 2;
	}
	return s;
}

static float cosf(float x)
{
	float s = 1.f;
	float n = 2;
	for(size_t i = 0; i < 32; ++i)
	{
		if(i % 2 == 0)
			s -= powf(x, n) / factorial(n);
		else
			s += powf(x, n) / factorial(n);
		n += 2;
	}
	return s;
}
#else
float expf(float);
float logf(float x);
float powf(float base, float exp);
float sinf(float x);
float cosf(float x);
float sqrtf(float x);
float tanf(float x);
double sqrt(double x);
double acos(double x);
double cos(double x);
double fmod(double x, double y);
double pow(double x, double y);
#endif

static double fabs(double x)
{
	if(x < 0.f)
		return -x;
	return x;
}

static double floor(double arg)
{
	return (int)arg;
}

static double ceil(double arg)
{
	return ((int)arg) + 1;
}

#endif
