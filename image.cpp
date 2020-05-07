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

void image::fillTable(int i)
{
    int max_row = 0;
    if (dimension_ == 3) {
        max_row = size_j_;
    } else if (dimension_ == 2) {
        max_row = size_i_;
    }

    for (int row_ = 0; row_<max_row; row_ ++){
        fillRow(row_,i);
    }
    qDebug() << "Filled Table";
}

void image::fillRow(int row, int numTable)
{
    //TODO: Проверка входных данных, переделать под bool
    int max_cell = 0;

    if (dimension_ == 2) {
        max_cell = size_j_;
    } else if (dimension_ == 3) {
        max_cell = size_k_;
    }

    for (int cell = 0; cell < max_cell; ++cell) {
        fillCell(numTable,row,cell);
    }
    qDebug() << "Filled Row";
}

void image::fillCell(int i, int j, int k)
{
    //TODO: Проверка входных данных, переделать под bool

    QRgb white = qRgb(255,255,255);
    QRgb red   = qRgb(255,200,200);

    int start_x =size_indent+k*size_cell_;
    int start_y = size_indent+(size_j_*size_cell_+size_indent_between_arr)*i+j*size_cell_;

        for (int x = start_x; x < start_x + size_cell_; x++)
        {
            for (int y = start_y; y < start_y + size_cell_; y++)
            {
                if (img->pixel(x,y) == white)
                {
                    img->setPixel(x,y, red);
                }
            }
        }
    qDebug() << "Filled Cell";
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
    if (img->save("txt.png", "PNG"))
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

    qDebug() << "Draw Table";
}
