#include "StdAfx.h"
#include "Reson.h"
#include <cmath>

CReson::CReson(void)
{
	freq = 0.01134;
	band = 0.01;
	QUEUESIZE = 2*int(44100+(10*44100)) ;

	R = 1 - (band/2);
	cosTheta = (2*R*cos(2*PI*freq)) / (1 + pow(R, 2));
	theta = acos(cosTheta);
	A = ((1 - pow(R, 2)) * sin(theta)) * gain;

	queue.resize(QUEUESIZE);
	inqueue.resize(QUEUESIZE);

	time =0.;
	wrloc = 0;
}


CReson::~CReson(void)
{
}


short CReson::ProcessReson(double sample)
{

	audio[0] = audio[1] = short(sample);

    wrloc = (wrloc + 2) % QUEUESIZE;
    queue[wrloc] = audio[0];
    queue[wrloc+1] = audio[1];

	int delaylength = 0;
	int rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;

	daudio[0] = audio[0] * A;// + queue[rdloc++]/2;
	daudio[1] = audio[1] * A;// + queue[rdloc]/2;

	delaylength = 1 * 2;
	rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;

	daudio[0] += inqueue[rdloc++] * (2 * R * cosTheta);
	daudio[1] += inqueue[rdloc] * (2 * R * cosTheta);

	delaylength = 2 * 2;
	rdloc = (wrloc + QUEUESIZE - delaylength) % QUEUESIZE;

	daudio[0] += inqueue[rdloc++] * -(pow(R,2));
	daudio[1] += inqueue[rdloc] * -(pow(R,2));

	audio[0] = daudio[0];
    audio[1] = daudio[1];

	inqueue[wrloc] = audio[0];
	inqueue[wrloc+1] = audio[1];

	return audio[0];
}
