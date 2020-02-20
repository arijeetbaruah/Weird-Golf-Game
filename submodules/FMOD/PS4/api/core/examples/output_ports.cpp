/*==============================================================================
Output Ports Example
Copyright (c), Firelight Technologies Pty, Ltd 2004-2020.

This example shows how to route channels into the PS4 controller, or the 
system background music port.
==============================================================================*/
#include "fmod.hpp"
#include "common.h"
#include <user_service.h>
#include "fmod_ps4.h"

int FMOD_Main()
{
    FMOD::System     *system;
    FMOD::Sound      *soundfx;
    FMOD::Sound      *music;
    FMOD::Channel    *musicChannel;
    FMOD_RESULT       result;
    unsigned int      version;
    void             *extradriverdata = 0;
    
    Common_Init(&extradriverdata);

    /*
        Create a System object and initialize.
    */
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }

    result = system->init(32, FMOD_INIT_NORMAL, extradriverdata);
    ERRCHECK(result);

    result = system->createSound(Common_MediaPath("drumloop.wav"), FMOD_LOOP_OFF | FMOD_2D, 0, &soundfx);
    ERRCHECK(result);

    result = system->createSound(Common_MediaPath("wave.mp3"), FMOD_LOOP_NORMAL | FMOD_2D, 0, &music);
    ERRCHECK(result);

    /* Create a channel group and attach it to the system background music port */
    FMOD::ChannelGroup* musicPort;
    result = system->createChannelGroup("BGM", &musicPort);
    ERRCHECK(result);

    result = system->attachChannelGroupToPort(FMOD_PS4_PORT_TYPE_MUSIC, FMOD_PORT_INDEX_NONE, musicPort);
    ERRCHECK(result);
    
    SceUserServiceUserId initialUser;
    sceUserServiceGetInitialUser(&initialUser);    
    
    /* Create a channel group and attach it to the initial users controller port */
    FMOD::ChannelGroup* controllerPort;
    result = system->createChannelGroup("Controller", &controllerPort);
    ERRCHECK(result);

    result = system->attachChannelGroupToPort(FMOD_PS4_PORT_TYPE_CONTROLLER, initialUser, controllerPort);
    ERRCHECK(result);

    /* Create a channel group and attach it to the initial users personal audio port */
    FMOD::ChannelGroup* personalPort;
    result = system->createChannelGroup("Personal", &personalPort);
    ERRCHECK(result);

    result = system->attachChannelGroupToPort(FMOD_PS4_PORT_TYPE_PERSONAL, initialUser, personalPort);
    ERRCHECK(result);

    /* Start background music and route into system music port */
    result = system->playSound(music, musicPort, false, &musicChannel);
    ERRCHECK(result);
        

    /*
        Main loop.
    */
    do
    {        
        bool musicPaused = false;
        result = musicChannel->getPaused(&musicPaused);
        ERRCHECK(result);

        Common_Update();

        if (Common_BtnPress(BTN_ACTION1))
        {
            FMOD::Channel* channel;
            result = system->playSound(soundfx, controllerPort, false, &channel);
            ERRCHECK(result);
        }        

        if (Common_BtnPress(BTN_ACTION2))
        {
            FMOD::Channel* channel;
            result = system->playSound(soundfx, personalPort, false, &channel);
            ERRCHECK(result);
        }

        if (Common_BtnPress(BTN_ACTION3))
        {
            musicPaused = !musicPaused;
            result = musicChannel->setPaused(musicPaused);
            ERRCHECK(result);
        }

        result = system->update();
        ERRCHECK(result);        

        float vol;
        result = FMOD_PS4_GetPadVolume((FMOD_SYSTEM*)system, initialUser, &vol);
        ERRCHECK(result);

        {
            Common_Draw("==================================================");
            Common_Draw("Output Ports Example.");
            Common_Draw("Copyright (c) Firelight Technologies 2004-2020.");
            Common_Draw("==================================================");
            Common_Draw("");
            Common_Draw("Press %s to play sound through controller port", Common_BtnStr(BTN_ACTION1));
            Common_Draw("Press %s to play sound through personal audio port", Common_BtnStr(BTN_ACTION2));
            Common_Draw("Press %s to toggle pause of background music port", Common_BtnStr(BTN_ACTION3));
            Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
            Common_Draw("");
            Common_Draw("Background music state: %s", musicPaused ? "paused" : "playing");
            Common_Draw("Pad Speaker Volume: %.2f", vol);
            Common_Draw("");
        }

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    
    /*
        Shut down
    */    
    result = system->detachChannelGroupFromPort(musicPort);
    ERRCHECK(result);
    musicPort->release();
    result = system->detachChannelGroupFromPort(controllerPort);
    ERRCHECK(result);
    controllerPort->release();
    result = system->detachChannelGroupFromPort(personalPort);
    ERRCHECK(result);
    personalPort->release();
    result = soundfx->release();
    ERRCHECK(result);
    result = music->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    Common_Close();

    return 0;
}
