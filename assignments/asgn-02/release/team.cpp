/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: Team
Filename: Team.cpp
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
#include "team.h"

namespace seneca
{
	Team::Team(const char* name) : m_name{ name ? name : "" } {}

	Team::Team(const Team& other)
	{
		*this = other;
	}

	Team& Team::operator=(const Team& other)
	{
		if (this != &other)
		{
			for (size_t i = 0; i < m_size; ++i)
				delete m_members[i];
			delete[] m_members;
			m_members = nullptr;
			m_size = 0;

			m_name = other.m_name;
			if (other.m_size > 0)
			{
				m_members = new Character*[other.m_size];
				m_size = other.m_size;
				for (size_t i = 0; i < m_size; ++i)
					m_members[i] = other.m_members[i]->clone();
			}
		}
		return *this;
	}

	Team::Team(Team&& other) noexcept
	{
		*this = std::move(other);
	}

	Team& Team::operator=(Team&& other) noexcept
	{
		if (this != &other)
		{
			for (size_t i = 0; i < m_size; ++i)
				delete m_members[i];
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

	Team::~Team()
	{
		for (size_t i = 0; i < m_size; ++i)
			delete m_members[i];
		delete[] m_members;
	}

	void Team::addMember(const Character* c)
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
		temp[m_size] = c->clone();
		delete[] m_members;
		m_members = temp;
		++m_size;
	}

	void Team::removeMember(const std::string& c)
	{
		for (size_t i = 0; i < m_size; ++i)
		{
			if (m_members[i]->getName() == c)
			{
				delete m_members[i];
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

	Character* Team::operator[](size_t idx) const
	{
		if (idx < m_size)
			return m_members[idx];
		return nullptr;
	}

	void Team::showMembers() const
	{
		if (m_name.empty())
		{
			std::cout << "No team.\n";
		}
		else
		{
			std::cout << "[Team] " << m_name << "\n";
			for (size_t i = 0; i < m_size; ++i)
			{
				std::cout << "    " << i + 1 << ": " << *m_members[i] << "\n";
			}
		}
	}
}
