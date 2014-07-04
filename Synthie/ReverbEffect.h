#pragma once

#include "AudioEffect.h"

#include <vector>

class CReverbEffect :
	public CAudioEffect
{
public:
	CReverbEffect(const double &reverbTime, const double &reverbGain);
	virtual ~CReverbEffect();

	virtual void Start();

	virtual void Process(double * const &frame);

	class Factory :
		public CAudioEffect::Factory
	{
	public:
		Factory() { m_reverbTime = 0.01; m_reverbGain = 0.9; };
		virtual ~Factory() { }

		virtual CAudioEffect *Create() { return new CReverbEffect(m_reverbTime, m_reverbGain); };

		virtual void XmlLoad(IXMLDOMNode * xml);

		const double& GetReverbTime() const { return m_reverbTime; };
		void SetReverbTime(const double& reverbTime) { m_reverbTime = reverbTime; };

		const double& GetReverbGain() const { return m_reverbGain; };
		void SetReverbGain(const double& reverbGain) { m_reverbGain = reverbGain; };

	private:
		double m_reverbTime;
		double m_reverbGain;
	};

private:
	CReverbEffect();
	CReverbEffect(const CReverbEffect &);
	CReverbEffect &operator=(const CReverbEffect &);

	double m_reverbTime;
	double m_reverbGain;

	std::vector<double> m_queue;
	unsigned int m_wrloc;
};

