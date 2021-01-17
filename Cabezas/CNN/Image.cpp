//#pragma once
#include "Image.h"
#include "label.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

namespace ReconLib {
	Image::Image(std::string ruta) {
		this->ruta = ruta;
		imagencita = new BMP(ruta.c_str());

		alto = imagencita->bmp_info_header.height;
		ancho = imagencita->bmp_info_header.width;
		int x, y, b, g, r;
		float gris;
		for (int i = 0; i < imagencita->data.size(); i = i + 3) {
			b = imagencita->data.at(i);
			g = imagencita->data.at(i + 1);
			r = imagencita->data.at(i + 2);
			//Se aplica un filtro de escala de grises para reducir la dimension.
			gris = (float)(r + g + b) / (float)(3.0*255.0);
			/*gris = (float)(r*0.4 + g*0.3 + b*0.3)/(float)(255.0);*/
			x = (i / 3) % ancho;
			y = (i / 3) / ancho;
			pixeles.push_back(gris);
		}
	}

	std::vector<float> Image::get_pixels()
	{
		return pixeles;
	}

	int Image::get_height()
	{
		return alto;
	}

	int Image::get_width()
	{
		return ancho;
	}

	Matriz Image::toMatriz() {
		Matriz mat(ancho, alto);
		for (int i = 0; i < alto; i++) {
			for (int j = 0; j < ancho; j++) {
				mat.set(alto-1-j, i-1, pixeles.at((int)j * alto + i));
			}
		}
		return mat;
	}

	std::vector<std::string> Image::ArchivosEnCarpeta(std::string ruta)
	{
		std::string comando = "dir \"";
		//comando.append("dir \"");
		comando.append(ruta);
		//comando.append("\" /b * > trucho.txt");
		comando.append("\" /b > trucho.txt");
		system(comando.c_str());
		std::vector<std::string> archivos;
		std::string linea;
		std::ifstream infile("trucho.txt");
		while (infile >> linea)
		{
			archivos.push_back(linea);
		}
		infile.close();
		system("del trucho.txt");
		return archivos;
	}

	Matriz transformador(cv::Mat mat) {
		int alto = mat.rows;
		int ancho = mat.cols;
		Matriz m(ancho, alto);
		for (int i = 0; i < mat.rows; i++)
		{
			for (int j = 0; j < mat.cols; j++)
			{
				cv::Vec3b bgrPixel = mat.at<cv::Vec3b>(i, j);
				//cout << bgrPixel[0] << "-" << bgrPixel[1] << "-" << bgrPixel[2] << endl;
				m.set(i, j, (bgrPixel[0] + bgrPixel[1] + bgrPixel[2]) * 1.0 / (3.0 * 255.0));
			}
		}
		return m;
	}

	std::vector<Matriz> Image::CargaCarpeta(std::string ruta) {
		std::vector<std::string> nombres = ArchivosEnCarpeta(ruta);
		//rutaarchivo se saca como ruta+nombres[i]
		std::cout <<"Leyendo "<< nombres.size() <<" archivos."<< std::endl;
		std::string rutaarchivo;
		std::vector<Matriz> imagenes;
		//cv::Mat m;
		//Matriz k;
		for (int i = 0; i < nombres.size(); i++) {
			rutaarchivo = "";
			rutaarchivo.append(ruta);
			rutaarchivo.append(nombres.at(i));
			//m=cv::imread(rutaarchivo);
			//k=Matriz(m);
			imagenes.push_back(transformador(cv::imread(rutaarchivo)));
			//imagenes.push_back(Image(rutaarchivo.c_str()).toMatriz());
		}
		return imagenes;
	}




	void Image::dibujarRect(struct label etiqueta, int anchoRect, int altoRect, int r, int g, int b)
	{
			if (etiqueta.x > 0 && etiqueta.y > 0) {
				//std::cout << "Etiquetando: " << etiqueta.clasificacion << "\n";
				imagencita->draw_rectangle(
					//CORRER LA COORDENADA A LA ESQUINA (esquina del rect) )para que la etiqueta quede centrada en el rectangulo.
					etiqueta.x - (anchoRect/2),
					alto - altoRect - etiqueta.y + (altoRect/2),
					anchoRect,
					altoRect,
					b, g,r, 0,  //B,G,R,A
					1 //ancho de la linea
				);
			}
	}

	void Image::dibujarLinea(int x0, int y0, int x1, int y1, int r, int g, int b)
	{
		imagencita->join_points(
			x0,
			alto - y0,
			x1,
			alto - y1,
			b, g, r, 0  //B,G,R,A
		);
		//guardar("_joined");
	}

	void Image::guardar(std::string suffix)
	{
		std::string salida = this->ruta;
		for (int i = 0; i < 4; i++) salida.pop_back(); //quita el ".bmp" de la imagen original
		salida.append(suffix);		
		std::string extension = ".bmp";
		salida.append(extension);
		imagencita->write(salida.c_str());
	}
}