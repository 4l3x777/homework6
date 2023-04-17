# homework6 17.04.23
### Спроектировать 2-мерную разреженную бесконечную матрицу, заполненную значениями по умолчанию.

## Задание
+ Матрица должна хранить только занятые элементы - значения которых хотя бы раз 
присваивались. 
+ Присвоение в ячейку значения по умолчанию освобождает ячейку.
+ Необходимо уметь отвечать на вопрос - сколько ячеек реально занято?
+ Необходимо уметь проходить по всем занятым ячейкам. Порядок не имеет значения. Возвращается 
позиция ячейки и ее значение.
+ При чтении элемента из свободной ячейки возвращать значение по умолчанию.
+ При запуске программы необходимо создать матрицу с пустым значением 0, заполнить главную 
диагональ матрицы (от [0,0] до [9,9]) значениями от 0 до 9.
+ Второстепенную диагональ (от [0,9] до [9,0]) значениями от 9 до 0.
+ Необходимо вывести фрагмент матрицы от [1,1] до [8,8]. 
+ Между столбцами пробел. 
+ Каждая строка матрицы на новой строке консоли.
+ Вывести количество занятых ячеек.
+ Вывести все занятые ячейки вместе со своими позициями.
+ Опционально реализовать N-мерную матрицу.
+ Опционально реализовать каноническую форму оператора `=`, допускающую выражения 
```C++ 
Matrix<int, -1> matrix;
((matrix[100][100] = 314) = 0) = 217;
```

## Пример 1:
```C++
Matrix<int, -1> matrix;
assert(matrix.size() == 0);
auto a = matrix[0][0];
assert(a == -1);
assert(matrix.size() == 0);
matrix[100][100] = 314;
assert(matrix[100][100] == 314);
assert(matrix.size() == 1);

// print one line
// 100100314
for(auto c: matrix)
{
    for(auto value: c)
    {
        std::cout << value;
    }
    std::cout << std::endl;
}

// Operator's `=` canonical from
((matrix[100][100] = 314) = 0) = 217;

// print one line
// 100100217
for(auto c: matrix)
{
    for(auto value: c)
    {
        std::cout << value;
    }
    std::cout << std::endl;
}
 ```

## Пример 2:
```C++
// N-arn matrix (N = 7)
matrix[1000][999][998][997][996][995][994] = 7777;

// print one line
// 1000 999 998 997 996 995 994 7777
for(auto c: matrix)
{
    for(auto value: c)
    {
        std::cout << value << ' ';
    }
    std::cout << std::endl;
}
 ```

## Самоконтроль
+ индексация оператором `[]`
+ количество занятых ячеек должно быть 18 после выполнения примера выше

## Проверка
+ Задание считается выполненным успешно, если после анализа кода, установки пакета и запуска 
приложения появился фрагмент матрицы, количество ячеек и список всех значений с позициями.

## Native build
+ mkdir build
+ cd build
+ cmake ../
+ cmake --build . --config Release|Debug

## Install build
+ cmake --install .

## Run tests (GTest & BoostTest)
### Linux
+ cmake --build . --target test --config Release|Debug
### Windows
+ cmake --build . --target RUN_TESTS --config Release|Debug

## CPack (build ZIP & DEB)
+ cpack -C Release|Debug

## Проверка Linux
+ apt update && apt install -y matrix-0.0.X-Linux.deb
+ ./matrix

## Проверка Windows
+ unzip matrix-0.0.X-win(64|32).zip
+ matrix.exe