/*==============================================================================
GPU Compute Example
Copyright (c), Firelight Technologies Pty, Ltd 2004-2020.

This example is a modification of the Convolution Reverb example to show
how this computationally expensive effect can be run on the GPU.

Impulse Response is based on "St Andrew's Church" by

    www.openairlib.net
    Audiolab, University of York
    Damian T. Murphy
    http://www.openairlib.net/auralizationdb/content/st-andrews-church

licensed under Attribution Share Alike Creative Commons license
http://creativecommons.org/licenses/by-sa/3.0/


Anechoic sample "Operatic Voice" by 

    www.openairlib.net
    http://www.openairlib.net/anechoicdb/content/operatic-voice

licensed under Attribution Share Alike Creative Commons license
http://creativecommons.org/licenses/by-sa/3.0/


### Features Demonstrated ###
+ FMOD_PS4_SetComputeDevice
+ FMOD_PS4_ReleaseComputeDevice

==============================================================================*/
#include "fmod.hpp"
#include "common.h"
#include "fmod_ps4.h"

int FMOD_Main()
{
    void *extradriverdata = 0;    
    Common_Init(&extradriverdata);

    FMOD_RESULT result;
    

    /*
        Allocate GPU memory
    */
    static const int OnionMemSize = 128 * 1024 * 1024;
    static const int GarlicMemSize = 128 * 1024 * 1024;
    static const int MemBlockAlignment = 64 * 1024;
    int ret;
    off_t onionPhysicalAddr = 0;    
    ret = sceKernelAllocateDirectMemory(0, SCE_KERNEL_MAIN_DMEM_SIZE, OnionMemSize, MemBlockAlignment, SCE_KERNEL_WB_ONION, &onionPhysicalAddr);    
    void* onionMem = 0;
    ret = sceKernelMapDirectMemory(&onionMem, OnionMemSize, SCE_KERNEL_PROT_GPU_ALL | SCE_KERNEL_PROT_CPU_RW, 0, onionPhysicalAddr, MemBlockAlignment);
    off_t garlicPhysicalAddr = 0;
    ret = sceKernelAllocateDirectMemory(0, SCE_KERNEL_MAIN_DMEM_SIZE, GarlicMemSize, MemBlockAlignment, SCE_KERNEL_WC_GARLIC, &garlicPhysicalAddr);      
    void* garlicMem = 0;
    ret = sceKernelMapDirectMemory(&garlicMem, GarlicMemSize, SCE_KERNEL_PROT_GPU_ALL | SCE_KERNEL_PROT_CPU_WRITE, 0, garlicPhysicalAddr, MemBlockAlignment);
    
    static const int GpuComputePipe = 0;
    static const int GpuComputeQueue = 3;
    
    result = FMOD_PS4_SetComputeDevice(GpuComputePipe, GpuComputeQueue, garlicMem, GarlicMemSize, onionMem, OnionMemSize);
    ERRCHECK(result);

    
    /*
        Create a System object and initialize
    */
    FMOD::System* system;
    result = FMOD::System_Create(&system);
    ERRCHECK(result);

    unsigned int version;
    result = system->getVersion(&version);
    ERRCHECK(result);

    if (version < FMOD_VERSION)
    {
        Common_Fatal("FMOD lib version %08x doesn't match header version %08x", version, FMOD_VERSION);
    }
        
    result = system->init(32, FMOD_INIT_NORMAL, 0);
    ERRCHECK(result);
        

    /*
        Create a new channel group to hold the convolution DSP unit
    */
    FMOD::ChannelGroup* reverbGroup;
    result = system->createChannelGroup("reverb", &reverbGroup);
    ERRCHECK(result);

    
    /*
        Create a new channel group to hold all the channels and process the dry path
    */
    FMOD::ChannelGroup* mainGroup;
    result = system->createChannelGroup("main", &mainGroup);
    ERRCHECK(result);

    /*
        Create the convultion DSP unit and set it as the tail of the channel group
    */
    FMOD::DSP* reverbUnit;    
    result = system->createDSPByType(FMOD_DSP_TYPE_CONVOLUTIONREVERB, &reverbUnit);
    ERRCHECK(result);
    result = reverbGroup->addDSP(FMOD_CHANNELCONTROL_DSP_TAIL, reverbUnit);
    ERRCHECK(result);

    /*
        Open the impulse response wav file, but use FMOD_OPENONLY as we want
        to read the data into a seperate buffer
    */
    FMOD::Sound* irSound;
    result = system->createSound(Common_MediaPath("standrews.wav"), FMOD_DEFAULT | FMOD_OPENONLY, NULL, &irSound);
    ERRCHECK(result);

    /*
        Retrieve the sound information for the Impulse Response input file
    */
    FMOD_SOUND_FORMAT irSoundFormat;
    FMOD_SOUND_TYPE irSoundType;
    int irSoundBits, irSoundChannels;
    result = irSound->getFormat(&irSoundType, &irSoundFormat, &irSoundChannels, &irSoundBits);
    ERRCHECK(result);
    unsigned int irSoundLength;
    result = irSound->getLength(&irSoundLength, FMOD_TIMEUNIT_PCM);
    ERRCHECK(result);

    
    if (irSoundFormat != FMOD_SOUND_FORMAT_PCM16)
    {
        /*
            For simplicity of the example, if the impulse response is the wrong format just display an error
        */        
        Common_Fatal("Impulse Response file is the wrong audio format");
    }

    /*
        The reverb unit expects a block of data containing a single 16 bit int containing
        the number of channels in the impulse response, followed by PCM 16 data
    */
    unsigned int irDataLength = sizeof(short) * (irSoundLength * irSoundChannels + 1);
    short* irData = (short*)malloc(irDataLength);
    irData[0] = (short)irSoundChannels;
    unsigned int irDataRead;
    result = irSound->readData(&irData[1], irDataLength - sizeof(short), &irDataRead);
    ERRCHECK(result);
    result = reverbUnit->setParameterData(FMOD_DSP_CONVOLUTION_REVERB_PARAM_IR, irData, irDataLength);
    ERRCHECK(result);

    /*
        Don't pass any dry signal from the reverb unit, instead take the dry part
        of the mix from the main signal path
    */
    result = reverbUnit->setParameterFloat(FMOD_DSP_CONVOLUTION_REVERB_PARAM_DRY, -80.0f);    
    ERRCHECK(result);

    /*
        We can now free our copy of the IR data and release the sound object, the reverb unit 
        has created it's internal data
    */
    free(irData);
    result = irSound->release();
    ERRCHECK(result);
    
    /*
        Load up and play a sample clip recorded in an anechoic chamber
    */
    FMOD::Sound* sound;
    system->createSound(Common_MediaPath("singing.wav"), FMOD_3D | FMOD_LOOP_NORMAL, NULL, &sound);
    ERRCHECK(result);

    FMOD::Channel* channel;
    system->playSound(sound, mainGroup, true, &channel);
    ERRCHECK(result);
    
    /*
        Create a send connection between the channel head and the reverb unit
    */
    FMOD::DSP* channelHead;
    channel->getDSP(FMOD_CHANNELCONTROL_DSP_HEAD, &channelHead);
    ERRCHECK(result);
    FMOD::DSPConnection* reverbConnection;
    result = reverbUnit->addInput(channelHead, &reverbConnection, FMOD_DSPCONNECTION_TYPE_SEND);
    ERRCHECK(result);

    result = channel->setPaused(false);
    ERRCHECK(result);

    static const float volumeFactor = 0.05f;
    int wetVolume = 4;
    int dryVolume = 0;
        
    /*
        Main loop
    */
    do
    {
        Common_Update();

        if (Common_BtnPress(BTN_LEFT))
        {
            wetVolume = (wetVolume <= 0) ? wetVolume : wetVolume - 1;
        }
        if (Common_BtnPress(BTN_RIGHT))
        {
            wetVolume = (wetVolume >= 20) ? wetVolume : wetVolume + 1;
        }        
        if (Common_BtnPress(BTN_DOWN))
        {
            dryVolume = (dryVolume <= 0) ? dryVolume : dryVolume - 1;
        }
        if (Common_BtnPress(BTN_UP))
        {
            dryVolume = (dryVolume >= 20) ? dryVolume : dryVolume + 1;
        }
        

        result = system->update();
        ERRCHECK(result);

        result = reverbConnection->setMix(wetVolume * volumeFactor);
        ERRCHECK(result);
        result = mainGroup->setVolume(dryVolume * volumeFactor);
        ERRCHECK(result);


        Common_Draw("==================================================");
        Common_Draw("Convolution Example.");
        Common_Draw("Copyright (c) Firelight Technologies 2004-2020.");
        Common_Draw("==================================================");
        Common_Draw("Press %s and %s to change dry mix", Common_BtnStr(BTN_UP), Common_BtnStr(BTN_DOWN));
        Common_Draw("Press %s and %s to change wet mix", Common_BtnStr(BTN_LEFT), Common_BtnStr(BTN_RIGHT));
        Common_Draw("wet mix (%.2f) dry mix (%.2f)", wetVolume * volumeFactor, dryVolume * volumeFactor);
        Common_Draw("Press %s to quit", Common_BtnStr(BTN_QUIT));
        Common_Draw("");

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT));

    /*
        Shut down
    */
    result = sound->release();
    ERRCHECK(result);
    result = mainGroup->release();
    ERRCHECK(result);
    result = reverbGroup->removeDSP(reverbUnit);
    ERRCHECK(result);
    result = reverbUnit->disconnectAll(true, true);
    ERRCHECK(result);
    result = reverbUnit->release();
    ERRCHECK(result);
    result = reverbGroup->release();
    ERRCHECK(result);
    result = system->close();
    ERRCHECK(result);
    result = system->release();
    ERRCHECK(result);

    /*
        Release GPU compute resources
    */
    ERRCHECK(FMOD_PS4_ReleaseComputeDevice());
    
    sceKernelMunmap(onionMem, OnionMemSize);
    sceKernelReleaseDirectMemory(onionPhysicalAddr, OnionMemSize);
    sceKernelMunmap(garlicMem, GarlicMemSize);
    sceKernelReleaseDirectMemory(garlicPhysicalAddr, GarlicMemSize);

    Common_Close();

    return 0;
}
