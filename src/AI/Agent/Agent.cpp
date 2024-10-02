//
// Created by Tobias on 12.08.2024.
//

#include "Agent.h"

Agent::Agent(int n, std::vector<int> &topology, std::vector<Activations> &activations, float min, float max) {
    for (int i = 0; i < n; ++i) {
        _networks.emplace_back(topology, activations, min, max);
    }
}

void Agent::breed(std::vector<float> fitness, int winners, int mutationIndex, float maxMutation) {
    int nets = _networks.size();
    std::vector<Network> parents;

    for (int i = 0; i < winners; ++i) {
        int maxIdx = 0;
        for (int j = 0; j < fitness.size(); ++j) {
            if(fitness[j] > fitness[maxIdx]){
                maxIdx = j;
            }
        }
        parents.emplace_back(_networks[maxIdx]);
        //_networks.erase(_networks.begin() + maxIdx);
        fitness.erase(fitness.begin() + maxIdx);
    }

    _networks.clear();

    _networks.insert(_networks.begin(), parents.begin(), parents.end());

    int cnt = winners;

    while(cnt < nets){
        for (int i = 0; i < winners; ++i) {
            for (int j = 0; j < winners; ++j) {
                if(i != j && cnt < nets){
                    _networks.emplace_back(createChild(parents[i], parents[j], mutationIndex, maxMutation));
                    cnt++;
                }
            }
        }
    }
}

int Agent::size() {
    return _networks.size();
}

Network &Agent::operator[](int i) {
    return _networks[i];
}

Network &Agent::at(int i) {
    return _networks[i];
}

