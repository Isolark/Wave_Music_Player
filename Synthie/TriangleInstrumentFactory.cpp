#include "StdAfx.h"
#include "TriangleInstrumentFactory.h"
#include "Notes.h"

CTriangleInstrumentFactory::CTriangleInstrumentFactory(void)
{
}


CTriangleInstrumentFactory::~CTriangleInstrumentFactory(void)
{
}

CTriangleInstrument *CTriangleInstrumentFactory::CreateInstrument()
{
    CTriangleInstrument *instrument = new CTriangleInstrument();

    return instrument;
}

void CTriangleInstrumentFactory::SetNote(CNote *note)
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

        }
		else if(name == "note")
        {
            SetFreq(NoteToFrequency(value.bstrVal));
        }

    }

}