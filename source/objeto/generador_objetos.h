#ifndef URJR_GENERADOR_OBJETOS_H
#define URJR_GENERADOR_OBJETOS_H

#include "objeto.h"
#include "../generator/class_generator.h"
#include "../generator/random_generator.h"


namespace urjr
{
	namespace Objeto
	{


		class GeneradorMovil
		: virtual public ClassGenerator::Interface <Movil>
		{
			public:

				virtual void inicializar () = 0;
				virtual void finalizar () = 0;
		};


		template <class M>
		class GeneradorObstaculo
		: virtual public GeneradorMovil
		, virtual public ClassGenerator::Instance <M, Movil>
		{
			public:

				void inicializar () {
					M::inicializar ();
				}

				void finalizar () {
					M::finalizar ();
				}
		};


		class GeneradorVehiculo
		: virtual public ClassGenerator::Interface <Vehiculo>
		{
			public:

				virtual void inicializar () = 0;
				virtual void finalizar () = 0;
		};


		template <class V>
		class GeneradorVehiculoEspecifico
		: virtual public GeneradorVehiculo
		, virtual public ClassGenerator::Instance <V, Vehiculo>
		{
			public:

				void inicializar () {
					V::inicializar ();
				}

				void finalizar () {
					V::finalizar ();
				}
		};


		const double
			PROB_OBSTACULO			= 0.70,
				PROB_PIRAMIDE			= 0.60 * PROB_OBSTACULO,
				PROB_CUBO				= 0.25 * PROB_OBSTACULO,
				PROB_CILINDRO			= 0.15 * PROB_OBSTACULO,
			PROB_ESFERA				= 0.125,
				PROB_ESFERA_BLANCA		= 0.40 * PROB_ESFERA,
				PROB_ESFERA_AZUL		= 0.30 * PROB_ESFERA,
				PROB_ESFERA_FUCSIA		= 0.10 * PROB_ESFERA,
				PROB_ESFERA_NEGRA		= 0.20 * PROB_ESFERA,
			PROB_NADA				= 0.125;


	}
}


#endif // URJR_GENERADOR_OBJETOS_H
