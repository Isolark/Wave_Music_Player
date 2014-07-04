#include "StdAfx.h"
#include "Synthesizer.h"
#include "ToneInstrument.h"
#include "SynthDrumInstrument.h"
#include "Instrument.h"
#include "Subtractive.h"
#include "SubNode.h"
#include "Note.h"
#include "xmlhelp.h"
#include "ChorusEffect.h"
#include "DRCEffect.h"
#include "FlangeEffect.h"
#include "NoiseGateEffect.h"
#include "ReverbEffect.h"
#include "RingModulationEffect.h"
#include "SquareInstrument.h"
#include "TriangleInstrument.h"
#include "Additive.h"

#include <algorithm>
#include <cmath>
#include <list>
#include <map>

using namespace std;

CSynthesizer::CSynthesizer(void)
{
    CoInitialize(NULL);

	m_waveinstfactory.LoadFile("drumwaves/snare1C5.wav"); //Soley as a safety measure to prevent crashing.
	m_channels = 2;
	m_sampleRate = 44100.;
	m_samplePeriod = 1 / m_sampleRate;

	m_time = 0;

	m_bpm = 120;
	m_secperbeat = 0.5;
	m_beatspermeasure = 4;

	m_effectsTable = new CEffectsTable();
}


CSynthesizer::~CSynthesizer(void)
{
	delete m_effectsTable;
}

//! Start the synthesizer
void CSynthesizer::Start(void)
{
    m_instruments.clear();
    m_currentNote = 0;
	m_repeat = 0;
    m_measure = 0;
    m_beat = 0;
    m_time = 0;

	m_effectsTable->Start(GetNumChannels(), GetSampleRate(), m_bpm);
}

