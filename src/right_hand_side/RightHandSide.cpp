//
// Created by legokol on 12.03.2022.
//

#include "RightHandSide.hpp"

Eigen::Vector<double, 6> RightHandSide::calc(const SatPositionState &state, SatData &satData,
                                             const std::vector<std::shared_ptr<BaseForce>> &forceVector) const {
    // Производная координат - скорость
    Eigen::Vector<double, 6> result;
    result(Eigen::seq(0, 2)) = state.velocity;
    // Расчёт силы
    Eigen::Vector3d force{0, 0, 0};
    for (int i = 0; i < forceVector.size(); ++i) {
        force += forceVector[i]->calcForce(state, satData);
    }
    // a = F / m
    result(Eigen::seq(3, 5)) = force / (satData.mass + satData.fuelMass);
    return result;
}