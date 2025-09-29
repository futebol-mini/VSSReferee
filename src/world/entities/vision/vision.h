#ifndef VISION_H
#define VISION_H

#include <QNetworkDatagram>
#include <QReadWriteLock>
#include <QUdpSocket>

#include <include/vssref_common.pb.h>
#include <include/wrapper.pb.h>
#include <src/constants/constants.h>
#include <src/utils/types/object/object.h>
#include <src/world/entities/entity.h>

class Vision : public Entity {
    Q_OBJECT
  public:
    Vision(Constants *constants);
    ~Vision() override;

    // Getters
    QList<quint8> getAvailablePlayers(VSSRef::Color teamColor);
    Position getPlayerPosition(VSSRef::Color teamColor, quint8 playerId);
    Velocity getPlayerVelocity(VSSRef::Color teamColor, quint8 playerId);
    Angle getPlayerOrientation(VSSRef::Color teamColor, quint8 playerId);
    Position getBallPosition();
    Velocity getBallVelocity();

  private:
    // Entity inherited methods
    void initialization() override;
    void loop() override;
    void finalization() override;

    // Constants
    Constants *_constants;
    Constants *getConstants();

    // Socket to receive vision data
    QUdpSocket *_visionClient{};
    void bindAndConnect();

    // Network
    QString _visionAddress;
    quint16 _visionPort;
    bool _isFIRAVision;

    // Objects
    Object *_ballObject{};
    QMap<VSSRef::Color, QHash<quint8, Object *> *> _objects;
    QMap<VSSRef::Color, QHash<quint8, bool> *> _objectsControl;
    void initObjects();
    void deleteObjects();
    void clearObjectsControl();

    // Data management
    QReadWriteLock _dataMutex;

    void SSLVisionPackets();
    void FIRAVisionPackets();

    std::string visionType = "[VISION] ";

  signals:
    void visionUpdated();

  public slots:
    void visionPacketChanged(bool isFIRAVision);
};

#endif // VISION_H
