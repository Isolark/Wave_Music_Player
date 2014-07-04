#pragma once
#include "Instrument.h"
#include "WavePlayer.h"
#include "SubtractivePlayer.h"
class CSawInstrument :
	public CInstrument
{
public:
	CSawInstrument(void);
	~CSawInstrument(void);

	virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);

    void SetFreq(double f) {m_frequency = f;}
    void SetAmplitude(double a) {m_amplitude = a;}
    void SetDuration(double d) {m_duration = d;}

	void SetSamples(std::vector<short>);

    CSubtractivePlayer *GetPlayer() {return &m_subPlayer;}

private:
    CSubtractivePlayer m_subPlayer;
	CAudioNode* m_source;
	double m_frequency;
	double m_amplitude;
    double m_duration;
    double m_time;
};

