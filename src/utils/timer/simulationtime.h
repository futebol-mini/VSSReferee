
#ifndef SIMULATION_TIME_H
#define SIMULATION_TIME_H

#include <QString>
#include <chrono>
#include <cstdint>
#include <memory>
#include <mutex>

class SimulationTime {
  public:
    /**
     * Singletons should not be cloneable.
     */
    SimulationTime(SimulationTime &other) = delete;

    SimulationTime() = default;
    ~SimulationTime() = default;

    /**
     * Singletons should not be assignable.
     */
    void operator=(const SimulationTime &) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static std::shared_ptr<SimulationTime> GetInstance();
    /**
     * Finally, any singleton should define some business logic, which can be
     * executed on its instance.
     */

    void update(uint32_t time);

    uint32_t now();

  private:
    // timespec _time1;
    // timespec _time2;
    // static std::shared_ptr<SimulationTime> pinstance_;
    static std::mutex mutex_;

    uint32_t last_time_{0};
    uint32_t elapsed_time_{0};

  protected:
};

// SimulationTime singleton;

#endif // SIMULATION_TIME_H
