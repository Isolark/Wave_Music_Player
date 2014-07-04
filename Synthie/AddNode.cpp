#include "StdAfx.h"
#include "AddNode.h"
#include <cmath>


CAddNode::CAddNode(void)
{
	m_amp = 1;
	m_sineRadians = 0;
	m_vibratoRadians = 0;
	m_largestHarmonic = 1;
	m_time = 0;
}


CAddNode::~CAddNode(void)
{
}

short CAddNode::RangeBound( double d )
{
	if ( d > 32767 )
		d = 32767;
	else if ( d < -32768 )
		d = -32768;
	return (short) d;
}

void CAddNode::SetFreq( double f )
{
	m_freq = f;
	while ( m_largestHarmonic * f <= ( GetSampleRate() / 2) )
	{
		m_largestHarmonic += 1; // Calculate what harmonic to go to
	}
}

void CAddNode::Start()
{
    m_phase = 0;
	m_time = 0;
}

bool CAddNode::Generate()
{
	double frame0 = 0;
	double frame1 = 0;
	CHarmonic* harmonic;

	if ( m_harmonics->size() == 0 )
	{
		//If vector is empty, we still want the
		//first harmonic
		harmonic = new CHarmonic();
		harmonic->SetAmplitude(2.5); //Default amplitude
		harmonic->SetHarmonicNumber(1);

		m_harmonics->push_back( *harmonic );
	}
	for ( unsigned i = 0 ; i < m_harmonics->size() ; i++ )
	{
		harmonic = &m_harmonics->at(i);
		double sinePortion = sin( GetPhase( harmonic->GetHarmonicNumber() ) );

		std::map<int,double>::iterator it;
		it = m_crossfades.find( harmonic->GetHarmonicNumber() );
		
		if ( it != m_crossfades.end() )
		{
			double percentProgress = m_time/m_duration;
			double harmonicPortion = (1.-percentProgress) * harmonic->GetAmplitude() * sinePortion;
			double crossfadePortion = percentProgress * m_crossfades[ harmonic->GetHarmonicNumber() ] * sinePortion;
			frame0 += harmonicPortion + crossfadePortion;
			frame1 += harmonicPortion + crossfadePortion;
		}
		else //No corresponding crossfade
		{
			frame0 += harmonic->GetAmplitude() * sinePortion;
			frame1 += frame0;
		}
	}

	m_frame[0] = RangeBound(frame0);
	m_frame[1] = RangeBound(frame1);
	m_time += GetSamplePeriod();

    return true;
}

double CAddNode::GetPhase( int harmonicNumber )
{
	double phase = 0;
	if ( m_vibrato ) //This returns a phasor that reflects vibrato
	{
		if ( harmonicNumber > 0  && harmonicNumber <= m_largestHarmonic )
		{
			phase = m_sineRadians * harmonicNumber;

			double frequencyDifferential = 10 * sin(m_vibratoRadians);
			m_sineRadians += ( 2 * PI * (m_freq + frequencyDifferential) )/GetSampleRate();
			m_vibratoRadians += ( 2 * PI * (m_freq / 2) )/GetSampleRate(); //Use freq/2 for vibrato frequency
		}
	}
	else //Returns a phasor without vibrato
	{
		if ( harmonicNumber > 0  && harmonicNumber <= m_largestHarmonic )
		{
			phase = harmonicNumber * m_phase * 2 * PI;
			m_phase += m_freq * GetSamplePeriod();
		}
	}
	return phase;
}



void CAddNode::SetHarmonics( std::vector<CHarmonic>* har )
{
	m_harmonics = har;
}

void CAddNode::SetCrossFades( std::map<int, double> cfades )
{
	m_crossfades = cfades;
}