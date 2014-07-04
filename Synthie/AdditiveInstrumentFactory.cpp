#include "StdAfx.h"
#include "AdditiveInstrumentFactory.h"


CAdditiveInstrumentFactory::CAdditiveInstrumentFactory(void)
{
}


CAdditiveInstrumentFactory::~CAdditiveInstrumentFactory(void)
{
}

void CAdditiveInstrumentFactory::AddHarmonic(double amplitude, int harmonicNumber)
{
	CHarmonic* newHarmonic = new CHarmonic();
	newHarmonic->SetAmplitude(amplitude);
	newHarmonic->SetHarmonicNumber(harmonicNumber);

	m_harmonics.push_back(newHarmonic);
}

CAdditive* CAdditiveInstrumentFactory::CreateAdditiveInstrument()
{
	CAdditive* newAdditiveInstrument = new CAdditive();

	for (unsigned i = 0 ; i < m_harmonics.size() ; i++ )
	{
		newAdditiveInstrument->AddHarmonic( *m_harmonics[i] );
	}

	return newAdditiveInstrument;
}

void CAdditiveInstrumentFactory::ClearHarmonics()
{
	for (unsigned i = 0 ; i < m_harmonics.size() ; i++ )
	{
		m_harmonics.clear();
	}
}