#pragma once
#include "WaveInstrument.h"
#include "SquareInstrument.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include <vector>
class CSquareInstrumentFactory
{
public:
	CSquareInstrumentFactory(void);
	~CSquareInstrumentFactory(void);

	//CSawInstrument *CreateSub(std::wstring wavetype, CNote *note);
    void SetNote(CNote *note);

    void SetFreq(double f) {m_frequency = f;}
	

	CSquareInstrument *CSquareInstrumentFactory::CreateInstrument();

private:
    std::vector<short> m_wave;
	double m_frequency;
	double m_rate;
};

