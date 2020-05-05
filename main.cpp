#include "main.h"

//a\u2081\u2082\u2083
//36pt = 24 пкс//17 пкс высота
//36pt = 21 пкс//9//12//12 ширина

int main(int argc, char *argv[])
{
    QGuiApplication app( argc, argv );                      //Инициализация ядра приложения

    int dimension = 3;
    int size_i    = 1;
    int size_j    = 2;
    int size_k    = 3;

    //Расчет изображения
    CalcImage size_image(dimension,size_i,size_j,size_k);

    image img1(3,4,2,3);


    //p.fillRect(tmp,QBrush(Qt::white,Qt::SolidPattern));   //Закраска квадрата


    return 0;
}

int calcCellForTable(int dimension, int size_i,int size_j, int size_k){
    //Поиск наибольшего значения
    QList<int> sort_size;
    sort_size<<size_i<<size_j<<size_k;
    qSort(sort_size.begin(),sort_size.end());
    int max_size = sort_size[2];

    int size_cell = 0;
    //Расчет производится по формуле:
    //     отступы по 5 пкс слева и справа
    //  +  размер названия массива
    //  +  размер самого большого индекса, умноженного на размерность массива
    //  +  размер разделителя между индексами, умноженный на размерность - 1
    size_cell = size_indent+size_name_array+dimension*max_size*size_subscript_number+(dimension-1)*size_comma;

    //Проверка расчета ячейки.
    if (size_cell ==0) {
        return -1;
    } else {
        return size_cell;
    }
}

bool calcSizeImage(int dimension, int size_cell, int *width, int *height)
{
    if (dimension == 1){
        *width  = size_i * size_cell;
        *height = size_cell;
    }else
        if (dimension_ == 2 ){
            width_img  = size_j_ * size_cell;
            height_img = size_i_ * size_cell;
        }else
            if (dimension_ == 3) {
                width_img  = size_k_ * size_cell;
                height_img = size_i_*size_j_ * size_cell+(size_i_-1)*size_indent_between_arr;
            }
    width_img+=size_indent*2;
    height_img+=size_indent*2;
}
