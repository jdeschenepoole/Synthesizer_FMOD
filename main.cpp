

#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "api\inc\fmod.hpp"
#include "api\inc\fmod_errors.h"
#include "api\inc\fmod.h"

#include "CPiano.h"

bool CheckCapsLock()
{
   if ((GetKeyState(VK_CAPITAL) & 0x0001)!=0)
      return true;
   else
      return false;
}

void ERRCHECK(FMOD_RESULT result)
{
    if (result != FMOD_OK)
    {
        printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
        exit(-1);
    }
}

void FadeOut(FMOD::System *system, FMOD::Channel *chan, float toVolume)
{
	float f;
	bool reachedVolume = false;

	do
	{
		system->update();
		chan->getVolume(&f);
		

		if (f <= toVolume)
		{
			reachedVolume = true;
			chan->setPaused(true);
		}

		chan->setVolume(f - 0.1f);

		Sleep(100);
	}while(!reachedVolume);

}

void FadeIn(FMOD::System *system, FMOD::Channel *chan, float toVolume)
{
	float f;

	chan->setPaused(false);

	bool reachedVolume = false;

	do
	{
		system->update();
	
		chan->getVolume(&f);

		if (f >= toVolume)
		{
			reachedVolume = true;
		}

		chan->setVolume(f + 0.1f);

		Sleep(100);
	}while(!reachedVolume);

}

void PlayNote(FMOD::System *system, FMOD::Channel *channel)
{
	FadeIn(system, channel, 0.5f);
	Sleep(100);
	FadeOut(system, channel, 0.25);
	Sleep(100);
	FadeOut(system, channel, 0.0f);
}

void playSounds(FMOD::System *system, FMOD::Channel *channel, FMOD::Sound *sound, float pitch, float pan, float gain, int pos)
{
	//FMOD::Sound* s = sounds[soundKey];
	//
	//result = system->playSound(FMOD_CHANNEL_FREE, s, false, &channel);
	//ERRCHECK(result);

	FMOD_RESULT result;

	channel->setPan(pan);
	channel->setVolume(gain);
	FMOD_TIMEUNIT FTU = 2 ;
	channel->setFrequency(pitch);
	channel->setPosition(pos, FTU);
	bool paused;
	channel->getPaused(&paused);

	result = system->playSound(FMOD_CHANNEL_FREE, sound, paused, &channel);
	ERRCHECK(result);
			
}

FMOD::DSP* FreeDSP(FMOD::DSP *dsp1, FMOD::DSP *dsp2, FMOD::DSP *dsp3, FMOD::DSP *dsp4)
{
	bool free = true;
	dsp1->getActive(&free);
	if (!free)
		return dsp1;
	dsp2->getActive(&free);
	if (!free)
		return dsp2;
	dsp3->getActive(&free);
	if (!free)
		return dsp3;
	dsp4->getActive(&free);
	if (!free)
		return dsp4;
	return 0;
}

FMOD::Channel* FreeChannel(FMOD::Channel *channel1, FMOD::Channel *channel2, FMOD::Channel *channel3, FMOD::Channel *channel4)
{
	bool free = true;
	channel1->isPlaying(&free);
	if (!free)
		return channel1;
	channel2->isPlaying(&free);
	if (!free)
		return channel2;
	channel3->isPlaying(&free);
	if (!free)
		return channel3;
	channel4->isPlaying(&free);
	if (!free)
		return channel4;
	return 0;

}


