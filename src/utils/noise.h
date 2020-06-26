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

template <class Noise>
class LayeredNoise {
	private:
		double m_persistence;
		double m_baseRoughness;
		double m_roughness;
		double m_ox;
		double m_oy;
		unsigned int m_layers;
	public:
		LayeredNoise(unsigned int layers=3, double persistence=0.5, double baseRoughness=1, double roughness=2, double ox=0, double oy=0): m_persistence(persistence), m_baseRoughness(baseRoughness), m_roughness(roughness), m_ox(ox), m_oy(oy), m_layers(layers) {}

		~LayeredNoise() {}

		double sample(double x, double y) {
			double value = 0;
			double frequency = m_baseRoughness;
			double amplitude = 1;
			for (unsigned int i = 0 ; i < m_layers ; i++) {
				value += Noise::noise2D(x*frequency+m_ox, y*frequency+m_oy)*amplitude;
				frequency *= m_roughness;
				amplitude *= m_persistence;
			}
			return value;
		}
};


#endif