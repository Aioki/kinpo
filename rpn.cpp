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


QVector<int> RPN::getValue()
{
    return parameters;
}

bool RPN::parceExp()
{
    //Разделяем выражение на операнды
    QStringList parce_expression = expression_.split(" ");
    //Пока операнды не закончились и нет ошибок
    while ((parce_expression.size() != 0) && isOk) {
        //Берем операнд
        QString cur_operand = parce_expression.takeFirst();
        //Если встречаем число
        if (isNum(cur_operand)){
            //Добавляем в стек
            stack.push_back(cur_operand.toInt());
        }
        //Если встречаем сложение
        if (cur_operand == "+") {
          //Выполняем сложение
          performCalc(Operation::ADD);
        }
        //Если встречаем вычитание
        if (cur_operand == "-") {
            //Выполняем вычитание
          performCalc(Operation::SUB);
        }
        //Если встречаем умножение
        if (cur_operand == "2*") {
            //Выполняем умножение
          performCalc(Operation::MUL);
        }
        //Если встречаем деление
        if (cur_operand == "/") {
            //Выполняем деление
            performCalc(Operation::DIV);
          }
        //Если встречаем инкремент
        if (cur_operand == "1++"){
            //Выполняем инкрементацию
            performCalc(Operation::INC);
        }
        //Если встречаем декремент
        if (cur_operand == "1--") {
            //Выполняем декрементацию
            performCalc(Operation::DEC);
        }
        //Если встречаем префиксный инкремент
        if (cur_operand == "++1"){
            //Выполняем префиксную инкрементацию
            performCalc(Operation::PRE_INC);
        }
        //Если встречаем префиксный декремент
        if (cur_operand == "--1") {
            //Выполняем префиксную декрементацию
            performCalc(Operation::PRE_DEC);
        }
        //Если встречаем "[" или "1*"
        if (cur_operand == "1*" || cur_operand == "["){
            //Добавляем в отдельный массив
            performCalc(Operation::INDEX);
        }
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

void RPN::performCalc(RPN::Operation cur)
{
    //.. Обьявляем переменные под операнды
    int a;
    int b;

    //Если операция сложения
    if (cur == Operation::ADD){
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
    if (cur == Operation::SUB){
        if (takeNum(a,b)){
            stack.push_back(b-a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции вычитания");
        }
    }
    if (cur == Operation::MUL){
        if (takeNum(a,b)){
            stack.push_back(a*b);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции умножения");
        }
    }
    if (cur == Operation::DIV){
        if (takeNum(a,b)){
            stack.push_back(b/a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции деления");
        }
    }
    if (cur == Operation::INC){
        if (takeNum(a)){
            stack.push_back(a++);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции инкрементации");
        }
    }
    if (cur == Operation::DEC){
        if (takeNum(a)){
            stack.push_back(a--);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции декрементации");
        }
    }
    if (cur == Operation::PRE_INC){
        if (takeNum(a)){
            stack.push_back(++a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции инкрементации ");
        }
    }
    if (cur == Operation::PRE_DEC){
        if (takeNum(a)){
            stack.push_back(--a);
        }
        else {
            genError("Ошибка. недостаточно операндов для операции декрементации");
        }
    }
    if (cur == Operation::INDEX){
        if (takeNum(a)){
            parameters.push_back(a);
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

