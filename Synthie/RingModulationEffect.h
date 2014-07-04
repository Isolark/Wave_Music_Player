#pragma once

#include "AudioEffect.h"

class CRingModulationEffect :
	public CAudioEffect
{
public:
	CRingModulationEffect(const double &frequency);
	virtual ~CRingModulationEffect();

	virtual void Start();
	
	virtual void Process(double * const &frame);

	class Factory :
		public CAudioEffect::Factory
	{
	public:
		Factory() { m_frequency = 1000.0; };
		virtual ~Factory() { };

		virtual CAudioEffect *Create() { return new CRingModulationEffect(m_frequency); };

		virtual void XmlLoad(IXMLDOMNode * xml);

		const double& GetFrequency() const { return m_frequency; };
		void SetFrequency(const double& frequency) { m_frequency = frequency; };

	private:
		double m_frequency;
	};

private:
	CRingModulationEffect();
	CRingModulationEffect(const CRingModulationEffect &);
	CRingModulationEffect &operator=(const CRingModulationEffect &);

	double m_frequency;

	double m_phase;
};

