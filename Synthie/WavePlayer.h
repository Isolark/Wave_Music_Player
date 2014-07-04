#pragma once
#include "audionode.h"
#include <vector>

class CWavePlayer : 
	public CAudioNode
{
public:
    CWavePlayer(void);
    ~CWavePlayer(void);

public:
    virtual void Start();
    virtual bool Generate();
	virtual bool Generate(double position);

    void SetSamples(short *s, int n) 
	{
		m_samples = s; 
		m_numsamples = n;
	}

	void SetReadposition(double position){m_DoublePosition = position; m_variableSpeed = true;}

private:
    short *m_samples;
	std::vector<short> m_wave;
    int    m_numsamples;
    int    m_position;
	double m_DoublePosition;
	bool m_variableSpeed;
	
};