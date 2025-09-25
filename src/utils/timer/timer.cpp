#include "timer.h"
#include "simulationtime.h"

#include <QDateTime>
#include <chrono>
#include <iomanip>
#include <sstream>

const uint32_t WEBOTS_TIMESTEP_US = 10'000;

const double MICRO_TO_SECONDS = 1e-6;
const double MICRO_TO_MILLISECONDS = 1e-3;

uint32_t Timer::now_provider() {
    switch (this->_provider) {
    case Timer::Provider::WALL:
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   std::chrono::high_resolution_clock::now().time_since_epoch())
            .count();
    case Timer::Provider::SIMULATION:
        return SimulationTime::GetInstance()->now() * WEBOTS_TIMESTEP_US;
    }

    return 0;
}

Timer::Timer(Timer::Provider provider)
    : _provider(provider), _time1_us(now_provider()), _time2_us(now_provider()) {
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
