#include "objeto.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{
			namespace Cajita
			{


				Accion Objeto::recibir_evento (Evento evento, double delta_tiempo, Vehiculo *vehiculo)
				{
					Accion accion = NO_REALIZAR_ACCION;

					/*switch (evento)
					{
						case VEHICULO_COLISIONO_CON_OBSTACULO:
						{
							if (vehiculo->colisiono_con == this)
							{
								iterador_altura.go_down();
								accion = QUITAR_VIDA;
							}
							break;
						}

						case MODO_VEHICULO_INVENCIBLE:
						{
							iterador_altura.go_down();
							break;
						}

						case FIN_MODO_VEHICULO_INVENCIBLE:
						{
							iterador_altura.go_up();
							break;
						}

						default:
						{}
					}

					escala = iterador_altura (delta_tiempo);*/

					return accion;
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
					semilado = 1.0;
				}


			}
		}
	}
}
