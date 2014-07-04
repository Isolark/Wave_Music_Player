#include "StdAfx.h"
#include "SawWave.h"

#include <cmath>

CSawWave::CSawWave(void)
{
	m_phase = 0;
	m_amp = 0.001;
	m_freq = 440;
}

CSawWave::~CSawWave(void)
{
}

void CSawWave::Start()
{
    m_phase = 0;
}

bool CSawWave::Generate()
{
	double s =0.;
	for(int h=1;h<(m_sampleRate / (2 * m_freq));h++){
		s += sin(2 * PI * h * m_phase) / h;
	}
    m_frame[0] = m_amp * s;
    m_frame[1] = m_frame[0];

    m_phase += m_freq * GetSamplePeriod();

    return true;
}