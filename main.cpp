#include "main.h"



//a\u2081\u2082\u2083
//36pt = 24 пкс//17 пкс высота
//36pt = 21 пкс//9//12//12 ширина

int main(int argc, char *argv[])
{
image img2(1,4,2,3);

    QGuiApplication app( argc, argv );                      //Инициализация ядра приложения

    QImage   img(70,70,QImage::Format_RGB32);
    QPainter p(&img);
    QRect    tmp(0,0,70,70);

    p.setFont(QFont("Times", 36));                          //Установка шрифта

    img.fill(Qt::white);                                    //Установка белого фона
    //p.fillRect(tmp,QBrush(Qt::white,Qt::SolidPattern));   //Закраска квадрата

    qDebug() << "Set painter";

   // p.drawText(tmp, Qt::AlignHCenter, QString("a"+tmp1[0]+tmp1[0])); //Печать элемента
    qDebug() << "Draw text";

    p.drawLine(0,0,70,70);                                  //Отрисовка диагональной линии
    qDebug() << "Draw line";

    img.save("txt.png", "PNG");                             // writes image into ba in PNG format
    qDebug() << "Success";

    return 0;
}
