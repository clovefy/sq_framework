#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "qt_lib/json/include/config.h"
#include "qt_lib/json/include/json.h"

extern data_agent gdataagent;
extern eventcallback gcallbackhandl;
extern msgcallback gcallbackmsghandl;
extern Json::Value ui_obj;
//==============================
char testbuffer[3686400];

void teststub()
{
    memset(testbuffer,0,3686400);
    gdataagent.uimainMask = RECORD_SHWO;
    gdataagent.locresult.fpostion.x = 0.5;
    gdataagent.locresult.fpostion.y = 0.5;



    ui_obj["Comm"]["Uimask"] = 1;
}

MainWindow::MainWindow(QWidget *parent,data_agent* input) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mdataagent = input;

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(100);

    setWindowTitle(tr("Analog 222"));
    resize(1280, 720);

    // load image;
    mlocbg_png =  QImage("./qt_res/loc_bg.png");
    mloccar_png =  QImage("./qt_res/car.png");

    mrecordflag = true;


    //dshow menu
    //ui->horizontalWidget0->setVisible(false);
    //ui->->setVisible(false);
     teststub();
}

MainWindow::~MainWindow()
{
    if(NULL != gcallbackhandl)
    {
        printf("gcallbackhandl null  %d\n",GLOBL_MSG_APP_EXIT);

        (*gcallbackhandl)(GLOBL_MSG_APP_EXIT);

    }
    else
    {
        printf("gcallbackhandl null  %d\n",mrecordflag);
    }

    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
     if(NULL == mdataagent)
     {

         return;
     }

     uint uimask = ui_obj["Comm"]["uimask"].asUInt();
     if((uimask&SEG_SHWO) == SEG_SHWO )
     {
         paintSeg();
         return;
     }
     else if((uimask&DOD_SHWO) == DOD_SHWO )
     {
         paintDod();
         return;
     }
     else if((uimask&LOC_SHWO) == LOC_SHWO)
     {
         paintLoc();
     }
     else if((uimask&PLD_SHWO) == PLD_SHWO)
     {
         paintPld();
     }
     else if((uimask&RECORD_SHWO) == RECORD_SHWO)
     {
         paintRecord();
     }
     else if((uimask&LDW_SHWO) == LDW_SHWO)
     {
         paintLdw();
     }
     else
     {
         paintSeg();
     }

     paintStatus();
}


void MainWindow::paintDod()
{
    QPainter painter(this);



    //描画处理

    QImage img = QImage((const unsigned char*)( ui_obj["Dod"]["Bgimage"]["data"].asUInt64()),
                                                ui_obj["Dod"]["Bgimage"]["width"].asInt(),
                                                ui_obj["Dod"]["Bgimage"]["height"].asInt(),
                                                ui_obj["Dod"]["Bgimage"]["width"].asInt()*4,
                                                QImage::Format_RGBA8888);


    QPixmap pixmap;
    pixmap.convertFromImage(img);
    QRect temp(0,0,width(),height());

    int show_width = width();
    int show_height = height();

    //back ground
    painter.drawPixmap(temp, (const QPixmap)pixmap);

    //kuang

    for(int i = 0; i  < ui_obj["Dod"]["Result"]["num"].asInt(); i++)
    {
           QPointF points[4] = {
               QPointF(ui_obj["Dod"]["Result"]["Lots"][i][0]["x"].asFloat()*show_width,
                       ui_obj["Dod"]["Result"]["Lots"][i][0]["y"].asFloat()*show_height),
               QPointF(ui_obj["Dod"]["Result"]["Lots"][i][1]["x"].asFloat()*show_width,
                       ui_obj["Dod"]["Result"]["Lots"][i][1]["y"].asFloat()*show_height),
               QPointF(ui_obj["Dod"]["Result"]["Lots"][i][2]["x"].asFloat()*show_width,
                       ui_obj["Dod"]["Result"]["Lots"][i][2]["y"].asFloat()*show_height),
               QPointF(ui_obj["Dod"]["Result"]["Lots"][i][3]["x"].asFloat()*show_width,
                       ui_obj["Dod"]["Result"]["Lots"][i][3]["y"].asFloat()*show_height)};

           painter.setPen(QPen(QColor(255,0,0),0));
           painter.setBrush(QColor(255,0,0,120));
           painter.drawPolygon(points,4);
    }
}

