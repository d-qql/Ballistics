//
// Created by legokol on 11.03.2022.
//

#ifndef BALLISTICS_DORMANDPRINCE78_HPP
#define BALLISTICS_DORMANDPRINCE78_HPP

#include <vector>

#include "StepStruct.hpp"
#include "../right_hand_side/RightHandSide.hpp"

class DormandPrince78 {
    /* Схема Дорманда-Принса 7(8) */
    int order; // Порядок метода
    int stages; // Стадийность метода
    Eigen::MatrixXd matrix; // Матрица для расчёта k
    Eigen::VectorXd column; // Столбец для переменной
    Eigen::VectorXd rowForSolution; // Строка расчёта решения
    Eigen::VectorXd rowForError; // Строка расчёта ошибки

    RightHandSide rightHandSide_; // Класс вычисления правой части

private:
    /** Метод для шага интегрирования
     *
     * @param stepStruct структура предыдущего шага
     *
     * @return сделанный шаг интегрирования
     */
    StepStruct calcOneStep(const StepStruct &stepStruct, double endTime) const;

public:
    /** Конструктор интегратора
     *
     * @param rightHandSide вычислитель правой части
     */
    DormandPrince78(const RightHandSide &rightHandSide);

    /** Метод интегрирования
     *
     * @param initialState начальное состояние
     * @param endTime время окончания интегрирования
     * @param step начальный шаг по времени
     *
     * @return вектор из состояний
     */
    std::vector<State> calc(const State &initialState, double endTime, double step) const;
};


#endif //BALLISTICS_DORMANDPRINCE78_HPP
