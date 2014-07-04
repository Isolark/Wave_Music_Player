#include "StdAfx.h"
#include "DRCEffect.h"

CDRCEffect::CDRCEffect(const double &attack, const double &release, const double &threshold, const double &ratio)
{
	m_attack = attack;
	m_release = release;
	m_threshold = threshold;
	m_ratio = ratio;

	m_inputAmplitude = 0.0;
	m_currentRatio = 1.0;
	m_wrloc = 0;
}

CDRCEffect::~CDRCEffect(void)
{
}

void CDRCEffect::Start()
{
	m_inputAmplitude = 0.0;
	m_currentRatio = 1.0;

	m_queue.clear();
	m_queue.resize(3, 0);
	m_wrloc = 0;
}

void CDRCEffect::Process(double * const &frame)
{
	double sample = 0.0;
	for (unsigned i = 0; i < GetChannels(); i++)
	{
		sample+= frame[i];
	}
	sample/= GetChannels();

	m_wrloc = (m_wrloc + 1) % 3;
	m_queue[m_wrloc] = sample;

	if ((m_queue[(m_wrloc + 1) % 3] < m_queue[(m_wrloc + 2) % 3] && m_queue[m_wrloc] < m_queue[(m_wrloc + 2) % 3])
		|| (m_queue[(m_wrloc + 2) % 3] < m_queue[(m_wrloc + 1) % 3] && m_queue[(m_wrloc + 2) % 3] < m_queue[m_wrloc]))
	{
		m_inputAmplitude = abs(m_queue[(m_wrloc + 2) % 3]);
	}

	if (m_threshold < m_inputAmplitude)
	{
		if (m_attack == 0.0)
		{
			m_currentRatio = m_ratio;
		}
		else
		{
			m_currentRatio+= (m_ratio - 1.0) * GetSamplePeriod() / m_attack;
			if (m_currentRatio > m_ratio)
			{
				m_currentRatio = m_ratio;
			}
		}
	}
	else
	{
		if (m_release == 0.0)
		{
			m_currentRatio = 1.0;
		}
		else
		{
			m_currentRatio-= (m_ratio - 1.0) * GetSamplePeriod() / m_release;
			if (m_currentRatio < 1.0)
			{
				m_currentRatio = 1.0;
			}
		}
	}

	double gain = (m_inputAmplitude - m_threshold) / m_currentRatio + m_threshold;
	for (unsigned int i = 0; i < GetChannels(); i++)
	{
		frame[i]*= gain;
	}
}

void CDRCEffect::Factory::XmlLoad(IXMLDOMNode * xml)
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
		else if (name == L"release")
		{
			value.ChangeType(VT_R8);
			m_release = value.dblVal;
		}
		else if (name == L"threshold")
		{
			value.ChangeType(VT_R8);
			m_threshold = value.dblVal;
		}
		else if (name == L"ratio")
		{
			value.ChangeType(VT_R8);
			m_ratio = value.dblVal;
		}
	}
}