#include "checker_goalie.h"

QString Checker_Goalie::name() { return "Checker_Goalie"; }

void Checker_Goalie::configure() {
    for (int i = VSSRef::Color::BLUE; i <= VSSRef::Color::YELLOW; i++) {
        // Insert hash for that team
        auto *teamHash = new QHash<quint8, Timer *>();
        _timers.insert(VSSRef::Color(i), teamHash);

        // Insert elapsedTimer hash for that team
        auto *teamElapsedTimer = new QHash<quint8, float>();
        _elapsedTimeInGoal.insert(VSSRef::Color(i), teamElapsedTimer);

        // Creating timers for each player
        for (int j = 0; j < getConstants()->qtPlayers(); j++) {
            // Create Timer pointer
            auto *playerTimer = new Timer();

            // Reset it
            playerTimer->start();

            // Insert in hash
            teamHash->insert(j, playerTimer);

            // Reset elapsedTimer
            teamElapsedTimer->insert(j, 0.0f);
        }
    }
}

void Checker_Goalie::run() {
    // Run for both teams
    for (int i = VSSRef::Color::BLUE; i <= VSSRef::Color::YELLOW; i++) {
        // Take team hash
        QHash<quint8, Timer *> *teamHash = _timers.value(VSSRef::Color(i));

        // Take team elapsed time hash
        QHash<quint8, float> *teamElapsedTimeHash = _elapsedTimeInGoal.value(VSSRef::Color(i));

        // Take available players
        QList<quint8> avPlayers = getVision()->getAvailablePlayers(VSSRef::Color(i));

        // Iterate in that players
        for (unsigned char avPlayer : avPlayers) {
            // Take player pos
            Position playerPos = getVision()->getPlayerPosition(VSSRef::Color(i), avPlayer);

            // Take player timer
            Timer *playerTimer = teamHash->value(avPlayer);

            // Check if is inside goal
            if (Utils::isInsideGoalArea(VSSRef::Color(i), playerPos)) {
                // Stop player timer
                playerTimer->stop();

                // Take elapsed time
                float elapsedPlayerTimeAtGoal = teamElapsedTimeHash->take(avPlayer);

                // Update it with passed time
                elapsedPlayerTimeAtGoal = elapsedPlayerTimeAtGoal + playerTimer->getSeconds();

                // Insert again
                teamElapsedTimeHash->insert(avPlayer, elapsedPlayerTimeAtGoal);
            }
            // If player is outside goal area, reset its timer
            else {
                teamElapsedTimeHash->insert(avPlayer, 0.0f);
            }

            // Reset timer
            playerTimer->start();
        }
    }

    // Check best elapsed time
    updateGoalies();
}

void Checker_Goalie::updateGoalies() {
    // Run for both teams
    for (int i = VSSRef::Color::BLUE; i <= VSSRef::Color::YELLOW; i++) {
        // Take team elapsed time hash
        QHash<quint8, float> *teamElapsedTimeHash = _elapsedTimeInGoal.value(VSSRef::Color(i));

        // Take available players
        QList<quint8> avPlayers = getVision()->getAvailablePlayers(VSSRef::Color(i));

        // Iterate in that players
        quint8 bestId = 0; // 0 by default
        float bestElapsedTime = 0.0f;
        for (unsigned char avPlayer : avPlayers) {
            // Take player elapsedTime at goal
            int elapsedTimeAtGoal = teamElapsedTimeHash->value(avPlayer);

            // Check if better than bestElapsedTime
            if (elapsedTimeAtGoal > bestElapsedTime) {
                // Update
                bestId = avPlayer;
                bestElapsedTime = elapsedTimeAtGoal;
            }
        }

        // Send signal to replacer and update
        emit updateGoalie(VSSRef::Color(i), bestId);
    }
}
