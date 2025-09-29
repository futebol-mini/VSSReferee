#ifndef WORLD_H
#define WORLD_H

#include <QHash>
#include <QMap>

#include <src/constants/constants.h>
#include <src/world/entities/entity.h>

class World {
  public:
    World(Constants *constants);

    // Entities management
    void addEntity(Entity *entity, int entityPriority);

    // Internal
    void startEntities();
    void stopAndDeleteEntities();

  private:
    // Hashtable for entities
    QMap<int, QHash<int, Entity *> *> _worldEntities;

    // Constants
    Constants *_constants;
    Constants *getConstants();
};

#endif // WORLD_H
