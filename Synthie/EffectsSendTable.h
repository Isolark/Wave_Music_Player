#pragma once

#include "EffectsSend.h"

#include <vector>

class CEffectsSendTable
{
public:
	CEffectsSendTable() { };
	virtual ~CEffectsSendTable() { };

	void AddSend(const CEffectsSend * const &send) { m_sends.push_back(send); };
	const CEffectsSend * const &GetSend(const unsigned int &index) const { return m_sends[index]; };
	const unsigned int GetNumSends() const { return m_sends.size(); };

private:
	std::vector<const CEffectsSend *> m_sends;
};

