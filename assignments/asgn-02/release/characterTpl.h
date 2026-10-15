/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: CharacterTpl
Filename: CharacterTpl.h
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

#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#ifndef SENECA_CHARACTER_TPL_H
#define SENECA_CHARACTER_TPL_H

#include <iostream>
#include "character.h"

namespace seneca
{
	template <typename T>
	class CharacterTpl : public Character
	{
		int m_healthMax{};
		T m_health{};

	public:
		CharacterTpl(const char* name, int healthMax)
			: Character(name), m_healthMax(healthMax)
		{
			m_health = healthMax;
		}

		void takeDamage(int dmg) override
		{
			m_health -= dmg;
			if (static_cast<int>(m_health) <= 0)
			{
				m_health = 0;
				std::cout << "    " << getName() << " has been defeated!\n";
			}
			else
			{
				std::cout << "    " << getName() << " took " << dmg << " damage, "
					<< getHealth() << " health remaining.\n";
			}
		}

		int getHealth() const override
		{
			return static_cast<int>(m_health);
		}

		int getHealthMax() const override
		{
			return m_healthMax;
		}

		void setHealth(int health) override
		{
			m_health = health;
		}

		void setHealthMax(int health) override
		{
			m_healthMax = health;
			m_health = health;
		}
	};
}

#endif
#endif