//! Generate one audio frame
bool CSynthesizer::Generate(double* frame)
{
	//
    // Phase 1: Determine if any notes need to be played.
    //

    while(m_currentNote < (int)m_notes.size())
    {
        // Get a pointer to the current note
        CNote *note = &m_notes[m_currentNote];

        // If the measure is in the future we can't play
        // this note just yet.
        if(note->Measure() > m_measure)
            break;
        
        // If this is the current measure, but the
        // beat has not been reached, we can't play
        // this note.
        if(note->Measure() == m_measure && note->Beat() > m_beat)
            break;

        //
        // Play the note!
        //

        // Create the instrument object
        CInstrument *instrument = NULL;
        if(note->Instrument() == L"ToneInstrument")
        {
            instrument = new CToneInstrument();
        }
		else if(note->Instrument() == L"SawInstrument")
        {
            m_sawfactory.SetNote(note);
            instrument = m_sawfactory.CreateInstrument();
        }
		else if(note->Instrument() == L"SquareInstrument")
        {
            m_squarefactory.SetNote(note);
            instrument = m_squarefactory.CreateInstrument();

        }
		else if(note->Instrument() == L"TriangleInstrument")
        {
            m_trianglefactory.SetNote(note);
            instrument = m_trianglefactory.CreateInstrument();
        }
		else if(note->Instrument() ==L"Trumpet")
		{
			m_waveTrumpetInstfactory.SetNote( note);
			m_waveTrumpetInstfactory.LoadFile("wavetables/trumpet2.wav");
			instrument = m_waveTrumpetInstfactory.CreateInstrument();
		}
		else if(note->Instrument() ==L"Cello")
		{
			m_waveCelloInstfactory.SetNote( note);
			m_waveCelloInstfactory.LoadFile("wavetables/Cello.wav");
			instrument = m_waveCelloInstfactory.CreateInstrument();
		}
		else if(note->Instrument() ==L"Clarinet")
		{
			m_waveClarinetInstfactory.SetNote( note);
			m_waveClarinetInstfactory.LoadFile("wavetables/Clarinet.wav");
			instrument = m_waveClarinetInstfactory.CreateInstrument();
		}
		else if(note->Instrument() ==L"Tuba")
		{
			m_waveTubaInstfactory.SetNote( note);
			m_waveTubaInstfactory.LoadFile("wavetables/Tuba.wav");
			instrument = m_waveTubaInstfactory.CreateInstrument();
		}
		else if(note->Instrument() ==L"DrawnWave")
		{
			m_waveDrawnWaveInstfactory.SetNote( note);
			m_waveDrawnWaveInstfactory.LoadFile("wavetables/bob2.wav");
			instrument = m_waveDrawnWaveInstfactory.CreateInstrument();
		}

		//WaveTable Drum Section
        else if(note->Instrument() == L"SnareDrum")
            instrument = m_waveinstfactory.CreateDrum(L"Snare", note);
		else if(note->Instrument() == L"ShakerDrum")
			instrument = m_waveinstfactory.CreateDrum(L"Shaker", note);
		else if(note->Instrument() == L"TomDrum1")
			instrument = m_waveinstfactory.CreateDrum(L"Tom1", note);
		else if(note->Instrument() == L"TomDrum2")
			instrument = m_waveinstfactory.CreateDrum(L"Tom2", note);
		else if(note->Instrument() == L"CrashDrum")
			instrument = m_waveinstfactory.CreateDrum(L"Crash", note);
		else if(note->Instrument() == L"BassDrum")
			instrument = m_waveinstfactory.CreateDrum(L"Bass", note);
		

		//Synthesized Drum Section
		else if(note->Instrument() == L"SynthDrum")
			instrument = new CSynthDrumInstrument(0);
		else if(note->Instrument() == L"BassSynthDrum")
			instrument = new CSynthDrumInstrument(1);
		
		//Additive Section
		else if (note->Instrument() == L"AdditiveSynth")
			instrument = new CAdditive();
		
        // Configure the instrument object
        if(instrument != NULL)
        {
            instrument->SetSampleRate(GetSampleRate());
			instrument->SetNote(note);
			instrument->SetBPM(m_bpm);
			instrument->SetSendTable(note->GetSendTable());
            instrument->Start();

            m_instruments.push_back(instrument);
        }

        m_currentNote++;
    }

    //
    // Phase 2: Clear all channels to silence 
    //

    for(int c=0;  c<GetNumChannels();  c++)
    {
        frame[c] = 0;
    }

	//
	// Keep track of samples per effect
	//

	// leave NULL effect for dry sounds
	map<CAudioEffect *, double *> effectAudio;
	effectAudio[NULL] = new double[GetNumChannels()];
	for (int c = 0; c < GetNumChannels(); c++)
	{
		effectAudio[NULL][c] = 0.0;
	}
	CIterator<CAudioEffect *> *effectIter = m_effectsTable->GetEffects();
	for (effectIter->First(); !effectIter->Done(); effectIter->Next())
	{
		CAudioEffect *effect = effectIter->Current();
		effectAudio[effect] = new double[GetNumChannels()];
		for (int c = 0; c < GetNumChannels(); c++)
		{
			effectAudio[effect][c] = 0.0;
		}
	}
	delete effectIter;

    //
    // Phase 3: Play an active instruments
    //

    //
    // We have a list of active (playing) instruments.  We iterate over 
    // that list.  For each instrument we call generate, then add the
    // output to our output frame.  If an instrument is done (Generate()
    // returns false), we remove it from the list.
    //

    for(list<CInstrument *>::iterator node = m_instruments.begin();  node!=m_instruments.end();  )
    {
        // Since we may be removing an item from the list, we need to know in 
        // advance, what is after it in the list.  We keep that node as "next"
        list<CInstrument *>::iterator next = node;
        next++;

        // Get a pointer to the allocated instrument
        CInstrument *instrument = *node;

        // Call the generate function
        if(instrument->Generate())
        {
            // If we returned true, we have a valid sample.  Add it 
            // to the frame.
			double dry = 1.0;
			const CEffectsSendTable sendTable = instrument->GetSendTable();
			for (unsigned int e = 0; e < sendTable.GetNumSends(); e++)
			{
				const CEffectsSend *send = sendTable.GetSend(e);
				// add to the pre-existing audio
				for (int c = 0; c < GetNumChannels(); c++)
				{
					effectAudio[send->GetEffect()][c]+= send->GetAmount() * instrument->Frame(c);
				}
				dry-= send->GetAmount();
			}

			// let the dry audio through if there is some left
			if (dry > 0.0)
			{
				for (int c = 0; c < GetNumChannels(); c++)
				{
					effectAudio[NULL][c]+= dry * instrument->Frame(c);
				}
			}
        }
        else
        {
            // If we returned false, the instrument is done.  Remove it
            // from the list and delete it from memory.
            m_instruments.erase(node);
            delete instrument;
        }

        // Move to the next instrument in the list
        node = next;
    }

	//
	// Process any effects and sum the results, also cleanup
	//

	for (map<CAudioEffect *, double *>::iterator iter = effectAudio.begin(); iter != effectAudio.end(); iter++)
	{
		if (iter->first != NULL)
		{
			iter->first->Process(iter->second);
		}

		for (int c = 0; c < GetNumChannels(); c++)
		{
			frame[c]+= iter->second[c];
		}

		delete iter->second;
	}

	//
    // Phase 4: Advance the time and beats
    //

    // Time advances by the sample period
    m_time += GetSamplePeriod();

    // Beat advances by the sample period divided by the 
    // number of seconds per beat.  The inverse of seconds
    // per beat is beats per second.
    m_beat += GetSamplePeriod() / m_secperbeat;

    // When the measure is complete, we move to
    // a new measure.  We might be a fraction into
    // the new measure, so we subtract out rather 
    // than just setting to zero.
    if(m_beat > m_beatspermeasure)
    {
        m_beat -= m_beatspermeasure;
        m_measure++;
    }

    //
    // Phase 5: Determine when we are done
    //

    // We are done when there is nothing to play.  We'll put something more 
    // complex here later.
    return !m_instruments.empty() || m_currentNote < (int)m_notes.size();
}

