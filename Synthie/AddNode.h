#pragma once
#include "AudioNode.h"
#include "Harmonic.h"
#include <vector>
#include <map>


class CAddNode :
	public CAudioNode
{
public:
	CAddNode(void); 
	virtual ~CAddNode(void);

	virtual void Start();
    virtual bool Generate(); 

	void SetVibrato(bool b) { m_vibrato = b; }
    void SetFreq(double f);
	void SetDuration(double d) { m_duration = d; }
    void SetAmplitude(int i, double a) {m_amp = a;}
	
	void SetHarmonics( std::vector<CHarmonic>* har );
	void SetCrossFades( std::map<int,double> cfades );

private:
	std::vector<CHarmonic>* m_harmonics;
	std::map<int,double> m_crossfades;
	int		m_largestHarmonic;
    double	m_freq;
	double	m_duration;
    double	m_phase;
    double	m_amp;
	double	m_time;
	double	m_sineRadians;
	double	m_vibratoRadians;
	bool	m_vibrato;

	short RangeBound( double d);
	double GetPhase( int harmonicNumber );
};

