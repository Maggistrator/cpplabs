#include "Body2D.h"
#include "Vector2D.h"
#include <list>

class World
{
    std::list<Body2D> entities;

    public:
        Body2D findEntity(Vector2D position){
            for(Body2D entity: entities){
                if(entity.position == position) return entity;
            }
            return NULL;
        }

    void addEnitity(Body2D& entity){
        entities.push_front(entity);
    }

    void getEntity(Body2D& entity){
        entities.remove(entity);
    }
};
