#pragma once
#include "Instrument.h"
#include "WavePlayer.h"


class CWavetableinstrument  :
	public CInstrument
{
public:
	CWavetableinstrument(void);
	virtual ~CWavetableinstrument(void);

	 virtual void Start();
     virtual bool Generate();
     virtual void SetNote(CNote *note);

	 void SetFreq(double f) {m_frequency = f;}
	 void SetGFreq(double f) {m_gFrequency = f;}
     void SetAmplitude(double a) {m_amplitude = a;}
     void SetDuration(double d) {m_duration = d;}
	 int GetSteps(){return m_steps;};
	 void SetSteps();

    CWavePlayer *GetPlayer() {return m_wavePlayer;}

private:
    CWavePlayer * m_wavePlayer;
	CAudioNode* m_source;

	double m_position; //!< sample to read

	double m_frequency;
	double m_gFrequency;
	double m_amplitude;
    double m_duration;
    double m_time;
	double m_nextStepTime;
	int m_steps;
};

