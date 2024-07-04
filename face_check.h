#ifndef FACE_CHECK_H
#define FACE_CHECK_H

#include <QMainWindow>
#include <QBuffer>
#include "face_root.h"
#include "ledctl.h"
#include "buttonctl.h"
#include "cameractl.h"
#include "udpcom.h"
#include "syn6288ctl.h"
#define MainWin 0
#define RootWin 1
#define TestWin 2
QT_BEGIN_NAMESPACE
namespace Ui { class face_check; }
QT_END_NAMESPACE

class face_check : public QMainWindow
{
    Q_OBJECT

public:
    face_check(QWidget *parent = nullptr);
    ~face_check();

private slots:
    void AButtonEvent();
    void BButtonEvent();
    void CButtonEvent();
    void DButtonEvent();
    void EButtonEvent();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

signals:
    void AButtonPass();
    void BButtonPass();
    void CButtonPass();
    void DButtonPass();
    void EButtonPass();
    void getFrameQPixmapToRootWin(QPixmap);
    void sendUDPQByteArray(QByteArray msg,QHostAddress address,quint16 port);

private:
    Ui::face_check *ui;
    LedCtl *ledCtlA,*ledCtlB;
    int A,B;
    ButtonCtl *buttonCtl;
    face_root *root_ui;
    int WinState;
    CameraCtl *cameraCtl;
    UDPCom *udpCom;
    QPixmap pix;
    SYN6288Ctl *syn6288Ctl;

};
#endif // FACE_CHECK_H
