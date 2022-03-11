//
// Created by d-qql on 11.03.2022.
//
#include "Time.hpp"
#include <cmath>
#include <sstream>
#include <sofa.h>

bool Time::isEqual(const Time &time, double tolerance) const {
    if (this->timeScale != time.timeScale) {
        std::stringstream buffer;
        buffer << "Разные шкалы времени" << std::endl;
        throw std::runtime_error(buffer.str().c_str());
    } else {
        return std::abs((this->jdDay - time.jdDay) + std::abs(this->jdPart - time.jdPart)) * SECS_IN_DAY < tolerance &&
               this->timeScale == time.timeScale;
    }
}

bool Time::operator>(const Time &time) const {
    if (this->timeScale != time.timeScale) {
        std::stringstream buffer;
        buffer << "Разные шкалы времени" << std::endl;
        throw std::runtime_error(buffer.str().c_str());
    } else {
        return (this->jdDay - time.jdDay) + (this->jdPart - time.jdPart) > 0;
    }
}

bool Time::operator<(const Time &time) const {
    if (this->timeScale != time.timeScale) {
        std::stringstream buffer;
        buffer << "Разные шкалы времени" << std::endl;
        throw std::runtime_error(buffer.str().c_str());
    } else {
        return (this->jdDay - time.jdDay) + (this->jdPart - time.jdPart) < 0;
    }
}

Time::Time(double jdDay, double jdPart, TimeScales scale) : jdDay(jdDay), jdPart(jdPart), timeScale(scale) {
    while (jdPart >= 1.) {
        jdPart -= 1.;
        jdDay += 1.;
    }
    while (jdPart < 0.) {
        jdPart += 1.;
        jdDay -= 1.;
    }
}

Time::Time(int year, int month, int day, int hour, int minute, double seconds, TimeScales scale) : jdDay(0.),
                                                                                                   jdPart(0.),
                                                                                                   timeScale(scale) {
    // Используем функции библиотеки sofa для конвертации каледарного формата
    int error =
            iauDtf2d(scaleStrings.at(scale).c_str(), year, month, day, hour, minute, seconds, &jdDay, &jdPart);
    if (!(error == 0 || error == 1)) {
        /*** Если Sofa возвращает не 0 или не 1, то бросаем исключение
         * 0 возвращается, если все в порядке
         * 1 возвращается, если дата слишком дальняя
         * ***/
        std::stringstream buffer;
        buffer << "Некорректное задание времени!"
               << " год: " << year << " месяц: " << month << " день: " << day << " час: " << hour << " минута: "
               << minute
               << " секунда: " << seconds;
        throw std::runtime_error(buffer.str().c_str());
    }
    // библиотека sofa возвращает данные немного в другом формате, поэтому:
    double jd = jdDay + jdPart;  // Формируем jd дату
    jdDay = std::floor(jd);          // берем целую часть дня
    jdPart = jd - jdDay;         // берем дробную часть дня
}

Time::Time(const Time::Calendar &calendar) : Time(calendar.year, calendar.month, calendar.day, calendar.hour,
                                                  calendar.minute, calendar.second, calendar.scale) {

}

Time Time::addSeconds(double seconds) const {
    Time result(jdDay, jdPart + seconds / SECS_IN_DAY, this->timeScale);
    while (result.jdPart >= 1.) {
        result.jdPart -= 1.;
        result.jdDay += 1.;
    }
    while (result.jdPart < 0.) {
        result.jdPart += 1.;
        result.jdDay -= 1.;
    }
    // Если мы прибавили отрицательное число секунд, то могли выйти за пределы даты jd
#ifndef NDEBUG
    if (result.jdPart < 0. || result.jdDay < .0) {
        std::stringstream buff;
        buff << "После прибавления секунд получается некорректное время! " << result;
        throw std::runtime_error(buff.str().c_str());
    }
#endif
    return result;
}

double Time::getJdDay() const noexcept {
    return jdDay;
}

double &Time::getJdDay() noexcept {
    return jdDay;
}

double Time::getJdPart() const noexcept {
    return jdPart;
}

double &Time::getJdPart() noexcept {
    return jdPart;
}

TimeScales Time::scale() const noexcept {
    return timeScale;
}

TimeScales &Time::scale() noexcept {
    return timeScale;
}

double Time::jd() const noexcept {
    return jdDay + jdPart;
}

double Time::secondsSinceJ2000() const noexcept {
    return ((jdDay - JD_MINUS_J2000) + jdPart) * SECS_IN_DAY;
}


