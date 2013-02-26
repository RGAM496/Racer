#include "geometria_colisiones.h"
#include <cmath>

#ifdef DEBUG_COLISION
	#include <iostream>
	#define debug(expr) std::cout << expr << std::endl
	#define test(x) debug ("\t" #x " = " << x)
#else
	#define debug(expr) {}
	#define test(x) {}
#endif


namespace urjr
{
	namespace Colisiones
	{

		Longitud distancia (Punto2D &p1, Punto2D &p2)
		{
			Longitud
				dx = p1[X] - p2[X],
				dy = p1[Y] - p2[Y];

			dx *= dx;
			dy *= dy;

			return sqrt(dx + dy);
		}

		Longitud distancia (Punto3D &p1, Punto3D &p2)
		{
			Longitud
				dx = p1[X] - p2[X],
				dy = p1[Y] - p2[Y],
				dz = p1[Z] - p2[Z];

			dx *= dx;
			dy *= dy;
			dz *= dz;

			return sqrt(dx + dy + dz);
		}


		//inline
		Coordenada coordenada_mas_cercana (Intervalo &intervalo, Coordenada referencia)
		{
			return coordenada_mas_cercana (intervalo[MIN], intervalo[MAX], referencia);
		}

		Coordenada coordenada_mas_cercana (Coordenada min, Coordenada max, Coordenada referencia)
		{
			if (min > referencia)
				return min;
			if (max < referencia)
				return max;
			return referencia;
		}


		//inline
		bool se_superponen (Intervalo &i1, Intervalo &i2)
		{
			return se_superponen (i1[MIN], i1[MAX], i2[MIN], i2[MAX]);
		}

		bool se_superponen (Coordenada min1, Coordenada max1, Coordenada min2, Coordenada max2)
		{
			if (min1 > max2)
				return false;
			if (min2 > max1)
				return false;
			return true;
		}


		bool colisionan (Rectangulo *r1, Rectangulo *r2)
		{
			debug ("\t\tC_CC");

			return
				se_superponen (r1->x, r2->x) &&
				se_superponen (r1->y, r2->y);
		}

		bool colisionan (Circulo *c1, Circulo *c2)
		{
			debug ("\t\tC_CC");
			
			Longitud
				dc = distancia (c1->centro, c2->centro),
				dr = c1->radio + c2->radio;

			return
				dc <= dr;
		}

		bool colisionan (Rectangulo *r, Circulo *c)
		{
			debug ("\t\tC_RC");

			Punto2D
				p; // Punto más cercano de "r" respecto a "c";

			p[X] = coordenada_mas_cercana (r->x, c->centro[X]);
			p[Y] = coordenada_mas_cercana (r->y, c->centro[Y]);

			debug ("\t\tCoordenada mas cercana.");
			test (p[X]);
			test (p[Y]);

			return
				distancia (p, c->centro) <= c->radio;
		}
	}
}

#undef debug
#undef test
