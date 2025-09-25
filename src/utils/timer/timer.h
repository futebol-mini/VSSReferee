#ifndef TIMER_H
#define TIMER_H

#include <QString>
#include <chrono>

class Timer {

    enum Provider {
        WALL,      //< Wall clock as reference
        SIMULATION //< Simulation clock as reference
    };

  public:
    Timer(Provider provider = Provider::SIMULATION);

    // Timer control
    void start();
    void stop();

    // Getters
    double getSeconds();
    double getMiliSeconds();
    double getMicroSeconds();
    static QString getActualTime();
    static qint64 systemTime();

    uint32_t now_provider();

  private:
    Provider _provider;
    // timespec _time1;
    // timespec _time2;

    uint32_t _time1_us;
    uint32_t _time2_us;
};

#endif // TIMER_H
