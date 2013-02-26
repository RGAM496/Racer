#ifndef URJR_REGLAS_AMBIENTE_ESTANDAR_H
#define URJR_REGLAS_AMBIENTE_ESTANDAR_H

#include "interfaz.h"


namespace urjr
{
	namespace Ambiente
	{
		namespace Estandar
		{


			class Reglas
			: virtual public Interfaz
			{
				protected:

					std::vector <Objeto::GeneradorMovil *>
						// Tendrá todos los generadores de obstáculos.
						generadorObstaculo;

					Objeto::GeneradorVehiculo
						// Tendrá al generador del vehículo.
						*generadorVehiculo;

					RandomGenerator::Discrete <Objeto::GeneradorMovil *>
						// Generará al azar los obstáculos.
						obstaculo_aleatorio;

					RandomGenerator::UniformReal <double>
						// Indicará al azar una nueva posición para el obstáculo.
						posicion_aleatoria;

					std::default_random_engine
						// Generador aleatorio para 'obstaculo_aleatorio' y 'posicion_aleatoria'.
						generador_aleatorio;

					Time::Tick <double>
						// Hará un tick cada vez que se cumpla cierta distancia.
						tickDistancia,
						// Hará un tick cada vez que deba aumentarse la velocidad.
						tickVelocidad;

				public:

					Reglas ();
					Reglas (Objeto::GeneradorVehiculo *);
					~Reglas ();

					void cargar_vehiculo (Objeto::GeneradorVehiculo *);
					void destruir_vehiculo ();

					// Procesa el juego, y devuelve si se continúa jugando.
					bool jugar ();

				public:

					void desplazar_objetos ();
					void analizar_colisiones ();

					// No es igual a la acción que realiza la misma tarea, pero cumple otro rol.
					void aumentar_velocidad ();

					void realizar_accion (Objeto::Accion);
					void accion_quitar_vida ();
					void accion_dar_vida ();
					void accion_aumentar_velocidad ();
					void accion_reducir_velocidad ();
					void accion_activar_invencibilidad ();
					void accion_desactivar_invencibilidad ();
					void accion_al_azar ();

					void generar_obstaculo ();
					void destruir_obstaculos ();
					void destruir_obstaculos (unsigned int);
			};


		}
	}
}


#endif // URJR_REGLAS_AMBIENTE_ESTANDAR_H
