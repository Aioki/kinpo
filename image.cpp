#include "image.h"


image::image(int height, int width)
{

    //Создание макета и пера
    img = new QImage(width,height,QImage::Format_RGB16);//Format_RGB32QImage::Format_RGB16
    img->fill(Qt::white);                                    //Установка белого фона
    p = new QPainter(img);
    p->setFont(QFont("Times", 36));                          //Установка шрифта
    qDebug() << "Set painter";
}

void image::drawArrays(int dimension, int size_i, int size_j, int size_k, int size_cell)
{
    //Передача аргументов в класс
    dimension_ = dimension;
    size_i_ = size_i;
    size_j_ = size_j;
    size_k_ = size_k;
    size_cell_ = size_cell;

    //Определение ширины и высоты
    if (dimension_ == 1) {
        drawTable(1,size_i_,QPoint(size_indent,size_indent)); //Одна строка, i столбцов
    }
    if (dimension_ == 2) {
        drawTable(size_i_,size_j_,QPoint(size_indent,size_indent));//i строк, j столбцов
    }
    if (dimension_ == 3) {
        for (int z=0;z<size_i_;z++) {
            drawTable(size_j_,size_k_,QPoint(size_indent, size_indent+(size_j_*size_cell_+size_indent_between_arr)*z), z);
            //TODO: Дорисовывать пунктирные линии
        }
    }



}

QString image::getElementName(int i, int j, int k)
{
   QString retval = "a";

   retval.append(getSubscriptNumber(i));

   if (j != -1) {
       retval.append(","+getSubscriptNumber(j));
   }
   if (k != -1){
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
    if (img->save("txt.png", "PNG",0))
        qDebug() << "Success";
    else
        qDebug() << "Failed";
}

void image::drawTable(int row, int column, QPoint start, int num)
{
    //                  Строка, столбец, нач. позиция
    //                    Oy       Ox
    //Для каждой строки
    for (int i=0;i<row;i++){
        //Для каждого столбца
        for(int j=0;j<column;j++){
            //Расчитываем начальную позицию квадрата
            int x = start.x()+j*size_cell_;
            int y = start.y()+i*size_cell_;
            QRect cur_square(x,y,size_cell_,size_cell_);
            //Нарисовать квадрат
            p->drawRect(cur_square);
            //Нарисовать элемент
            if (dimension_ == 1){
                p->drawText(cur_square, Qt::AlignCenter,  getElementName(j));
            } else if (num==-1) {
                p->drawText(cur_square, Qt::AlignCenter,  getElementName(i,j));
             } else {
                p->drawText(cur_square, Qt::AlignCenter,  getElementName(num,i,j));
            }
        }
    }

    qDebug() << "Draw 2D Table";
}
