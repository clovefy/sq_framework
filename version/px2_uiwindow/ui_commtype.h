#ifndef UI_COMMTYPE_H
#define UI_COMMTYPE_H

//
struct Uiimagehead
{
    int width;
    int height;
    int imagetype;
    int imagesize;
    char* data;
};

struct UIrectangle
{
    float x;
	float y;
	float width;
	float height;
};

struct UIpoint
{
    float x;
	float y;
};

struct UIdodresult
{
    int num;
    UIrectangle rectangel[10];
    UIpoint fdodlots[10][4];
};


struct UIlocresult
{ 
    UIpoint fpostion;
    float fHeading; 
};


struct UIpldresult
{ 
    int parkingnum;
    UIpoint fparkinglotp[4];
};

struct UIldwresult
{
    int num;
    UIpoint fldwlotp[2][20];
};

struct UImaincontrol
{
    int uwPlayMode;
    int uwPrePlayMode;
    int uwShowMode;
    int uwRecordingFlag;
    int uwRecordCanNum;
    int uwRecordFrameNum;

    int uwCanNumPer1s;
    int uwCapturePer1s;
    int uwFramePer1s;
    int uwShowPer1s;
    int uwRecordFramePer1s;

    int uwLostFrameNum;
    int uwTotalTime;
    int uwVersionNum;


    int LDW_Workstatus;
    int BSD_Workstatus;

    float LDW_CostTime;
    float BSD_CostTime;

    int TotalTime;
    int uwCurrentTime;
    int StartTime;
};

typedef struct STR_MSG_BUFFER
{
    int uwMsgId;
    int uwMsgLen;

    int auwBuffer[512];
}STR_MSG_BUFFER;

typedef void (*eventcallback)(int ID);
typedef void (*msgcallback)(STR_MSG_BUFFER* msg);


enum EVENT_ID
{
    GLOBL_MSG_ID = 0,
    GLOBL_MSG_TASK_START,
    GLOBL_MSG_STOP,
    GLOBL_MSG_PLAY,
    GLOBL_MSG_OUTPUTXML,
    GLOBL_MSG_INPUTXML,
    GLOBL_MSG_GRABER2MFC,
    GLOBL_MSG_FRAMESETID,
    GLOBL_MSG_DISPLYWNDCHANGE,
    GLOBL_MSG_MFC2DIS_GETPICTURE,
    GLOBL_MSG_DETECTION_TO_ESTIMATE,
    GLOBL_MSG_MFC_TO_DETECTION,
    GLOBL_MSG_ESTIMATE_TO_STRCH,
    GLOBL_MSG_MODE_SWITCH,
    GLOBL_MSG_SHOW_MODE_SWITCH,
    GLOBL_MSG_SHOW_LOADING,
    GLOBL_MSG_GET_LOG,
    GLOBL_MSG_VERTICL_PARK,
    GLOBL_MSG_PARALL_PARK,
    GLOBL_MSG_TURN_LEFT,
    GLOBL_MSG_TURN_RIGHT,
    GLOBL_MSG_ADD_SPEED,
    GLOBL_MSG_MINUS_SPEED,
    GLOBL_MSG_GEAR,
    GLOBL_MSG_ENABLE_ONLINE_CALIB,
    GLOBL_MSG_ADTF_CONTROL,
    GLOBL_MSG_APP_SWITCH,
    GLOBL_MSG_TIMESTAMP_CHECK,
    GLOBL_MSG_APP_EXIT,
    GLOBL_MSG_ALL_RSP,
    GLOBL_MSG_SAVE_DAT_HEAD,
    GLOBL_MSG_UPDATE_CALIB_FROM_FILE,
    GLOBL_MSG_SAVE_CALIB_TO_FILE,
    GLOBL_MSG_EOL_CALIB,
    GLOBL_MSG_CAPTURELIVE_ADTFFILTER_NEWMEDIA,
    GLOBL_MSG_CAPTURELIVE_NEWFRAME,
    GLOBL_MSG_CAPTURE_PLAYBACK_LASTFRAME,
    GLOBL_MSG_CAPTURE_PLAYBACK_FIRSTFRAME,
    GLOBL_MSG_START_RECORD,
    GLOBL_MSG_STOP_RECORD,
    GLOBL_MSG_OPENFILE,

};
#endif // UI_COMMTYPE_H
