#include "reglas.h"
#include "../../objeto/simple/obstaculos.h"

#ifdef DEBUG
	#include <iostream>
	#define debug(expr) std::cout << expr << std::endl
	#define test(x) debug ("\t" #x " = " << x)
#else
	#define debug(expr) {}
	#define test(x) {}
#endif


namespace urjr
{
	namespace Ambiente
	{
		namespace Estandar
		{
			using namespace Objeto;


			const Rectangulo
				// Dimensiones de la pista.
				r_pista = {
					{-10.0, 10.0},
					{-150.0, 25.0}
				};

			const double
				// Distancia para que ocurra un tick.
				DISTANCIA_TICK = 10.0,
				// Tiempo que debe transcurrir para que cambie la velocidad.
				PERIODO_CAMBIO_VELOCIDAD = 10.0,
				// Distancia recorrida a velocidad '1.0'.
				VELOCIDAD_BASE = 0.3,
				// Coordenadas predeterminadas al generarse el obstáculo.
				NUEVO_OBSTACULO_Y = 0.01,
				NUEVO_OBSTACULO_Z = r_pista.y[MIN];


			Reglas::Reglas ()
			: generadorObstaculo {
					&Simple::piramide_roja,
					&Simple::cubo_verde,
					&Simple::cilindro_amarillo,
					&Simple::esfera_blanca,
					&Simple::esfera_azul,
					&Simple::esfera_fucsia,
					&Simple::esfera_negra
				}
			, obstaculo_aleatorio {
					{&Simple::piramide_roja,		PROB_PIRAMIDE},
					{&Simple::cubo_verde,			PROB_CUBO},
					{&Simple::cilindro_amarillo,	PROB_CILINDRO},
					{&Simple::esfera_blanca,		PROB_ESFERA_BLANCA},
					{&Simple::esfera_azul,			PROB_ESFERA_AZUL},
					{&Simple::esfera_fucsia,		PROB_ESFERA_FUCSIA},
					{&Simple::esfera_negra,			PROB_ESFERA_NEGRA},
					{NULL,							PROB_NADA}
				}
			, posicion_aleatoria (r_pista.x[MIN], r_pista.x[MAX])
			, tickDistancia (DISTANCIA_TICK)
			, tickVelocidad (PERIODO_CAMBIO_VELOCIDAD)
			{
				pista = r_pista;
				RandomGenerator::time_seed (generador_aleatorio);
				velocidad_base = VELOCIDAD_BASE;
				vehiculo = NULL;

				ultimo_evento = SIN_EVENTOS;
				ultima_accion = NO_REALIZAR_ACCION;

				for (unsigned int i = generadorObstaculo.size(); --i; )
				{
					generadorObstaculo[i]->inicializar();
				}
			}


			Reglas::Reglas (Objeto::GeneradorVehiculo *gv)
			: Reglas ()
			{
				cargar_vehiculo (gv);
			}


			Reglas::~Reglas ()
			{
				destruir_vehiculo ();
				destruir_obstaculos ();
				for (unsigned int i = generadorObstaculo.size(); --i; )
				{
					generadorObstaculo[i]->finalizar();
				}
			}


			void Reglas::cargar_vehiculo (GeneradorVehiculo *gv)
			{
				Punto3D p;

				destruir_vehiculo ();

				vehiculo = gv->generate();
				gv->inicializar();
				generadorVehiculo = gv;

				vehiculo->vidas					= 3;
				vehiculo->velocidad				= 3.5;
				vehiculo->velocidad_horizontal	= 1.0;
				vehiculo->tiempo_invencible		= 0.0;
				vehiculo->distancia_recorrida	= 0.0;
				vehiculo->tiempo_recorrido		= 0.0;
				vehiculo->colisiono_con = NULL;
				p[X] = 0.0;
				p[Y] = NUEVO_OBSTACULO_Y;
				p[Z] = 0.0;
				vehiculo->setPosicionCentral (p);
			}


			void Reglas::destruir_vehiculo ()
			{
				if (vehiculo)
				{
					generadorVehiculo->finalizar();
					delete vehiculo;
					vehiculo = NULL;
				}
			}


			bool Reglas::jugar()
			{
				avanzar_tiempo ();

				desplazar_objetos ();

				analizar_colisiones();
				if (vehiculo->vidas < 1)
					return false;

				return true;
			}


