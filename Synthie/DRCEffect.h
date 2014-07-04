#pragma once

#include "AudioEffect.h"

#include <vector>

class CDRCEffect :
	public CAudioEffect
{
public:
	CDRCEffect(const double &attack, const double &release, const double &threshold, const double &ratio);
	virtual ~CDRCEffect();

	virtual void Start();

	virtual void Process(double * const &frame);

	class Factory :
		public CAudioEffect::Factory
	{
	public:
		Factory() { m_attack = 1.0; m_release = 1.0; m_threshold = 0.1; m_ratio = 2.0; }
		virtual ~Factory() { }

		virtual CAudioEffect *Create() { return new CDRCEffect(m_attack, m_release, m_threshold, m_ratio); };

		virtual void XmlLoad(IXMLDOMNode * xml);

		const double& GetAttack() const { return m_attack; };
		void SetAttack(const double& attack) { m_attack = attack; };

		const double& GetRelease() const { return m_release; };
		void SetRelease(const double& release) { m_release = release; };

		const double& GetThreshold() const { return m_threshold; };
		void SetThreshold(const double& threshold) { m_threshold = threshold; };

		const double& GetRatio() const { return m_ratio; };
		void SetRation(const double& ratio) { m_ratio = ratio; };

	private:
		double m_attack;
		double m_release;
		double m_threshold;
		double m_ratio;
	};

private:
	CDRCEffect();
	CDRCEffect(const CDRCEffect &);
	CDRCEffect &operator=(const CDRCEffect &);

	// dynamic range compression parameters
	double m_attack;
	double m_release;
	double m_threshold;
	double m_ratio;

	// state variables
	double m_inputAmplitude;
	double m_currentRatio;
	std::vector<double> m_queue;
	unsigned int m_wrloc;
};

