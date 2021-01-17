#ifndef Image_H
#define Image_H

#include <vector>
#include "BMP.h"
#include "Matriz.h"
#include "label.h"

namespace ReconLib {
    class Image {
	private:
		std::string ruta;
	public:
		BMP *imagencita;
		int alto;
		int ancho;
		std::vector<float> pixeles;
		Image(std::string ruta);
		int get_height();
		int get_width();
		Matriz toMatriz();
		std::vector<float> get_pixels();
		static std::vector<std::string> ArchivosEnCarpeta(std::string ruta);
		static std::vector<Matriz> CargaCarpeta(std::string ruta);

		void dibujarRect(struct label etiqueta, int anchoRect, int altoRect, int r, int g, int b);
		void dibujarLinea(int x0, int y0, int x1, int y1, int r, int g, int b);
		void guardar(std::string suffix);
		
	};
}

#endif