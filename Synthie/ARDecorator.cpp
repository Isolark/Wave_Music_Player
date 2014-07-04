#include "StdAfx.h"
#include "ARDecorator.h"


CARDecorator::CARDecorator(CAudioNode* decoratedAudioNode)
	: CAudioNodeDecorator(decoratedAudioNode)
{
	m_attack = m_release = 0.05;
	m_duration = 1.0;
	m_time = 0;
}

CARDecorator::~CARDecorator(void)
{
}

void CARDecorator::Start()
{
	m_decoratedAudioNode->Start();

	m_time = 0;
}

bool CARDecorator::Generate()
{
	if (!m_decoratedAudioNode->Generate())
		return false;

	double durationInSeconds = 60.0 * m_duration / m_decoratedAudioNode->GetBPM();

	double a = m_time > 0 ? (m_time < m_attack ? (m_time / m_attack) : 1) : 0;
	double r = m_time > durationInSeconds - m_release ? (m_time < durationInSeconds ? ((durationInSeconds - m_time) / m_release) : 0) : 1;
	double factor = min(a, r);

	m_frame[0] = factor * m_decoratedAudioNode->Frame(0);
	m_frame[1] = factor * m_decoratedAudioNode->Frame(1);

	m_time+= m_decoratedAudioNode->GetSamplePeriod();
	return true;
}