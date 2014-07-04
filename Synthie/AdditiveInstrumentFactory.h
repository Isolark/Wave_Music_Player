#pragma once
#include "Additive.h"
#include "Harmonic.h"
#include <vector>


class CAdditiveInstrumentFactory
{
public:
	CAdditiveInstrumentFactory(void);
	virtual ~CAdditiveInstrumentFactory(void);

	void AddHarmonic(double amplitude, int harmonicNumber);
	void ClearHarmonics();
	CAdditive* CreateAdditiveInstrument();

private:
	std::vector<CHarmonic*> m_harmonics;
};

