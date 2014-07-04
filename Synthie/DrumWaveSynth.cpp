#include "StdAfx.h"
#include "DrumWaveSynth.h"
#include <cstdlib>
#include <random>
#include <cmath>



CDrumWaveSynth::CDrumWaveSynth(void)
{
	m_phase = 0;
	m_amp = 0.01;
	m_freq = 660;

	m_pastFrame[0] = 0;
	m_pastFrame[1] = 0;
}

CDrumWaveSynth::~CDrumWaveSynth(void)
{
}

void CDrumWaveSynth::Start()
{
    m_phase = 0;
}

bool CDrumWaveSynth::Generate()
{
	srand(m_phase * m_phase * 250);

	//Generate White Noise...
    m_frame[0] = m_amp * double(1000 - (rand() % 2001)) / 1000;

	//Generate Swept wave...

	const double gain = 5;
	double R, cosTheta, theta, A, freq, band;

	freq = (m_freq - 50) / GetSampleRate();//0.01134;
	band = 0.01;

	R = 1 - (band/2);
	cosTheta = (2*R*cos(2*PI*freq)) / (1 + pow(R, 2));
	theta = acos(cosTheta);
	A = ((1 - pow(R, 2)) * sin(theta)) * gain;

    m_frame[0] += m_amp * sin(m_phase * 2 * PI);

	m_frame[0] = (A * m_frame[0]) + (2 * R * cosTheta * m_pastFrame[0]) - (pow(R,2) * m_pastFrame[1]);
    m_frame[1] = m_frame[0];

	m_pastFrame[1] = m_pastFrame[0];
	m_pastFrame[0] = m_frame[0];

    m_phase += m_freq * GetSamplePeriod();

    return true;
}