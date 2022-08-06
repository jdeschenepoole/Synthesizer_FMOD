
#include "CPiano.h"
#include <math.h>

CPiano::CPiano()
{
	createNotes();
}

CPiano::~CPiano()
{
}

float CPiano::getNotesFromKeys(int key)
{
	return notes[key];
}

void CPiano::createNotes()
{
	//float note = 0.0f;
	//for (int i = 0; i < 88; i++)
	//{
	//	note = 440 * ( pow(2.0f,((i-49)/12)));
	//	notes.push_back(note);
	//}
	notes.push_back(27.5000);
	notes.push_back(29.1352);
	notes.push_back(30.8677);
	notes.push_back(32.7032);
	notes.push_back(34.6478);
	notes.push_back(36.7081);
	notes.push_back(38.8909);
	notes.push_back(41.2034);
	notes.push_back(43.6535);
	notes.push_back(46.2493);
	notes.push_back(48.9994);
	notes.push_back(51.9131);
	notes.push_back(55.0000);
	notes.push_back(58.2705);
	notes.push_back(61.7354);
	notes.push_back(65.4064);
	notes.push_back(69.2957);
	notes.push_back(73.4162);
	notes.push_back(77.7817);
	notes.push_back(82.4069);
	notes.push_back(87.3071);
	notes.push_back(92.4986);
	notes.push_back(97.9989);
	notes.push_back(103.826);
	notes.push_back(110.000);
	notes.push_back(116.541);
	notes.push_back(123.471);
	notes.push_back(130.813);
	notes.push_back(138.591);
	notes.push_back(146.832);

	notes.push_back(155.563);
	notes.push_back(164.814);
	notes.push_back(174.614);
	notes.push_back(184.997);
	notes.push_back(195.998);
	notes.push_back(207.652);
	notes.push_back(220.000);
	notes.push_back(233.082);
	notes.push_back(246.942);
	notes.push_back(261.626);
	notes.push_back(277.183);
	notes.push_back(293.665);
	notes.push_back(311.127);
	notes.push_back(329.628);
	notes.push_back(349.228);
	notes.push_back(369.994);
	notes.push_back(415.305);
	notes.push_back(440.000);
	notes.push_back(466.164);
	notes.push_back(493.883);
	notes.push_back(523.251);
	notes.push_back(554.365);
	notes.push_back(587.330);
	notes.push_back(622.254);
	notes.push_back(659.255);
	notes.push_back(698.456);
	notes.push_back(739.989);
	notes.push_back(783.991);
	notes.push_back(830.609);
	notes.push_back(880.000);
	notes.push_back(932.328);
	notes.push_back(987.767);
	notes.push_back(1046.50);
	notes.push_back(1108.73);
	notes.push_back(1174.66);
	notes.push_back(1244.51);
	notes.push_back(1318.51);
	notes.push_back(1396.91);
	notes.push_back(1479.98);
	notes.push_back(1567.98);
	notes.push_back(1661.22);
	notes.push_back(1760.00);
	notes.push_back(1864.66);
	notes.push_back(1975.53);
	notes.push_back(2093.00);
	notes.push_back(2217.46);
	notes.push_back(2349.32);
	notes.push_back(2489.02);
	notes.push_back(2637.02);
	notes.push_back(2793.83);
	notes.push_back(2959.96);
	notes.push_back(3135.96);
	notes.push_back(3322.44);
	notes.push_back(3520.00);
	notes.push_back(3729.31);
	notes.push_back(3951.07);
}