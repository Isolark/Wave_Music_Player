#include "StdAfx.h"
#include "EffectsTable.h"

using namespace std;

CEffectsTable::CEffectsTable(void)
{
}

CEffectsTable::~CEffectsTable(void)
{
	// cleanup the effects
	for (map<std::wstring, CAudioEffect *>::iterator iter = m_effects.begin(); iter != m_effects.end(); iter++)
	{
		delete iter->second;
	}

	// cleanup the sends
	for (vector<CEffectsSend *>::iterator iter = m_sends.begin(); iter != m_sends.end(); iter++)
	{
		delete *iter;
	}
}

const CEffectsSend * const &CEffectsTable::GetEffectsSend(CAudioEffect * const &effect, const double &amount)
{
	// check if send already exists
	for (vector<CEffectsSend *>::iterator iter = m_sends.begin(); iter != m_sends.end(); iter++)
	{
		if ((*iter)->GetEffect() == effect && (*iter)->GetAmount() == amount)
		{
			return *iter;
		}
	}

	// create the new send
	CEffectsSend *send = new CEffectsSend(effect, amount);
	m_sends.push_back(send);
	return m_sends.back();
}

void CEffectsTable::Start(const unsigned int &channels, const double &sampleRate, const double &bpm)
{
	for (map<wstring, CAudioEffect *>::iterator iter = m_effects.begin(); iter != m_effects.end(); iter++)
	{
		iter->second->SetChannels(channels);
		iter->second->SetSampleRate(sampleRate);
		iter->second->SetBPM(bpm);
		iter->second->Start();
	}
}