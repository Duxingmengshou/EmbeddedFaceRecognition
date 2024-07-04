#include "face_root.h"
#include "ui_face_root.h"

face_root::face_root(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::face_root)
{
    ui->setupUi(this);
    WinState=RootWin;
    SoundTestMBox.setWindowTitle("声音测试");
    SoundTestMBox.setText("是否听到声音");
    QPushButton *SoundTestYesButton = SoundTestMBox.addButton("听到", QMessageBox::YesRole);
    QPushButton *SoundTestNoButton = SoundTestMBox.addButton("没有听到", QMessageBox::NoRole);

    connect(SoundTestYesButton,&QPushButton::clicked,this,[this](){
        qDebug()<<"听到";
        ui->label_3->setText(ui->label_3->text()+"语音模块正常\n");
    });
    connect(SoundTestNoButton,&QPushButton::clicked,this,[this](){
        qDebug()<<"没有听到";
        ui->label_3->setText(ui->label_3->text()+"语音模块异常\n");
    });

    LEDTestMBox.setWindowTitle("LED测试");
    LEDTestMBox.setText("是否LED灯闪烁");
    QPushButton *LEDTestYesButton = LEDTestMBox.addButton("LED灯闪烁", QMessageBox::YesRole);
    QPushButton *LEDTestNoButton =LEDTestMBox.addButton("LED异常", QMessageBox::NoRole);

    connect(LEDTestYesButton,&QPushButton::clicked,this,[this](){
        qDebug()<<"LED灯正常";
        ui->label_3->setText(ui->label_3->text()+"LED模块正常\n");
    });
    connect(LEDTestNoButton,&QPushButton::clicked,this,[this](){
        qDebug()<<"LED灯异常";
        ui->label_3->setText(ui->label_3->text()+"LED模块异常\n");
    });


    ButtonTestMBox.setWindowTitle("声音测试");
    ButtonTestMBox.setText("请依次按下所有按键");
    QPushButton *ButtonTestYesButton = ButtonTestMBox.addButton("按键正常", QMessageBox::YesRole);
    QPushButton *ButtonTestNoButton = ButtonTestMBox.addButton("按键异常", QMessageBox::NoRole);

    connect(ButtonTestYesButton,&QPushButton::clicked,this,[this](){
        qDebug()<<"按键正常";
        ui->label_3->setText(ui->label_3->text()+"按键模块正常\n");

    });
    connect(ButtonTestNoButton,&QPushButton::clicked,this,[this](){
        qDebug()<<"按键异常";
        ui->label_3->setText(ui->label_3->text()+"按键模块异常\n");

    });
}

face_root::~face_root()
{
    delete ui;
}

void face_root::showQPixmap(QPixmap pix)
{
    pix.scaled(ui->label_5->size(), Qt::KeepAspectRatio);
    ui->label_5->setScaledContents(true);
    ui->label_5->setPixmap(pix);
}

void face_root::AButtonEvent()
{
    if(WinState==RootWin)
    {
        on_pushButton_3_clicked();
    }
    if(WinState==TestWin)
    {
        ButtonTestMBox.setText("A按键被按下");
    }
}

void face_root::BButtonEvent()
{
    if(WinState==RootWin)
    {

    }
    if(WinState==TestWin)
    {
        ButtonTestMBox.setText("B按键被按下");
    }
}

void face_root::CButtonEvent()
{
    if(WinState==RootWin)
    {
    }
    if(WinState==TestWin)
    {
        ButtonTestMBox.setText("C按键被按下");
    }
}


void face_root::DButtonEvent()
{
    if(WinState==RootWin)
    {
    }
    if(WinState==TestWin)
    {
        ButtonTestMBox.setText("D按键被按下");
    }
}


void face_root::EButtonEvent()
{
    if(WinState==RootWin)
    {
        on_pushButton_2_clicked();
    }
    if(WinState==TestWin)
    {
        ButtonTestMBox.setText("E按键被按下");
    }
}

void face_root::on_pushButton_3_clicked()
{
    emit this->returnMain();
}


void face_root::on_pushButton_2_clicked()
{
    WinState=TestWin;
    QString str="测试功能中...\n";
    ui->label_3->setText(str);
    //    emit test();
    emit SoundTest();
    SoundTestMBox.exec();
    emit LEDTest();
    LEDTestMBox.exec();
    ButtonTestMBox.exec();
    WinState=RootWin;
}



