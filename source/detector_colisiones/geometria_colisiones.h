#ifndef GEOMETRIA_COLISIONES_H
#define GEOMETRIA_COLISIONES_H

#include <cstddef>
#include <initializer_list>


namespace urjr
{

		typedef double Coordenada;
		typedef double Longitud;


		template <size_t N>
		class Coord {
			private:

				Coordenada c[N];

			public:

				size_t size() {
					return N;
				}

				Coordenada & operator [] (size_t i) {
					return c[i];
				}

				Coordenada operator [] (size_t i) const {
					return c[i];
				}

				Coord & operator = (const Coord &coord) {
					for (size_t i = 0; i < N; i++)
						c[i] = coord[i];
					return *this;
				}

				Coord & operator = (const Coordenada coord[N]) {
					for (size_t i = 0; i < N; i++)
						c[i] = coord[i];
					return *this;
				}

				Coord & operator = (std::initializer_list <Coordenada> il) {
					const Coordenada *v = begin(il);
					size_t n = end(il) - begin(il);
					if (n > N) n = N;
					for (size_t i = 0; i < n; ++i)
						c[i] = v[i];
					return *this;
				}

				Coord (const Coord &coord) {
					this->operator = (coord);
				}

				Coord (const Coordenada coord[N]) {
					this->operator = (coord);
				}

				Coord (std::initializer_list <Coordenada> il) {
					this->operator = (il);
				}

				Coord ()
				{}
		};

		typedef Coord<2> Punto2D; // 0: x. 1: y.
		typedef Coord<3> Punto3D; // 0: x. 1: y. 2: z.
		typedef Coord<2> Intervalo; // 0: mínimo. 1: máximo.

		enum
		{
			X = 0,
			Y,
			Z,

			MIN = 0,
			MAX
		};

		struct Rectangulo {
			Intervalo
				x,
				y;
		};

		struct Circulo {
			Punto2D
				centro;

			Longitud
				radio;
		};


	namespace Colisiones
	{


		// Devuelve la distancia entre dos puntos.
		Longitud distancia (Punto2D &, Punto2D &);
		Longitud distancia (Punto3D &, Punto3D &);

		// Obtiene la coordenada más cercana a "referencia" delimitada por el intervalo.
		Coordenada coordenada_mas_cercana (Intervalo &intervalo, Coordenada referencia);
		Coordenada coordenada_mas_cercana (Coordenada min, Coordenada max, Coordenada referencia);

		// Comprueba si dos intervalos se superponen.
		bool se_superponen (Intervalo &i1, Intervalo &i2);
		bool se_superponen (Coordenada min1, Coordenada max1, Coordenada min2, Coordenada max2);

		// Comprueba si colisionan dos objetos dados.
		bool colisionan (Rectangulo *, Rectangulo *);
		bool colisionan (Circulo *, Circulo *);
		bool colisionan (Rectangulo *, Circulo *);


	}
}


#endif // GEOMETRIA_COLISIONES_H
