#include "StdAfx.h"
#include "SubtractivePlayer.h"


CSubtractivePlayer::CSubtractivePlayer(void)
{
	m_samples = NULL;
	m_numsamples =0;
}


CSubtractivePlayer::~CSubtractivePlayer(void)
{
}

void CSubtractivePlayer::Start()
{
	m_position = 0;
}

bool CSubtractivePlayer::Generate()
{
    if(m_position < m_numsamples)
    {
        m_frame[0] = m_samples[m_position++] / 32768.0;
        m_frame[1] = m_frame[0];
        return true;
    }
    else
    {
        m_frame[1] = m_frame[0] = 0;
        return false;
    }
}