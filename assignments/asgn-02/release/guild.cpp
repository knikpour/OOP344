/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: Guild
Filename: Guild.cpp
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

#include <iostream>
#include <utility>
#include "guild.h"

namespace seneca
{
	Guild::Guild(const char* name) : m_name{ name ? name : "" } {}

	Guild::Guild(const Guild& other)
	{
		*this = other;
	}

	Guild& Guild::operator=(const Guild& other)
	{
		if (this != &other)
		{
			delete[] m_members;
			m_members = nullptr;
			m_size = 0;

			m_name = other.m_name;
			if (other.m_size > 0)
			{
				m_members = new Character*[other.m_size];
				m_size = other.m_size;
				for (size_t i = 0; i < m_size; ++i)
					m_members[i] = other.m_members[i];
			}
		}
		return *this;
	}

	Guild::Guild(Guild&& other) noexcept
	{
		*this = std::move(other);
	}

	Guild& Guild::operator=(Guild&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_members;

			m_name = std::move(other.m_name);
			m_members = other.m_members;
			m_size = other.m_size;

			other.m_name.clear();
			other.m_members = nullptr;
			other.m_size = 0;
		}
		return *this;
	}

	Guild::~Guild()
	{
		delete[] m_members;
	}

	void Guild::addMember(Character* c)
	{
		if (!c)
			return;

		for (size_t i = 0; i < m_size; ++i)
		{
			if (m_members[i]->getName() == c->getName())
				return;
		}

		Character** temp = new Character*[m_size + 1];
		for (size_t i = 0; i < m_size; ++i)
			temp[i] = m_members[i];
		temp[m_size] = c;
		delete[] m_members;
		m_members = temp;
		++m_size;

		c->setHealthMax(c->getHealthMax() + 300);
	}

	void Guild::removeMember(const std::string& c)
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			if (m_members[i]->getName() == c)
			{
				m_members[i]->setHealthMax(m_members[i]->getHealthMax() - 300);
				Character** temp = nullptr;
				if (m_size > 1)
				{
					temp = new Character*[m_size - 1];
					for (size_t j = 0, k = 0; j < m_size; ++j)
					{
						if (j != i)
							temp[k++] = m_members[j];
					}
				}
				delete[] m_members;
				m_members = temp;
				--m_size;
				return;
			}
		}
	}

	Character* Guild::operator[](size_t idx) const
	{
		if (idx < m_size)
			return m_members[idx];
		return nullptr;
	}

	void Guild::showMembers() const
	{
		if (m_name.empty())
		{
			std::cout << "No guild.\n";
		}
		else
		{
			std::cout << "[Guild] " << m_name << "\n";
			for (size_t i = 0; i < m_size; ++i)
			{
				std::cout << "    " << i + 1 << ": " << *m_members[i] << "\n";
			}
		}
	}
}
