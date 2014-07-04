#pragma once
#include "WaveInstrument.h"
#include "SawInstrument.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include "Reson.h"
#include <vector>
class CSawInstrumentFactory
{
public:
	CSawInstrumentFactory(void);
	~CSawInstrumentFactory(void);

	//CSawInstrument *CreateSub(std::wstring wavetype, CNote *note);
    void SetNote(CNote *note);

    void SetFreq(double f) {m_frequency = f;}

	CSawInstrument *CSawInstrumentFactory::CreateInstrument();


private:

    std::vector<short> m_wave;
	double m_frequency;
	double m_rate;
};

