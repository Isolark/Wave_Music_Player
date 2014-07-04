#pragma once
#include "audionode.h"
class CSubNode :
	public CAudioNode
{
public:
	CSubNode(void);
	virtual ~CSubNode(void);

public:
    virtual void Start();
    virtual bool Generate();

    void SetFreq(double f) {m_freq = f;}
    void SetAmplitude(int i, double a) {m_amp[i] = a;}

private:
    double m_freq;
    double m_phase;
    double m_amp[4];

//Generation Functions
public:
	bool GenerateSawtooth();
	bool GenerateSquare();
	bool GenerateTriangle();
};

