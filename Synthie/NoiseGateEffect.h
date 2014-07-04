#pragma once

#include "AudioEffect.h"

#include <vector>

class CNoiseGateEffect :
	public CAudioEffect
{
public:
	CNoiseGateEffect(const double &attack, const double &hold, const double &release, const double &openThreshold, const double &closeThreshold);
	virtual ~CNoiseGateEffect();

	virtual void Start();

	virtual void Process(double * const &frame);

	class Factory :
		public CAudioEffect::Factory
	{
	public:
		Factory() { m_attack = 0.05; m_hold = 0.05; m_release = 0.05; m_openThreshold = 0.05; m_closeThreshold = 0.05; };
		virtual ~Factory() { };

		virtual CAudioEffect *Create() { return new CNoiseGateEffect(m_attack, m_hold, m_release, m_openThreshold, m_closeThreshold); };

		virtual void XmlLoad(IXMLDOMNode * xml);

		const double& GetAttack() const { return m_attack; };
		void SetAttack(const double& attack) { m_attack = attack; };

		const double& GetHold() const { return m_hold; };
		void SetHold(const double& hold) { m_hold = hold; };

		const double& GetRelease() const { return m_release; };
		void SetRelease(const double& release) { m_release = release; };

		const double& GetOpenThreshold() const { return m_openThreshold; };
		void SetOpenThreshold(const double& openThreshold) { m_openThreshold = openThreshold; };

		const double& GetCloseThreshold() const { return m_closeThreshold; };
		void SetCloseThreshold(const double& closeThreshold) { m_closeThreshold = closeThreshold; };

	private:
		double m_attack;
		double m_hold;
		double m_release;
		double m_openThreshold;
		double m_closeThreshold;
	};

private:
	CNoiseGateEffect();
	CNoiseGateEffect(const CNoiseGateEffect &);
	CNoiseGateEffect &operator=(const CNoiseGateEffect &);

	// parameters of the noise gate
	double m_attack; // amount of time to fade-in in seconds
	double m_hold; // amount of time to hold after a sound in seconds
	double m_release; // amount of time to fade-out in seconds
	double m_openThreshold; // the noise level required to open the gate
	double m_closeThreshold; // the noise level required to close the gate

	// state variables
	std::vector<bool> m_open; // whether the gate is open per channel
	std::vector<double> m_gain; // the current gain of the gate per channel
	std::vector<double> m_noise; // the current noise of the input signal per channel
	std::vector<double> m_noiseTime; // how long ago the noise variable was set per channel
};

