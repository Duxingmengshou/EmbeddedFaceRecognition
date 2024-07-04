#ifndef FACE_ROOT_H
#define FACE_ROOT_H

#include <QWidget>
#include <QMessageBox>
#include <QDebug>
#define RootWin 1
#define TestWin 2
namespace Ui {
class face_root;
}

class face_root : public QWidget
{
    Q_OBJECT

public:
    explicit face_root(QWidget *parent = nullptr);
    ~face_root();
signals:
    void returnMain();
    void SoundTest();
    void LEDTest();
    void ButtonTest();
    void registerFace(QString uid);

public slots:
    void showQPixmap(QPixmap);
    void AButtonEvent();
    void BButtonEvent();
    void CButtonEvent();
    void DButtonEvent();
    void EButtonEvent();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::face_root *ui;
    QMessageBox SoundTestMBox,LEDTestMBox,ButtonTestMBox;
    int WinState=RootWin;
};

#endif // FACE_ROOT_H
