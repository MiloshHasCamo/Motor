#ifndef COLOR_H_
#define COLOR_H_

enum { r = 0, g = 1, b = 2, a = 3 };

typedef float* RGB ;
typedef float* RGBA;
typedef float* BGR ;
typedef float* BGRA;

struct sRGBA
{
	float r, g, b, a;
};

struct sRGB
{
	float r, g, b;
};

struct sBGR
{
	float b, g, r;
};

struct sBGRA
{
	float b, g, r, a;
};

#endif//COLOR_H_