#pragma once
#include "WaveInstrument.h"
#include "msxml2.h"
#include "xmlhelp.h"
#include "TriangleInstrument.h"
#include <vector>
class CTriangleInstrumentFactory
{
public:
	CTriangleInstrumentFactory(void);
	~CTriangleInstrumentFactory(void);

	//CSawInstrument *CreateSub(std::wstring wavetype, CNote *note);
    void SetNote(CNote *note);

    void SetFreq(double f) {m_frequency = f;}


	CTriangleInstrument *CTriangleInstrumentFactory::CreateInstrument();

private:
    std::vector<short> m_wave;
	double m_frequency;
	double m_rate;
};

