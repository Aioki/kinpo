#include "image.h"

image::image()
{

}

image::image(int _dimension,int _size_i, int _size_j, int _size_k)
{
    dimension = _dimension;
    size_i = _size_i;
    size_j = _size_j;
    size_k = _size_k;

    //Поиск наибольшего значения
    QList<int> sort_size;
    sort_size<<size_i<<size_j<<size_k;
    qSort(sort_size.begin(),sort_size.end());
    int max_size = sort_size[2];

    calcCell(dimension,max_size);
    calcSizeImage();
    img = new QImage(width_img,height_img,QImage::Format_RGB32);
    p = new QPainter(img);
    p->setFont(QFont("Times", 36));                          //Установка шрифта
}


void image::calcCell(int dimension, int max_size)
{
    widthCell = 0;
    //Расчет производится по формуле:
    //     отступы по 5 пкс слева и справа
    //  +  размер названия массива+размер самого большого индекса, умноженного на размерность массива
    //  +  размер разделителя между индексами, умноженный на размерность - 1
    widthCell = size_indent+size_name_array+dimension*max_size*size_subscript_number+(dimension-1)*size_comma;
    heightCell = widthCell;
}

void image::calcSizeImage()
{
    if (dimension == 1){
        width_img  = size_i * widthCell;
        height_img = heightCell;
    }else
        if (dimension == 2 ){
            width_img  = size_j * widthCell;
            height_img = size_i * heightCell;
        }else
            if (dimension == 3) {
                width_img  = size_k * widthCell;
                height_img = size_i*size_j * heightCell+(size_i-1)*size_indent_between_arr;
            }
}

void image::drawElements()
{
    for (int k=0;k<=size_k;k++){
        for (int j=0;j<=size_j;j++) {
            for (int i=0;i<=size_i;i++) {

            }
        }
    }

}
