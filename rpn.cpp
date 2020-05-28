#include "rpn.h"

RPN::RPN(QString str)
{
    //Задать выражение
    expression_ = str;
    //Обработать выражение
    parceExp();
}

QString RPN::getError()
{
    return error;
}


QVector<int> RPN::getIndexes()
{
    return indexes;
}

bool RPN::parceExp()
{
    //Разделяем выражение на операнды
    QStringList parce_expression = {};
    if (!expression_.isEmpty()){
        parce_expression = expression_.split(" ");
    }

    //Пока операнды не закончились и нет ошибок
    while ((parce_expression.size() != 0) && isOk) {
        //Берем операнд
        QString cur_operand = parce_expression.takeFirst();
        //Если встречаем число
        if (isNum(cur_operand)){
            //Добавляем в стек
            stack.push_back(cur_operand.toInt());
        } else
        //Если встречаем сложение
        if (cur_operand == "+") {
          //Выполняем сложение
          performCalc(OPERATION::ADD);
        } else
        //Если встречаем вычитание
        if (cur_operand == "-") {
            //Выполняем вычитание
          performCalc(OPERATION::SUB);
        } else
        //Если встречаем умножение
        if (cur_operand == "2*") {
            //Выполняем умножение
          performCalc(OPERATION::MUL);
        } else
        //Если встречаем деление
        if (cur_operand == "/") {
            //Выполняем деление
            performCalc(OPERATION::DIV);
          } else
        //Если встречаем инкремент
        if (cur_operand == "1++"){
            //Выполняем инкрементацию
            performCalc(OPERATION::INC);
        } else
        //Если встречаем декремент
        if (cur_operand == "1--") {
            //Выполняем декрементацию
            performCalc(OPERATION::DEC);
        } else
        //Если встречаем префиксный инкремент
        if (cur_operand == "++1"){
            //Выполняем префиксную инкрементацию
            performCalc(OPERATION::PRE_INC);
        } else
        //Если встречаем префиксный декремент
        if (cur_operand == "--1") {
            //Выполняем префиксную декрементацию
            performCalc(OPERATION::PRE_DEC);
        } else
        //Если встречаем "[" или "1*"
        if (cur_operand == "1*" || cur_operand == "["){
            //Добавляем в отдельный массив
            performCalc(OPERATION::INDEX);
        } else
            genError("Ошибка. Встречен неизвестный операнд: "+cur_operand);
    }
    //Если в стеке остались значения
    if (stack.size() != 0) {
        genError("Ошибка. Выражение задано неправильно - недостаточно операций над операндами");
        //Сообщить об ошибке
    }
    return isOk;
}

bool RPN::takeNum(int &a)
{
    //Если стэк пустой
    if (stack.isEmpty()){
        //Вернуть остутствие числа
        return false;
    } else  {
        //Иначе вернуть первое число из стэка
        a = stack.takeLast();
        //Вернуть присутствие числа
        return true;
    }
}

bool RPN::takeNum(int &a, int &b)
{
    //Если стек пустой
    if (stack.isEmpty()){
        //Возвращаем отсутсвие числа
        return false;
    } else
        //Иначе берем число из начала стека
        a = stack.takeLast();
 //Если стек пустой
    if (stack.isEmpty()){
        //Возвращаем отсутсвие числа
        return false;
    } else{
        //Иначе берем число из начала стека
        b = stack.takeLast();
    }

    return true;

}

void RPN::genError(QString str)
{
    //Остановить действия
    isOk = false;
    //Запись ошибки
    error=str;
    //Обнуление стеков
    expression_.resize(0);
    stack.resize(0);
}

void RPN::performCalc(RPN::OPERATION cur)
{
    //.. Обьявляем переменные под операнды
    int a;
    int b;

    //Если операция сложения
    if (cur == OPERATION::ADD){
        //Если операнды получилось взять
        if (takeNum(a,b)){
            //Добавляем в начало стека
            stack.push_back(a+b);
        }
        else {
            //Иначе информируем о нехватке операндов
            genError("Ошибка. недостаточно операндов для операции сложения");
        }
    }
    if (cur == OPERATION::SUB){
        if (takeNum(a,b)){
            stack.push_back(b-a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции вычитания");
        }
    }
    if (cur == OPERATION::MUL){
        if (takeNum(a,b)){
            stack.push_back(a*b);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции умножения");
        }
    }
    if (cur == OPERATION::DIV){
        if (takeNum(a,b)){
            stack.push_back(b/a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции деления");
        }
    }
    if (cur == OPERATION::INC){
        if (takeNum(a)){
            stack.push_back(a++);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции инкрементации");
        }
    }
    if (cur == OPERATION::DEC){
        if (takeNum(a)){
            stack.push_back(a--);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции декрементации");
        }
    }
    if (cur == OPERATION::PRE_INC){
        if (takeNum(a)){
            stack.push_back(++a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции инкрементации ");
        }
    }
    if (cur == OPERATION::PRE_DEC){
        if (takeNum(a)){
            stack.push_back(--a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции декрементации");
        }
    }
    if (cur == OPERATION::INDEX){
        if (takeNum(a)){
            indexes.push_back(a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции обращения к элементу массива");
        }
    }
}

bool RPN::isNum(QString num)
{
    //Пока есть символы
    while (num.size()!=0) {
        //Если первый символ не цифра
        if (!num[0].isDigit()){
            //То это не число
            return false;
        }
        //Удалить первый символ
        num.remove(0,1);
    }
    //Если символов не было найдено, то это число
    return true;
}

