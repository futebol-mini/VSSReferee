
#ifndef SIMULATION_TIME_H
#define SIMULATION_TIME_H

#include <QString>
#include <cstdint>
#include <memory>
#include <mutex>

class SimulationTime {
  public:
    /**
     * Singletons should not be cloneable.
     */
    SimulationTime(SimulationTime &other) = delete;
    SimulationTime(SimulationTime &&other) = delete;

    /**
     * Singletons should not be assignable.
     */
    void operator=(const SimulationTime &) = delete;
    void operator=(const SimulationTime &&) = delete;

    ~SimulationTime() = default;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static std::shared_ptr<SimulationTime> GetInstance();

    /**
     * @brief Update the current reference of simulation time
     *
     * @param time_step Last received time step from simulation
     *
     * @note The function update should be only called ONCE in code, as it's not thread safe
     */
    void update(uint64_t time_step);

    uint64_t now();

  private:
    static std::mutex mutex_;

    SimulationTime() = default;

    uint64_t last_time_step_{0};
    uint64_t elapsed_time_steps_{0};

  protected:
};

// SimulationTime singleton;

#endif // SIMULATION_TIME_H
