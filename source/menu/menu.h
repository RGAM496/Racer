#ifndef URJR_MENU_H
#define URJR_MENU_H


namespace urjr
{
	/* Define la interfaz de un menú genérico. */
	class Menu {
		virtual void inicializar() = 0;
		virtual void finalizar () = 0;
		//virtual void teclado () = 0; // Redefinir según la necesidad.
		virtual void dibujar () = 0;
	};
}


#endif // URJR_MENU_H
