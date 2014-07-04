#include "StdAfx.h"
#include "SquareWave.h"

#include <cmath>

CSquareWave::CSquareWave(void)
{
	m_phase = 0;
	m_amp = 0.4;
	m_freq = 440;
}


CSquareWave::~CSquareWave(void)
{
}

void CSquareWave::Start()
{
    m_phase = 0;
}

bool CSquareWave::Generate()
{
	double s =0.;
	for(int h=3;(h* m_freq)<(m_sampleRate/2);h+=2){
		s += (m_amp/h * sin(2 * PI * h * m_phase));
	}
    m_frame[0] = s;
    m_frame[1] = m_frame[0];

    m_phase += m_freq * GetSamplePeriod();

    return true;
}