void CSynthesizer::Clear(void)
{
    m_instruments.clear();
	m_notes.clear();

	delete m_effectsTable;
	m_effectsTable = new CEffectsTable();
}

void CSynthesizer::OpenScore(CString & filename)
{
    Clear();

    //
    // Create an XML document
    //

    CComPtr<IXMLDOMDocument>  pXMLDoc;
    bool succeeded = SUCCEEDED(CoCreateInstance(CLSID_DOMDocument, NULL, CLSCTX_INPROC_SERVER,  
                               IID_IXMLDOMDocument, (void**)&pXMLDoc));
    if(!succeeded)
    {
        AfxMessageBox(L"Failed to create an XML document to use");
	    return;
    }

    // Open the XML document
    VARIANT_BOOL ok;
    succeeded = SUCCEEDED(pXMLDoc->load(CComVariant(filename), &ok));
    if(!succeeded || ok == VARIANT_FALSE)
    {
        AfxMessageBox(L"Failed to open XML score file");
        return;
    }

    //
    // Traverse the XML document in memory!!!!
    // Top level tag is <score>
    //

    CComPtr<IXMLDOMNode> node;
    pXMLDoc->get_firstChild(&node);
    for( ; node != NULL;  NextNode(node))
    {
        // Get the name of the node
        CComBSTR nodeName;
        node->get_nodeName(&nodeName);

		if(nodeName == "score")
        {
            XmlLoadScore(node);
        }
    }

	sort(m_notes.begin(), m_notes.end());
}

void CSynthesizer::XmlLoadScore(IXMLDOMNode * xml)
{
    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
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

        if(name == L"bpm")
        {
            value.ChangeType(VT_R8);
            m_bpm = value.dblVal;
            m_secperbeat = 1 / (m_bpm / 60);
        }
        else if(name == L"beatspermeasure")
        {
            value.ChangeType(VT_I4);
            m_beatspermeasure = value.intVal;
        }

    }

    CComPtr<IXMLDOMNode> node;
    xml->get_firstChild(&node);
    for( ; node != NULL;  NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

	    if (name == L"effect")
		{
			XmlLoadEffect(node);
		}
    }

    xml->get_firstChild(&node);
    for( ; node != NULL;  NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

	    if(name == L"instrument")
        {
            XmlLoadInstrument(node);
        }
    }
}

