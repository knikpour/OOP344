#ifndef SENECA_SPAMFILTERPLUGIN_H
#define SENECA_SPAMFILTERPLUGIN_H

#include <string>
#include "plugin.h"

namespace seneca
{
	class SpamFilterPlugin : public Plugin
	{
		std::string m_spamKeywords[100]{};
		size_t m_keywordCount{0};
		size_t m_spamCount{0};

	public:
		SpamFilterPlugin(const char* filename);
		void operator()(Message& msg) override;
		void showStats() const override;
	};
}

#endif
