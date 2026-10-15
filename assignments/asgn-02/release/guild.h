/* Citation and Sources...
-----------------------------------------------------------
Assignment 02
Module: Guild
Filename: Guild.h
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

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include <string>
#include "character.h"

namespace seneca
{
	class Guild
	{
		std::string m_name{};
		Character** m_members{ nullptr };
		size_t m_size{ 0 };

	public:
		Guild() = default;
		Guild(const char* name);
		Guild(const Guild& other);
		Guild& operator=(const Guild& other);
		Guild(Guild&& other) noexcept;
		Guild& operator=(Guild&& other) noexcept;
		~Guild();

		void addMember(Character* c);
		void removeMember(const std::string& c);
		Character* operator[](size_t idx) const;
		void showMembers() const;
	};
}

#endif
