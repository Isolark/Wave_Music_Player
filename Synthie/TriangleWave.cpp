#include "StdAfx.h"
#include "TriangleWave.h"

#include <cmath>


CTriangleWave::CTriangleWave(void)
{
	m_phase = 0;
	m_amp = 0.025;
	m_freq = 440;
}


CTriangleWave::~CTriangleWave(void)
{
}

void CTriangleWave::Start()
{
    m_phase = 0;
}

bool CTriangleWave::Generate()
{
	double s =0.;
	int alt = -1;
	for(double h=3;(h* m_freq)<(m_sampleRate/2);h+=2){
		s += (alt*m_amp/(pow(h,2)) * sin(2 * PI * h * m_phase));
		alt *= -1;
	}
    m_frame[0] = s;
    m_frame[1] = m_frame[0];

    m_phase += m_freq * GetSamplePeriod();

    return true;
}