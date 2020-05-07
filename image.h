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
    void drawArrays(int dimension, int size_i, int size_j, int size_k, int size_cell);

    void fillAll();
    void fillTable(int i);
    void fillRow(int row, int numTable = 0);
    bool fillCell(int cell, int row = 0, int numTable = 0);




private:

    int size_cell_  = 0;

    int dimension_;
    int size_i_ = 0;
    int size_j_ = 0;
    int size_k_ = 0;
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
    const QString subscript_number[10] = {"\u2080","\u2081","\u2082","\u2083","\u2084","\u2085","\u2086","\u2087","\u2088","\u2089"};
    int size_indent             = 2*5;
    int size_indent_between_arr = 100;
};

#endif // IMAGE_H
