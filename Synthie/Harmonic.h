#pragma once
class CHarmonic
{
public:
	CHarmonic(void);
	virtual ~CHarmonic(void);

	void SetAmplitude(double amp) {m_amplitude = amp;}
	void SetHarmonicNumber(int num) {m_harmonicNumber = num;}

	double GetAmplitude() {return m_amplitude;}
	int GetHarmonicNumber() {return m_harmonicNumber;}

private:
	double  m_amplitude; 
	int		m_harmonicNumber;
};

