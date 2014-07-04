#pragma once
#include "audionode.h"
#include <vector>
class CSubtractivePlayer :
	public CAudioNode
{
public:
	CSubtractivePlayer(void);
	virtual ~CSubtractivePlayer(void);

public:
	virtual void Start();
    virtual bool Generate();

    void SetSamples(short *s, int n) {m_samples = s; m_numsamples = n;}
private:
    short* m_samples;
    int    m_numsamples;
	int	   m_position;
};

