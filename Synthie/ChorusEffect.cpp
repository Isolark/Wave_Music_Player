#include "StdAfx.h"
#define _USE_MATH_DEFINES

#include "ChorusEffect.h"

#include <cmath>

CChorusEffect::CChorusEffect(const double &delayMean, const double &delayAmplitude, const double &delayFrequency)
{
	m_delayMean = delayMean;
	m_delayAmplitude = delayAmplitude;
	m_delayFrequency = delayFrequency;
}

CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Start()
{
	m_phase = 0.0;
	m_queue.clear();
	m_queue.resize(GetChannels() * int((m_delayMean + m_delayAmplitude) / GetSamplePeriod() + 1), 0.0);
	m_wrloc = 0;
}

void CChorusEffect::Process(double * const &frame)
{
	// write the input into the queue
	m_wrloc = (m_wrloc + GetChannels()) % m_queue.size();
	for (unsigned int i = 0; i < GetChannels(); i++)
	{
		m_queue[m_wrloc + i] = frame[i];
	}

	// determine the current delay
	double delay = m_delayMean + m_delayAmplitude * sin(m_phase);

	// determine the rdloc
	unsigned int rdloc = (m_wrloc + m_queue.size() - GetChannels() * int(delay / GetSamplePeriod())) % m_queue.size();

	// read the output from the queue
	for (unsigned int i = 0; i < GetChannels(); i++)
	{
		frame[i]+= m_queue[rdloc + i] = frame[i];
	}

	// increment the phase
	m_phase = fmod(m_phase + 2 * M_PI * m_delayFrequency * GetSamplePeriod(), 2 * M_PI);
}

void CChorusEffect::Factory::XmlLoad(IXMLDOMNode * xml)
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

		if (name == L"mean")
		{
			value.ChangeType(VT_R8);
			m_delayMean = value.dblVal;
		}
		else if (name == L"amplitude")
		{
			value.ChangeType(VT_R8);
			m_delayAmplitude = value.dblVal;
		}
		else if (name == L"frequency")
		{
			value.ChangeType(VT_R8);
			m_delayFrequency = value.dblVal;
		}
	}
}