#pragma once
#include <string>

#define WARRIOR_COST 3 // + Level
#define MAGICIAN_COST 4 // + Level
#define ASSASSIN_COST 3 // + Level
#define HEALER_COST 4 // + Level

class Entity;

class Ability
{
    public:
        virtual ~Ability() = default;

        int cost;
        bool isAOE;
        std::wstring getName() const;
		std::wstring getInfo() const;

        virtual void action(Entity* user, Entity* target) = 0;
        void attack(int damage, int manaCost, bool isSpecial, Entity* user, Entity* target);

    protected:
        std::wstring name;
		std::wstring info;

    private:
        int modifyAccuracy(int userAccuracy);
        bool doesAttackHit(int modifiedAccuracy, int targetDefense);
};
