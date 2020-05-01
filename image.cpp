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
    calcCell();
    calcSizeImage();
    //Создание макета и пера
    img = new QImage(width_img,height_img,QImage::Format_RGB32);
    p = new QPainter(img);
    p->setFont(QFont("Times", 36));                          //Установка шрифта

}


void image::calcCell()
{
    //Поиск наибольшего значения
    QList<int> sort_size;
    sort_size<<size_i_<<size_j_<<size_k_;
    qSort(sort_size.begin(),sort_size.end());
    int max_size = sort_size[2];

    sizeCell = 0;
    //Расчет производится по формуле:
    //     отступы по 5 пкс слева и справа
    //  +  размер названия массива+размер самого большого индекса, умноженного на размерность массива
    //  +  размер разделителя между индексами, умноженный на размерность - 1
    sizeCell = size_indent+size_name_array+dimension_*max_size*size_subscript_number+(dimension_-1)*size_comma;
}

void image::calcSizeImage()
{
    if (dimension_ == 1){
        width_img  = size_i_ * sizeCell;
        height_img = sizeCell;
    }else
        if (dimension_ == 2 ){
            width_img  = size_j_ * sizeCell;
            height_img = size_i_ * sizeCell;
        }else
            if (dimension_ == 3) {
                width_img  = size_k_ * sizeCell;
                height_img = size_i_*size_j_ * sizeCell+(size_i_-1)*size_indent_between_arr;
            }
}

void image::drawElements()
{
    for (int k=0;k<=size_k_;k++){
        for (int j=0;j<=size_j_;j++) {
            for (int i=0;i<=size_i_;i++) {

            }
        }
    }

}
