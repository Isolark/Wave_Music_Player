#pragma once

#include "msxml2.h"
#include "Instrument.h"
#include "WaveInstrumentFactory.h"
#include "SawInstrumentFactory.h"
#include "SquareInstrumentFactory.h"
#include "TriangleInstrumentFactory.h"
#include "WaveTableInstrumentFactory.h"
#include "Note.h"
#include "EffectsTable.h"
#include "EffectsSendTable.h"
#include <list>
#include <vector>

class CSynthesizer
{
public:
	CSynthesizer(void);
	virtual ~CSynthesizer(void);

public:
	//! Number of audio channels
    int GetNumChannels() { return m_channels; }

	//! Sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }

	//! Sample period in seconds (1/samplerate)
    double GetSamplePeriod() { return m_samplePeriod; }
    
	//! Set the number of channels
    void SetNumChannels(int n) { m_channels = n; }

	//! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

	//! Get the time since we started generating audio
	double GetTime() { return m_time; }

	void Start(void);

	bool Generate(double* frame);

	void Clear(void);

	void OpenScore(CString& filename);

	void XmlLoadScore(IXMLDOMNode * xml);

	void XmlLoadInstrument(IXMLDOMNode * xml);

	void XmlLoadEffect(IXMLDOMNode * xml);

	void XmlLoadSend(IXMLDOMNode *xml, CEffectsSendTable *sendTable);

	void XmlLoadNote(IXMLDOMNode *xml, std::wstring & instrument, CEffectsSendTable *sendTable);

private:
    int		m_channels;
    double	m_sampleRate;
    double	m_samplePeriod;
	double m_time;
    std::list<CInstrument *>  m_instruments;
	CWaveInstrumentFactory m_waveinstfactory;
	CSawInstrumentFactory m_sawfactory;
	CSquareInstrumentFactory m_squarefactory;
	CTriangleInstrumentFactory m_trianglefactory;
	CWaveTableInstrumentFactory m_waveTrumpetInstfactory;
	CWaveTableInstrumentFactory m_waveCelloInstfactory;
	CWaveTableInstrumentFactory m_waveTubaInstfactory;
	CWaveTableInstrumentFactory m_waveClarinetInstfactory;
	CWaveTableInstrumentFactory m_waveDrawnWaveInstfactory;
	
	double  m_bpm;                  //!< Beats per minute
    int     m_beatspermeasure;  //!< Beats per measure
    double  m_secperbeat;        //!< Seconds per beat
	std::vector<CNote> m_notes;
	int m_currentNote;          //!< The current note we are playing
    int m_measure;              //!< The current measure
    double m_beat;              //!< The current beat within the measure
	int m_repeat;

	CEffectsTable *m_effectsTable;
};

