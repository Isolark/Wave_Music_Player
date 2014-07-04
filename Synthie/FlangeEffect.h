#pragma once

#include "AudioEffect.h"

#include <vector>

class CFlangeEffect :
	public CAudioEffect
{
public:
	CFlangeEffect(const double &delayMean, const double &delayAmplitude, const double &delayFrequency);
	virtual ~CFlangeEffect();

	virtual void Start();

	virtual void Process(double * const &frame);

	class Factory :
		public CAudioEffect::Factory
	{
	public:
		Factory() { m_delayMean = 0.006; m_delayAmplitude = 0.004; m_delayFrequency = 0.25; };
		virtual ~Factory() { };

		virtual CAudioEffect *Create() { return new CFlangeEffect(m_delayMean, m_delayAmplitude, m_delayFrequency); };

		virtual void XmlLoad(IXMLDOMNode * xml);

		const double& GetDelayMean() const { return m_delayMean; };
		void SetDelayMean(const double& delayMean) { m_delayMean = delayMean; };

		const double& GetDelayAmplitude() const { return m_delayAmplitude; };
		void SetDelayAmplitude(const double& delayAmplitude) { m_delayAmplitude = delayAmplitude; };

		const double& GetDelayFrequency() const { return m_delayFrequency; };
		void SetDelayFrequency(const double& delayFrequency) { m_delayFrequency = delayFrequency; };

	private:
		double m_delayMean;
		double m_delayAmplitude;
		double m_delayFrequency;
	};

private:
	CFlangeEffect();
	CFlangeEffect(const CFlangeEffect &);
	CFlangeEffect &operator=(const CFlangeEffect &);

	double m_delayMean;
	double m_delayAmplitude;
	double m_delayFrequency;

	double m_phase;
	std::vector<double> m_queue;
	unsigned int m_wrloc;
};

