#include "calcimage.h"

CalcImage::CalcImage(int dimension, int size_i, int size_j, int size_k)
{
    //Передача аргументов в класс
    dimension_ = dimension;
    size_i_ = size_i;
    size_j_ = size_j;
    size_k_ = size_k;
    //Расчет размера изображения
    calcSizeImage();
}

int CalcImage::getSizeCell() const
{
    return size_cell;
}

int CalcImage::getWidth() const
{
    return width;
}

int CalcImage::getHeight() const
{
    return height;
}

void CalcImage::calcCell()
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

void CalcImage::calcSizeImage()
{
    calcCell();

    if (dimension_ == 1){
        width  = size_i_ * size_cell;
        height = size_cell;
    }else
        if (dimension_ == 2 ){
            width  = size_j_ * size_cell;
            height = size_i_ * size_cell;
        }else
            if (dimension_ == 3) {
                width  = size_k_ * size_cell;
                height = size_i_*size_j_ * size_cell+(size_i_-1)*size_indent_between_arr;
            }
    width+=size_indent*2;
    height+=size_indent*2;
}
