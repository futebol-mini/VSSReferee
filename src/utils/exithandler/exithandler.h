#ifndef EXITHANDLER_H
#define EXITHANDLER_H

#include <QApplication>
#include <QObject>

class ExitHandler : public QObject {
  public:
    ExitHandler();
    static void setApplication(QApplication *app);
    static void setup();
    static void run(int s);

  private:
    static QCoreApplication *_app;
    static int _counter;
};

#endif // EXITHANDLER_H
