#include <queue>
#include <random>
#include <iostream>

// Oopsie I wrote some code..

int generateRandNum(int len) {

    // Seed the random number generator
    std::random_device rd;
    std::mt19937 gen(rd()); // Mersenne Twister engine

    // Define the range
    std::uniform_int_distribution<int> distribution(0, len);

    return distribution(gen);
}

class CustomQueue {
public:
    std::queue <int> queueInQuestion;

    void enqueue() {
        queueInQuestion.push(generateRandNum(queueInQuestion.size()));
    }
};