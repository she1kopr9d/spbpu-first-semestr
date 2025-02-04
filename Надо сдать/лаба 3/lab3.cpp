/**
 * Практическое занятие №3. Встроенные массивы. Динамическое выделение памяти.
 * Простейшие алгоритмы сортировки и поиска. Сложные указатели.
 */

#include  <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <limits>
#include <vector>

int sum(int* pArray, int lenght){
    int summa = 0;
    for (int i = 0; i < lenght; i++)
        summa += *(pArray++);
    return summa;
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

double middleValue(int arr[], int n){
    int s = sum(&arr[0], n);
    return s / double(n);
}

void print1DArrayInt(int arr[], int n){
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
}

bool isDuplicate(int arr[], int n, int num) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == num) {
            return true;
        }
    }
    return false;
}

unsigned char generateRandomByte() {
    return static_cast<unsigned char>(std::rand() % 256);
}

unsigned char count(char string[], int n, char symbol){
    int c = 0;
    for (int i = 0; i < n; i++)
        c += static_cast<int>(string[i] == symbol);
    return c;
}

int main()
{
    /**
     * Задание 1. Встроенные массивы.
     */

    /**
     * Задание 1.1.
     *
     * Объявите трехмерный N*M*K массив и сформируйте значения
     * элементов, указанные на иллюстрации ниже, с помощью инициализации при
     * объявлении.
     *
     *                   |--------|     
     *                 / |3  3  3 |     
     *               |---------|3 |
     *             / | 2  2  2 |3 |
     *            |---------|2 |__|
     *            | 1  1  1 |2 | /
     *            | 1  1  1 |__| 
     *            | 1  1  1 | /
     *            |_________|
     */
    std::cout << "Ex 1.1" << std::endl;
    int arr1[3][3][3] = {
        {
            {1, 1, 1}, 
            {1, 1, 1}, 
            {1, 1, 1}
        },
        {
            {2, 2, 2}, 
            {2, 2, 2}, 
            {2, 2, 2}
        },
        {
            {3, 3, 3}, 
            {3, 3, 3}, 
            {3, 3, 3}
        }
    };
    /**
     * Задание 1.2.
     *
     * Объявите неинициализированный массив и присвойте значения элементам с
     * помощью кода так, чтобы в итоге получился такой же массив, как в задании
     * 1.1.
     */
    std::cout << "Ex 1.2" << std::endl;
    int arr2[3][3][3];
    for (int n = 0; n < 3; n++)
    {
        for (int m = 0; m < 3; m++)
        {
            for (int k = 0; k < 3; k++)
            {
                arr2[n][m][k] = n+1;
            }
        }
    }
    /**
     * Задание 1.3.
     *
     * Напишите код, с помощью которого можно найти сумму элементов массива,
     * полученного в задании 1.
     */
    std::cout << "Ex 1.3" << std::endl;
    // TODO: отладить, выдает неправильно - решил
    std::cout << sum(&arr2[0][0][0], sizeof(arr2)/sizeof(***arr2)) << std::endl;
    /**
     * Задание 1.4.
     *
     * Проинициализируйте массив при объявлении следующим образом:
     *
     *                   |--------|     
     *                 / |3  0  0 |     
     *               |---------|0 |
     *             / | 2  0  0 |0 |
     *            |---------|0 |__|
     *            | 1  0  0 |0 | /
     *            | 0  0  0 |__| 
     *            | 0  0  0 | /
     *            |_________|
     *
     * Как это можно сделать наиболее коротким (в смысле количества кода)
     * образом?
     */
    std::cout << "Ex 1.4" << std::endl;
    int arr3[3][3][3] = {{{1}}, {{2}}, {{3}}}; // TODO: задать значения при инициализации - сделал
    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            for (int k = 0; k < 3; k ++){
                std::cout << arr3[i][j][k] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    for (int i = 0; i < 3; i++){
        arr3[i][0][0] = i+1;
    }

    for (int i = 0; i < 3; i ++){
        for (int j = 0; j < 3; j ++){
            for (int k = 0; k < 3; k ++){
                std::cout << arr3[i][j][k] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "\n";
    }

    /**
     * Задание 1.5. Инициализация массивов строковыми литералами.
     * 
     * Объявите и проинициализируйте строковыми литералами два массива:
     * двухмерный массив и массив указателей. Поясните разницу в использовании
     * элементов таких массивов.
     */

    /**
     * Задание 2. Динамическое выделение памяти.
     */

    /**
     * Задание 2.1.
     *
     * Создайте динамический двухмерный массив с размерностями, вычисляемыми в
     * процессе выполнения программы - N*M, эти размерности можно сформировать
     * случайно в некотором диапазоне или ввести с консоли.
     *
     * Задайте значения элементов помощью генератора случайных чисел. 
     *
     * Найдите сумму элементов.
     *
     * Подсказка 1: для генерации случайных чисел используйте функцию
     * стандартной библиотеки - rand() (<cstdlib>).
     *
     * Подсказка 2: На самом деле те значения, которые создаются генератором
     * случайных чисел являются «псевдослучайными», то есть при двух
     * последовательных запусках приложения Вы получаете две одинаковые
     * последовательности значений.
     *
     * Для того чтобы генерируемые "случайные" значения были разными при каждом
     * запуске приложения используйте функции стандартной библиотеки srand()
     * (<cstdlib>) и time() (<ctime>).
     *
     * Функция srand() осуществляет «привязку» начала генерации к указанному в
     * качестве параметра значению.
     *
     * Функция time() задает эту точку отсчета, считывая текущее время.
     */
    std::cout << "Ex 2.1" << std::endl;
    srand(time(0));

    int N, M;
    std::cout << "Введите количество строк (N): ";
    std::cin >> N;
    std::cout << "Введите количество столбцов (M): ";
    std::cin >> M;

    int** arr = new int*[N];  // массив указателей строки
    for (int i = 0; i < N; i++) {
        arr[i] = new int[M];  // выделяем память под M элементов
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            arr[i][j] = rand() % 100 + 1;
        }
    }

    int sum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            sum += arr[i][j];
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << sum << std::endl;

    
    /**
     * Задание 2.2.
     *
     * В сформированном массиве отсортируйте каждую строку по убыванию
     * значений. Используйте сортировку "выбором".
     */
    std::cout << "Ex 2.2" << std::endl;
    for (int i = 0; i < N; i++) {
        selectionSort(arr[i], N);
        for (int j = 0; j < M; j++) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << "\n";
    }

    /**
     * Задание 2.3.
     *
     * Объявите одномерный массив размерностью N. 
     *
     * Сформируйте значение i-ого элемента одномерного массива  равным среднему
     * значению элементов i-ой строки двухмерного массива.
     */
    std::cout << "Ex 2.3" << std::endl;
    double* arr_sr = new double[N];
    for (int i = 0; i < N; i++){
        arr_sr[i] = middleValue(arr[i], N);
        std::cout << arr_sr[i] << " ";
    }
    std::cout << "\n";

    /**
     * Задание 2.4. 
     *
     * Убедитесь, что вся выделенная память очищена.
     *
     * Чтобы убедиться в этом, скомпилируйте программу с включенной проверкой
     * утечек памяти - с ключом `-fsanitize=address`:
     *
     * `gcc <ваши обычные флаги> -fsanitize=address lab3.cpp`
     *
     * Если после выполнении программы выдаются сообщения об утечках, это
     * означает, что где-то не удалена выделенная память.
     */
    std::cout << "Ex 2.4" << std::endl;
    for (int i = 0; i < N; i++) {
        delete[] arr[i];
    }
    delete[] arr;
    delete[] arr_sr;

    /**
     * Задание 3.
     */

    /**
     * Задание 3.1. Онлайн-упорядочивание.
     *
     * Напишите фрагмент кода, который вводит N целых чисел с помощью потока
     * ввода в объявленный Вами встроенный одномерный массив, каждый раз
     * упорядочивая полученное значение по возрастанию.
     *
     * Дайте оценку количества сравнений и перестановок при вводе всех чисел
     * относительно N.
     *
     * Постарайтесь, чтобы и сравнений, и перестановок было не больше, чем
     * k*N^2, где k - некоторое число.
     */
    {
        std::cout << "Ex 3.1" << std::endl;
        int N;
        std::cout << "Введите количество чисел N: ";
        std::cin >> N;

        int* arr = new int[N];  

        for (int i = 0; i < N; i++) {
            std::cout << "Введите число " << i + 1 << ": ";
            std::cin >> arr[i];

            int j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                j--;
            }

            std::cout << "Массив после ввода " << i + 1 << " числа: ";
            for (int k = 0; k <= i; k++) {
                std::cout << arr[k] << " ";
            }
            std::cout << std::endl;
        }

        delete[] arr;
    }
    /**
     * Задание 3.2. Простой поиск.
     *
     * Модифицируйте предыдущее задание следующим образом:очередное значение
     * вводится в массив только при условии, что там еще такого нет (то есть
     * дубли игнорируются).
     */
    {
        std::cout << "Ex 3.2" << std::endl;
        int N;
        std::cout << "Введите количество чисел N: ";
        std::cin >> N;

        int* arr = new int[N];
        int selectNum;

        for (int i = 0; i < N; i++) {
            std::cout << "Введите число " << i + 1 << ": ";
            std::cin >> selectNum;
            if (isDuplicate(arr, N, selectNum) == true){
                i--;
                continue;
            }
            arr[i] = selectNum;

            int j = i;
            while (j > 0 && arr[j - 1] > arr[j]) {
                std::swap(arr[j - 1], arr[j]);
                j--;
            }

            std::cout << "Массив после ввода " << i + 1 << " числа: ";
            for (int k = 0; k <= i; k++) {
                std::cout << arr[k] << " ";
            }
            std::cout << std::endl;
        }

        delete[] arr;
    }     
    /**
     * Задание 4. Сортировка строк.
     *
     * С помощью данной заготовки напишите программу, которая:
     *
     * 1. вводит строки с клавиатуры с помощью cin>>... в объявленный Вами
     *    двухмерный встроенный массив 5*80 элементов типа char; признаком конца
     *    ввода является символ * (то есть строка - "*") или заполнение массива
     *    (больше свободных строк нет);
     * 2. сортирует строки в алфовитном порядке и выводит на экран.
     *
     * Пояснение: крайне не рекомендуется для сортировки сложных объектов
     * физически перемещать их в памяти. Намного эффективнее завести массив
     * указателей на соответствующие строки и перемещать только указатели.
     *
     * Подсказка: для лексиграфического сравнения строк пользуйтесь функцией
     * стандартной библиотеки strcmp(...), заголовочный файл <string>.
     */

    {
        /** Определите необходимые значения как константы */

        // STOP_STRING  -  "*"  //признак "прекратить ввод"
        // M  -  80 //максимальный размер одной строки
        // N  -  10 //максимальное количество строк в массиве

        /** 
         * Объявите двухмерный массив с именем cBuffer типа char и размерностью
         * N*M.
         */
        std::cout << "Ex 4.0" << std::endl;
        #define STOP_STRING "*"
        #define M 80
        #define N 10

        char cBuffer[N * M] = {};
        
        /**
         * Объявите массив (с именем cPointers) указателей на строки
         * размерностью N.
         */

        char* cPointers[N] = {};
        for (int i = 0; i < N; i++) {
            cPointers[i] = &cBuffer[i * M];
        }

        /** 
         * Цикл ввода строк:
         * 1. выведите приглашение для ввода; 
         * 2. пока не введена строка STOP_STRING или не заполнен весь массив; 
         */

        int nIndex = 0;

        {
            /** ввод строки в массив cBuffer: */
                                    
            /** если введена строка - признак окончания, то выйти из цикла */

            /** Присвойте элементу массива cPointers с индексом nIndex */

            /** указатель на строку с номером nIndex в массиве cBuffer */
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            while (nIndex < N) {
                std::cout << "Введите строку (или '" << STOP_STRING << "' для завершения): ";
                std::cin.getline(cPointers[nIndex], M);

                if (strcmp(cPointers[nIndex], STOP_STRING) == 0) {
                    break;
                }

                nIndex++;
            }
        }


        /** Выдать диагностику о том, что прием строк завершен.*/
        std::cout << "Прием строк завершен. Всего строк: " << nIndex << std::endl;

        /**
         * Теперь сортируем строки.
         *
         * Необходимо использовать сортировку строк по методу "всплывающего
         * пузырька" в порядке возрастания. 
         *
         * На каждой итерации - промежуточная печать отсортированных строк.
         */
        for (int i = 0; i < nIndex - 1; i++) {
            for (int j = 0; j < nIndex - i - 1; j++) {
                if (strcmp(cPointers[j], cPointers[j + 1]) > 0) {
                    char* temp = cPointers[j];
                    cPointers[j] = cPointers[j + 1];
                    cPointers[j + 1] = temp;
                }
            }

            std::cout << "Состояние после итерации " << i + 1 << ": " << std::endl;
            for (int k = 0; k < nIndex; k++) {
                std::cout << cPointers[k] << std::endl;
            }
        }

        std::cout << "Сортировка завершена. Итоговый список строк: " << std::endl;
        for (int i = 0; i < nIndex; i++) {
            std::cout << cPointers[i] << std::endl;
        }
    }

/*
    /**
     * Задание 5. Динамические строки.
     *
     * Реализуйте задание №4, используя не встроенные, а динамические массивы
     * (массив?). Так как строки могут быть разной длины, эффективным решением
     * было бы отводить под каждую строку ровно столько байтов, сколько
     * требуется для ее хранения.
     *
     * Реализуйте это задание так, чтобы пользователь мог ввести строку любой
     * длины (которая помещается в память компьютера - читайте: неограниченной
     * длины).
     *
     * При этом необходимые параметры (количество строк) сформируйте с помощью
     * потока ввода.
     */

    {
        std::cout << "Ex 5.0" << std::endl;
        int nStringNumber;

        /** Цикл ввода строк: */

        std::cout << "Введите количество строк: ";
        std::cin >> nStringNumber;

        // TODO: использовать массив - исправил
        char** strings = new char * [nStringNumber];

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        char symbol_buffer;
        int cap;
        int index;
        char * buffer;

        for (int i = 0; i < nStringNumber; i++) {
            std::cout << "Введите строку " << i + 1 << ": ";

            // TODO: реализовать ввод без string (vector и пр) - управлять памятью вручную - выполнил
            cap = 2;
            index = 0;
            buffer = new char[cap];
            buffer[cap-1] = '\0';
            symbol_buffer = std::cin.get();
            while (symbol_buffer != '\n'){
                buffer[index++] = symbol_buffer;
                if (index+1 == cap){
                    cap *= 2;
                    char * second_buffer = new char[cap];
                    for(int j = 0; j < cap/2; j++){
                        second_buffer[j] = buffer[j];
                    }
                    delete[] buffer;
                    buffer = second_buffer;
                }
                symbol_buffer = std::cin.get();
            }
            buffer[index] = '\0';
            strings[i] = buffer;
        }

        /** 
         * Цикл сортировки строк по методу "всплывающего пузырька" в порядке
         * возрастания кода первого символа.
         */

        for (int i = 0; i < nStringNumber - 1; i++) {
            for (int j = 0; j < nStringNumber - i - 1; j++) {
                if (std::strcmp(strings[j], strings[j + 1]) > 0) {
                    char* temp = strings[j];
                    strings[j] = strings[j + 1];
                    strings[j + 1] = temp;
                }
            }

            std::cout << "Состояние после итерации " << i + 1 << ":" << std::endl;
            for (int k = 0; k < nStringNumber; k++) {
                std::cout << strings[k] << std::endl;
            }
        }

        std::cout << "Сортировка завершена. Итоговый список строк:" << std::endl;
        for (int i = 0; i < nStringNumber; i++) {
            std::cout << strings[i] << std::endl;
        }

        /** Освобождение занятой памяти */
        for (int i = 0; i < nStringNumber; i++) {
            delete[] strings[i];
        }
        delete[] strings;
    }

    /** 
     * Задание 6. Работа со строками.
     *
     * Реализуйте следующую программу. Пользователь вводит строку (любого
     * размера), после чего пользователю выводится на консоль следующее
     * изображение, где его ввод помещен в "speech bubble":
     *
     *  _____________________________________
     * / Here user input is shown. This line \ 
     * \ Here user input is shown. This line must be at most 40 characters long. /
     *  ------------------------------------
     *     \
     *      \
     *        /\_/\  (
     *       ( ^.^ ) _)
     *         \"/  (
     *       ( | | )
     *      (__d b__)
     *
     *  При этом длина строки в "облачке" должна быть не более 40 символов, при
     *  этом слова должны переноситься аккуратно. Это означет, что не должно
     *  быть переносов в центре слова (если только это слово не больше 40
     *  символов).
     *
     *  Дизайн облачка и ASCII-арт допустимо поменять по усмотрению.
     *
     *  Подсказка: обратите внимание на конкатенацию строковых литералов в
     *  языке С, это позволит задавать подобные рисунки так, чтобы они
     *  адекватно выглядели в коде.
     */

    {  
        std::cout << "Ex 6.0" << std::endl;
        // Ввод текста от пользователя
        std::cout << "Введите строку: ";

        int max_lenght = 40;

        int line_cap = 1;
        char ** lines = new char * [line_cap];
        for (int i = 0; i < line_cap; i++){
            lines[i] = new char[max_lenght];
            lines[i][0] = '\0';
        }
        int size = 0;

        int x = 0;
        int y = 0;
        int b_i = 0;
        int ml = 0;

        char buffer[max_lenght];

        char c = std::cin.get();
        while(c != '\n'){
            if ((x + 2) > line_cap){
                line_cap *= 2;
                char ** temp = new char *[line_cap];
                for (int i = 0; i < (x+1); i++){
                    temp[i] = lines[i];
                }
                delete[] lines;
                for (int i = (x+1); i < line_cap; i++){
                    temp[i] = new char[max_lenght];
                    temp[i][0] = '\0';
                }
                lines = temp;
            }
            if (y >= max_lenght){
                if (b_i >= (max_lenght)){
                    x++;
                    y = 0;
                    b_i = 0;
                    ml = max_lenght;
                }
                else{
                    if (max_lenght-b_i-1 > ml)
                        ml = max_lenght-b_i-1;
                    lines[x][max_lenght-b_i-1] = '\0';
                    x++;
                    y = 0;
                    for (int i = 0; i < b_i; i++){
                        lines[x][y++] = buffer[i];
                    }
                }
            }
            if (((y == 0) && (c == ' ')) == false)
                lines[x][y++] = c;
                buffer[b_i++] = c;
            
            if (c == ' ')
                b_i = 0;
            c = std::cin.get();
        }
        if (y > ml)
            ml = y;
        lines[x][y] = '\0';

        std::cout << line_cap << "\n";
        for (int i = 0; i < 4 + ml; i++)
            std::cout << "-";
        std::cout << '\n';

        for (int i = 0; i < line_cap; i++){
            if (lines[i][0] == '\0')
                break;
            std::cout << "| ";
            int j = 0;
            for (; j < max_lenght; j++){
                if (lines[i][j] == '\0')
                    break;
                std::cout << lines[i][j];
            }
            for(; j < ml; j++)
                std::cout << " ";
            std::cout << " |\n";
        }

        for (int i = 0; i < line_cap; i++)
            delete[] lines[i];
        delete[] lines;

        for (int i = 0; i < 4 + ml; i++)
            std::cout << "-";
        std::cout << '\n';
        
        std::cout <<
            "     \\\n"
            "      \\\n"
            "        /\\_/\\  (\n"
            "       ( o.o ) _)\n"
            "         \\\"/  (\n"
            "       ( | | )\n"
            "      (__d b__)\n";
    }

    /** 
     * Задание 7. Сложные указатели.
     *
     * Объявление и использование указателей на многомерные массивы.
     * Проинициализируйте трехмерный массив double dArray[4][3][3] так, как
     * показано на рисунке и напишите фрагмент кода, который меняет местами
     * значения элементов четных и нечетных слоев:
     *
     *  было:                |--------|     
     *                     / |4  4  4 |     
     *                   |--------| 4 | 
     *                 / |3  3  3 | 4 | 
     *               |---------|3 |   |
     *             / | 2  2  2 |3 | /
     *            |---------|2 |__|
     *            | 1  1  1 |2 | /
     *            | 1  1  1 |__| 
     *            | 1  1  1 | /
     *            |_________|
     *
     *  стало:               |--------|     
     *                     / |3  3  3 |     
     *                   |--------| 3 | 
     *                 / |4  4  4 | 3 | 
     *               |---------|4 |   |
     *             / | 1  1  1 |4 | /
     *            |---------|1 |__|
     *            | 2  2  2 |1 | /
     *            | 2  2  2 |__| 
     *            | 2  2  2 | /
     *            |_________|
     */

    {

        std::cout << "Ex 7.0" << std::endl;
        double dArray[4][3][3] = {
            { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} },
            { {2, 2, 2}, {2, 2, 2}, {2, 2, 2} },
            { {3, 3, 3}, {3, 3, 3}, {3, 3, 3} },
            { {4, 4, 4}, {4, 4, 4}, {4, 4, 4} }
        };
        std::cout << "Исходный массив:\n";
        for (int layer = 0; layer < 4; ++layer) {
            std::cout << "Слой " << layer << ":\n";
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    std::cout << dArray[layer][row][col] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
        for (int i = 0; i < 4; i += 2) {

            /** 
             * Замечание: НЕ НУЖНО МОДИФИЦИРОВАТЬ ВЫРАЖЕНИЯ СПРАВА ОТ ЗНАКА
             * РАВЕНСТВА!!! 
             */

            double (*evenLayer)[3] = dArray[i];
            double (*oddLayer)[3] = dArray[i + 1];
            
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    double temp = evenLayer[row][col];
                    evenLayer[row][col] = oddLayer[row][col];
                    oddLayer[row][col] = temp;
                }
            }

            /** переставляем местами элементы i-того и i+1-ого слоев */
        }
        
        std::cout << "Массив после перестановки:\n";
        for (int layer = 0; layer < 4; ++layer) {
            std::cout << "Слой " << layer << ":\n";
            for (int row = 0; row < 3; ++row) {
                for (int col = 0; col < 3; ++col) {
                    std::cout << dArray[layer][row][col] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "\n";
        }
    }
    
    /**
     * Задание 7.
     */

    /**
     * Задание 7.1.
     *
     * Объявите двухмерный встроенный массив элементов типа char.
     *
     * Сформируйте значения элементов массива с помощью генератора случайных
     * чисел таким образом, чтобы в массиве были только символы '*' и '_'.
     *
     * В каждой строке "сдвиньте звездочки" в начало строки, например:
     * было - '*' '_' '_' '*' '*' '_' '*' '_' '*' '_'
     * стало: '*' '*' '*' '*' '*' '_' '_' '_' '_' '_'
     * и распечатайте массив по строкам.
     *
     * При этом оцените количество операций, которое требуется для обработки
     * одной строки относительно длины этой строки.
     *
     * Постарайтесь решить эту задачу так, чтобы требовалось не более k*N 
     * операций, где N - длина строки, k - некое фиксированное число.
     */
    
    {
        std::cout << "Ex 7.1" << std::endl;
        const int ROWS = 5;
        const int COLS = 10;
        char array[ROWS][COLS];

        std::srand(static_cast<unsigned>(std::time(0)));

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                array[i][j] = (std::rand() % 2 == 0) ? '*' : '_';
            }
        }

        std::cout << "Исходный массив:\n";
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                std::cout << array[i][j] << " ";
            }
            std::cout << "\n";
        }

        for (int i = 0; i < ROWS; ++i) {
            int starCount = 0;

            for (int j = 0; j < COLS; ++j) {
                if (array[i][j] == '*') {
                    ++starCount;
                }
            }

            for (int j = 0; j < COLS; ++j) {
                if (j < starCount) {
                    array[i][j] = '*';
                } else {
                    array[i][j] = '_';
                }
            }
        }

        std::cout << "\nМодифицированный массив:\n";
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                std::cout << array[i][j] << " ";
            }
            std::cout << "\n";
        }
    }

    /**
     * Задание 7.2.
     *
     * Модифицируйте предыдущее задание следующим способом: После заполнения
     * массива с помощью генератора случайных чисел "сдвиньте" звездочки по
     * столбцам вниз и распечатайте результат.
     */

    {
        std::cout << "Ex 7.2" << std::endl;
        const int ROWS = 5; // Количество строк
        const int COLS = 10; // Количество столбцов
        char array[ROWS][COLS];

        // Инициализация генератора случайных чисел
        std::srand(static_cast<unsigned>(std::time(0)));

        // Заполнение массива случайными '*' и '_'
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                array[i][j] = (std::rand() % 2 == 0) ? '*' : '_';
            }
        }

        // Вывод исходного массива
        std::cout << "Исходный массив:\n";
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                std::cout << array[i][j] << " ";
            }
            std::cout << "\n";
        }

        // Сдвиг звездочек вниз по столбцам
        for (int j = 0; j < COLS; ++j) {
            int starCount = 0;

            // Подсчет количества '*' в столбце
            for (int i = 0; i < ROWS; ++i) {
                if (array[i][j] == '*') {
                    ++starCount;
                }
            }

            // Заполнение столбца: внизу '*', сверху '_'
            for (int i = 0; i < ROWS; ++i) {
                if (i < ROWS - starCount) {
                    array[i][j] = '_';
                } else {
                    array[i][j] = '*';
                }
            }
        }

        // Вывод модифицированного массива
        std::cout << "\nМодифицированный массив:\n";
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                std::cout << array[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
    return 0;
}
