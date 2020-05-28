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
    enum SIZE_ELEM_PIC {
        SIZE_NAME_ARRAY         = 21,
        SIZE_INDENT             = 10,
        SIZE_SUBSCRIPT_NUMBER   = 20,
        SIZE_COMMA              = 10,
        SIZE_INDENT_BETWEEN_ARR = 100
    };
};

#endif // CALCIMAGE_H
