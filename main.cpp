#include "main.h"

//a\u2081\u2082\u2083
//36pt = 24 пкс//17 пкс высота
//36pt = 21 пкс//9//12//12 ширина

int main(int argc, char *argv[])
{
    QGuiApplication app( argc, argv );                      //Инициализация ядра приложения

    int dimension = 3;
    int size_i    = 2;
    int size_j    = 4;
    int size_k    = 3;

    //Расчет изображения
    CalcImage size_image(dimension,size_i,size_j,size_k);

    qDebug() << size_image.getSizeCell() << " - Cell";
    qDebug() << size_image.getWidth() << "x" << size_image.getHeight();

    //Ограничение:
    // Одномерный массив до 100 элементов
    // Двумерный массив до 100 в каждом направлении
    // Трехмерный массив 58х1 2х44 19х4 10х8 и (j =90,7/i-1,036 и k до 90)
    if (size_image.getHeight() >= 16384 || size_image.getWidth() >= 16384){
        qDebug() << "Over resolution";
        return -1;
    }

    //Создание изображение нужного размера
    image img1(size_image.getHeight(),size_image.getWidth());

    //TODO: Ограничение - изображение не больше
    img1.drawArrays(dimension,size_i,size_j,size_k,size_image.getSizeCell());

    img1.fillCell(1,1,1);

    img1.fillRow(3,1);

    img1.fillTable(1);

    //img1.drawElements(1,2,3);
    img1.saveImage();
    //p.fillRect(tmp,QBrush(Qt::white,Qt::SolidPattern));   //Закраска квадрата


    return 0;
}
