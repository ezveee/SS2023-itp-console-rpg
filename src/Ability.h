#pragma once
#include <string>

class Entity;

class Ability
{
    public:
        virtual ~Ability() = default;

        int cost;
        bool isAOE;
        void setLevel(Entity* entity);
        std::wstring getName() const;

        virtual void action(Entity* user, Entity* target) = 0;
        void attack(int damage, int manaCost, bool isSpecial, Entity* user, Entity* target);

    protected:
        std::wstring name;
        int level;

    private:
        int modifyAccuracy(int userAccuracy);
        bool doesAttackHit(int modifiedAccuracy, int targetDefense);
};
