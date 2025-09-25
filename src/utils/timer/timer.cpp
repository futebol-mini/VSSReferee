#include "timer.h"
#include "simulationtime.h"

#include <QDateTime>
#include <chrono>
#include <iomanip>
#include <sstream>

const uint32_t WEBOTS_TIMESTEP_US = 10'000;

const double MICRO_TO_SECONDS = 1e-6;
const double MICRO_TO_MILLISECONDS = 1e-3;

#define SIM_TIME true

uint32_t now_provider() {
    if (SIM_TIME)
        return SimulationTime::GetInstance()->now() * WEBOTS_TIMESTEP_US;
    else
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
}

Timer::Timer() : _time1_us(now_provider()), _time2_us(now_provider()) {
    // Updating time1 and time2 with actual time
}

void Timer::start() {
    // Updating time1 with last time
    _time1_us = now_provider();
}

void Timer::stop() {
    // Updating time2 with last time
    _time2_us = now_provider();
}

double Timer::getSeconds() { return (getMicroSeconds() * MICRO_TO_SECONDS); };

double Timer::getMiliSeconds() { return (getMicroSeconds() * MICRO_TO_MILLISECONDS); };

double Timer::getMicroSeconds() {

    double passedTime = ((double)_time2_us) - ((double)_time1_us);

    return passedTime;
}

QString Timer::getActualTime() {

    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d|%H:%M:%S");

    QString actualTime(ss.str().c_str());

    return actualTime;
}

qint64 Timer::systemTime() {
    return QDateTime::currentMSecsSinceEpoch();
}
