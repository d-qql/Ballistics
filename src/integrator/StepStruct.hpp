//
// Created by legokol on 11.03.2022.
//

#ifndef BALLISTICS_STEPSTRUCT_HPP
#define BALLISTICS_STEPSTRUCT_HPP

#include "../ballistics/satellite/SatelliteData.hpp"

struct StepStruct {
    /* Структура шага интегрирования */
    double step;
    SatPositionState satPositionState;
    SatData satData;
};

#endif //BALLISTICS_STEPSTRUCT_HPP
