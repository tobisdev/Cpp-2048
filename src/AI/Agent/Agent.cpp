//
// Created by Tobias on 12.08.2024.
//

#include "Agent.h"

Agent::Agent(int n, std::vector<int> &topology, std::vector<Activations> &activations, float min, float max) {
    for (int i = 0; i < n; ++i) {
        _networks.emplace_back(topology, activations, min, max);
    }
}

void Agent::breed(std::vector<float> &fitness, int winners, int mutationIndex, float maxMutation) {
    int nets = _networks.size();
    std::vector<Network> parents;

    // Use a min-heap to track the winners networks
    using FitnessIndexPair = std::pair<float, int>;
    std::priority_queue<FitnessIndexPair, std::vector<FitnessIndexPair>, std::greater<>> minHeap;

    for (int i = 0; i < fitness.size(); ++i) {
        if (minHeap.size() < winners) {
            minHeap.emplace(fitness[i], i);
        } else if (fitness[i] > minHeap.top().first) {
            minHeap.pop();
            minHeap.emplace(fitness[i], i);
        }
    }

    // Store the networks of the top winners
    parents.reserve(winners); // Reserve space for winners
    while (!minHeap.empty()) {
        int maxIdx = minHeap.top().second;
        minHeap.pop();
        parents.emplace_back(_networks[maxIdx]); // Keep the top performing networks
    }

    // Clear the networks and insert the parents back
    _networks.clear();
    _networks.reserve(nets); // Reserve space for all networks
    _networks.insert(_networks.begin(), parents.begin(), parents.end());

    // Breeding phase - generate child networks
    int cnt = winners;

    while (cnt < nets) {
        for (int i = 0; i < winners && cnt < nets; ++i) {
            for (int j = 0; j < winners && cnt < nets; ++j) {
                if (i != j) {
                    // Create child from parents[i] and parents[j], mutate it, and add to the network
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

