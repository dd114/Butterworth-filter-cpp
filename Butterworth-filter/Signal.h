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

	static tuple<vector<double>, vector<double>> getCoeffs(int order, double w){
		int p;
		if(order % 2 == 0)
			p = order;
		else
			p = (order - 1);

		vector<double> numerator(p + 1); 
		for(int k = 0; k < p + 1; k++){
			numerator[k] = simplePow(-w * w, p / 2) * C(k, p); // numerator is got
		}

		vector<double> denominator(p + 1);
		denCoeffs(denominator, w, order, p); // denominator is got


		double a0 = 0;

		if (order % 2 == 0) {	
			a0 = denominator.back();
			denominator.pop_back();

		} else {
			numerator.push_back(0);
			denominator.push_back(0);

			vector<double> zNumerator = NumPy::roll(numerator, 1);
			vector<double> zDenominator = NumPy::roll(denominator, 1);

			for (int i = 0; i < numerator.size(); i++) {
				numerator[i] = (zNumerator[i] + numerator[i]) * w;
			}

			for (int i = 0; i < denominator.size(); i++) {
				denominator[i] = (zDenominator[i] + denominator[i]) * w + (zDenominator[i] - denominator[i]);
			}
			
			a0 = denominator.back();
			denominator.pop_back();

		}

		return make_tuple(NumPy::valueDivideVector(a0, numerator), NumPy::valueDivideVector(a0, denominator));


		
	}

	static double transformFrequency(double w, int sample_rate){
		return tan(M_PI * w / sample_rate);
	}

private:
	static int factorial(int n){
		int mult = 1;
		for(int i = 2; i < n + 1; i++){
			mult *= i;
		}

		return mult;
	}

	static double simplePow(double number, unsigned int degree){
		double output = 1;
		for(int i = 0; i < degree; i++){
			output *= number;
		}

		return output;
	}

	static double C(int k, int n){ // return can be shorten by math rules
		return factorial(n) / (factorial(n - k) * factorial(k));
	}

	static double a(double w, int order, int k){
		return 2. * w * cos(M_PI * k / order) * sin(M_PI / (2. * order)) - 2. * w * sin(M_PI * k / order) * cos(M_PI / (2. * order)) - w * w - 1.;
	}

	static double b(double w){
		return -2. * w * w + 2.;
	}

	static double c(double w, int order, int k){
		return -2. * w * cos(M_PI * k / order) * sin(M_PI / (2. * order)) + 2. * w * sin(M_PI * k / order) * cos(M_PI / (2. * order)) - w * w - 1.;
	}

	static void denCoeffs(vector<double>& denominator, double& w, int& order, int &p, int degree = 0, double prod = 1, int k = 1) {

		if(k > p / 2){
			denominator[degree] += prod;
			return;
		}

		if(degree + 2 <= p) {
			denCoeffs(denominator, w, order, p, degree + 2, prod * a(w, order, k), k + 1);
		}

		if(degree + 1 <= p) {
			denCoeffs(denominator, w, order, p, degree + 1, prod * b(w), k + 1);
		}

		if(degree <= p) {
			denCoeffs(denominator, w, order, p, degree, prod * c(w, order, k), k + 1);
		}

	}












public:
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

