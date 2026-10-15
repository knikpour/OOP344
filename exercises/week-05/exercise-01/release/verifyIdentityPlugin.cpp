#include <iostream>
#include <fstream>
#include "verifyIdentityPlugin.h"
#include "message.h"

namespace seneca
{
	VerifyIdentityPlugin::VerifyIdentityPlugin(const char* filename)
	{
		if (filename)
		{
			std::ifstream file(filename);
			if (!file)
			{
				throw std::string("Cannot open file: ") + filename;
			}
			std::string line;
			while (std::getline(file, line) && m_trustedCount < 100)
			{
				if (!line.empty() && line.back() == '\r')
				{
					line.pop_back();
				}
				if (!line.empty())
				{
					m_trustedEmails[m_trustedCount++] = line;
				}
			}
		}
	}

	void VerifyIdentityPlugin::operator()(Message& msg)
	{
		for (size_t i = 0; i < m_trustedCount; ++i)
		{
			if (msg.m_fromAddress == m_trustedEmails[i])
			{
				msg.m_subject = "[TRUSTED] " + msg.m_subject;
				break;
			}
		}
	}

	void VerifyIdentityPlugin::showStats() const
	{
		std::cout << "[Identity Checker Plugin] can validate identity for ";
		for (size_t i = 0; i < m_trustedCount; ++i)
		{
			std::cout << m_trustedEmails[i] << (i + 1 < m_trustedCount ? ", " : "");
		}
		std::cout << "\n";
	}
}
