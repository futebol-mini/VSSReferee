#ifndef RECORDER_H
#define RECORDER_H

#include <QDataStream>
#include <QDir>
#include <QFile>
#include <QMutex>
#include <QNetworkDatagram>
#include <QUdpSocket>

#include <src/utils/text/text.h>
#include <src/utils/timer/timer.h>
#include <src/utils/types/messagetype/messagetype.h>

class Recorder : public QObject {
  public:
    Recorder(QString fileName, QString visionAddress, quint16 visionPort, QString refereeAddress,
             quint16 refereePort);
    ~Recorder() override;

  private:
    // File
    QFile *_file{nullptr};
    QString _fileName;
    void openFile();
    void writeDatagram(MessageType messageType, QByteArray data, qint64 timeStamp);

    // Mutex control
    QMutex _fileMutex;

    // Network
    // Vision
    QUdpSocket *_visionSocket{nullptr};
    QString _visionAddress;
    quint16 _visionPort;
    void connectToVisionNetwork();

    // Referee
    QUdpSocket *_refereeSocket{nullptr};
    QString _refereeAddress;
    quint16 _refereePort;
    void connectToRefereeNetwork();
};

#endif // RECORDER_H
