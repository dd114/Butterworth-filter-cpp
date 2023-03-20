#pragma once

#include <vector>
#include <cassert>

using namespace std;
class NumPy {

public:
	NumPy() {

	}

    static vector<double> linspace(double start, double end, int count) {
        std::vector<double> output(count);

        double step = (end - start) / (count - 1);
        for (int i = 0; i < count; i++) {
            output[i] = start + i * step;
        }

        return output;
    }

    template <typename T>
    static vector<T> valueMultVector(double value, const vector<T>& vec) {
        vector<T> output(vec.size());

        for (int i = 0; i < output.size(); i++) {
            output[i] = value * vec[i];
        }

        return output;
    }

    template <typename T>
    static vector<T> vectorSumVector(const vector<T>& vec1, const vector<T>& vec2) {
        assert(vec1.size() == vec2.size() && "Sizes match");

        vector<T> output(vec1.size());

        for (int i = 0; i < output.size(); i++) {
            output[i] = vec1[i] + vec2[i];
        }


        return output;
    }

};

