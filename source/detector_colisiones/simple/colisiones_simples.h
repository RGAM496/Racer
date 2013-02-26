#ifndef COLISIONES_SIMPLES_H
#define COLISIONES_SIMPLES_H

#include "paralelepipedo.h"
#include "cilindro.h"
#include "piramide.h"
#include "esfera.h"


namespace urjr
{
	namespace Colisiones
	{

		using namespace Objeto;

		bool colisionan (Paralelepipedo *, Paralelepipedo *);
		bool colisionan (Paralelepipedo *, Cilindro *);
		bool colisionan (Paralelepipedo *, Piramide *);
		bool colisionan (Paralelepipedo *, Esfera *);
		bool colisionan (Cilindro *, Cilindro *);
		bool colisionan (Cilindro *, Piramide *);
		bool colisionan (Cilindro *, Esfera *);
		bool colisionan (Piramide *, Piramide *);
		bool colisionan (Piramide *, Esfera *);
		bool colisionan (Esfera *, Esfera *);

	}
}


#endif // COLISIONES_SIMPLES_H
