#include "StdAfx.h"
#include "SynthDrumInstrument.h"
#include "SineWave.h"
#include "Notes.h"
#include "ARDecorator.h"

CSynthDrumInstrument::CSynthDrumInstrument(int type)
{
	m_frequency = 440;
	m_amplitude = 0.02;
    m_duration = 0.1;
	m_type = type;
	m_attack = m_release = 0.05;
}

CSynthDrumInstrument::~CSynthDrumInstrument(void)
{
	delete m_source;
}

void CSynthDrumInstrument::Start()
{
	drumwave = new CDrumWaveSynth();
	drumwave->SetFreq(m_frequency);
	drumwave->SetAmplitude(m_amplitude);
	drumwave->SetSampleRate(GetSampleRate());
	
	m_source = new CARDecorator(drumwave);
	m_source->SetBPM(GetBPM());
	m_source->SetAttack(m_attack);
	m_source->SetRelease(m_release);
	((CARDecorator*) m_source)->SetDuration(m_duration);
	m_source->Start();

    m_time = 0;
}

bool CSynthDrumInstrument::Generate()
{
	if(m_type == 0)
		drumwave->SetFreq((m_frequency / 2) + (m_frequency / 2) * pow((1 - (m_time / m_duration)),3));

	else if(m_type == 1)
		drumwave->SetFreq((m_frequency / 4) + (m_frequency * 3 / 4) * pow((1 - (m_time / m_duration)),3));

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

void CSynthDrumInstrument::SetNote(CNote *note)
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
		else if(name == "measure")
		{
            value.ChangeType(VT_R8);
            if(value.dblVal == 1.0)
			{
				m_attack = 0.04;
				m_release = 0.06;
			}
			else if((value.dblVal - int(value.dblVal)) >= 0)
			{
				m_attack = 0.04;
				m_release = 0.04;
			}
		}

    }

}