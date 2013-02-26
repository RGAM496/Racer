#ifndef URJR_BASE_AMBIENTE_ESTANDAR_H
#define URJR_BASE_AMBIENTE_ESTANDAR_H

#include "../../objeto/objeto.h"
#include "../../objeto/generador_objetos.h"
#include "../../tiempo/time.h"
#include "../../generator/random_generator.h"
#include "../../keyboard/glfw_keyboard.h"
#include <vector>


namespace urjr
{
	namespace Ambiente
	{
		namespace Estandar
		{


			class Base
			{
				public:

					Rectangulo
						// Establece los límites de la pista.
						pista;

					Objeto::Evento
						// Indica el último evento ocurrido.
						ultimo_evento;

					Objeto::Accion
						// Indica la última acción ocurrida.
						ultima_accion;

					Objeto::Vehiculo
						// Apuntará al vehículo que se usará durante el juego.
						*vehiculo;

					std::vector <Objeto::Movil *>
						// Almacenará los obstáculos que se crearán y destruirán.
						obstaculo;

					double
						// Tiempo en el estado actual.
						new_time,
						// Tiempo en estado anterior.
						old_time,
						// Diferencia de los tiempos.
						delta_time,
						// Distancia que recorre a velocidad '1.0'.
						velocidad_base;

					KeyboardInterface
						// Manejador del teclado.
						key;
			};


		}
	}
}


#endif // URJR_BASE_AMBIENTE_ESTANDAR_H
