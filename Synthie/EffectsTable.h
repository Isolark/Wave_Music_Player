#pragma once

#include "AudioEffect.h"
#include "EffectsSend.h"
#include "Iterator.h"

#include <map>
#include <string>
#include <vector>

class CEffectsTable
{
public:
	CEffectsTable();
	virtual ~CEffectsTable();

	void AddEffect(const std::wstring &name, CAudioEffect * const &effect) { if (m_effects.count(name) == 1) delete m_effects[name]; m_effects[name] = effect; };
	CAudioEffect * const &GetEffect(const std::wstring &name) { return m_effects[name]; };
	CIterator<CAudioEffect *> *GetEffects() { return new EffectIterator(this); };

	void Start(const unsigned int &channels, const double &sampleRate, const double &bpm);

	const CEffectsSend * const &GetEffectsSend(CAudioEffect * const &effect, const double &amount);

private:
	class EffectIterator :
		public CIterator<CAudioEffect *>
	{
	public:
		EffectIterator(CEffectsTable * const &parent) { m_parent = parent; First(); };
		virtual ~EffectIterator() { };

		virtual void First() { m_iter = m_parent->m_effects.begin(); };
		virtual void Next() { if (!Done()) m_iter++; };
		virtual bool Done() { return m_iter == m_parent->m_effects.end(); };
		virtual CAudioEffect *Current() { return m_iter->second; };

	private:
		EffectIterator();
		EffectIterator(const EffectIterator &);
		EffectIterator &operator=(const EffectIterator &);

		CEffectsTable *m_parent;
		std::map<std::wstring, CAudioEffect *>::iterator m_iter;
	};

	std::map<std::wstring, CAudioEffect *> m_effects;
	std::vector<CEffectsSend *> m_sends;
};

