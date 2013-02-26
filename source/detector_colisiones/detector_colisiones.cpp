#include "detector_colisiones.h"
#include "comprobar_colisiones.h"

namespace urjr
{
	namespace Colisiones
	{


		/*Forma Detector::tipo_colision ()
		{
			return forma_colision;
		}*/


		bool Detector::colisiona_con (Detector *detector)
		{
			return colisionan (this, detector);
		}


		/*Detector::Detector (Forma forma)
		{
			forma_colision = forma;
		}*/


		bool colisionan (Detector *d1, Detector *d2)
		{
			Forma
				t1 = d1->tipo_colision (),
				t2 = d2->tipo_colision ();

			if (t1 >= t2)
				return comprobar[t1][t2] (d2, d1);
			return comprobar[t2][t1] (d1, d2);
		}

	}
}
