#pragma once

#include <tuple>
#include <fstream>
#include <iostream>

#include "NumPy.h"

# define M_PI 3.14159265358979323846  /* pi */

using namespace std;
class Signal {

public:
	Signal() {

	}

	static tuple<vector<double>, vector<double>> generateSineWave(double freq, int sample_rate, int duration) {

		vector<double> x = NumPy::linspace(0, duration, sample_rate * duration);

		vector<double> y(x.size());
		for (int i = 0; i < y.size(); i++) {
			y[i] = sin(2 * M_PI * freq * x[i]);
		}

		return make_tuple(x, y);

	}













	template <typename T>
	static void printFile(const vector<T>& x, const vector<T>& y, string nameOfFile = "2d.txt") {
		fstream myFile(nameOfFile, ios::out);

		for (int i = 0; i < y.size(); i++) {
			myFile << x[i] << " " << y[i] << endl;
		}

		myFile.close();
	}

	template <typename T>
	static void printArray(const vector<T>& matrix1) {
		cout << endl;
		cout << "SIZE = " << matrix1.size() << endl;

		for (int i = 0; i < matrix1.size(); i++) {
			cout << matrix1[i] << endl;
		}

	}

	template <typename T>
	static void printArray(const vector<vector<T>>& matrix1) {
		cout << endl;
		cout << "SIZE 1 = " << matrix1.size() << endl;
		cout << "SIZE 2 = " << matrix1[0].size() << endl;

		for (int i = 0; i < matrix1.size(); i++) {
			for (int j = 0; j < matrix1[i].size(); j++) {
				cout << matrix1[i][j] << " ";
			}
			cout << endl;
		}
	}

};

