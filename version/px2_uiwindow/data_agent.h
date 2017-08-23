#ifndef DATA_AGENT_H
#define DATA_AGENT_H
#include "ui_commtype.h"

//UImain windows enable mask
enum Mainwindowsmask
{
    NONE_SHOW,
    SEG_SHWO = 1,
    PLD_SHWO = 2,
    DOD_SHWO = 4,
    LOC_SHWO= 8,
    RECORD_SHWO = 16,
    LDW_SHWO = 32,
};





class data_agent
{
public:

public:
    Uiimagehead imagebev;
    Uiimagehead imageseg;
	Uiimagehead imagedod;
    Uiimagehead imagerecord;

    Mainwindowsmask uimainMask;

	//===========================

    UIdodresult dodresult;
	UIlocresult locresult;
	UIpldresult pldresult;
    UIldwresult ldwresult;

    //===========================
    UImaincontrol maincontrolinfo;
};
#endif // DATA_AGENT_H
