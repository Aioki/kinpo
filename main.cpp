#include "main.h"



//a\u2081\u2082\u2083
//36pt = 24 пкс//17 пкс высота
//36pt = 21 пкс//9//12//12 ширина

int main(int argc, char *argv[])
{
    image img1(2,4,2,3);

    QGuiApplication app( argc, argv );                      //Инициализация ядра приложения

    //p.fillRect(tmp,QBrush(Qt::white,Qt::SolidPattern));   //Закраска квадрата



   // p.drawText(tmp, Qt::AlignHCenter, QString("a"+tmp1[0]+tmp1[0])); //Печать элемента
   // qDebug() << "Draw text";



    return 0;
}
