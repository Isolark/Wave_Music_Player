#pragma once
#include "instrument.h"
#include "ARDecorator.h"
#include "WavePlayer.h"

class CWaveInstrument :
    public CInstrument
{
public:
    CWaveInstrument(void);
    ~CWaveInstrument(void);

    virtual void Start();
    virtual bool Generate();
    virtual void SetNote(CNote *note);

    CWavePlayer *GetPlayer() {return m_wavePlayer;}

	void SetDuration(double duration) {m_duration = duration;}

private:
    CWavePlayer* m_wavePlayer;
	CARDecorator* m_source;

	double m_attack;
	double m_release;

	double m_duration;
	double m_amp; //Will be set to lower number to compensate for generally louder drum sounds...
	double m_freq;
	double it_counter;


};