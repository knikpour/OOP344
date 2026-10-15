#include <iostream>
#include <fstream>
#include "spamFilterPlugin.h"
#include "message.h"

namespace seneca
{
	SpamFilterPlugin::SpamFilterPlugin(const char* filename)
	{
		if (filename)
		{
			std::ifstream file(filename);
			if (!file)
			{
				throw std::string("Cannot open file: ") + filename;
			}
			std::string line;
			while (std::getline(file, line) && m_keywordCount < 100)
			{
				if (!line.empty() && line.back() == '\r')
				{
					line.pop_back();
				}
				if (!line.empty())
				{
					m_spamKeywords[m_keywordCount++] = line;
				}
			}
		}
	}

	void SpamFilterPlugin::operator()(Message& msg)
	{
		for (size_t i = 0; i < m_keywordCount; ++i)
		{
			if (msg.m_subject.find(m_spamKeywords[i]) != std::string::npos)
			{
				msg.m_subject = "[SPAM] " + msg.m_subject;
				++m_spamCount;
				break;
			}
		}
	}

	void SpamFilterPlugin::showStats() const
	{
		std::cout << "[Spam Filter Plugin] Identified " << m_spamCount << " spam messages.\n";
	}
}
