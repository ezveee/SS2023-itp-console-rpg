#pragma once
#include <string>

#define WARRIOR_COST 3 // + Level
#define MAGICIAN_COST 4 // + Level

class Entity;

class Ability
{
    public:
        virtual ~Ability() = default;

        int cost;
        bool isAOE;
        std::wstring getName() const;

        virtual void action(Entity* user, Entity* target) = 0;
        void attack(int damage, int manaCost, bool isSpecial, Entity* user, Entity* target);

    protected:
        std::wstring name;

    private:
        int modifyAccuracy(int userAccuracy);
        bool doesAttackHit(int modifiedAccuracy, int targetDefense);
};
