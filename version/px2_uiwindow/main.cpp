
#include <QApplication>
#include "data_agent.h"
#include "mainwindow.h"
#include "qt_lib/json/include/config.h"
#include "qt_lib/json/include/json.h"

//
eventcallback gcallbackhandl;
msgcallback gcallbackmsghandl;
data_agent gdataagent;
Json::Value ui_obj;
//event anget


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //gdataagent = new data_agent();
    MainWindow w(0,&gdataagent);
    w.show();

    return a.exec();
}


//初始化数据交互buffder
extern "C" data_agent* UI_Getdataagent()
{
    return &gdataagent;
}

//初始化数据交互buffder
extern "C" Json::Value* UI_Get_json()
{
    return &ui_obj;
}

extern "C" int UI_Enable()
{
    int argc = 0;
    QApplication a(argc, NULL);
   // gdataagent = new data_agent;
    MainWindow w(0,&gdataagent);
    w.show();

    return a.exec();
}

extern "C" void UI_Seteventcallback(void* handl)
{
    //printf("UI_Seteventcallback is in \n");
    gcallbackhandl = (eventcallback)handl;
}

extern "C" void UI_Setmsgcallback(void* handl)
{
    //printf("UI_Seteventcallback is in \n");
    gcallbackmsghandl = (msgcallback)handl;
}


