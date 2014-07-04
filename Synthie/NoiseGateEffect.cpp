#include "StdAfx.h"
#include "NoiseGateEffect.h"

#include <cmath>

CNoiseGateEffect::CNoiseGateEffect(const double &attack, const double &hold, const double &release, const double &openThreshold, const double &closeThreshold)
{
	m_attack = attack;
	m_hold = hold;
	m_release = release;
	m_openThreshold = openThreshold;
	m_closeThreshold = closeThreshold;
}

CNoiseGateEffect::~CNoiseGateEffect()
{
}

void CNoiseGateEffect::Start()
{
	m_open.clear();
	m_gain.clear();
	m_noise.clear();
	m_noiseTime.clear();

	m_open.resize(GetChannels(), false);
	m_gain.resize(GetChannels(), 0.0);
	m_noise.resize(GetChannels(), 0.0);
	m_noiseTime.resize(GetChannels(), 0.0);
}

void CNoiseGateEffect::Process(double * const &frame)
{
	for (unsigned int i = 0; i < GetChannels(); i++)
	{
		// advance the time since the noise variable was set
		m_noiseTime[i]+= GetSamplePeriod();

		// if the current noise is greater or the holding period has expired, reset the noise
		if (m_noise[i] < abs(frame[i]) || m_noiseTime[i] < m_hold)
		{
			m_noise[i] = abs(frame[i]);
			m_noiseTime[i] = 0.0;
		}

		// check if we should open or close the gate
		if (m_noise[i] > m_openThreshold)
		{
			m_open[i] = true;
		}
		else if(m_noise[i] < m_closeThreshold)
		{
			m_open[i] = false;
		}

		// modify the gain
		if (m_open[i])
		{
			if (m_attack == 0.0)
			{
				m_gain[i] = 1.0;
			}
			else
			{
				m_gain[i]+= GetSamplePeriod() / m_attack;
				if (m_gain[i] > 1.0)
				{
					m_gain[i] = 1.0;
				}
			}
		}
		else
		{
			if (m_release == 0.0)
			{
				m_gain[i] = 0.0;
			}
			else
			{
				m_gain[i]-= GetSamplePeriod() / m_release;
				if (m_gain[i] < 0.0)
				{
					m_gain[i] = 0.0;
				}
			}
		}

		// modify the frame
		frame[i]*= m_gain[i];
	}
}

void CNoiseGateEffect::Factory::XmlLoad(IXMLDOMNode * xml)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (long i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == L"attack")
		{
			value.ChangeType(VT_R8);
			m_attack = value.dblVal;
		}
		else if (name == L"hold")
		{
			value.ChangeType(VT_R8);
			m_hold = value.dblVal;
		}
		else if (name == L"release")
		{
			value.ChangeType(VT_R8);
			m_release = value.dblVal;
		}
		else if (name == L"openThreshold")
		{
			value.ChangeType(VT_R8);
			m_openThreshold = value.dblVal;
		}
		else if (name == L"closeThreshold")
		{
			value.ChangeType(VT_R8);
			m_closeThreshold = value.dblVal;
		}
	}
}