#include "colisiones.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Piramide
			{


				void DetectorColisiones::base (Rectangulo *r)
				{
					r->x[MIN] = centro_base[X] - semilado;
					r->x[MAX] = centro_base[X] + semilado;
					r->y[MIN] = centro_base[Z] - semilado;
					r->y[MAX] = centro_base[Z] + semilado;
				}


				void DetectorColisiones::base (Rectangulo *r, Longitud h)
				{
					Longitud
						// Semilado que se usará para generar el nuevo rectángulo.
						sl = semilado * (1 - h / altura_actual);

					r->x[MIN] = centro_base[X] - sl;
					r->x[MAX] = centro_base[X] + sl;
					r->y[MIN] = centro_base[Z] - sl;
					r->y[MAX] = centro_base[Z] + sl;
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
					return semilado * 2.0;
				}


				void DetectorColisiones::zona_influencia (Intervalo &i)
				{
					i[MIN] = centro_base[Z] - semilado;
					i[MAX] = centro_base[Z] + semilado;
				}


			}
		}
	}
}
