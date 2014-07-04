#pragma once
#include "Instrument.h"

class CToneInstrument :
	public CInstrument
{
public:
	CToneInstrument(void);
	virtual ~CToneInstrument(void);

    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_frequency = f;}
    void SetAmplitude(double a) {m_amplitude = a;}
    void SetDuration(double d) {m_duration = d;}

	void SetNote(CNote *note);

private:
	CAudioNode* m_source;
	double m_frequency;
	double m_amplitude;
    double m_duration;
    double m_time;
};