			void Reglas::desplazar_objetos ()
			{
				double
					delta_distancia,
					delta_distancia_horizontal;
				Intervalo
					influencia_obstaculo;
				unsigned int
					obstaculos_a_eliminar,
					numero_obstaculos;

				debug ("\nDesplazar Objetos - Inicio");

				if (tickVelocidad (delta_time))
					aumentar_velocidad ();

				delta_distancia = velocidad_base * vehiculo->velocidad;
				delta_distancia_horizontal = velocidad_base * vehiculo->velocidad_horizontal;

				test (delta_distancia);
				test (delta_distancia_horizontal);

				if (key.is_down(GLFW_KEY_LEFT))
				{
					Punto3D p;
					double desplazamiento_horizontal;
					vehiculo->getPosicionCentral (p);
					desplazamiento_horizontal = p[X] - (pista.x[MIN] + vehiculo->ancho_maximo() / 2.0);
					if (delta_distancia_horizontal < desplazamiento_horizontal)
						desplazamiento_horizontal = delta_distancia_horizontal;
					vehiculo->desplazar (desplazamiento_horizontal, IZQUIERDA);
				}
				else if (key.is_down(GLFW_KEY_RIGHT))
				{
					Punto3D p;
					double desplazamiento_horizontal;
					vehiculo->getPosicionCentral (p);
					desplazamiento_horizontal = (pista.x[MAX] - vehiculo->ancho_maximo() / 2.0) - p[X];
					if (delta_distancia_horizontal < desplazamiento_horizontal)
						desplazamiento_horizontal = delta_distancia_horizontal;
					vehiculo->desplazar (desplazamiento_horizontal, DERECHA);
				}

				test (key.is_down(GLFW_KEY_LEFT));
				test (key.is_down(GLFW_KEY_RIGHT));

				vehiculo->tiempo_recorrido += delta_time;
				vehiculo->distancia_recorrida += delta_distancia;

				test (vehiculo->tiempo_recorrido);
				test (vehiculo->distancia_recorrida);
				test (obstaculo.size());

				obstaculos_a_eliminar = 0;
				numero_obstaculos = obstaculo.size();
				for (unsigned int i = 0; i < numero_obstaculos; ++i)
				{
					test (i);
					obstaculo[i]->desplazar (delta_distancia, ATRAS);
					obstaculo[i]->zona_influencia (influencia_obstaculo);
					if (influencia_obstaculo[MIN] > pista.y[MAX])
						obstaculos_a_eliminar++;
				}
				destruir_obstaculos (obstaculos_a_eliminar);

				if (tickDistancia (delta_distancia))
					generar_obstaculo ();

				debug ("Desplazar Objetos - Fin\n");
			}


			void Reglas::analizar_colisiones ()
			{
				Intervalo
					influencia_vehiculo,
					influencia_obstaculo;
				unsigned int
					numero_obstaculos;
				Accion
					accion;

				numero_obstaculos = obstaculo.size();

				if (vehiculo->tiempo_invencible > 0.0)
				{
					// El vehículo es invencible. Hay que descontar el tiempo.
					vehiculo->tiempo_invencible -= delta_time;
					if (vehiculo->tiempo_invencible <= 0)
					{
						// El vehículo dejó de ser invencible.
						accion_desactivar_invencibilidad ();
					}
				}

				vehiculo->zona_influencia (influencia_vehiculo);
				vehiculo->colisiono_con = NULL;
				for (unsigned int i = 0; i < numero_obstaculos; ++i)
				{
					if (obstaculo[i]->puede_colisionar())
					{
						obstaculo[i]->zona_influencia (influencia_obstaculo);
						if (Colisiones::se_superponen (influencia_vehiculo, influencia_obstaculo))
						{
							if (vehiculo->colisiona_con (obstaculo[i]))
							{
								obstaculo[i]->setNuncaColisionable ();

								ultimo_evento = VEHICULO_COLISIONO_CON_OBSTACULO;
								vehiculo->colisiono_con = obstaculo[i];

								accion = obstaculo[i]->recibir_evento (ultimo_evento, delta_time, vehiculo);
								realizar_accion (accion);
								if (accion != QUITAR_VIDA)
								{
									ultimo_evento = VEHICULO_COLISIONO_CON_BONIFICADOR;
								}
								for (i = 0; i < numero_obstaculos; ++i)
								{
									if (vehiculo->colisiono_con != obstaculo[i])
										obstaculo[i]->recibir_evento (ultimo_evento, delta_time, vehiculo);
								}
								break;
							}
						}
					}
				}

				if (!(vehiculo->colisiono_con))
				{
					ultimo_evento = SIN_EVENTOS;
					for (unsigned int i = 0; i < numero_obstaculos; ++i)
						obstaculo[i]->recibir_evento (ultimo_evento, delta_time, vehiculo);
				}
			}


