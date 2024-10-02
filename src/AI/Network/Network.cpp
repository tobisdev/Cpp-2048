//
// Created by Tobias on 12.08.2024.
//

#include "Network.h"

Network::Network(std::vector<int> &topology, std::vector<Activations> &activations, float min, float max) {
    this->_activations = activations;

    for (int i = 1; i < topology.size(); ++i) {
        int &currentNeurons = topology[i];
        int &previousNeurons = topology[i - 1];

        std::vector<float> currentBiases;
        for (int j = 0; j < currentNeurons; ++j) {
            currentBiases.emplace_back(random(min, max));
        }
        _biases.emplace_back(currentBiases);

        std::vector<float> currentWeights;
        for (int j = 0; j < currentNeurons * previousNeurons; ++j) {
            currentWeights.emplace_back(random(min, max));
        }
        _weights.emplace_back(currentWeights);
    }
}

std::vector<float> Network::feedForward(std::vector<float> &input) {
    int layers = _weights.size();
    std::vector<float> previous = input;
    std::vector<float> current;

    for (int i = 0; i < layers; ++i) {
        int neurons = _biases[i].size();
        int previousNeurons = _weights[i].size() / neurons;

        // Apply _activations
        for (int j = 0; j < previousNeurons; ++j) {
            previous[j] = calculateActivation(_activations[i], previous[j]);
        }

        // Matrix multiplication
        for (int j = 0; j < neurons; ++j) {
            float currentValue = 0.0f;
            for (int k = 0; k < previousNeurons; ++k) {
                currentValue += previous[k] * _weights[i][previousNeurons * j + k];
            }
            current.push_back(currentValue);
        }

        // Add the _biases
        for (int j = 0; j < neurons; ++j) {
            current[j] += _biases[i][j];
        }

        previous = current;
        current.clear();
    }

    // Apply _activations
    for (int i = 0; i < previous.size(); ++i) {
        previous[i] = calculateActivation(_activations[layers], previous[i]);
    }

    return previous;
}

float Network::calculateActivation(Activations activation, float value) {
    switch (activation) {
        case ReLU:
            return value > 0 ? value : 0.0f;
        case LeakyReLU:
            return value > 0 ? value : value * 0.1f;
        case Tanh:
            return tanhf(value);
        case Sigmoid:
            return 1.0f / (1.0f + expf(-value));
        default:
            return value;
    }
}

int random(int min, int max){
    return min + (max - min) * rand() / RAND_MAX;
}

float random(float min, float max){
    float f = (float)rand() / RAND_MAX;
    return min + f * (max - min);
}

Network createChild(Network &net1, Network &net2) {
    Network net = net2;

    for (int i = 0; i < net.biases().size(); ++i) {
        for (int j = 0; j < net.biases()[i].size(); ++j) {
            net.biases()[i][j] = (net.biases()[i][j] + net1.biases()[i][j]) / 2;
        }
    }
    for (int i = 0; i < net.weights().size(); ++i) {
        for (int j = 0; j < net.weights()[i].size(); ++j) {
            net.weights()[i][j] = (net.weights()[i][j] + net1.weights()[i][j]) / 2;
        }
    }

    return net;
}

Network createChild(Network &net1, Network &net2, int mutationIndex, float max) {
    auto net = createChild(net1, net2);
    int mutations = random(0, mutationIndex);

    for (int i = 0; i < mutations; ++i) {
        bool weights = random(0, 2);
        if(weights){
            int x = random(0, net.weights().size() - 1);
            int y = random(0, net.weights()[x].size() - 1);
            net.weights()[x][y] += random(-max, max);
        }else{
            int x = random(0, net.biases().size() - 1);
            int y = random(0, net.biases()[x].size() - 1);
            net.biases()[x][y] += random(-max, max);
        }
    }

    return net;
}
