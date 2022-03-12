//
// Created by legokol on 11.03.2022.
//

#include "DormandPrince78.hpp"

StepStruct DormandPrince78::calcOneStep(const StepStruct &stepStruct, double endTime) const {
    std::vector<Eigen::VectorXd> k(stages);
    k[0] = stepStruct.state.x;
}

DormandPrince78::DormandPrince78(const RightHandSide &rightHandSide) : rightHandSide_(rightHandSide) {
    order = 8;
    stages = 13;
    // Заполнение таблицы Бутчера
    matrix(1, 0) = 1.0 / 18.0;
    matrix(2, 0) = 1.0 / 48.0;
    matrix(2, 1) = 1.0 / 16.0;
    matrix(3, 0) = 1.0 / 32.0;
    matrix(3, 2) = 3.0 / 32.0;
    matrix(4, 0) = 5.0 / 16.0;
    matrix(4, 2) = -75.0 / 64.0;
    matrix(4, 3) = 75.0 / 64.0;
    matrix(5, 0) = 3.0 / 80.0;
    matrix(5, 3) = 3.0 / 16.0;
    matrix(5, 4) = 3.0 / 20.0;
    matrix(6, 0) = 29443841.0 / 614563906.0;
    matrix(6, 3) = 77736538.0 / 692538347.0;
    matrix(6, 4) = -28693883.0 / 1.125e9;
    matrix(6, 5) = 23124283.0 / 1.8e9;
    matrix(7, 0) = 16016141.0 / 946692911.0;
    matrix(7, 3) = 61564180.0 / 158732637.0;
    matrix(7, 4) = 22789713.0 / 633445777.0;
    matrix(7, 5) = 545815736.0 / 2771057229.0;
    matrix(7, 6) = -180193667.0 / 1043307555.0;
    matrix(8, 0) = 39632708.0 / 573591083.0;
    matrix(8, 3) = -433636366.0 / 683701615.0;
    matrix(8, 4) = -421739975.0 / 2616292301.0;
    matrix(8, 5) = 100302831.0 / 723423059.0;
    matrix(8, 6) = 790204164.0 / 839813087.0;
    matrix(8, 7) = 800635310.0 / 3783071287.0;
    matrix(9, 0) = 246121993.0 / 1340847787.0;
    matrix(9, 3) = -37695042795 / 15268766246.0;
    matrix(9, 4) = -309121744.0 / 1061227803.0;
    matrix(9, 5) = -12992083.0 / 490766935.0;
    matrix(9, 6) = 6005943493.0 / 2108947869.0;
    matrix(9, 7) = 393006217.0 / 1396673457.0;
    matrix(9, 8) = 123872331.0 / 1001029789.0;
    matrix(10, 0) = -1028468189.0 / 846180014.0;
    matrix(10, 3) = 8478235783.0 / 508512852.0;
    matrix(10, 4) = 1311729495.0 / 1432422823.0;
    matrix(10, 5) = -10304129995.0 / 1701304382.0;
    matrix(10, 6) = -48777925059.0 / 3047939560.0;
    matrix(10, 7) = 15336726248.0 / 1032824649.0;
    matrix(10, 8) = -45442868181.0 / 3398467696.0;
    matrix(10, 9) = 3065993473.0 / 597172653.0;
    matrix(11, 0) = 185892177.0 / 718116043.0;
    matrix(11, 3) = -3185094517.0 / 667107341.0;
    matrix(11, 4) = -477755414.0 / 1098053517.0;
    matrix(11, 5) = -703635378.0 / 230739211.0;
    matrix(11, 6) = 5731566787.0 / 1027545527.0;
    matrix(11, 7) = 5232866602.0 / 850066563.0;
    matrix(11, 8) = -4093664535.0 / 808688257.0;
    matrix(11, 9) = 3962137247.0 / 1805957418.0;
    matrix(11, 10) = 65686358.0 / 487910083.0;
    matrix(12, 0) = 403863854.0 / 491063109.0;
    matrix(12, 3) = -5068492393.0 / 434740067.0;
    matrix(12, 4) = -411421997.0 / 543043805.0;
    matrix(12, 5) = 652783627.0 / 914296604.0;
    matrix(12, 6) = 11173962825.0 / 925320556.0;
    matrix(12, 7) = -13158990841.0 / 6184727034.0;
    matrix(12, 8) = 3936647629.0 / 1978049680.0;
    matrix(12, 9) = -160528059.0 / 685178525.0;
    matrix(12, 10) = 248638103.0 / 1413531060.0;
    // Заполенние столбца для переменной
    column(0) = 0.0;
    column(1) = 1.0 / 18.0;
    column(2) = 1.0 / 12.0;
    column(3) = 0.1250;
    column(4) = 5.0 / 16.0;
    column(5) = 3.0 / 8.0;
    column(6) = 59.0 / 4.e2;
    column(7) = 93.0 / 2.e2;
    column(8) = 5490023248.0 / 9719169821.0;
    column(9) = 13.0 / 2.e1;
    column(10) = 1201146811.0 / 1299019798.0;
    column(11) = 1.0;
    column(12) = 1.0;
    // Заполнение строки для решения (с 8-ым порядком)
    rowForSolution(0) = 13451932.0 / 455176623.0;
    rowForSolution(1) = 0.0;
    rowForSolution(2) = 0.0;
    rowForSolution(3) = 0.0;
    rowForSolution(4) = 0.0;
    rowForSolution(5) = -808719846.0 / 976000145.0;
    rowForSolution(6) = 1757004468.0 / 5645159321.0;
    rowForSolution(7) = 656045339.0 / 265891186.0;
    rowForSolution(8) = -3867574721.0 / 1518517206.0;
    rowForSolution(9) = 465885868.0 / 322736535.0;
    rowForSolution(10) = 53011238.0 / 667516719.0;
    rowForSolution(11) = 2.0 / 45.0;
    rowForSolution(12) = 0.0;
    // Заполнение строки для расчёта решения с меньшим порядком (7-ым)
    rowForError(0) = 14005451.0 / 335480064.0;
    rowForError(1) = 0.0;
    rowForError(2) = 0.0;
    rowForError(3) = 0.0;
    rowForError(4) = 0.0;
    rowForError(5) = -59238493.0 / 1068277825.0;
    rowForError(6) = 181606767.0 / 758867731.0;
    rowForError(7) = 561292985.0 / 797845732.0;
    rowForError(8) = -1041891430.0 / 1371343529.0;
    rowForError(9) = 760417239.0 / 1151165299.0;
    rowForError(10) = 118820643.0 / 751138087.0;
    rowForError(11) = -528747749.0 / 2220607170.0;
    rowForError(12) = 0.25;
    // Вычитание одной строки из другой, чтобы получить строку для расчёта погрешности
    rowForError -= rowForSolution;
}

std::vector<State> DormandPrince78::calc(const State &initialState, double endTime, double step) const {
    StepStruct stepStruct{step, initialState};
    std::vector<State> result;
    State currentState = initialState;
    while (currentState.time < endTime) {
        // Шаг интегрирования и коррекция шага
        stepStruct = calcOneStep(stepStruct, endTime);
        // Запись данных
        currentState = stepStruct.state;
        result.push_back(currentState);
    }
    return result;
}