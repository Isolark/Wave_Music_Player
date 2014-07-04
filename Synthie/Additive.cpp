#include "StdAfx.h"
#include "Additive.h"
#include "Notes.h"
#include "ARDecorator.h"
#include "SineWave.h"
#include "EnvelopeDecorator.h"
#include "AddNode.h"


CAdditive::CAdditive(void)
{
	m_vibrato = false;
}


CAdditive::~CAdditive(void)
{
}

void CAdditive::Start()
{
	CAddNode* additiveNode = new CAddNode();
	additiveNode->SetFreq(m_frequency);
	additiveNode->SetSampleRate(GetSampleRate());
	additiveNode->SetVibrato( m_vibrato );
	additiveNode->SetHarmonics( &m_harmonics );
	additiveNode->SetCrossFades( m_crossFades );
	additiveNode->SetDuration(m_duration);
	
	m_addNode = additiveNode;

	m_source = new CEnvelopeDecorator(additiveNode);
	m_source->SetBPM(GetBPM());
	((CEnvelopeDecorator*) m_source)->SetDuration(m_duration);
	m_source->Start();

    m_time = 0;
}

bool CAdditive::Generate()
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

void CAdditive::SetNote( CNote *note )
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
		else if ( name == "a1" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 1 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a2" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 2 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a3" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 3 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a4" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 4 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a5" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 5 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a6" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 6 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a7" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 7 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "a8" )
		{
			value.ChangeType(VT_R8);
            CHarmonic* newHarmonic = new CHarmonic();
			newHarmonic->SetAmplitude( value.dblVal );
			newHarmonic->SetHarmonicNumber( 8 );
			m_harmonics.push_back( *newHarmonic );
		}
		else if ( name == "c1" )
		{
			value.ChangeType(VT_R8);
			m_crossFades[1] = value.dblVal;
		}
		else if ( name == "c2" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[2] = value.dblVal;
		}
		else if ( name == "c3" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[3] = value.dblVal;
		}
		else if ( name == "c4" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[4] = value.dblVal;
		}
		else if ( name == "c5" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[5] = value.dblVal;
		}
		else if ( name == "c6" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[6] = value.dblVal;
		}
		else if ( name == "c7" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[7] = value.dblVal;
		}
		else if ( name == "c8" )
		{
			value.ChangeType(VT_R8);
            m_crossFades[8] = value.dblVal;
		}
		else if ( name == "vibrato" )
		{
			if ( value.bstrVal == (CString) "true")
				m_vibrato = true;
			else
				m_vibrato = false;
		}
    }
}

void CAdditive::AddHarmonic(CHarmonic harmonic)
{
	m_harmonics.push_back(harmonic);
}