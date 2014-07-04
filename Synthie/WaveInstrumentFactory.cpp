#include "StdAfx.h"
#include "WaveInstrumentFactory.h"
#include <cmath>

CWaveInstrumentFactory::CWaveInstrumentFactory(void)
{

}

CWaveInstrumentFactory::~CWaveInstrumentFactory(void)
{
}


CWaveInstrument *CWaveInstrumentFactory::CreateDrum(std::wstring drumtype, CNote *note)
{
	m_type = drumtype;

	SetDrumNote(note);

    CWaveInstrument *instrument = new CWaveInstrument();
    instrument->GetPlayer()->SetSamples(&m_wave[0], (int)m_wave.size());
	m_wave.clear();
	instrument->SetNote(note);

    return instrument;
}

void CWaveInstrumentFactory::SetDrumPitch(const std::wstring notefreq)
{
	if(m_type == L"Snare")
	{
		if(notefreq == L"F5")
			LoadFile("drumwaves/snare1F5.wav");
		else if(notefreq == L"E5")
			LoadFile("drumwaves/snare1E5.wav");
		else if(notefreq == L"D5")
			LoadFile("drumwaves/snare1D5.wav");
		else if(notefreq == L"C5")
			LoadFile("drumwaves/snare1C5.wav");
		else if(notefreq == L"B4")
			LoadFile("drumwaves/snare1B4.wav");
		else if(notefreq == L"A4")
			LoadFile("drumwaves/snare1A4.wav");
		else
			LoadFile("drumwaves/snare1G4.wav");
	}
	else if(m_type == L"Tom1")
	{
		if(notefreq == L"F5")
			LoadFile("drumwaves/tom1F5.wav");
		else if(notefreq == L"E5")
			LoadFile("drumwaves/tom1E5.wav");
		else if(notefreq == L"D5")
			LoadFile("drumwaves/tom1D5.wav");
		else if(notefreq == L"C5")
			LoadFile("drumwaves/tom1C5.wav");
		else if(notefreq == L"B4")
			LoadFile("drumwaves/tom1B4.wav");
		else if(notefreq == L"A4")
			LoadFile("drumwaves/tom1A4.wav");
		else
			LoadFile("drumwaves/tom1G4.wav");
	}
	else if(m_type == L"Tom2")
	{
		if(notefreq == L"F5")
			LoadFile("drumwaves/tom2F5.wav");
		else if(notefreq == L"E5")
			LoadFile("drumwaves/tom2E5.wav");
		else if(notefreq == L"D5")
			LoadFile("drumwaves/tom2D5.wav");
		else if(notefreq == L"C5")
			LoadFile("drumwaves/tom2C5.wav");
		else if(notefreq == L"B4")
			LoadFile("drumwaves/tom2B4.wav");
		else if(notefreq == L"A4")
			LoadFile("drumwaves/tom2A4.wav");
		else
			LoadFile("drumwaves/tom2G4.wav");
	}
	else if(m_type == L"Shaker")
	{
		if(notefreq == L"F5")
			LoadFile("drumwaves/shaker1F5.wav");
		else if(notefreq == L"E5")
			LoadFile("drumwaves/shaker1E5.wav");
		else if(notefreq == L"D5")
			LoadFile("drumwaves/shaker1D5.wav");
		else if(notefreq == L"C5")
			LoadFile("drumwaves/shaker1C5.wav");
		else if(notefreq == L"B4")
			LoadFile("drumwaves/shaker1B4.wav");
		else if(notefreq == L"A4")
			LoadFile("drumwaves/shaker1A4.wav");
		else
			LoadFile("drumwaves/shaker1G4.wav");
	}
	else if(m_type == L"Crash")
	{
		if(notefreq == L"F5")
			LoadFile("drumwaves/crash1F5.wav");
		else if(notefreq == L"E5")
			LoadFile("drumwaves/crash1E5.wav");
		else if(notefreq == L"D5")
			LoadFile("drumwaves/crash1D5.wav");
		else if(notefreq == L"C5")
			LoadFile("drumwaves/crash1C5.wav");
		else if(notefreq == L"B4")
			LoadFile("drumwaves/crash1B4.wav");
		else if(notefreq == L"A4")
			LoadFile("drumwaves/crash1A4.wav");
		else
			LoadFile("drumwaves/crash1G4.wav");
	}
	else
		LoadFile("drumwaves/bass1C5.wav");
}
void CWaveInstrumentFactory::SetNote(CNote *note)
{
}

void CWaveInstrumentFactory::SetDrumNote(CNote *note)
{
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    note->Node()->get_attributes(&attributes);
    long len;
    attributes->get_length(&len);

    for(int i=0;  i<len;  i++)
    {
        CComPtr<IXMLDOMNode> attrib;
        attributes->get_item(i, &attrib);

        CComBSTR name;
        attrib->get_nodeName(&name);

        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "duration")
        {
            //value.ChangeType(VT_R8);
            //SetDuration(value.dblVal);
        }
		else if(name == "note")
        {
            SetDrumPitch(value.bstrVal);
        }
    }
}

bool CWaveInstrumentFactory::LoadFile(const char *filename)
{
    m_wave.clear();

    CDirSoundSource m_file;
    if(!m_file.Open(filename))
    {
        CString msg = L"Unable to open audio file: ";
        msg += filename;
        AfxMessageBox(msg);
        return false;
    }

    for(int i=0;  i<m_file.NumSampleFrames();  i++)
    {
        short frame[2];
        m_file.ReadFrame(frame);

        m_wave.push_back(frame[0]);
    }

    m_file.Close();
    return true;
}