#include "Activations.h"
#include <iostream>
namespace ReconLib {

	std::vector<float> Activations::softmax(std::vector<float> input)
	{
		std::vector<float> suavecita;
		float sumaton=0;
		float termino;

		for (int i = 0; i < input.size(); i++) {
			termino = exp(input.at(i)/10.0); // T R U C H O
			//std::cout << input.at(i) << ' '<<termino<<'\n';
			suavecita.push_back(termino);
			sumaton = sumaton + termino;
		}
		for (int i = 0; i < suavecita.size(); i++) {
			suavecita[i] = suavecita[i] / sumaton;
		}
		return suavecita;
	}
	
	int Activations::argmax(std::vector<float>input) {
		int k = 0;
		int i_max = 0;
		for (int i = 0; i < input.size(); i++) {
			if (input.at(i) > input.at(i_max)) i_max = i;
		}
		return i_max;
	}

	std::vector<float> Activations::hardmax(std::vector<float> input)
	{
		std::vector<float> output;
		float sumaton = 0;
		float termino;
		int i_max = argmax(input);
		for (int i = 0; i < input.size(); i++) {
			if (i != i_max) output.push_back(0);
			else output.push_back(1);
		}
		return output;
	}

	
	float Activations::crossentropy(std::vector<float> prob, std::vector<float> labelcorrecto)
	{
		//std::vector<float> hard = hardmax(suave);
		float sumaton = 0;
		float termino;
		for (int i = 0; i < prob.size(); i++) {
			termino = log10(prob.at(i)) * labelcorrecto.at(i) * (-1.0);
			sumaton += termino;
			//std::cout << "\nTermino: " << termino << "\nSumaton: " << sumaton;
		}
		return sumaton;
	}

	void Activations::Mostrar(std::vector<float>input) {
		std::cout << "[ ";
		for (int i = 0; i < input.size(); i++) {
			printf("%.4f ", input.at(i));
		}
		std::cout << "]";
	}

	void Activations::testeo() {
		std::vector<float> in;
		std::vector<float> out;
		std::vector<float> out2;
		in.push_back(8);
		in.push_back(5);
		in.push_back(10);
		in.push_back(-3);
		Activations S = Activations();
		out = S.softmax(in);
		std::cout <<" \nActivations: ";
		S.Mostrar(out);
		out2 = S.hardmax(in);
		std::cout << "\nHardargmax: ";
		S.Mostrar(out2);
		///std::cout << "Entropia: " << S.crossentropy(in) << "\n";

	}
	float Activations::ReLu(float relu) {
		if (relu > 0) {
			return relu;
		}
		return 0;
	}

	Matriz Activations::ReLuApply(Matriz m) {
		Matriz res(m.ancho, m.alto);
		for (int i = 0; i < m.alto; i++) {
			for (int j = 0; j < m.ancho; j++) {
				res.set(i, j, ReLu(m.get(i, j)));
			}
		}
		return res;
	}
}