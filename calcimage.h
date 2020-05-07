#ifndef CALCIMAGE_H
#define CALCIMAGE_H

#include <QObject>
#include <QVector>
#include <QList>

//\brief Класс, расчитывающий размеры изображения по характеристикам массива - размера и размерности. Расчет происходит при объвлении класса
class CalcImage
{
public:
    CalcImage(int dimension, int countCell, int countRow=0, int countTable=0);

    int getSizeCell() const;
    int getWidth() const;
    int getHeight() const;

private:


    //\brief Расчитывает размер одной ячейки, из которых будет составлена таблица.
    void calcCell();
    //\brief Расчитывает конечный размер изображения
    void calcSizeImage();

    int height     = 0;
    int width      = 0;
    int size_cell  = 0;

    //\brief [0]-countCell, [1]-countRow, [2]-countTable, size() - dimension
    QVector<int> arr_size;

protected:
    const int size_name_array         = 21;
    const int size_indent             = 10;
    const int size_subscript_number   = 20;
    const int size_comma              = 10;
    const int size_indent_between_arr = 100;
};

#endif // CALCIMAGE_H
