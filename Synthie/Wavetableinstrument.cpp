#include "StdAfx.h"
#include "Wavetableinstrument.h"
#include "Instrument.h"
#include "Notes.h"
#include "ARDecorator.h"
#include "EnvelopeDecorator.h"


CWavetableinstrument::CWavetableinstrument(void)
{

	m_position = 0;

	m_frequency = 440;
	m_gFrequency = 440;
	m_amplitude = 0.1;
    m_duration = 0.5;
	m_steps = 0;

	m_wavePlayer = new CWavePlayer();
}


CWavetableinstrument::~CWavetableinstrument(void)
{
	delete m_source;
}


void CWavetableinstrument::Start()
{
    //m_wavePlayer.SetSampleRate(GetSampleRate());
    //m_wavePlayer.Start();

	
	m_wavePlayer->SetSampleRate(GetSampleRate());

	//m_source = new CARDecorator(m_wavePlayer);
	m_source = new CEnvelopeDecorator(m_wavePlayer);
	m_source->SetBPM(GetBPM());

	//((CARDecorator*) m_source)->SetDuration(m_duration);
	((CEnvelopeDecorator*) m_source)->SetDuration(m_duration);
	m_source->Start();
	



	 m_time = 0;
	 m_nextStepTime = 0.0;
	
}





bool CWavetableinstrument::Generate()
{
	//m_wavePlayer.SetReadposition(m_position);
    //bool valid = m_wavePlayer.Generate();
	m_wavePlayer->SetReadposition(m_position);
	m_source->Generate();
	
	//double gFreq = (m_gFrequency-m_frequency)/m_duration *m_time;
	
	//do glissandro if neccesary
	if(m_gFrequency != m_frequency)
	{
		int halftones =  GetSteps();
		double steptime = m_duration/halftones;

		if(m_nextStepTime <= m_time)
		{
			m_nextStepTime += steptime;
			if(m_gFrequency >= m_frequency)
			{
				m_frequency *= 1.05946;
			}
			else
			{
				m_frequency /= 1.05946;
			}
		}
	}

	//m_position +=  (m_frequency + gFreq)/261.626;
	m_position +=  (m_frequency)/261.626;

   // m_frame[0] = m_wavePlayer.Frame(0);
	//m_frame[1] = m_frame[0];
     m_frame[0] = m_source->Frame(0);
	  m_frame[1] = m_source->Frame(1);
	

	 // Update time
    m_time += m_bpm * GetSamplePeriod() / 60.0;

    // We return true until the time reaches the duration.
    return m_time < m_duration;

}

void CWavetableinstrument::SetSteps()
{
	int steps = 0;
	double gfreq = m_gFrequency;

	if(gfreq >m_frequency)
	{
		while(gfreq >m_frequency)
		{
			gfreq /= 1.05946;
			steps++;
		}
		steps--;
	}
	else if(gfreq <m_frequency)
	{
		while(gfreq <m_frequency)
		{
			gfreq *= 1.05946;
			steps++;
		}
		steps--;
	}
	
	m_steps =  steps;
	
}

void CWavetableinstrument::SetNote(CNote *note)
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
			SetGFreq(NoteToFrequency(value.bstrVal)); // set glissandro frequency to same as note 
        }
		else if(name == "Gnote")
        {
            SetGFreq(NoteToFrequency(value.bstrVal));// if there is glisandro note set the frequency
			SetSteps();
        }

    }

}
