#ifndef URJR_OBSTACULOS_SIMPLES_H
#define URJR_OBSTACULOS_SIMPLES_H

#include "obstaculo/piramide/objeto.h"
#include "obstaculo/cubo/objeto.h"
#include "obstaculo/cilindro/objeto.h"
#include "obstaculo/esfera/objeto.h"
#include "../generador_objetos.h"

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
	namespace Objeto
	{
		namespace Simple
		{


			enum
			{
				PIRAMIDE_ROJA,
				CUBO_VERDE,
				CILINDRO_AMARILLO,
				ESFERA_BLANCA,
				ESFERA_AZUL,
				ESFERA_FUCSIA,
				ESFERA_NEGRA,

				TOTAL_OBSTACULOS
			};


			class PiramideRoja
			: virtual public Piramide::Objeto
			{
				public:
					void dibujar ();
					PiramideRoja ();
			};


			class CuboVerde
			: virtual public Cubo::Objeto
			{
				public:
					void dibujar ();
					CuboVerde ();
			};


			class CilindroAmarillo
			: virtual public Cilindro::Objeto
			{
				public:
					void dibujar ();
					CilindroAmarillo ();
			};


			class EsferaBlanca
			: virtual public Esfera::Objeto
			{
				public:
					Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *);
					void dibujar ();
					EsferaBlanca ();
			};


			class EsferaAzul
			: virtual public Esfera::Objeto
			{
				public:
					Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *);
					void dibujar ();
					EsferaAzul ();
			};


			class EsferaFucsia
			: virtual public Esfera::Objeto
			{
				public:
					Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *);
					void dibujar ();
					EsferaFucsia ();
			};


			class EsferaNegra
			: virtual public Esfera::Objeto
			{
				public:
					Accion recibir_evento (Evento, double delta_tiempo, Vehiculo *);
					void dibujar ();
					EsferaNegra ();
			};


			extern GeneradorObstaculo <PiramideRoja> piramide_roja;
			extern GeneradorObstaculo <CuboVerde> cubo_verde;
			extern GeneradorObstaculo <CilindroAmarillo> cilindro_amarillo;
			extern GeneradorObstaculo <EsferaBlanca> esfera_blanca;
			extern GeneradorObstaculo <EsferaAzul> esfera_azul;
			extern GeneradorObstaculo <EsferaFucsia> esfera_fucsia;
			extern GeneradorObstaculo <EsferaNegra> esfera_negra;


		}
	}
}


#undef debug
#undef test

#endif // URJR_OBSTACULOS_SIMPLES_H
