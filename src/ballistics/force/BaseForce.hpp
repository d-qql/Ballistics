//
// Created by d-qql on 11.03.2022.
//

#ifndef BALLISTICS_BASEFORCE_HPP
#define BALLISTICS_BASEFORCE_HPP

#include <Eigen/Dense>
#include <ballistics/satellite/SatelliteData.hpp>
class BaseForce {
public:
    virtual Eigen::Vector3d calcForce(const SatPositionState& satPositionState, const SatData& satData) = 0;
};

#endif //BALLISTICS_BASEFORCE_HPP
