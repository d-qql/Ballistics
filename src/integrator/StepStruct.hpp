//
// Created by legokol on 11.03.2022.
//

#ifndef BALLISTICS_STEPSTRUCT_HPP
#define BALLISTICS_STEPSTRUCT_HPP

#include "State.hpp"

struct StepStruct {
    /* Структура шага интегрирования */
    double step;
    State state;
};

#endif //BALLISTICS_STEPSTRUCT_HPP
