/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: Team
Filename: Team.h
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

#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include <string>
#include "character.h"

namespace seneca
{
	class Team
	{
		std::string m_name{};
		Character** m_members{ nullptr };
		size_t m_size{ 0 };

	public:
		Team() = default;
		Team(const char* name);
		Team(const Team& other);
		Team& operator=(const Team& other);
		Team(Team&& other) noexcept;
		Team& operator=(Team&& other) noexcept;
		~Team();

		void addMember(const Character* c);
		void removeMember(const std::string& c);
		Character* operator[](size_t idx) const;
		void showMembers() const;
	};
}

#endif
