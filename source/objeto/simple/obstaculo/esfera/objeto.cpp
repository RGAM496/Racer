#include "objeto.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Esfera
			{


				Accion Objeto::recibir_evento (Evento evento, double delta_tiempo, Vehiculo *vehiculo)
				{
					switch (evento)
					{
						case VEHICULO_COLISIONO_CON_OBSTACULO:
						{
							if (vehiculo->colisiono_con == this)
							{
								iterador_altura.go_down();
							}
							break;
						}

						default:
						{}
					}

					escala = iterador_altura (delta_tiempo);

					return NO_REALIZAR_ACCION;
				}


				void Objeto::desplazar (double magnitud, Direccion direccion)
				{
					switch (direccion)
					{
						case IZQUIERDA:
							centro_base[X] -= magnitud;
							break;

						case DERECHA:
							centro_base[X] += magnitud;
							break;

						case ADELANTE:
							centro_base[Z] -= magnitud;
							break;

						case ATRAS:
							centro_base[Z] += magnitud;
							break;
					}
				}


				Objeto::Objeto ()
				{
					setSiempreColisionable();
				}


			}
		}
	}
}
