#include "algorithm/reliability_calculator_random.h"

reliability_calculator_random::reliability_calculator_random() {
    boost::random::mt19937 gen(std::time(nullptr)); //Boost Random Generator 
    boost::random::uniform_01<> dist;
    this->gen = gen;
    this->dist = dist;
}

reliability_calculator_random::~reliability_calculator_random() {
    //empty
}

float reliability_calculator_random::calculate_reliability(boost::shared_ptr<tiled_image> ti, boost::shared_ptr<tile_junction> junc) {
    return static_cast<float>(dist(gen));
}

float reliability_calculator_random::calculate_reliability(boost::shared_ptr<tiled_image> ti, boost::shared_ptr<tile> t) {
    return static_cast<float>(dist(gen));
}

void reliability_calculator_random::init_junctions(sharedptr<tiled_image> ti) {
    //empty
}
