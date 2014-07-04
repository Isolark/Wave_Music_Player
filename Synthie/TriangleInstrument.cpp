#include "StdAfx.h"
#include "TriangleInstrument.h"
#include "TriangleWave.h"
#include "ARDecorator.h"
#include "EnvelopeDecorator.h"
#include "Notes.h"

CTriangleInstrument::CTriangleInstrument(void)
{
	m_amplitude = 0.3;
}


CTriangleInstrument::~CTriangleInstrument(void)
{
}

void CTriangleInstrument::Start()
{
	CTriangleWave* Trianglewave = new CTriangleWave();
    Trianglewave->SetSampleRate(GetSampleRate());
	Trianglewave->SetFreq(m_frequency);
	Trianglewave->SetAmplitude(m_amplitude);

	m_source = new CEnvelopeDecorator(Trianglewave);
	m_source->SetBPM(GetBPM());
	((CEnvelopeDecorator*) m_source)->SetDuration(m_duration);
	m_source->Start();

    m_time = 0;
}

void CTriangleInstrument::SetNote(CNote *note)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    // Loop over the list of attributes
    for(int i=0;  i<len;  i++)
    {
        // Get attribute i
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        // Get the name of the attribute
        CComBSTR name;
        attrib->get_nodeName(&name);

        // Get the value of the attribute.  A CComVariant is a variable
        // that can have any type. It loads the attribute value as a
        // string (UNICODE), but we can then change it to an integer 
        // (VT_I4) or double (VT_R8) using the ChangeType function 
        // and then read its integer or double value from a member variable.
        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "duration")
        {
            value.ChangeType(VT_R8);
            SetDuration(value.dblVal);
        }
		else if(name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }

    }

}


bool CTriangleInstrument::Generate()
{
    // Tell the component to generate an audio sample
    m_source->Generate();

    // Read the component's sample and make it our resulting frame.
    m_frame[0] = m_source->Frame(0);
    m_frame[1] = m_source->Frame(1);

    // Update time

    m_time += m_bpm * GetSamplePeriod() / 60.0;
    // We return true until the time reaches the duration.
    return m_time < m_duration;
}