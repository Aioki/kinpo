#ifndef IMAGE_H
#define IMAGE_H

#include <QGuiApplication>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QObject>
#include "QDebug"

class image
{
public:

    image(int height, int width);

    void saveImage();
    bool drawArrays(int size_cell, int dimension, int countCell, int countRow = 0, int countTable = 0);

    void fillAll();
    bool fillTable(int i);
    bool fillRow(int row, int numTable = 0);
    bool fillCell(int cell, int row = 0, int numTable = 0);




private:

    QImage   *img;
    QPainter *p;
    QRect    tmp;

    /*\brief Рисует таблицу с элементами. Количество строк row и столбцов column.
     * Верхний левый угол таблицы указывается в start.
     * Если рисуется несколько таблиц, номер таблицы указывается в num
    */
    void drawTable(int row, int column, QPoint start, int num = -1);

    QString getElementName(int i,int j=-1,int k=-1);
    QString getSubscriptNumber(int num);

protected:

    int size_cell_  = 0;
    int dimension_;
    int count_cell_ = 0;
    int count_row_  = 0;
    int count_table_ = 0;

    const QString subscript_number[10] = {"\u2080","\u2081","\u2082","\u2083","\u2084","\u2085","\u2086","\u2087","\u2088","\u2089"};
    enum SIZE_INDENTS {
        SIZE_INDENT             = 2*5,
        SIZE_INDENT_BETWEEN_ARR = 100
    };

    QRgb COLOR_SELECTED_CELL    = qRgb(255,200,200);
};

#endif // IMAGE_H
