#include "calcimage.h"

CalcImage::CalcImage(int dimension, int size_i, int size_j, int size_k)
{
    arr_index <<size_i<<size_j<<size_k;
    arr_index.resize(dimension);

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
    //Поиск наибольшего значения и

    QList<int> sort_size;
    sort_size.fromVector(arr_index);
    qSort(sort_size.begin(),sort_size.end());
    int max_size = sort_size[sort_size.size()-1];
    int dimension_ = arr_index.size();

    size_cell = 0;

    //Расчет производится по формуле:
    //     отступы по 10 пкс слева и справа
    //  +  размер названия массива (в нашем случае - символа a)
    //  +  размер самого большого индекса, умноженного на размерность массива
    //  +  размер разделителя между индексами, умноженный на размерность - 1
    size_cell = 2*size_indent+
                size_name_array+
                dimension_*max_size*size_subscript_number+
                (dimension_-1)*size_comma;
}

void CalcImage::calcSizeImage()
{

    //Рассчитать размер ячейки
    calcCell();
    //Если одномерный массив (1хi)
    if (arr_index.size() == 1){
        //Ширина = размер i, умноженного на размер ячейки
        width  = arr_index[0] * size_cell;
        //Высота = размер ячейки
        height = size_cell;
    }else
        //Если двумерный массив(ixj)
        if (arr_index.size() == 2 ){
            //Ширина = размер j, умноженный на размер ячейки
            width  = arr_index[1] * size_cell;
            //Высота = размер i, умноженный на размер ячейки
            height = arr_index[0] * size_cell;
        }else
            //Если трехмерный массив(ixjxk)
            if (arr_index.size() == 3) {
                //Ширина = размер k, умноженный на размер ячейки
                width  = arr_index[2] * size_cell;
                //Высота = размер i * j (количество двумерных массивов)
                // +  отступы между массивами, умноженный на количество двумерных массивов - 1
                height = arr_index[0]*arr_index[1] * size_cell+(arr_index[0]-1)*size_indent_between_arr;
            }
    //Добавление отступов слева и справа, сверху и снизу
    width+=(size_indent*2);
    height+=(size_indent*2);
}
