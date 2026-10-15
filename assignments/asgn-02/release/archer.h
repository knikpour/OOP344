/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: Archer
Filename: Archer.h
-----------------------------------------------------------
Author: Kiarash Nikpour
Student number: 140371246
Email: knikpour@myseneca.ca
Subject: OOP344NBB
-----------------------------------------------------------
Revision History
------------------------------------------------------------
Version Date      Reason
V0.1    2026/08/15  Completed
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my work for function whatever.
-----------------------------------------------------------
*/

#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include <iostream>
#include "characterTpl.h"
#include "health.h"

namespace seneca
{
	template <typename Weapon_t>
	class Archer : public CharacterTpl<seneca::SuperHealth>
	{
		int m_baseDefense{};
		int m_baseAttack{};
		Weapon_t m_weapon{};

	public:
		Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
			: CharacterTpl<seneca::SuperHealth>(name, healthMax),
			  m_baseDefense(baseDefense),
			  m_baseAttack(baseAttack),
			  m_weapon(weapon)
		{}

		int getAttackAmnt() const override
		{
			return static_cast<int>(1.3 * m_baseAttack);
		}

		int getDefenseAmnt() const override
		{
			return static_cast<int>(1.2 * m_baseDefense);
		}

		Character* clone() const override
		{
			return new Archer(*this);
		}

		void attack(Character* enemy) override
		{
			std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
			int dmg = getAttackAmnt();
			std::cout << "    Archer deals " << dmg << " ranged damage!\n";
			enemy->takeDamage(dmg);
		}

		void takeDamage(int dmg) override
		{
			std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
			std::cout << "    Archer has a defense of " << getDefenseAmnt()
				<< ". Reducing damage received.\n";
			dmg -= getDefenseAmnt();
			if (dmg < 0)
				dmg = 0;
			CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
		}
	};
}

#endif
