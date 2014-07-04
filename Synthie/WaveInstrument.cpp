#include "StdAfx.h"
#include "WaveInstrument.h"
#include "Notes.h"

CWaveInstrument::CWaveInstrument(void)
{
	m_wavePlayer = new CWavePlayer();
	m_duration = 1.0;
	m_attack = m_release = 0.05;
}

CWaveInstrument::~CWaveInstrument(void)
{
	delete m_source;
}


void CWaveInstrument::Start()
{
    m_wavePlayer->SetSampleRate(GetSampleRate());

	m_source = new CARDecorator(m_wavePlayer);
	m_source->SetBPM(GetBPM());
	m_source->SetAttack(m_attack);
	m_source->SetRelease(m_release);
	((CARDecorator*) m_source)->SetDuration(m_duration);
	m_source->Start();
}


void CWaveInstrument::SetNote(CNote *note)
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
            m_freq = NoteToFrequency(L"C5") - NoteToFrequency(value.bstrVal);
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


bool CWaveInstrument::Generate()
{
    bool valid = m_source->Generate();

    m_frame[0] = m_source->Frame(0);
    m_frame[1] = m_frame[0];

    return valid;
}