int main()
{
	int key = 0;
	FMOD::System    *system;
	FMOD::Channel   *channel1 = 0, *channel2 = 0, *channel3 = 0, *channel4 = 0, *drumChannel = 0;
	FMOD::Sound		*sound1;
    FMOD::DSP       *dsp1 = 0, *dsp2 = 0, *dsp3 = 0, *dsp4 = 0;;
    FMOD_RESULT      result;

	bool playNote = false;

	bool drumSample = false;
	float drumPitch = 0.0f;
	float drumGain = 0.1f;

	result = FMOD::System_Create(&system);
    ERRCHECK(result);

	result = system->init(32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);

	result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp1);
	ERRCHECK(result);
	result = dsp1->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 0);
	ERRCHECK(result);

	result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp2);
	ERRCHECK(result);
	result = dsp2->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 0);
	ERRCHECK(result);

	result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp3);
	ERRCHECK(result);
	result = dsp3->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 0);
	ERRCHECK(result);

	result = system->createDSPByType(FMOD_DSP_TYPE_OSCILLATOR, &dsp4);
	ERRCHECK(result);
	result = dsp4->setParameter(FMOD_DSP_OSCILLATOR_TYPE, 0);
	ERRCHECK(result);

	result = system->createSound("media\\drumloop.wav", FMOD_SOFTWARE, 0, &sound1);
	drumChannel->setVolume(0.0f);

	ERRCHECK(result);

	CPiano *piano = new CPiano();

	float freq = 0.0f;

	printf( "*****************************************\n");
	printf( " 3Oct A A# B C C# D D# E F F# G G# A A#  \n");
	printf( "      q Q  w e E  r R  t y Y  u U  i I   \n");
	printf(	" 4Oct      B C C# D D# E F F# G G# A A#  \n");
	printf(	"           s d D  f F  g h H  j J  k K   \n");
	printf(	" 5Oct      B C C# D D# E F F# G G# A A# B\n");
	printf(	"           z x X  c C  v b B  n N  m M  ,\n");
	printf(	"*****************************************\n");
	do
    {
		//for(int yy=0;yy<7;yy++)
  //          for(int xx=0;xx<42;xx++)
  //                  mvaddch(yy,xx,map[yy][xx]);

        if (_kbhit())
        {
			 key = _getch();

			int x = 27; // 3, 15, 27, 39, 51

			float f;
			bool drumPitchChange = false;
			drumChannel->getFrequency(&f);

			switch (key)
			{
			case 'q':
				freq = piano->getNotesFromKeys(x-2);
				playNote = true;
				break;
			case 'Q':
				freq = piano->getNotesFromKeys(x-1);
				playNote = true;
				break;

			case 'w': // B
				freq = piano->getNotesFromKeys(x+0);
				playNote = true;
				break;
			case 'e': // C
				freq = piano->getNotesFromKeys(x+1);
				playNote = true;
				break;
			case 'E': // C#
				freq = piano->getNotesFromKeys(x+2);
				playNote = true;
				break;
			case 'r': //D
				freq = piano->getNotesFromKeys(x+3);
				playNote = true;
				break;
			case 'R': //D#
				freq = piano->getNotesFromKeys(x+4);
				playNote = true;
				break;
			case 't': //E
				freq = piano->getNotesFromKeys(x+5);
				playNote = true;
				break;
			case 'y': //F
				freq = piano->getNotesFromKeys(x+6);
				playNote = true;
				break;
			case 'Y': //F#
				freq = piano->getNotesFromKeys(x+7);
				playNote = true;
				break;
			case 'u': //G
				freq = piano->getNotesFromKeys(x+8);
				playNote = true;
				break;
			case'U': //G#
				freq = piano->getNotesFromKeys(x+9);
				playNote = true;
				break;
			case'i': //A
				freq = piano->getNotesFromKeys(x+10);
				playNote = true;
				break;
			case 'I': //A#
				freq = piano->getNotesFromKeys(x+11);
				playNote = true;
				break;


			case 's': // B
				freq = piano->getNotesFromKeys(x+12);
				playNote = true;
				break;
			case 'd': // C
				freq = piano->getNotesFromKeys(x+13);
				playNote = true;
				break;
			case 'D': // C#
				freq = piano->getNotesFromKeys(x+14);
				playNote = true;
				break;
			case 'f': //D
				freq = piano->getNotesFromKeys(x+15);
				playNote = true;
				break;
			case 'F': //D#
				freq = piano->getNotesFromKeys(x+16);
				playNote = true;
				break;
			case 'g': //E
				freq = piano->getNotesFromKeys(x+17);
				playNote = true;
				break;
			case 'h': //F
				freq = piano->getNotesFromKeys(x+18);
				playNote = true;
				break;
			case 'H': //F#
				freq = piano->getNotesFromKeys(x+19);
				playNote = true;
				break;
			case 'j': //G
				freq = piano->getNotesFromKeys(x+20);
				playNote = true;
				break;
			case'J': //G#
				freq = piano->getNotesFromKeys(x+21);
				playNote = true;
				break;
			case'k': //A
				freq = piano->getNotesFromKeys(x+22);
				playNote = true;
				break;
			case 'K': //A#
				freq = piano->getNotesFromKeys(x+23);
				playNote = true;
				break;

			case 'z': // B
				freq = piano->getNotesFromKeys(x+24);
				playNote = true;
				break;
			case 'x': // C
				freq = piano->getNotesFromKeys(x+25);
				playNote = true;
				break;
			case 'X': // C#
				freq = piano->getNotesFromKeys(x+26);
				playNote = true;
				break;
			case 'c': //D
				freq = piano->getNotesFromKeys(x+27);
				playNote = true;
				break;
			case 'C': //D#
				freq = piano->getNotesFromKeys(x+28);
				playNote = true;
				break;
			case 'v': //E
				freq = piano->getNotesFromKeys(x+29);
				playNote = true;
				break;
			case 'b': //F
				freq = piano->getNotesFromKeys(x+30);
				playNote = true;
				break;
			case 'B': //F#
				freq = piano->getNotesFromKeys(x+31);
				playNote = true;
				break;
			case 'n': //G
				freq = piano->getNotesFromKeys(x+32);
				playNote = true;
				break;
			case'N': //G#
				freq = piano->getNotesFromKeys(x+33);
				playNote = true;
				break;
			case'm': //A
				freq = piano->getNotesFromKeys(x+34);
				playNote = true;
				break;
			case 'M': //A#
				freq = piano->getNotesFromKeys(x+35);
				playNote = true;
				break;

			case ',':
				freq = piano->getNotesFromKeys(x+36);
				playNote = true;
				break;

			case '1':
				if (!drumSample)
				{
					drumSample = true;
					drumChannel->setFrequency(drumPitch);
					result = system->playSound(FMOD_CHANNEL_REUSE, sound1, true, &drumChannel);
					FadeIn(system, drumChannel, drumGain);
				}
				else
				{
					drumSample = false;
					result = system->playSound(FMOD_CHANNEL_REUSE, sound1, true, &drumChannel);
					FadeOut(system, drumChannel, 0.0f);	
				}
				break;
			case '=':
				if ((drumSample) && (drumPitch < 1.0f))
				{
					drumPitch += 0.1f;
					f *= drumPitch;
					drumPitchChange = true;
				}
				break;
			case '-':
				if ((drumSample) && (drumPitch > -1.0f))
				{
					drumPitch -= 0.1f;
					f /= drumPitch;
					drumPitchChange = true;
				}
				break;
			}

			if(drumSample && drumPitchChange)
			{
				drumChannel->setFrequency(f);
				result = system->playSound(FMOD_CHANNEL_REUSE, sound1, true, &drumChannel);
			}
			
			if(playNote)
			{
				FMOD::DSP *dsp = FreeDSP(dsp1, dsp2, dsp3, dsp4);
				if (dsp == 0)
					break;
				result = dsp->setParameter(FMOD_DSP_OSCILLATOR_RATE, freq); 
				ERRCHECK(result);
				FMOD::Channel *channel = FreeChannel(channel1, channel2, channel3, channel4);
				if (channel = 0)
					break;
				result = system->playDSP(FMOD_CHANNEL_FREE, dsp, true, &channel);
				channel->setVolume(0.0f);
				PlayNote(system, channel);
				playNote = false;
			}
		}

		// Reverb Toggle
		if (CheckCapsLock)
		{
			FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL;
			system->setReverbProperties(&prop);
		}
		else
		{
			FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_OFF;
			system->setReverbProperties(&prop);
		}

		system->update();
	 } while (key != 27);

	return 0;
}


