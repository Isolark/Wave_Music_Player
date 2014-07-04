
#include "StdAfx.h"
#include "SubNode.h"
#include <cmath>

CSubNode::CSubNode(void)
{
    for(int i=0; i<4;  i++)
        m_amp[i] = 1;
}

CSubNode::~CSubNode(void)
{
}


void CSubNode::Start()
{
    m_phase = 0;
}

bool CSubNode::Generate()
{
    double sample = 0;
    for(int i=0;  i<4;  i++)
    {
        sample += m_amp[i] * sin(m_phase * (i * 2 + 1));
    }

    m_frame[1] = m_frame[0] = sample;
    m_phase += 2 * PI * m_freq * GetSamplePeriod();

    return true;
}
bool CSubNode::GenerateSawtooth()
{
	return false;
}


bool CSubNode::GenerateSquare()
{
	return false;
}


bool CSubNode::GenerateTriangle()
{
	return false;
}