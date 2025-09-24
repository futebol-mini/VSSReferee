
#include "simulationtime.h"
#include <cstdint>
#include <memory>

/**
 * Static methods should be defined outside the class.
 */

std::mutex SimulationTime::mutex_;

std::shared_ptr<SimulationTime> SimulationTime::GetInstance() {

    static std::shared_ptr<SimulationTime> pinstance_;

    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr) {
        pinstance_ = std::make_shared<SimulationTime>();
    }
    return pinstance_;
}

void SimulationTime::update(uint32_t time) {

    if (time < this->last_time_) {
        // Reeived time from the past
        this->last_time_ = time;
        return;
    }

    this->elapsed_time_ += time - this->last_time_;

    this->last_time_ = time;
}

uint32_t SimulationTime::now() { return this->elapsed_time_; }
