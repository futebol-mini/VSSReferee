#include "timer.h"
#include "simulationtime.h"

#include <QDateTime>
#include <chrono>

const uint32_t WEBOTS_TIMESTEP_MS = 10;

const double MILLI_TO_SECONDS = 1E-3;

#define SIM_TIME true

uint32_t now_provider() {
    if (SIM_TIME)
        return SimulationTime::GetInstance()->now() * WEBOTS_TIMESTEP_MS;
    else
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
}

Timer::Timer() : _time1_ms(now_provider()), _time2_ms(now_provider()) {
    // Updating time1 and time2 with actual time
}

void Timer::start() {
    // Updating time1 with last time
    _time1_ms = now_provider();
}

void Timer::stop() {
    // Updating time2 with last time
    _time2_ms = now_provider();
}

double Timer::getSeconds() { return (getMiliSeconds() * MILLI_TO_SECONDS); }

double Timer::getMiliSeconds() {

    double passedTime = ((double)_time2_ms) - ((double)_time1_ms);

    return passedTime;
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
