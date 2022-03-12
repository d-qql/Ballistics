//
// Created by d-qql on 11.03.2022.
//

#ifndef BALLISTICS_TIME_HPP
#define BALLISTICS_TIME_HPP

#include <ballistics/utils/Consts.hpp>
#include <map>
#include <string>

enum TimeScales {
    TT_SCALE = 0, UTC_SCALE = 1, UT1_SCALE = 2, TDB_SCALE = 3
};

const std::map<const TimeScales, const std::string> scaleStrings = {
        {TimeScales::TT_SCALE,  "tt"},
        {TimeScales::UTC_SCALE, "UTC"},
        {TimeScales::UT1_SCALE, "ut1"},
        {TimeScales::TDB_SCALE, "tdb"}};

class Time {
private:
    double jdDay;
    double jdPart;
    TimeScales timeScale;
public:
    struct Calendar {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        double second;
        TimeScales scale;
    };

    Time(int year, int month, int day, int hour, int minute, double seconds, TimeScales scale = TimeScales::TT_SCALE);

    Time(const Calendar &calendar);

    Time(double jdDay, double jdPart, TimeScales scale = TimeScales::TT_SCALE);

    Time addSeconds(double seconds) const;

    bool operator<(const Time &time) const;

    bool operator>(const Time &time) const;

    bool isEqual(const Time &time, double tolerance = TIME_TOLERANCE) const;

    [[nodiscard]] double getJdDay() const noexcept;

    double &getJdDay() noexcept;

    [[nodiscard]] double getJdPart() const noexcept;

    double &getJdPart() noexcept;

    [[nodiscard]] TimeScales scale() const noexcept;

    TimeScales &scale() noexcept;

    [[nodiscard]] double jd() const noexcept;

    [[nodiscard]] double secondsSinceJ2000() const noexcept;

};


#endif //BALLISTICS_TIME_HPP
