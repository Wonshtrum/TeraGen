#ifndef __NOISE_H__
#define __NOISE_H__

class PerlinNoise {
	public:
		static double noise2D(double x,double y);

	private:
		static double fade(double t);

		static double lerp(double t, double a, double b);

		static double grad(int hash, double x, double y);

		static int p[];
};


#endif