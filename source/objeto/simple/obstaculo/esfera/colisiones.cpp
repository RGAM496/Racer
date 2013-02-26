#include "colisiones.h"
#include <cmath>


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Esfera
			{


				void DetectorColisiones::centro (Punto3D &punto)
				{
					punto[X] = centro_base[X];
					punto[Y] = centro_base[Y] + altura_actual / 2.0;
					punto[Z] = centro_base[Z];
				}


				Longitud DetectorColisiones::radio ()
				{
					return radio_cuerpo;
				}


				void DetectorColisiones::base (Circulo *c)
				{
					c->centro[X] = centro_base[X];
					c->centro[Y] = centro_base[Z];
					c->radio = radio_cuerpo;
				}


				void DetectorColisiones::base (Circulo *c, Longitud h)
				{
					Longitud
						// Altura de la figura si altura_actual == 2 * radio_cuerpo.
						h_r,
						// Radio del circulo resultante.
						r;

					h_r = h / altura_actual * (2.0 * radio_cuerpo);
					r = h_r - radio_cuerpo;
					r *= r;
					r = sqrt (radio_cuerpo * radio_cuerpo + r);

					c->centro[X] = centro_base[X];
					c->centro[Y] = centro_base[Z];
					c->radio = r;
				}


				void DetectorColisiones::altura (Intervalo &i)
				{
					i[MIN] = centro_base[Y];
					i[MAX] = centro_base[Y] + altura_actual;
				}


				void DetectorColisiones::getPosicionCentral (Punto3D &punto)
				{
					punto = centro_base;
				}


				void DetectorColisiones::setPosicionCentral (const Punto3D &punto)
				{
					centro_base = punto;
				}


				Longitud DetectorColisiones::ancho_maximo ()
				{
					return radio_cuerpo * 2.0;
				}


				void DetectorColisiones::zona_influencia (Intervalo &i)
				{
					i[MIN] = centro_base[Z] - radio_cuerpo;
					i[MAX] = centro_base[Z] + radio_cuerpo;
				}


			}
		}
	}
}