void MainWindow::paintSeg()
{
    QPainter painter(this);

    QImage img = QImage((const unsigned char*)( ui_obj["Bev"]["Bgimage"]["data"].asUInt64()),
                                                ui_obj["Bev"]["Bgimage"]["width"].asInt(),
                                                ui_obj["Bev"]["Bgimage"]["height"].asInt(),
                                                ui_obj["Bev"]["Bgimage"]["width"].asInt()*4,
                                                QImage::Format_RGBA8888);



    QPixmap pixmap;
    pixmap.convertFromImage(img);
    QRect temp(0,0,width()/2,height());
    painter.drawPixmap(temp, (const QPixmap)pixmap);

    //描画处理,
    QImage imggray = QImage((const unsigned char*)( ui_obj["Seg"]["Bgimage"]["data"].asUInt64()),
                                                    ui_obj["Seg"]["Bgimage"]["width"].asInt(),
                                                    ui_obj["Seg"]["Bgimage"]["height"].asInt(),
                                                    ui_obj["Seg"]["Bgimage"]["width"].asInt(),
                                                    QImage::Format_Grayscale8);


    QPixmap pixmapgray;
    pixmapgray.convertFromImage(imggray);
    QRect tempgray(width()/2,0,width()/2,height());
    painter.drawPixmap(tempgray, (const QPixmap)pixmapgray);
}


 void MainWindow::paintLoc()
 {
     QPainter painter(this);

     QImage img = QImage((const unsigned char*)( ui_obj["Bev"]["Bgimage"]["data"].asUInt64()),
                                                 ui_obj["Bev"]["Bgimage"]["width"].asInt(),
                                                 ui_obj["Bev"]["Bgimage"]["height"].asInt(),
                                                 ui_obj["Bev"]["Bgimage"]["width"].asInt()*4,
                                                 QImage::Format_RGBA8888);



     QPixmap pixmap;
     pixmap.convertFromImage(img);
     QRect temp(0,0,width()/2,height());
     //back ground
     painter.drawPixmap(temp, (const QPixmap)pixmap);



     //bg render
     QPixmap pixmapbg;
     pixmapbg.convertFromImage((mlocbg_png));
     QRect tempbg(width()/2,0,width()/2,height());
     painter.drawPixmap(tempbg, (const QPixmap)pixmapbg);


     if(ui_obj["Pld"]["Result"]["parkingnum"].asInt() > 0)
     {
        QPointF points[4] = {
            QPointF(ui_obj["Pld"]["Result"]["Lots"][0]["x"].asFloat()*tempbg.width(),
                    ui_obj["Pld"]["Result"]["Lots"][0]["y"].asFloat()*tempbg.height()),
            QPointF(ui_obj["Pld"]["Result"]["Lots"][1]["x"].asFloat()*tempbg.width(),
                    ui_obj["Pld"]["Result"]["Lots"][1]["y"].asFloat()*tempbg.height()),
            QPointF(ui_obj["Pld"]["Result"]["Lots"][2]["x"].asFloat()*tempbg.width(),
                    ui_obj["Pld"]["Result"]["Lots"][2]["y"].asFloat()*tempbg.height()),
            QPointF(ui_obj["Pld"]["Result"]["Lots"][3]["x"].asFloat()*tempbg.width(),
                    ui_obj["Pld"]["Result"]["Lots"][3]["y"].asFloat()*tempbg.height())};


        painter.setPen(QPen(QColor(255,0,0),0));
        painter.setBrush(QColor(255,0,0,120));
        painter.drawPolygon(points,4);
     }


     //draw car
     QPixmap pixmapcar;
     pixmapcar.convertFromImage((mloccar_png));

     int x = ui_obj["Loc"]["Result"]["Postion"]["x"].asFloat()*tempbg.width()+ tempbg.x();
     int y = ui_obj["Loc"]["Result"]["Postion"]["y"].asFloat()*tempbg.height()+ tempbg.y();
     int with = 30;
     int height = 50;

     int centerx = x-with/2;
     if(centerx < 0)
     {
         centerx = 0;
     }

     int centery = y - height/2;
     if(centery <0 )
     {
         centery = 0;
     }

     QRect carrect(centerx ,centery,with,height);

     painter.translate(x,y);
     painter.rotate(ui_obj["Loc"]["Result"]["Postion"]["heading"].asFloat());
     painter.translate(0-x,0-y);
     painter.drawPixmap(carrect,(const QPixmap)pixmapcar);


 }


 void MainWindow::paintPld()
 {
     QPainter painter(this);

     QImage img = QImage((const unsigned char*)( ui_obj["Bev"]["Bgimage"]["data"].asUInt64()),
                                                 ui_obj["Bev"]["Bgimage"]["width"].asInt(),
                                                 ui_obj["Bev"]["Bgimage"]["height"].asInt(),
                                                 ui_obj["Bev"]["Bgimage"]["width"].asInt()*4,
                                                 QImage::Format_RGBA8888);



     QPixmap pixmap;
     pixmap.convertFromImage(img);
     QRect temp(0,0,width()/2,height());
     painter.drawPixmap(temp, (const QPixmap)pixmap);


     if(ui_obj["Pld"]["Result"]["parkingnum"].asInt() > 0)
     {
        QPointF points[4] = {
            QPointF(ui_obj["Pld"]["Result"]["Lots"][0]["x"].asFloat()*temp.width(),
                    ui_obj["Pld"]["Result"]["Lots"][0]["y"].asFloat()*temp.height()),
            QPointF(ui_obj["Pld"]["Result"]["Lots"][1]["x"].asFloat()*temp.width(),
                    ui_obj["Pld"]["Result"]["Lots"][1]["y"].asFloat()*temp.height()),
            QPointF(ui_obj["Pld"]["Result"]["Lots"][2]["x"].asFloat()*temp.width(),
                    ui_obj["Pld"]["Result"]["Lots"][2]["y"].asFloat()*temp.height()),
            QPointF(ui_obj["Pld"]["Result"]["Lots"][3]["x"].asFloat()*temp.width(),
                    ui_obj["Pld"]["Result"]["Lots"][3]["y"].asFloat()*temp.height())};


        painter.setPen(QPen(QColor(255,0,0),0));
        painter.setBrush(QColor(255,0,0,120));
        painter.drawPolygon(points,4);
     }
 }


 void MainWindow::paintRecord()
 {

     QPainter painter(this);

     for(int i = 0; i <4 ; i ++)
     {

         QImage img = QImage((const unsigned char*)( ui_obj["Record"]["Bgimage"][i]["data"].asUInt64()),
                                                     ui_obj["Record"]["Bgimage"][i]["width"].asInt(),
                                                     ui_obj["Record"]["Bgimage"][i]["height"].asInt(),
                                                     ui_obj["Record"]["Bgimage"][i]["width"].asInt()*4,
                                                     QImage::Format_RGBA8888);

         QPixmap pixmap;
         pixmap.convertFromImage(img);


         QRect temp(i/2*width()/2
                    ,i%2*height()/2
                    ,width()/2
                    ,height()/2);
         painter.drawPixmap(temp, (const QPixmap)pixmap);
     }
 }


 void MainWindow::paintLdw()
 {
     QPainter painter(this);

     QImage img = QImage((const unsigned char*)( ui_obj["Bev"]["Bgimage"]["data"].asUInt64()),
                                                 ui_obj["Bev"]["Bgimage"]["width"].asInt(),
                                                 ui_obj["Bev"]["Bgimage"]["height"].asInt(),
                                                 ui_obj["Bev"]["Bgimage"]["width"].asInt()*4,
                                                 QImage::Format_RGBA8888);

     QPixmap pixmap;
     pixmap.convertFromImage(img);
     QRect temp(0,0,width()/2,height());
     painter.drawPixmap(temp, (const QPixmap)pixmap);




     if(ui_obj["Ldw"]["Result"]["num"].asInt() > 0)
     {
         painter.setPen(QPen(QColor(0,255,0),5));
         for(int i = 1; i < 20; i++)
         {

            QPointF start_p(ui_obj["Ldw"]["Result"]["Lots"][0][i-1]["x"].asFloat()*temp.width(),
                            ui_obj["Ldw"]["Result"]["Lots"][0][i-1]["y"].asFloat()*temp.height());

            QPointF end_p(ui_obj["Ldw"]["Result"]["Lots"][0][i]["x"].asFloat()*temp.width(),
                            ui_obj["Ldw"]["Result"]["Lots"][0][i]["y"].asFloat()*temp.height());

            painter.drawLine(start_p,end_p);
         }

         for(int i = 1; i < 20; i++)
         {
             QPointF start_p(ui_obj["Ldw"]["Result"]["Lots"][1][i-1]["x"].asFloat()*temp.width(),
                             ui_obj["Ldw"]["Result"]["Lots"][1][i-1]["y"].asFloat()*temp.height());

             QPointF end_p(ui_obj["Ldw"]["Result"]["Lots"][1][i]["x"].asFloat()*temp.width(),
                             ui_obj["Ldw"]["Result"]["Lots"][1][i]["y"].asFloat()*temp.height());

             painter.drawLine(start_p,end_p);
         }
     }
     //printf("record uwRecordFramePer1s %d \n",mdataagent->maincontrolinfo.uwRecordFramePer1s );
 }



