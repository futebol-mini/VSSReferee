#ifndef TIMER_H
#define TIMER_H

#include <QString>
#include <chrono>

class Timer {
  public:
    Timer();

    // Timer control
    void start();
    void stop();

    // Getters
    double getSeconds();
    double getMiliSeconds();
    double getMicroSeconds();
    static QString getActualTime();
    static qint64 systemTime();

  private:
    // timespec _time1;
    // timespec _time2;

    uint32_t _time1_us;
    uint32_t _time2_us;
};

#endif // TIMER_H
