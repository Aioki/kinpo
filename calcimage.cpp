#include "calcimage.h"

CalcImage::CalcImage(int dimension, int countCell, int countRow, int countTable)
{
    arr_size <<countCell<<countRow<<countTable;
    arr_size.resize(dimension);

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

    QList<int> sort_size = arr_size.toList();
    qSort(sort_size.begin(),sort_size.end());
    int max_size = sort_size[sort_size.size()-1];
    int dimension_ = arr_size.size();

    //Подсчет количества цифр в числе
    QString count_max_size;
    count_max_size.setNum(max_size-1);


    //Расчет производится по формуле:
    //     отступы по 10 пкс слева и справа
    //  +  размер названия массива (в нашем случае - символа a)
    //  +  размер самого большого индекса, умноженного на размерность массива
    //  +  размер разделителя между индексами, умноженный на размерность - 1
    size_cell = 2*size_indent+
                size_name_array+
                (count_max_size.size()*size_subscript_number)*dimension_+
                (dimension_-1)*size_comma;
}

void CalcImage::calcSizeImage()
{

    //Рассчитать размер ячейки
    calcCell();

    //Ширина = количество ячеек, умноженного на размер ячейки
    width  = arr_size[0] * size_cell;

    //Если одномерный массив (1хi)
    if (arr_size.size() == 1){
        //Высота = размер ячейки
        height = size_cell;
    }else
        //Если двумерный массив(ixj)
        if (arr_size.size() == 2 ){
            //Высота = количество строк, умноженный на размер ячейки
            height = arr_size[1] * size_cell;
        }else
            //Если трехмерный массив(ixjxk)
            if (arr_size.size() == 3) {
                //Высота = количество строк * количество таблиц
                // +  отступы между массивами, умноженный на количество таблиц - 1
                height = arr_size[1]*arr_size[2] * size_cell+(arr_size[2]-1)*size_indent_between_arr;
            }

    //Добавление отступов слева и справа, сверху и снизу
    width+=(size_indent*2);
    height+=(size_indent*2);
}
