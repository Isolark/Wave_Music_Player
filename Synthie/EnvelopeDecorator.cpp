#include "StdAfx.h"
#include "EnvelopeDecorator.h"


CEnvelopeDecorator::CEnvelopeDecorator(CAudioNode* decoratedAudioNode)
	: CAudioNodeDecorator(decoratedAudioNode)
{
	//m_attack = m_release = 0.05;
	m_attack = 0.05 ;
	m_decay = 0.10;
	m_sustain = 0.35;
	m_release = 0.50; 

	m_duration = 1.0;
	m_time = 0;
	
}


CEnvelopeDecorator::~CEnvelopeDecorator(void)
{
}

void CEnvelopeDecorator::Start()
{
	m_decoratedAudioNode->Start();

	m_time = 0;
}

bool CEnvelopeDecorator::Generate()
{
	if (!m_decoratedAudioNode->Generate())
		return false;

	



	double durationInSeconds = 60.0 * m_duration / m_decoratedAudioNode->GetBPM();

	double atime = m_attack * durationInSeconds;
	double dtime =  atime + m_decay * durationInSeconds;
	double stime = dtime +m_sustain * durationInSeconds;
	double rtime = stime;// m_release * durationInSeconds;

	//double a = m_time > 0 ? (m_time < m_attack ? (m_time / m_attack) : 1) : 0;
	//double d = m_time > m_attack ? (m_time <m_sustain ? :1):2'
	//double r = m_time > durationInSeconds - m_release ? (m_time < durationInSeconds ? ((durationInSeconds - m_time) / m_release) : 0) : 1;
	//double factor = min(a, r);

	double a = m_time > 0 ? (m_time < atime ? 1.5*(m_time / atime) : 2) : 0;
	double d = m_time > atime ?(m_time < dtime ? 1.5 -(m_time - atime)/dtime:2):2;
	double s = m_time > dtime ?(m_time < stime ? 1:2): 2;
	double r = m_time > stime ? (m_time < durationInSeconds ? 1-.5*(1-((durationInSeconds - m_time)) / rtime) : 0) : 2;
	double r2 = m_time > durationInSeconds - .05 ? (m_time < durationInSeconds ? ((durationInSeconds - m_time) / .05) : 0) : 2;
	double factor1 = min(a, r);
	double factor2 = min(s,r2);
	double factor = min(factor1, factor2);
	factor = min(factor,d);

	m_frame[0] = factor * m_decoratedAudioNode->Frame(0);
	m_frame[1] = factor * m_decoratedAudioNode->Frame(1);

	m_time+= m_decoratedAudioNode->GetSamplePeriod();
	return true;
}
