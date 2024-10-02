//
// Created by Tobias on 12.08.2024.
//

#ifndef GAN_AGENT_H
#define GAN_AGENT_H

#include <vector>
#include "../../Network/Network.h"

class Agent {
private:
    std::vector<Network> _networks;
    int _generation;
public:
    Agent() = default;

    Agent(int, std::vector<int> &topology, std::vector<Activations> &activations, float min, float max);

    void breed(std::vector<float>, int, int, float);

    int size();

    Network &at(int i);
    Network &operator[](int i);
};


#endif //GAN_AGENT_H