			void Reglas::aumentar_velocidad ()
			{
				vehiculo->velocidad *= 1.1;
			}


			void Reglas::realizar_accion (Objeto::Accion accion)
			{
				typedef void (Reglas::*accion_fn) ();
				static accion_fn fnAccion[] = {
					&Reglas::accion_quitar_vida,
					&Reglas::accion_dar_vida,
					&Reglas::accion_reducir_velocidad,
					&Reglas::accion_activar_invencibilidad,
					&Reglas::accion_al_azar
				};

				if (accion != NO_REALIZAR_ACCION)
					(this->*fnAccion[accion]) ();
			}


			void Reglas::accion_quitar_vida ()
			{
				vehiculo->vidas--;
				ultima_accion = Accion::QUITAR_VIDA;
			}


			void Reglas::accion_dar_vida ()
			{
				vehiculo->vidas++;
				ultima_accion = Accion::DAR_VIDA;
			}


			void Reglas::accion_aumentar_velocidad ()
			{
				aumentar_velocidad ();
				ultima_accion = Accion::AUMENTAR_VELOCIDAD;
			}


			void Reglas::accion_reducir_velocidad ()
			{
				vehiculo->velocidad /= 1.1;
				ultima_accion = Accion::REDUCIR_VELOCIDAD;
			}


			void Reglas::accion_activar_invencibilidad ()
			{
				unsigned int numero_obstaculos = obstaculo.size();

				if (vehiculo->tiempo_invencible <= 0)
				{
					for (unsigned int i = 0; i < numero_obstaculos; ++i)
					{
						obstaculo[i]->puede_colisionar (false);
					}
				}

				vehiculo->tiempo_invencible = 10.0;
				for (unsigned int i = 0; i < numero_obstaculos; ++i)
				{
					obstaculo[i]->puede_colisionar (false);
					obstaculo[i]->recibir_evento (MODO_VEHICULO_INVENCIBLE, 0.0, vehiculo);
				}

				ultima_accion = Accion::ACTIVAR_INVENCIBILIDAD;
			}


			void Reglas::accion_desactivar_invencibilidad ()
			{
				unsigned int numero_obstaculos = obstaculo.size();
				for (unsigned int i = 0; i < numero_obstaculos; ++i)
				{
					obstaculo[i]->puede_colisionar (true);
					obstaculo[i]->recibir_evento (FIN_MODO_VEHICULO_INVENCIBLE, 0.0, vehiculo);
				}

				vehiculo->tiempo_invencible = 0.0;
				ultima_accion = DESACTIVAR_INVENCIBILIDAD;
			}


			void Reglas::accion_al_azar ()
			{
				typedef void (Reglas::*accion_fn) ();
				static RandomGenerator::Discrete <accion_fn> elegir_accion = {
					{&Reglas::accion_quitar_vida, 2.0},
					{&Reglas::accion_dar_vida, 5.0},
					{&Reglas::accion_aumentar_velocidad, 2.0},
					{&Reglas::accion_reducir_velocidad, 3.0},
					{&Reglas::accion_activar_invencibilidad, 1.0}
				};
				accion_fn accion_elegida;

				accion_elegida = elegir_accion (generador_aleatorio);
				(this->*accion_elegida) ();
			}




			void Reglas::generar_obstaculo ()
			{
				Punto3D
					p;
				GeneradorMovil
					*gen_o;
				Movil
					*o;
				Longitud
					a;

				gen_o = obstaculo_aleatorio (generador_aleatorio);

				if (gen_o)
				{
					o = gen_o->generate();
					a = o->ancho_maximo() / 2.0;

					p[X] = posicion_aleatoria (
						generador_aleatorio,
						pista.x[MIN] + a,
						pista.x[MAX] - a);
					p[Y] = NUEVO_OBSTACULO_Y;
					p[Z] = NUEVO_OBSTACULO_Z;

					if (vehiculo->tiempo_invencible > 0)
					{
						o->puede_colisionar (false);
						o->recibir_evento (MODO_VEHICULO_INVENCIBLE, 0.0, vehiculo);
					}

					o->setPosicionCentral (p);
					obstaculo.push_back (o);
				}
			}


			void Reglas::destruir_obstaculos ()
			{
				destruir_obstaculos (obstaculo.size());
			}


			void Reglas::destruir_obstaculos (unsigned int n)
			{
				auto it = obstaculo.begin();

				for (unsigned int i = 0; i < n; ++i)
					delete obstaculo[i];

				obstaculo.erase (it, it + n);
			}


		}
	}
}


#undef debug
#undef test
