#pragma once
#include <vector>
class CReson
{
public:
	CReson(void);
	~CReson(void);


private:
	double R, cosTheta, theta, A, gain, time;
	int wrloc;

	short audio[2];
	double daudio[2];

	double freq;
	double band;
	int QUEUESIZE;
	std::vector<short> queue;
	std::vector<short> inqueue;
public:
	short ProcessReson(double);
};

