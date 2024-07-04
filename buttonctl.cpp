#include "buttonctl.h"

ButtonCtl::ButtonCtl(QObject *parent)
    : QThread{parent}
{
    keys_fd = open("/dev/input/event0", O_RDONLY);
    if (keys_fd <= 0)
    {
        printf("open /dev/input/event0 device error!\n");
        exit(0);
    }
    else{
        printf("open /dev/input/event0 device successfully!\n");
    }
}

ButtonCtl::~ButtonCtl()
{
    close(keys_fd);
}

void ButtonCtl::run()
{
    while (1)
    {
        if (read(keys_fd, &t, sizeof(t)) == sizeof(t))
        {
            if (t.type == EV_KEY)
            {
                if (t.value == 0 || t.value == 1)
                {
                    qDebug()<<t.code<<"-"<<t.value;
                }
                if(t.code==172&&t.value==0)
                {
                    this->AButton();
                }
                if(t.code==158&&t.value==0)
                {
                    this->BButton();
                }
                if(t.code==116&&t.value==0)
                {
                    this->CButton();
                }
                if(t.code==115&&t.value==0)
                {
                    this->DButton();
                }
                if(t.code==114&&t.value==0)
                {
                    this->EButton();
                }
            }
        }
    }
}
