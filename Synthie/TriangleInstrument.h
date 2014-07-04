#pragma once
#include "instrument.h"
class CTriangleInstrument :
	public CInstrument
{
public:
	CTriangleInstrument(void);
	~CTriangleInstrument(void);

	virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);

    void SetFreq(double f) {m_frequency = f;}
    void SetAmplitude(double a) {m_amplitude = a;}
    void SetDuration(double d) {m_duration = d;}

private:
	CAudioNode* m_source;
	double m_frequency;
	double m_amplitude;
    double m_duration;
    double m_time;
};

