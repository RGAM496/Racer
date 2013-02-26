#include "comprobar_colisiones.h"
#include "simple/colisiones_simples.h"


namespace urjr
{
	namespace Colisiones
	{
		using std::vector;


		typedef bool (*CombrobadorColision) (Detector *, Detector *);


		vector<vector<CombrobadorColision>> comprobar = {
			{
				comprobar_colision <Paralelepipedo, Paralelepipedo>
			},
			{
				comprobar_colision <Paralelepipedo, Cilindro>,
				comprobar_colision <Cilindro, Cilindro>
			},
			{
				comprobar_colision <Paralelepipedo, Piramide>,
				comprobar_colision <Cilindro, Piramide>,
				comprobar_colision <Piramide, Piramide>,
			},
			{
				comprobar_colision <Paralelepipedo, Esfera>,
				comprobar_colision <Cilindro, Esfera>,
				comprobar_colision <Piramide, Esfera>,
				comprobar_colision <Esfera, Esfera>
			}
		};


	}
}