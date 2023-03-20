#include <iostream>

#include "Signal.h"

int main() {
    int SAMPLE_RATE = 1000;
    int DURATION = 1;
    int N = SAMPLE_RATE * DURATION;


    vector<double> x;

    vector<double> nice_tone1, noise_tone2, noise_tone3;

    tie(x, nice_tone1) = Signal::generateSineWave(30, SAMPLE_RATE, DURATION);
    tie(x, noise_tone2) = Signal::generateSineWave(100, SAMPLE_RATE, DURATION);
    tie(x, noise_tone3) = Signal::generateSineWave(125, SAMPLE_RATE, DURATION);

    vector<double> mixed_tone1(x.size());

    for (int i = 0; i < mixed_tone1.size(); i++)
        mixed_tone1[i] = nice_tone1[i] + 0.8 * noise_tone2[i] + 0.5 * noise_tone3[i];

    //Signal::printArray(nice_tone1);
    Signal::printFile(x, mixed_tone1, "inputSignal.txt");


}
