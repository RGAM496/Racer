#include "colisiones_simples.h"

#ifdef DEBUG_COLISION
	#include <iostream>
	#define debug(expr) std::cout << expr << std::endl
	#define test(x) debug ("\t" #x " = " << x)
#else
	#define debug(expr) {}
	#define test(x) {}
#endif


namespace urjr
{
	namespace Colisiones
	{
		using namespace Objeto;


		bool colisionan (Paralelepipedo *p1, Paralelepipedo *p2)
		{
			Intervalo
				h1,
				h2;
			Rectangulo
				b1,
				b2;

			debug ("\nInicio - Colision: Paralelepipedo & Paralelepipedo");

			p1->altura (h1);
			p2->altura (h2);

			if (!se_superponen (h1, h2))
				return false;

			p1->base (&b1);
			p2->base (&b2);

			debug ("Fin - Colision: Paralelepipedo & Paralelepipedo\n");

			return colisionan (&b1, &b2);
		}


		bool colisionan (Paralelepipedo *p, Cilindro *c)
		{
			Intervalo
				hp,
				hc;
			Rectangulo
				bp;
			Circulo
				bc;

			debug ("\nInicio - Colision: Paralelepipedo & Cilindro");

			p->altura (hp);
			c->altura (hc);

			if (!se_superponen (hp, hc))
				return false;

			p->base (&bp);
			c->base (&bc);

			debug ("Fin - Colision: Paralelepipedo & Cilindro\n");

			return colisionan (&bp, &bc);
		}


		bool colisionan (Paralelepipedo *pa, Piramide *pi)
		{
			Intervalo
				hpa,
				hpi;
			Rectangulo
				bpa,
				bpi;
			Longitud
				lhpi;

			debug ("\nInicio - Colision: Paralelepipedo & Piramide");

			pa->altura (hpa);
			pi->altura (hpi);

			if (!se_superponen (hpa, hpi))
				return false;

			lhpi = coordenada_mas_cercana (hpa, hpi[MIN]) - hpi[MIN];

			pa->base (&bpa);
			pi->base (&bpi, lhpi);

			debug ("Fin - Colision: Paralelepipedo & Piramide\n");

			return colisionan (&bpa, &bpi);
		}


		bool colisionan (Paralelepipedo *p, Esfera *e)
		{
			Intervalo
				hp,
				he;
			Rectangulo
				bp;
			Circulo
				be;
			Longitud
				lhe;
			Coordenada
				ce; // Coordenada del corte horizontal que biseca a la esfera.

			debug ("\nInicio - Colision: Paralelepipedo & Esfera");

			p->altura (hp);
			e->altura (he);

			if (!se_superponen (hp, he))
				return false;

			ce = he[MAX] + he[MIN] / 2.0;
			lhe = coordenada_mas_cercana (hp, ce) - he[MIN];

			p->base (&bp);
			e->base (&be, lhe);

			debug ("Fin - Colision: Paralelepipedo & Esfera\n");

			return colisionan (&bp, &be);
		}


		bool colisionan (Cilindro *c1, Cilindro *c2)
		{
			Intervalo
				h1,
				h2;
			Circulo
				b1,
				b2;

			debug ("\nInicio - Colision: Cilindro & Cilindro");

			c1->altura (h1);
			c2->altura (h2);

			if (!se_superponen (h1, h2))
				return false;

			c1->base (&b1);
			c2->base (&b2);

			debug ("Fin - Colision: Cilindro & Cilindro\n");

			return colisionan (&b1, &b2);
		}


		bool colisionan (Cilindro *c, Piramide *p)
		{
			Intervalo
				hc,
				hp;
			Circulo
				bc;
			Rectangulo
				bp;
			Longitud
				lhp;

			debug ("\nInicio - Colision: Cilindro & Piramide");

			c->altura (hc);
			p->altura (hp);

			if (!se_superponen (hp, hc))
				return false;

			lhp = coordenada_mas_cercana (hc, hp[MIN]) - hp[MIN];
			
			test (lhp);

			c->base (&bc);
			p->base (&bp, lhp);
			
			debug ("\t\tbc");
			test (bc.centro[X]);
			test (bc.centro[Y]);
			test (bc.radio);
			debug ("\t\tbp");
			test (bp.x[MIN]);
			test (bp.x[MAX]);
			test (bp.y[MIN]);
			test (bp.y[MAX]);

			debug ("Fin - Colision: Cilindro & Piramide\n");

			return colisionan (&bp, &bc);
		}


		bool colisionan (Cilindro *c, Esfera *e)
		{
			Intervalo
				hc,
				he;
			Circulo
				bc,
				be;
			Longitud
				lhe;
			Coordenada
				ce; // Coordenada del corte horizontal que biseca a la esfera.

			debug ("\nInicio - Colision: Cilindro & Esfera");

			c->altura (hc);
			e->altura (he);

			if (!se_superponen (hc, he))
				return false;

			ce = he[MAX] + he[MIN] / 2.0;
			lhe = coordenada_mas_cercana (hc, ce) - he[MIN];

			c->base (&bc);
			e->base (&be, lhe);

			debug ("Fin - Colision: Cilindro & Esfera\n");

			return colisionan (&bc, &be);
		}


		bool colisionan (Piramide *p1, Piramide *p2)
		{
			Intervalo
				h1,
				h2;
			Rectangulo
				b1,
				b2;
			Longitud
				lh1,
				lh2;

			debug ("\nInicio - Colision: Piramide & Piramide");

			p1->altura (h1);
			p2->altura (h2);

			if (!se_superponen (h1, h2))
				return false;

			lh1 = coordenada_mas_cercana (h2, h1[MIN]) - h1[MIN];
			lh2 = coordenada_mas_cercana (h1, h2[MIN]) - h2[MIN];

			p1->base (&b1, lh1);
			p2->base (&b2, lh2);

			debug ("Fin - Colision: Piramide & Piramide\n");

			return colisionan (&b1, &b2);
		}


		bool colisionan (Piramide *p, Esfera *e)
		{
			Intervalo
				he,
				hp;
			Circulo
				be;
			Rectangulo
				bp;
			Longitud
				lhp;

			debug ("\nInicio - Colision: Piramide & Esfera");

			e->altura (he);
			p->altura (hp);

			if (!se_superponen (hp, he))
				return false;

			// Por ahora, colisionarán como pirámide con cilindro.

			lhp = coordenada_mas_cercana (he, hp[MIN]) - hp[MIN];

			e->base (&be);
			p->base (&bp, lhp);

			debug ("Fin - Colision: Piramide & Esfera\n");

			return colisionan (&bp, &be);
		}


		bool colisionan (Esfera *e1, Esfera *e2)
		{
			Punto3D
				c1,
				c2;
			Longitud
				suma_radios;

			debug ("\nInicio - Colision: Esfera & Esfera");

			e1->centro (c1);
			e2->centro (c2);
			suma_radios = e1->radio() + e2->radio();

			debug ("Fin - Colision: Esfera & Esfera\n");

			return distancia (c1, c2) <= suma_radios;
		}

	}
}


#undef debug
#undef test
