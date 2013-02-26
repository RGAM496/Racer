#include "objeto.h"


namespace urjr
{
	namespace Objeto
	{


		bool Colisionable::puede_colisionar ()
		{
			return (
				(estado == SIEMPRE_COLISIONABLE) ||
				((estado != NUNCA_COLISIONABLE) && 
				puedeColisionar));
		}


		void Colisionable::puede_colisionar (bool set)
		{
			puedeColisionar = set;
		}


		void Colisionable::setSiempreColisionable ()
		{
			estado = SIEMPRE_COLISIONABLE;
		}


		void Colisionable::setNormalmenteColisionable ()
		{
			estado = NORMALMENTE_COLISIONABLE;
		}


		void Colisionable::setNuncaColisionable ()
		{
			estado = NUNCA_COLISIONABLE;
		}




		Colisionable::Colisionable (bool set_colisionar)
		: puedeColisionar (set_colisionar)
		, estado (NORMALMENTE_COLISIONABLE)
		{}


		Movil::~Movil ()
		{}


	}
}
