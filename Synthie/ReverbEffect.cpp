#include "StdAfx.h"

#include "ReverbEffect.h"

CReverbEffect::CReverbEffect(const double &reverbTime, const double &reverbGain)
{
	m_reverbTime = reverbTime;
	m_reverbGain = reverbGain;
}

CReverbEffect::~CReverbEffect(void)
{
}

void CReverbEffect::Start()
{
	m_queue.clear();
	m_queue.resize(GetChannels() * int(m_reverbTime / GetSamplePeriod() + 1), 0.0);
	m_wrloc = 0;
}

void CReverbEffect::Process(double * const &frame)
{
	unsigned int rdloc = (m_wrloc + GetChannels()) % m_queue.size();
	for (unsigned int i = 0; i < GetChannels(); i++)
	{
		frame[i]+= m_reverbGain * m_queue[rdloc + i];
		m_queue[m_wrloc + i] = frame[i];
	}
	m_wrloc = rdloc;
}

void CReverbEffect::Factory::XmlLoad(IXMLDOMNode * xml)
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

		if (name == L"delay")
		{
			value.ChangeType(VT_R8);
			m_reverbTime = value.dblVal;
		}
		else if (name == L"gain")
		{
			value.ChangeType(VT_R8);
			m_reverbGain = value.dblVal;
		}
	}
}