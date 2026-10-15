/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: Barbarian
Filename: Barbarian.h
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

#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include <iostream>
#include "characterTpl.h"

namespace seneca
{
	template <typename T, typename Ability_t, typename Weapon_t>
	class Barbarian : public CharacterTpl<T>
	{
		int m_baseDefense{};
		int m_baseAttack{};
		Ability_t m_ability{};
		Weapon_t m_weapon[2]{};

	public:
		Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense,
			Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
			: CharacterTpl<T>(name, healthMax),
			  m_baseDefense(baseDefense),
			  m_baseAttack(baseAttack),
			  m_ability{},
			  m_weapon{ primaryWeapon, secondaryWeapon }
		{}

		int getAttackAmnt() const override
		{
			return static_cast<int>(m_baseAttack +
				static_cast<double>(m_weapon[0]) / 2.0 +
				static_cast<double>(m_weapon[1]) / 2.0);
		}

		int getDefenseAmnt() const override
		{
			return m_baseDefense;
		}

		Character* clone() const override
		{
			return new Barbarian(*this);
		}

		void attack(Character* enemy) override
		{
			std::cout << this->getName() << " is attacking " << enemy->getName() << ".\n";
			m_ability.useAbility(this);
			int dmg = getAttackAmnt();
			m_ability.transformDamageDealt(dmg);
			std::cout << "    Barbarian deals " << dmg << " melee damage!\n";
			enemy->takeDamage(dmg);
		}

		void takeDamage(int dmg) override
		{
			std::cout << this->getName() << " is attacked for " << dmg << " damage.\n";
			std::cout << "    Barbarian has a defense of " << m_baseDefense
				<< ". Reducing damage received.\n";
			dmg -= m_baseDefense;
			if (dmg < 0)
				dmg = 0;
			m_ability.transformDamageReceived(dmg);
			CharacterTpl<T>::takeDamage(dmg);
		}
	};
}

#endif
