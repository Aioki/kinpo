#ifndef IMAGE_H
#define IMAGE_H

#include <QGuiApplication>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QObject>

class image
{
public:
    image();
    image(int dimension, int size_i, int size_j, int size_k);


    void calcCell();
    void calcSizeImage();
    void drawElements();


private:
    int height_img=0;
    int width_img =0;

    int sizeCell  = 0;

    int dimension_;
    int size_i_;
    int size_j_;
    int size_k_;
    QImage   *img;
    QPainter *p;
    QRect    tmp;

protected:
    const QString subscript_number[10] = {"\u2080","\u2081","\u2082","\u2083","\u2084","\u2085","\u2086","\u2087","\u2088","\u2089"};
    int size_name_array         = 21;
    int size_indent             = 2*5;
    int size_subscript_number   = 15;
    int size_comma              = 9;
    int size_indent_between_arr = 100;
};

#endif // IMAGE_H
