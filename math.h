#ifndef MATH_H
#define MATH_H

#ifndef M_PI
#    define M_PI 3.14159265358979323846
#endif

float expf(float x)
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

float absf(float f)
{
	if(f < 0.f)
		return -f;
	return f;
}

float modf(float x, int *integer)
{
	*integer = (int)x;
	return x - (int)x;
}

float logf(float x)
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

float powf(float base, float exp)
{
	if(base == 0)
		return (exp == 0) ? 1.f : 0.f;
	return expf(exp * logf(base));
}

float factorial(float x)
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

float sinf(float x)
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

float cosf(float x)
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

#endif
