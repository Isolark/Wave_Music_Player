#include "StdAfx.h"
#include "WavePlayer.h"
#include <cmath>

CWavePlayer::CWavePlayer(void)
{
    m_samples = NULL;
    m_numsamples = 0;
	m_variableSpeed = false;
}

CWavePlayer::~CWavePlayer(void)
{
}

void CWavePlayer::Start()
{
    m_position = 0;

	for(int i = 0; i < m_numsamples; i++)
	{m_wave.push_back(m_samples[i]);}

	m_DoublePosition = 0.0;
}

bool CWavePlayer::Generate()
{
	if(m_variableSpeed)
	{
		return Generate(m_DoublePosition);
	}
    if(m_position < m_numsamples)
    {
        m_frame[0] = m_wave[m_position++] / 32768.0;
        m_frame[1] = m_frame[0];
        return true;
    }
    else
    {
        m_frame[1] = m_frame[0] = 0;
        return false;
    }
}



bool CWavePlayer::Generate(double position)
{
	//interpolate the sound at the correct position

	int myposition = int(position);

	double inbetween = fmod(position,1);

	if(myposition >= m_numsamples)
    {    
		int  offset = m_numsamples - 5*170;
		myposition = (myposition-offset)% (5*170) + offset ;
		int a = 3;
	}

    if(myposition < m_numsamples || true)
    {
		int leftPos = ((myposition))%m_numsamples ;
		int rightPos = (myposition+1)%m_numsamples;
        m_frame[0] = ((1. - inbetween) * m_samples[leftPos] + inbetween * m_samples[rightPos]) / 32768.0;
        m_frame[1] = m_frame[0];
        return true;
    }
    else
    {
        m_frame[1] = m_frame[0] = 0;
        return false;
    }
}