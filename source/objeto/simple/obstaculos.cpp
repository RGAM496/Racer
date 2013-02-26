#include "obstaculos.h"


namespace urjr
{
	namespace Objeto
	{
		namespace Simple
		{


			/* Pirámide roja. */


			void PiramideRoja::dibujar ()
			{
				glColor3d (1.0, 0.0, 0.0);
				Objeto::dibujar ();
			}


			PiramideRoja::PiramideRoja ()
			{
				semilado = 0.5;
				altura_actual = 2.0;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Cubo verde. */


			void CuboVerde::dibujar ()
			{
				glColor3d (0.0, 1.0, 0.0);
				Objeto::dibujar ();
			}


			CuboVerde::CuboVerde ()
			{
				semilado = 1.0;
				altura_actual = 2.0 * semilado;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Cilindro amarillo. */


			void CilindroAmarillo::dibujar ()
			{
				glColor3d (1.0, 1.0, 0.0);
				Objeto::dibujar ();
			}


			CilindroAmarillo::CilindroAmarillo ()
			{
				radio_base = 0.5;
				altura_actual = 2.0;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Esfera blanca. */


			Accion EsferaBlanca::recibir_evento (Evento e, double delta_tiempo, Vehiculo *v)
			{
				Objeto::recibir_evento (e, delta_tiempo, v);
				return DAR_VIDA;
			}


			void EsferaBlanca::dibujar ()
			{
				glColor3d (1.0, 1.0, 1.0);
				Objeto::dibujar ();
			}


			EsferaBlanca::EsferaBlanca ()
			{
				radio_cuerpo = 0.5;
				altura_actual = 2.0 * radio_cuerpo;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Esfera Azul. */


			Accion EsferaAzul::recibir_evento (Evento e, double delta_tiempo, Vehiculo *v)
			{
				Objeto::recibir_evento (e, delta_tiempo, v);
				return REDUCIR_VELOCIDAD;
			}


			void EsferaAzul::dibujar ()
			{
				glColor3d (0.0, 0.0, 1.0);
				Objeto::dibujar ();
			}


			EsferaAzul::EsferaAzul ()
			{
				radio_cuerpo = 0.5;
				altura_actual = 2.0 * radio_cuerpo;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Esfera Fucsia. */


			Accion EsferaFucsia::recibir_evento (Evento e, double delta_tiempo, Vehiculo *v)
			{
				Objeto::recibir_evento (e, delta_tiempo, v);
				return ACTIVAR_INVENCIBILIDAD;
			}


			void EsferaFucsia::dibujar ()
			{
				glColor3d (1.0, 0.0, 1.0);
				Objeto::dibujar ();
			}


			EsferaFucsia::EsferaFucsia ()
			{
				radio_cuerpo = 0.5;
				altura_actual = 2.0 * radio_cuerpo;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Esfera negra. */


			Accion EsferaNegra::recibir_evento (Evento e, double delta_tiempo, Vehiculo *v)
			{
				Objeto::recibir_evento (e, delta_tiempo, v);
				return EFECTO_AL_AZAR;
			}


			void EsferaNegra::dibujar ()
			{
				glColor3d (0.0, 0.0, 0.0);
				Objeto::dibujar ();
			}


			EsferaNegra::EsferaNegra ()
			{
				radio_cuerpo = 0.5;
				altura_actual = 2.0 * radio_cuerpo;
				iterador_altura.set_top (escala = 1.0);
				iterador_altura.set_period (0.125);
			}


			/* Instanciaciones de objetos. */

			GeneradorObstaculo <PiramideRoja> piramide_roja;
			GeneradorObstaculo <CuboVerde> cubo_verde;
			GeneradorObstaculo <CilindroAmarillo> cilindro_amarillo;
			GeneradorObstaculo <EsferaBlanca> esfera_blanca;
			GeneradorObstaculo <EsferaAzul> esfera_azul;
			GeneradorObstaculo <EsferaFucsia> esfera_fucsia;
			GeneradorObstaculo <EsferaNegra> esfera_negra;


		}
	}
}
