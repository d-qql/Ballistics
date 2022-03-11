//
// Created by d-qql on 11.03.2022.
//

#ifndef BALLISTICS_SATELLITEDATA_HPP
#define BALLISTICS_SATELLITEDATA_HPP

#include <Eigen/Dense>
#include <ballistics/coordinate_system/time/Time.hpp>

struct SatPositionState{
    Time timeTT;
    Eigen::Vector3d position;
    Eigen::Vector3d velocity;
};
struct SatData{
    double mass;
    double fuelMass;
};
#endif //BALLISTICS_SATELLITEDATA_HPP