void CSynthesizer::XmlLoadEffect(IXMLDOMNode * xml)
{
	// Loop over the list of attributes
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	CAudioEffect::Factory *factory = NULL;
	wstring effectName = L"";

	for (long i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == L"effect")
		{
			value.ChangeType(VT_BSTR);
			if (wstring(value.bstrVal) == L"chorus")
			{
				factory = new CChorusEffect::Factory();
			}
			else if (wstring(value.bstrVal) == L"drc")
			{
				factory = new CDRCEffect::Factory();
			}
			else if (wstring(value.bstrVal) == L"flange")
			{
				factory = new CFlangeEffect::Factory();
			}
			else if (wstring(value.bstrVal) == L"gate")
			{
				factory = new CNoiseGateEffect::Factory();
			}
			else if (wstring(value.bstrVal) == L"reverb")
			{
				factory = new CReverbEffect::Factory();
			}
			else if (wstring(value.bstrVal) == L"ring")
			{
				factory = new CRingModulationEffect::Factory();
			}
		}
		else if (name == L"name")
		{
			effectName = value.bstrVal;
		}
	}

	if (factory != NULL)
	{
		factory->XmlLoad(xml);
		CAudioEffect *effect = factory->Create();
		m_effectsTable->AddEffect(effectName, effect);
		delete factory;
		factory = NULL;
	}
}

void CSynthesizer::XmlLoadInstrument(IXMLDOMNode * xml)
{
    wstring instrument = L"";

    // Get a list of all attribute nodes and the
    // length of that list
    CComPtr<IXMLDOMNamedNodeMap> attributes;
    xml->get_attributes(&attributes);
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

        // Get the value of the attribute.  
        CComVariant value;
        attrib->get_nodeValue(&value);

        if(name == "instrument")
        {
            instrument = value.bstrVal;
        }
		else if(name == "repeat")
		{
			value.ChangeType(VT_I4);
            m_repeat = value.intVal;
		}
    }

	// find any effects sends for the instrument
	CEffectsSendTable sendTable;
    CComPtr<IXMLDOMNode> node;
    xml->get_firstChild(&node);
    for( ; node != NULL;  NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

        if(name == L"send")
        {
           XmlLoadSend(node, &sendTable);
        }
    }

    xml->get_firstChild(&node);
    for( ; node != NULL;  NextNode(node))
    {
        // Get the name of the node
        CComBSTR name;
        node->get_nodeName(&name);

        if(name == L"note")
        {
           XmlLoadNote(node, instrument, &sendTable);
        }
    }

	m_repeat = 0; //Clear repeating instruments when done looking through its notes.
}

void CSynthesizer::XmlLoadNote(IXMLDOMNode * xml, std::wstring & instrument, CEffectsSendTable *sendTable)
{
    m_notes.push_back(CNote());
    m_notes.back().XmlLoad(xml, instrument, sendTable);

	for(int i = 0; i < m_repeat; i++)
	{
		m_notes.push_back(CNote(i+1));
		m_notes.back().XmlLoad(xml, instrument, sendTable);
	}
}

void CSynthesizer::XmlLoadSend(IXMLDOMNode *xml, CEffectsSendTable *sendTable)
{
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	xml->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	CAudioEffect *effect = NULL;
	double amount = 0.0;

	for (long i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "effect")
		{
			value.ChangeType(VT_BSTR);
			effect = m_effectsTable->GetEffect(value.bstrVal);
		}
		else if (name == "amount")
		{
			value.ChangeType(VT_R8);
			amount = value.dblVal;
		}
	}

	if (effect != NULL && amount != 0.0)
	{
		const CEffectsSend *send = m_effectsTable->GetEffectsSend(effect, amount);
		sendTable->AddSend(send);
	}
}