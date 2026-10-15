#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <utility>
#include "mailServer.h"
#include "plugin.h"

namespace seneca
{
	MailServer::MailServer(const char* name, const char* address)
		: m_userName(name ? name : ""), m_userAddress(address ? address : "")
	{
	}

	MailServer::~MailServer()
	{
		delete[] m_inbox;
	}

	MailServer::MailServer(const MailServer& other)
		: m_userName(other.m_userName),
		  m_userAddress(other.m_userAddress),
		  m_cnt(other.m_cnt)
	{
		if (other.m_cnt > 0 && other.m_inbox)
		{
			m_inbox = new Message[other.m_cnt];
			for (size_t i = 0; i < other.m_cnt; ++i)
			{
				m_inbox[i] = other.m_inbox[i];
			}
		}
		m_plugins[0] = other.m_plugins[0];
		m_plugins[1] = other.m_plugins[1];
	}

	MailServer& MailServer::operator=(const MailServer& other)
	{
		if (this != &other)
		{
			delete[] m_inbox;
			m_inbox = nullptr;
			m_cnt = other.m_cnt;
			m_userName = other.m_userName;
			m_userAddress = other.m_userAddress;
			onNewMailArrived = nullptr;
			m_plugins[0] = other.m_plugins[0];
			m_plugins[1] = other.m_plugins[1];

			if (other.m_cnt > 0 && other.m_inbox)
			{
				m_inbox = new Message[other.m_cnt];
				for (size_t i = 0; i < other.m_cnt; ++i)
				{
					m_inbox[i] = other.m_inbox[i];
				}
			}
		}
		return *this;
	}

	MailServer::MailServer(MailServer&& other) noexcept
		: m_userName(std::move(other.m_userName)),
		  m_userAddress(std::move(other.m_userAddress)),
		  m_inbox(other.m_inbox),
		  m_cnt(other.m_cnt)
	{
		m_plugins[0] = other.m_plugins[0];
		m_plugins[1] = other.m_plugins[1];

		other.m_inbox = nullptr;
		other.m_cnt = 0;
		other.onNewMailArrived = nullptr;
		other.m_plugins[0] = nullptr;
		other.m_plugins[1] = nullptr;
	}

	MailServer& MailServer::operator=(MailServer&& other) noexcept
	{
		if (this != &other)
		{
			delete[] m_inbox;

			m_userName = std::move(other.m_userName);
			m_userAddress = std::move(other.m_userAddress);
			m_inbox = other.m_inbox;
			m_cnt = other.m_cnt;
			onNewMailArrived = nullptr;
			m_plugins[0] = other.m_plugins[0];
			m_plugins[1] = other.m_plugins[1];

			other.m_inbox = nullptr;
			other.m_cnt = 0;
			other.onNewMailArrived = nullptr;
			other.m_plugins[0] = nullptr;
			other.m_plugins[1] = nullptr;
		}
		return *this;
	}

	void MailServer::receiveMail(Message msg)
	{
		if (msg.m_toAddress != m_userAddress)
		{
			throw msg.m_toAddress;
		}

		Message* temp = new Message[m_cnt + 1];
		for (size_t i = 0; i < m_cnt; ++i)
		{
			temp[i] = std::move(m_inbox[i]);
		}
		temp[m_cnt] = std::move(msg);
		delete[] m_inbox;
		m_inbox = temp;
		++m_cnt;

		for (size_t i = 0; i < 2; ++i)
		{
			if (m_plugins[i])
			{
				(*m_plugins[i])(m_inbox[m_cnt - 1]);
			}
		}

		if (onNewMailArrived)
		{
			onNewMailArrived(m_inbox[m_cnt - 1]);
		}
	}

	void MailServer::addPlugin(Plugin* thePlugin)
	{
		for (size_t i = 0; i < 2; ++i)
		{
			if (!m_plugins[i])
			{
				m_plugins[i] = thePlugin;
				break;
			}
		}
	}

	void MailServer::setObserver(void(*observer)(const Message&))
	{
		onNewMailArrived = observer;
	}

	Message& MailServer::operator[](size_t idx)
	{
		if (idx >= m_cnt)
		{
			throw std::out_of_range("Index " + std::to_string(idx) + " is out of bounds.");
		}
		return m_inbox[idx];
	}

	size_t MailServer::getInboxSize() const
	{
		return m_cnt;
	}

	void MailServer::showInbox() const
	{
		for (size_t i = 0; i < m_cnt; ++i)
		{
			size_t pos = m_inbox[i].m_date.find(' ');
			std::string dateOnly = (pos != std::string::npos) ? m_inbox[i].m_date.substr(0, pos) : m_inbox[i].m_date;
			std::cout << std::setw(20) << std::right << m_inbox[i].m_fromName << "  "
			          << std::setw(40) << std::left << m_inbox[i].m_fromAddress << "  "
			          << std::setw(15) << std::left << dateOnly << "  "
			          << m_inbox[i].m_subject << "\n";
		}
		std::cout << std::right;
	}
}
