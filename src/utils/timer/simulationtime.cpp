
#include "simulationtime.h"
#include <cstdint>
#include <memory>

#include <src/utils/text/text.h>

#include <iostream>

/**
 * Static methods should be defined outside the class.
 */

std::mutex SimulationTime::mutex_;

std::shared_ptr<SimulationTime> SimulationTime::GetInstance() {

    static std::shared_ptr<SimulationTime> pinstance_ =
        std::shared_ptr<SimulationTime>(new SimulationTime());

    return pinstance_;
}

void SimulationTime::update(uint64_t time_step) {

    std::cout << Text::green("[SimulationTime] Got step ", true) << time_step << '\n';

    if (time_step < this->last_time_step_) {
        std::cout << Text::red("[SimulationTime] Got date from the past", true) << '\n';

        // Reeived time from the past
        this->last_time_step_ = time_step;
        return;
    }

    this->elapsed_time_steps_ += time_step - this->last_time_step_;

    this->last_time_step_ = time_step;
}

uint64_t SimulationTime::now() { return this->elapsed_time_steps_; }
