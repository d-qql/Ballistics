//
// Created by legokol on 11.03.2022.
//

#ifndef BALLISTICS_RIGHTHANDSIDE_HPP
#define BALLISTICS_RIGHTHANDSIDE_HPP

#include "../ballistics/satellite/SatelliteData.hpp"
#include "../ballistics/force/BaseForce.hpp"

#include <memory>
#include <Eigen/Dense>

class RightHandSide {
    /* Класс вычисления правой части */
public:

    /** Вычисление правой части
     *
     * @param state позиция аппарата
     * @param satData состояние аппарата (может меняться)
     * @param forceVector силы, которые необходимо учесть
     *
     * @return правая часть дифференциального уравнения движения
     */
    Eigen::Vector<double, 6>
    calc(const SatPositionState &state, SatData &satData, const std::vector<std::shared_ptr<BaseForce>> &forceVector) const;
};


#endif //BALLISTICS_RIGHTHANDSIDE_HPP
