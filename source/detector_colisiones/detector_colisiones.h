#ifndef DETECTOR_COLISIONES_H
#define DETECTOR_COLISIONES_H


namespace urjr
{
	namespace Colisiones
	{

		/* Posibles formas de las colisiones */
		enum Forma {
				PARALELEPIPEDO,
				CILINDRO,
				PIRAMIDE,
				ESFERA,

				TOTAL_FORMAS
		};


		/* Interfaz del detector de colisiones. */
		class Detector
		{

			public:

				/* Devuelve el tipo de objeto colisionable. */
				virtual Forma tipo_colision () = 0;

				/** Devuelve true si este objeto y el referido están en una
				 *  situación de colisión.
				 */
				 bool colisiona_con (Detector *);
		};


		bool colisionan (Detector *, Detector *);


		namespace Objeto
		{

			/* Objeto detector de colisiones. */
			template <Forma forma>
			class Detectable
			: virtual public Detector
			{
				public:

					Forma tipo_colision() {
						return forma;
					}
			};

		}


	}
}


#endif // DETECTOR_COLISIONES_H
