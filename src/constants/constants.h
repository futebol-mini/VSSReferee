#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QString>
#include <QFile>

#include <src/utils/text/text.h>

class Constants
{
public:
    Constants(QString fileName);

    // Entities constants getters
    int threadFrequency();

    // Network constants getters
    QString networkInterface();

    // Referee constants getters
    QString refereeAddress();
    quint16 refereePort();
    float transitionTime();
    QString gameType();
    float ballRadius();
    float robotLength();
    float halfTime();
    float overtimeHalfTime();
    float ballMinSpeedForStuck();
    float stuckedBallTime();
    float ballInAreaMaxTime();
    bool useRefereeSuggestions();
    bool maintainSpeedAtSuggestions();
    void setIs5v5(bool is5v5);
    bool is5v5();

    // Vision constants getters
    QString visionAddress();
    quint16 visionPort();
    QString firaVisionAddress();
    quint16 firaVisionPort();

    bool isFIRAVision();

    bool useKalman();
    int noiseTime();
    int lossTime();

    // Replacer constants getters
    QString replacerAddress();
    quint16 replacerPort();
    QString firaAddress();
    quint16 firaPort();

    // Teams constants getters
    int qtPlayers();
    bool blueIsLeftSide();
    void swapSides();
    QStringList teams();

    // Discord webhook token
    QString getHToken();
    QString getHID();

    int timeoutsPerTeam();
    float timeoutLength();
    int varsPerTeam();


protected:
    QVariantMap documentMap() { return _documentMap; }

private:
    // Internal file management
    QString _fileName;
    QString _fileBuffer;
    QFile _file;

    // Internal json parse vars
    QJsonDocument _document;
    QVariantMap _documentMap;

    // Entities constants
    int _threadFrequency;
    void readEntityConstants();

    // Network interface
    QString _networkInterface;
    void readNetworkConstants();

    // Referee
    QString _refereeAddress;
    quint16 _refereePort;
    float _transitionTime;
    QString _gameType;
    float _ballRadius;
    float _robotLength;
    float _halfTime;
    float _overtimeHalfTime;
    float _ballMinSpeedForStuck;
    float _stuckedBallTime;
    float _ballInAreaMaxTime;
    bool _useRefereeSuggestions;
    bool _maintainSpeedAtSuggestions;
    bool _is5v5;
    void readRefereeConstants();

    // Vision constants
    QString _visionAddress;
    quint16 _visionPort;
    QString _firaVisionAddress;
    quint16 _firaVisionPort;
    bool _isFIRAVision;
    bool _useKalman;
    int _noiseTime;
    int _lossTime;
    void readVisionConstants();

    // Replacer constants
    QString _replacerAddress;
    quint16 _replacerPort;
    QString _firaAddress;
    quint16 _firaPort;
    void readReplacerConstants();

    // Teams constants
    int _qtPlayers;
    QStringList _teams;
    bool _blueIsLeftSide;
    void readTeamConstants();

    // Discord webhook
    QString _hID;
    QString _hToken;
    void readWebhookConstants();
};

#endif // CONSTANTS_H
