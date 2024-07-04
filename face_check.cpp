#include "face_check.h"
#include "ui_face_check.h"
QByteArray getImageDataFromQImage(const QImage &image)
{
    QByteArray imageData;
    QBuffer buffer(&imageData);
    image.save(&buffer, "png");
    imageData = imageData.toBase64();
    return imageData;
}
face_check::face_check(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::face_check)
{
    ui->setupUi(this);
    ledCtlA=new LedCtl;
    ledCtlB=new LedCtl;
    ledCtlA->led_open("/dev/dev_LEDA");
    ledCtlB->led_open("/dev/dev_LEDB");
    ledCtlA->led_off();
    ledCtlB->led_off();
    buttonCtl=new ButtonCtl;
    cameraCtl=new CameraCtl;
    root_ui=new face_root;
    udpCom=new UDPCom;
    syn6288Ctl=new SYN6288Ctl;
    root_ui->hide();
    ui->label_2->setWordWrap(true);
    WinState=MainWin;
    connect(root_ui,&face_root::returnMain,this,[this](){
        this->show();
        root_ui->hide();
        WinState=MainWin;
    });
    connect(cameraCtl,&CameraCtl::getFrameQPixmap,this,[this](QPixmap pix){
        this->pix=pix;
        if(WinState==MainWin)
        {
            pix.scaled(ui->label_3->size(), Qt::KeepAspectRatio);
            ui->label_3->setScaledContents(true);
            ui->label_3->setPixmap(pix);
            //            emit this->sendUDPQByteArray(getImageDataFromQImage(pix.toImage()),QHostAddress("192.168.175.1"),12345);
            //            udpCom->sendData(getImageDataFromQImage(pix.toImage()),QHostAddress("192.168.175.1"),12345);
            //            udpCom->setBufferAndSend(getImageDataFromQImage(pix.toImage()));
        }
        else if(WinState==RootWin)
        {
            emit getFrameQPixmapToRootWin(pix);
        }
    });
    connect(this,&face_check::getFrameQPixmapToRootWin,root_ui,&face_root::showQPixmap);
    cameraCtl->start();
    buttonCtl->start();
    connect(buttonCtl,&ButtonCtl::AButton,this,&face_check::AButtonEvent);
    connect(buttonCtl,&ButtonCtl::BButton,this,&face_check::BButtonEvent);
    connect(buttonCtl,&ButtonCtl::CButton,this,&face_check::CButtonEvent);
    connect(buttonCtl,&ButtonCtl::DButton,this,&face_check::DButtonEvent);
    connect(buttonCtl,&ButtonCtl::EButton,this,&face_check::EButtonEvent);

    connect(this,&face_check::AButtonPass,root_ui,&face_root::AButtonEvent);
    connect(this,&face_check::BButtonPass,root_ui,&face_root::BButtonEvent);
    connect(this,&face_check::CButtonPass,root_ui,&face_root::CButtonEvent);
    connect(this,&face_check::DButtonPass,root_ui,&face_root::DButtonEvent);
    connect(this,&face_check::EButtonPass,root_ui,&face_root::EButtonEvent);

    connect(root_ui,&face_root::SoundTest,this,[this](){
        syn6288Ctl->SYN_FrameInfo(1,syn6288Ctl->UTF8ToGB2312("语音模块测试"));
    });
    connect(root_ui,&face_root::LEDTest,this,[this](){
        this->ledCtlA->led_on();
        sleep(1);
        this->ledCtlA->led_off();
        this->ledCtlB->led_on();
        sleep(1);
        this->ledCtlB->led_off();
    });
    udpCom->start();
    connect(this,&face_check::sendUDPQByteArray,udpCom,&UDPCom::sendData);
    connect(udpCom,&UDPCom::newMessage,this,[this](QByteArray data){
        if(QString(data)=="0")
        {
            ui->label_2->setText("验证失败");
            syn6288Ctl->SYN_FrameInfo(1,syn6288Ctl->UTF8ToGB2312("人脸验证失败，请重试"));
            ledCtlA->led_on();
            ledCtlB->led_on();
            sleep(1);//表示其他动作
        }
        else{
            ui->label_2->setText(QString(data));
            syn6288Ctl->SYN_FrameInfo(1,syn6288Ctl->UTF8ToGB2312("人脸验证成功，欢迎"));
            ledCtlA->led_off();
            ledCtlB->led_on();
            sleep(1);//表示其他动作
        }
        ledCtlA->led_off();
        ledCtlB->led_off();
    });
}

face_check::~face_check()
{
    delete root_ui;
    delete ui;
    delete ledCtlA;
    delete ledCtlB;
    delete buttonCtl;
}

void face_check::on_pushButton_clicked()
{
    //验证
    udpCom->sendData(getImageDataFromQImage(pix.toImage()),QHostAddress("192.168.11.228"),12345);
    ledCtlA->led_on();
    ledCtlB->led_off();
}
void face_check::on_pushButton_2_clicked()
{
    this->hide();
    root_ui->show();
    WinState=RootWin;
}

void face_check::AButtonEvent()
{
    if(WinState==MainWin)
    {
        on_pushButton_2_clicked();
        return;
    }
    if(WinState==RootWin)
    {
        emit this->AButtonPass();
    }
}


void face_check::BButtonEvent()
{
    if(WinState==MainWin)
    {
        on_pushButton_clicked();
        return;
    }
    if(WinState==RootWin)
    {
        emit this->BButtonPass();
    }
}

void face_check::CButtonEvent()
{
    if(WinState==MainWin)
    {
    }
    if(WinState==RootWin)
    {
        emit this->CButtonPass();
    }
}

void face_check::DButtonEvent()
{
    if(WinState==MainWin)
    {
    }
    if(WinState==RootWin)
    {
        emit this->DButtonPass();
    }
}

void face_check::EButtonEvent()
{
    if(WinState==MainWin)
    {
    }
    if(WinState==RootWin)
    {
        emit this->EButtonPass();
    }
}


