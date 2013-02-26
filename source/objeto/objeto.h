#ifndef URJR_OBJETO_H
#define URJR_OBJETO_H

#include "../detector_colisiones/detector_colisiones.h"
#include "../detector_colisiones/geometria_colisiones.h"


namespace urjr
{
	namespace Objeto
	{


		enum Direccion
		{
			IZQUIERDA,
			DERECHA,
			ADELANTE,
			ATRAS
		};


		enum Evento
		{
			SIN_EVENTOS,
			VEHICULO_COLISIONO_CON_OBSTACULO,
			VEHICULO_COLISIONO_CON_BONIFICADOR,
			MODO_VEHICULO_INVENCIBLE,
			FIN_MODO_VEHICULO_INVENCIBLE
		};


		enum Accion
		{
			// Acciones ordenadas. para incluir en un vector de punteros a funciones.
			QUITAR_VIDA,
			DAR_VIDA,
			REDUCIR_VELOCIDAD,
			ACTIVAR_INVENCIBILIDAD,
			EFECTO_AL_AZAR,
			// Acciones que no requieren estar ordenadas.
			AUMENTAR_VELOCIDAD,
			DESACTIVAR_INVENCIBILIDAD,

			// Acción nula, se utiliza en caso de que no sea necesario realizar acción alguna.
			NO_REALIZAR_ACCION
		};


		class Vehiculo;


		class Colisionable
		: virtual public Colisiones::Detector
		{
			public:

				virtual void getPosicionCentral (Punto3D &) = 0;
				virtual void setPosicionCentral (const Punto3D &) = 0;
				virtual Longitud ancho_maximo () = 0;
				virtual void zona_influencia (Intervalo &) = 0;

				bool puede_colisionar ();
				void puede_colisionar (bool set);

				void setSiempreColisionable ();
				void setNormalmenteColisionable ();
				void setNuncaColisionable ();

				Colisionable (bool set_colisionar = true);

			private:

				enum Estado
				{
					SIEMPRE_COLISIONABLE,
					NORMALMENTE_COLISIONABLE,
					NUNCA_COLISIONABLE
				};

				bool puedeColisionar;
				Estado estado;
		};


		class Modelo3D
		{
			public:

				static void inicializar ();
				static void finalizar ();

				virtual void dibujar () = 0;
		};


		class Movil
		: virtual public Colisionable
		, virtual public Modelo3D
		{
			public:

				virtual Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *) = 0;
				virtual void desplazar (double magnitud, Direccion) = 0;

				virtual ~Movil () = 0;
		};


		class Vehiculo
		: virtual public Movil
		{
			public :

				unsigned int
					vidas;
				double
					velocidad,
					velocidad_horizontal,
					tiempo_invencible,
					distancia_recorrida,
					tiempo_recorrido;

				Movil
					*colisiono_con;
		};


	}
}


#endif // URJR_OBJETO_H
