#pragma once
#include "instrument.h"
#include "DrumWaveSynth.h"
#include "ARDecorator.h"

class CSynthDrumInstrument :
	public CInstrument
{
public:
	CSynthDrumInstrument(int type);
	virtual ~CSynthDrumInstrument(void);

    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_frequency = f;}
    void SetAmplitude(double a) {m_amplitude = a;}
    void SetDuration(double d) {m_duration = d;}

	void SetNote(CNote *note);

private:
	CARDecorator* m_source;
	CDrumWaveSynth* drumwave;
	double m_frequency;
	double m_amplitude;
    double m_duration;
    double m_time;

	double m_attack,m_release;

	//0: High pitched synth.
	//1: Bass synth (utilizes different sweep rate).

	int m_type;
};