void MainWindow::on_record_status_clicked()
{
    printf("record switch  %d\n",mrecordflag);


    if(mrecordflag)
    {
        mrecordflag = false;
        ui->record_status->setText("START");
    }
    else
    {
        mrecordflag = true;
        ui->record_status->setText("STOP");
    }



    if(NULL != gcallbackhandl)
    {
        if(mrecordflag)
        {
            (*gcallbackhandl)(GLOBL_MSG_START_RECORD);
        }
        else
        {
            (*gcallbackhandl)(GLOBL_MSG_STOP_RECORD);
        }
    }
    else
    {
        printf("gcallbackhandl null  %d\n",mrecordflag);
    }

}

void MainWindow::paintStatus()
{
    //watch dog color

    if(ui_obj["Comm"]["canper1s"].asInt() > 10)
    {
        ui->canstatus_button->setStyleSheet("background-color: rgb(0,255,0)");
    }
    else
    {
        ui->canstatus_button->setStyleSheet("background-color: rgb(255,0,0)");
    }

    //watch dog color
    if(ui_obj["Comm"]["frameper1s"].asInt() > 20)
    {
        ui->framestatus_button->setStyleSheet("background-color: rgb(0,255,0)");
    }
    else if(ui_obj["Comm"]["frameper1s"].asInt() > 10)
    {
        ui->framestatus_button->setStyleSheet("background-color: rgb(255,255,0)");
    }
    else
    {
        ui->framestatus_button->setStyleSheet("background-color: rgb(255,0,0)");
    }
    ui->framestatus_button->setText(QString::number(ui_obj["Comm"]["frameper1s"].asInt()));

}

void MainWindow::on_actionOpenfile_triggered()
{
    STR_MSG_BUFFER temmsg;
    temmsg.uwMsgId = GLOBL_MSG_OPENFILE;
    temmsg.uwMsgLen = sizeof(GLOBL_MSG_OPENFILE);

    QFileDialog* fd = new QFileDialog(this);
    fd->resize(240,320);
    fd->setNameFilter(tr("Video Files(*.mp4)"));
    fd->setViewMode(QFileDialog::List);

    if(fd->exec() == QDialog::Accepted)
    {
        QStringList filelist = fd->selectedFiles();
        QString filename = filelist[0];
        std::string stdfilename= filename.toStdString();
        memcpy((char*)temmsg.auwBuffer,stdfilename.c_str(),stdfilename.size());
       *( (char*)(temmsg.auwBuffer) + stdfilename.size()) = '\0';

        temmsg.uwMsgLen = 8 + stdfilename.size() + 1;

        if(NULL != gcallbackmsghandl)
        {
            (*gcallbackmsghandl)(&temmsg);
        }
        else
        {
            printf("gcallbackhandl null  %d\n",mrecordflag);
        }
    }

}
