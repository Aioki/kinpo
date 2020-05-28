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

bool image::drawArrays(int size_cell, int dimension, int countCell, int countRow, int countTable)
{
    if (size_cell <= 0 || dimension < 1 || dimension > 3 || countCell < 0 || countRow <0 || countTable <0) {
        return false;
    }

    //Передача аргументов в класс
    dimension_ = dimension;
    count_cell_ = countCell;
    count_row_ = countRow;
    count_table_ = countTable;

    size_cell_ = size_cell;

    //Определение ширины и высоты
    if (dimension_ == 1) {
        drawTable(1,countCell,QPoint(SIZE_INDENT,SIZE_INDENT)); //Одна строка, i столбцов
    }
    if (dimension_ == 2) {
        drawTable(countRow,countCell,QPoint(SIZE_INDENT,SIZE_INDENT));//i строк, j столбцов
    }
    if (dimension_ == 3) {
        for (int curTable=0;curTable<countTable;curTable++) {

            int start_x = SIZE_INDENT;
            int start_y = SIZE_INDENT+curTable*(count_row_*size_cell_+SIZE_INDENT_BETWEEN_ARR);

            drawTable(countRow,countCell,QPoint(start_x, start_y), curTable);
            //TODO: Дорисовывать пунктирные линии
        }
    }
    return true;
}

void image::fillAll()
{

    if (dimension_ == 3) {
        for (int z=0;z<count_table_ ;z++) {
            fillTable(z);
        }
    }
    else
        fillTable(0);

    qDebug() << "Filled All";

}

bool image::fillTable(int i)
{

    if (dimension_ == 1){
        fillRow(0);
    } else
        for (int cur_row = 0; cur_row < count_row_; cur_row ++){
            fillRow(cur_row,i);
        }
    qDebug() << "Filled Table";
    return true;
}

bool image::fillRow(int row, int numTable)
{
    for (int cell = 0; cell < count_cell_; ++cell) {
        fillCell(cell,row,numTable);
    }
    qDebug() << "Filled Row";
    return true;
}

bool image::fillCell(int cell, int row, int numTable)
{

    QRgb white = qRgb(255,255,255);

    int start_x =SIZE_INDENT+cell*size_cell_;
    int start_y = SIZE_INDENT+(count_row_*size_cell_+SIZE_INDENT_BETWEEN_ARR)*numTable+row*size_cell_;

    for (int x = start_x; x < start_x + size_cell_; x++)
    {
        for (int y = start_y; y < start_y + size_cell_; y++)
        {
            if (img->pixel(x,y) == white)
            {
                img->setPixel(x,y, COLOR_SELECTED_CELL);
            }
        }
    }
    qDebug() << "Filled Cell";
    return true;
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
    for (int cur_row=0;cur_row<row;cur_row++){
        //Для каждого столбца
        for(int cur_column=0;cur_column<column;cur_column++){
            //Расчитываем начальную позицию квадрата
            int x = start.x()+cur_column*size_cell_;
            int y = start.y()+cur_row*size_cell_;
            QRect cur_square(x,y,size_cell_,size_cell_);
            //Нарисовать квадрат
            p->drawRect(cur_square);
            //Нарисовать элемент
            if (dimension_ == 1){
                p->drawText(cur_square, Qt::AlignCenter,  getElementName(cur_column));
            } else if (dimension_ ==2) {
                p->drawText(cur_square, Qt::AlignCenter,  getElementName(cur_row,cur_column));
            } else {
                p->drawText(cur_square, Qt::AlignCenter,  getElementName(num,cur_row,cur_column));
            }
        }
    }

    qDebug() << "Draw Table";
}
