#include "image.h"

image::image()
{

}

image::image(int dimension,int size_i, int size_j, int size_k)
{
    //Передача аргументов в класс
    dimension_ = dimension;
    size_i_ = size_i;
    size_j_ = size_j;
    size_k_ = size_k;

    //Расчет размера ячейки и изображения

    calcSizeImage();
    //Создание макета и пера
    img = new QImage(width_img,height_img,QImage::Format_RGB32);
    img->fill(Qt::white);                                    //Установка белого фона
    p = new QPainter(img);
    p->setFont(QFont("Times", 36));                          //Установка шрифта
    qDebug() << "Set painter";
    drawElements();
    saveImage();
}


void image::calcCell()
{
    //Поиск наибольшего значения
    QList<int> sort_size;
    sort_size<<size_i_<<size_j_<<size_k_;
    qSort(sort_size.begin(),sort_size.end());
    int max_size = sort_size[2];

    size_cell = 0;
    //Расчет производится по формуле:
    //     отступы по 5 пкс слева и справа
    //  +  размер названия массива+размер самого большого индекса, умноженного на размерность массива
    //  +  размер разделителя между индексами, умноженный на размерность - 1
    size_cell = size_indent+size_name_array+dimension_*max_size*size_subscript_number+(dimension_-1)*size_comma;
}

void image::calcSizeImage()
{
    calcCell();

    if (dimension_ == 1){
        width_img  = size_i_ * size_cell;
        height_img = size_cell;
    }else
        if (dimension_ == 2 ){
            width_img  = size_j_ * size_cell;
            height_img = size_i_ * size_cell;
        }else
            if (dimension_ == 3) {
                width_img  = size_k_ * size_cell;
                height_img = size_i_*size_j_ * size_cell+(size_i_-1)*size_indent_between_arr;
            }
    width_img+=size_indent*2;
    height_img+=size_indent*2;
}

void image::drawElements()
{
    //Определение ширины и высоты
    if (dimension_ == 1) {
        draw2DTable(1,size_i_,QPoint(size_indent,size_indent)); //Одна строка, i столбцов
    }
    if (dimension_ == 2) {
        draw2DTable(size_i_,size_j_,QPoint(size_indent,size_indent));//i строк, j столбцов
    }
    if (dimension_ == 3) {
        for (int z=0;z<size_i_;z++) {
            draw2DTable(size_j_,size_k_,QPoint(size_indent, size_indent+(size_j_*size_cell+size_indent_between_arr)*z));
            //TODO: Дорисовывать пунктирные линии
        }
    }



}

QString image::getElementName(int i, int j, int k)
{
   QString retval = "a";

   retval.append(getSubscriptNumber(i));

   if (dimension_ >= 2) {
       retval.append(","+getSubscriptNumber(j));
   }
   if (dimension_ == 3){
       retval.append(","+getSubscriptNumber(k));
   }
   return retval;
}

QString image::getSubscriptNumber(int num)
{
    QString tmp;
    QString retval;

    tmp.setNum(num);
    for (int i = 0;i<tmp.size();i++) {
        retval.append(subscript_number[tmp[i].digitValue()]);
    }
    return retval;
}

void image::saveImage()
{
    img->save("txt.png", "PNG");
    qDebug() << "Success";
}

void image::draw2DTable(int x, int y, QPoint start)
{
    //                  Строка, столбец, нач. позиция
    //Рисуем вертикальные линии(столбцы)
    for (int j=0;j<=y;j++) {
        p->drawLine(start.x()+j*size_cell,start.y(), start.x()+j*size_cell,start.y()+x*size_cell);
    }

    //Рисуем горизонтальные линии
    for (int i=0;i<=x;i++) {
        p->drawLine(start.x(),start.y()+i*size_cell, start.x()+y*size_cell,start.y()+i*size_cell);
    }




    qDebug() << "Draw 2D Table";
    draw2DElements(y,x,start);
}

void image::draw2DElements(int x, int y, QPoint start)
{
    //x- строка, y- столбец, начальная точка
    for (int i=0;i<x;i++) {
        for (int j=0;j<y;j++) {
            p->drawText(start.x()+size_cell*i,start.y()+size_cell*j,size_cell,size_cell, Qt::AlignCenter, QString("a"+subscript_number[0]+subscript_number[0])); //Печать элемента
        }
    }
    //TODO: Писать индексы согласно порядку с помощью функции getElementName
    qDebug() << "Draw text";
}
