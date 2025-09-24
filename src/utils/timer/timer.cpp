#include "timer.h"
#include "simulationtime.h"

#include <QDateTime>

const auto TICKS_TO_MILLISECONDS = 10;

Timer::Timer() {
    // Updating time1 and time2 with actual time
    _time1 = SimulationTime::GetInstance()->now();
    _time2 = SimulationTime::GetInstance()->now();
}

void Timer::start() {
    // Updating time1 with last time
    _time1 = SimulationTime::GetInstance()->now();
}

void Timer::stop() {
    // Updating time2 with last time
    _time2 = SimulationTime::GetInstance()->now();
}

double Timer::getSeconds() {
    return (getNanoSeconds() / 1E9);
}

double Timer::getMiliSeconds() {
    return (getNanoSeconds() / 1E6);
}

double Timer::getMicroSeconds() {
    return (getNanoSeconds() / 1E3);
}

double Timer::getNanoSeconds() {
    double passedTime = _time2 - _time1;
    return (passedTime * TICKS_TO_MILLISECONDS / 1E3);
}

QString Timer::getActualTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char str[100];
    sprintf(str, "%04d-%02d-%02d|%02d:%02d:%02d", 1900+ltm->tm_year, 1+ltm->tm_mon, ltm->tm_mday,
                                                  ltm->tm_hour, ltm->tm_min, ltm->tm_sec);

    QString actualTime(str);

    return actualTime;
}

qint64 Timer::systemTime() {
    return QDateTime::currentMSecsSinceEpoch();
}
