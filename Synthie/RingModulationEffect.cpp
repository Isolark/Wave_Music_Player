#include "StdAfx.h"
#define _USE_MATH_DEFINES

#include "RingModulationEffect.h"

#include <cmath>

CRingModulationEffect::CRingModulationEffect(const double &frequency)
{
	m_frequency = frequency;
}

CRingModulationEffect::~CRingModulationEffect(void)
{
}

void CRingModulationEffect::Start()
{
	m_phase = 0.0;
}

void CRingModulationEffect::Process(double * const &frame)
{
	// determine the second waveform
	double sample = sin(m_phase);

	// modify the input
	for (unsigned int i = 0; i < GetChannels(); i++)
	{
		frame[i]*= sample;
	}

	// increment the phase
	m_phase+= 2 * M_PI * m_frequency * GetSamplePeriod();
}

void CRingModulationEffect::Factory::XmlLoad(IXMLDOMNode * xml)
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

		if (name == L"frequency")
		{
			value.ChangeType(VT_R8);
			m_frequency = value.dblVal;
		}
	}
}