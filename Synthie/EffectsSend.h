#pragma once

#include "AudioEffect.h"

class CEffectsSend
{
public:
	virtual ~CEffectsSend() { }

	CAudioEffect * const &GetEffect() const { return m_effect; };
	const double &GetAmount() const { return m_amount; };

	friend class CEffectsTable;

private:
	CEffectsSend();
	CEffectsSend(CAudioEffect * const &effect, const double &amount) { m_effect = effect; m_amount = amount; };

	CAudioEffect *m_effect;
	double m_amount;
};

