class PerlinNoise {
	public:
		static double noise2D(double x,double y) {
			int X = (int)x;
			int Y = (int)y;
			x -= X;
			y -= Y;
			double u = fade(x);
			double v = fade(y);
			int A1 = p[X & 255]+Y;
			int A2 = p[A1 & 255];
			int A3 = p[(A1+1) & 255];
			int B1 = p[(X+1) & 255]+Y;
			int B2 = p[B1 & 255];
			int B3 = p[(B1+1) & 255];
			return 0.5+0.5*lerp(v,  lerp(u, grad(p[A2 & 255], x, y),
						grad(p[B2 & 255], x-1, y)),
					lerp(u, grad(p[A3 & 255], x, y-1),
						grad(p[B3 & 255], x-1, y-1)));
		}

	private:
		static double fade(double t) { return t*t*t*(t*(t*6-15)+10); }

		static double lerp(double t, double a, double b) { return a+t*(b-a); }

		static double grad(int hash, double x, double y) {
			return ((hash & 1) ? x : -x) + ((hash & 2) ? y : -y);
		}

		static int p[] = { 151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,190,6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,102,143,54,65,25,63,161,1,216,80,73,209,76,132,187,208,89,18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,223,183,170,213,119,248,152,2,44,154,163,70,221,153,101,155,167,43,172,9,129,22,39,253,19,98,108,110,79,113,224,232,178,185,112,104,218,246,97,228,251,34,242,193,238,210,144,12,191,179,162,241,81,51,145,235,249,14,239,107,49,192,214,31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };
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
			double amplitude = 0.5;
			for (unsigned int i = 0 ; i < m_layers ; i++) {
				value += Noise::noise2D((x+m_ox)*frequency, (y+m_oy)*frequency)*amplitude;
				frequency *= m_roughness;
				amplitude *= m_persistence;
			}
			return value;
		}
};
