//
// Created by Tobias on 12.08.2024.
//

#ifndef GAN_NETWORK_H
#define GAN_NETWORK_H

#include <vector>
#include <random>
#include <iostream>

enum Activations {Sigmoid, ReLU, LeakyReLU, Tanh, Linear};

class Network {
private:
    std::vector<std::vector<float>> _weights;
    std::vector<std::vector<float>> _biases;
    std::vector<Activations> _activations;

    float calculateActivation(Activations, float);
public:

    // Constructor
    Network() = default;
    Network(std::vector<int> &, std::vector<Activations> &, float, float);

    // Methods
    std::vector<float> feedForward(std::vector<float> &);

    // Getter - Setter
    [[nodiscard]] std::vector<std::vector<float>> &weights() { return _weights; }
    [[nodiscard]] std::vector<std::vector<float>> &biases() { return _biases; }
    [[nodiscard]] std::vector<Activations> &activations() { return _activations; }
};

Network createChild(Network &, Network &);
Network createChild(Network &, Network &, int, float);
float random(float min, float max);
int random(int min, int max);

#endif //GAN_NETWORK_H
