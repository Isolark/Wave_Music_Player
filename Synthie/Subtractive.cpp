#include "StdAfx.h"
#include "Subtractive.h"
#include "Notes.h"
#include "SineWave.h"




CSubtractive::~CSubtractive(void)
{
}

void CSubtractive::Start()
{
    m_sub.SetSampleRate(GetSampleRate());
    m_sub.Start();
 //   m_time = 0;
}


void CSubtractive::SetNote(CNote *note)
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


bool CSubtractive::Generate()
{
	switch(style){
		case 1:
			m_sub.GenerateSawtooth();
		case 2:
			m_sub.GenerateSquare();
		case 3:
			m_sub.GenerateTriangle();
	}
	return false;
}


