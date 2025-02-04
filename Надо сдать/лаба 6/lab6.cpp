#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"
#include "book.h"

#define PATH "catalog.txt"

#define	  stop __asm nop

/*
TODO:
1. Если картотека пуста, говорить об этом. +
2. Реализовать функцию, которая безопасно вводит число и использовать ее везде. +
3. Проверка на правильность чисел. +
4. Проверить границы массива при удалении +
5. Если картотека пуста не пускать пользователя в бесполезные диалоги +
6. При вводе жанра пользователь либо вводит новый жанр (как сейчас), либо выбирает из тех, что уже добавлены +
7. Выполнить индивидуальное задание (см. актуальную версию работы) сортировка выбором +
*/

/**
 * Практическое занятие №6. Консольное приложение.
 *
 * Темы:
 * - динамический массив структур,
 * - добавление, чтение, изменение и удаление структур,
 * - поиск,
 * - сортировка,
 * - сохранение данных в файл и чтение данных из файла,
 * - обработка ошибок пользовательского ввода,
 * - работа с функциями семейства printf и scanf,
 * - функциональная и модульная декомпозиция программы.
 *
 * Отдельные задания в этой работе не нужно выполнять последовательно, в этой
 * работе задания скорее являются требованиями к тому, что ваша программа должна
 * делать.
 *
 * Обратите внимание на следующие указания.
 *
 * 1. Для ввода и вывода данных из консоли и файлов *необходимо* использовать
 *    фукцнии семейства printf и scanf.
 * 2. Ваша программа должна быть оформлена в виде нескольких файлов исходного
 *    кода, каждый из которых реализует набор функций, относящихся к одной теме.
 * 3. В результате работы программы не должно быть утечек памяти.
 * 4. Для каждой функциональности приложения у пользователя должен быть консольный 
 *    интерфейс (см. ниже). Этот интерфейс должен быть устойчив к человеческим ошибкам
 *    (например, если пользователь выбрал несуществующий пункт меню или ввел букву 
 *    вместо числа).
 * 5. Вам необходимо выполнить индивидуальное задание, которое закодировано на странице
 *    http://13633.mooo.com/file/att.html. Напротив вашей фамилии указан тип сортировки,
 *    который вам нужно реализовать и дополнительное задание по номеру:
 *    1) вывести все книги данного автора и/или данного жанра, автор и жанр вводится 
 *       пользователем;
 *    2) найти книгу с самым маленьким годом издания после заданного пользователем года;
 *    3) найти наиболее популярный жанр книг среди книг картотеки;
 *    4) найти минимальный, максимальный, средний (арифметически) и средний в смысле +
 *       медианы год издания книги среди книг в картотеке; +
 *    5) найти книги с самым длинным и самым коротким названием.
 * 
 * Консольный интерфейс главного меню может выглядеть примерно так:
 *
 * ```
   Добро пожаловать в библиотеку! Выберите действие:
   1. Распечатать библиотеку.
   2. Добавить книгу.
   ...
   0. Выход из программы.
  
   Ваше действие: _
 * ```
 */


void Clear()
{
#if defined _WIN32
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
    system("clear");
#endif
}



bool book_cmp(SortField state, void * p1, void * p2){
    Book * left = (Book *)p1;
    Book * right = (Book *)p2;
    switch(state){
        case AUTHOR:
            return (cmp_str(const_cast<char *>(left->author), const_cast<char *>(right->author)) > 0);
        case TITLE:
            return (cmp_str(const_cast<char *>(left->author), const_cast<char *>(right->author)) > 0);
        case YEAR:
            return (left->year > right->year);
        case PRICE:
            return (left->price > right->price);
        case CATEGORY:
            return (cmp_str(const_cast<char *>(left->author), const_cast<char *>(right->author)) > 0);
    }
    return false;
}

void void_swap(void ** p1, void ** p2){
    void * temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_library(SortField state, void ** items, int lenght, bool flag = false){
    if (lenght <= 1)
        return;
    int index = 0;
    for (int i = 0; i < lenght - 1; i++){
        index = i;
        for (int j = i + 1; j < lenght; j++){
            if (book_cmp(state, items[index], items[j]) == flag)
                continue;
            index = j;
        }
        if (i == index)
            continue;
        void_swap(&items[index], &items[i]);
    }
}

void write_to_file(dinamic_array * array_ptr, const char * path){

    FILE* file = fopen(path, "w");

    void * ptr;

    for (int i = 0; i < utils::get_lenght(array_ptr); i++) {
        ptr = utils::get_item(array_ptr, i);
        if (ptr == nullptr)
            continue;
        fputs((const char *)((*(Book *)(ptr)).author), file);
        fputc('\n', file);
        fputs((const char *)((*(Book *)(ptr)).title), file);
        fputc('\n', file);
        fputs((const char *)(std::to_string((*(Book *)(ptr)).year).c_str()), file);
        fputc('\n', file);
        fputs((const char *)(std::to_string((*(Book *)(ptr)).price).c_str()), file);
        fputc('\n', file);
        fputs((const char *)((*(Book *)(ptr)).category), file);
        fputc('\n', file);
    }

    fclose(file);
    printf("Каталог успешно выгружен!\n");
}

void read_file(dinamic_array * array_ptr, const char * path, dinamic_array * set){
    std::ifstream file(path);
    if (!file) {
        std::cerr << "Не удалось открыть файл!\n" << std::endl;
        return;
    }
    char c;
    int buffer_index = 0;
    int buffer_capacity = 1;
    char * buffer = new char[buffer_capacity];
    buffer[0] = '\0';
    SortField state = AUTHOR;
    while (file.get(c)) {
        if (buffer_index == buffer_capacity){
            buffer_capacity *= 2;
            char * buffer_2 = new char[buffer_capacity];
            for(int i = 0; i < (buffer_capacity / 2); i++){
                buffer_2[i] = buffer[i];
            }
            delete[] buffer;
            buffer = buffer_2;
        }
        buffer[buffer_index++] = c;
        if (c == '\n'){
            buffer[buffer_index-1] = '\0';
            char * answer = new char[buffer_index];
            for (int i = 0; i < buffer_index; i++){
                answer[i] = buffer[i];
            }
            delete[] buffer;
            buffer_index = 0;
            buffer_capacity = 1;
            buffer = new char[buffer_capacity];
            buffer[0] = '\0';
            Book * temp;
            if (state == AUTHOR){
                temp = new Book();
                init_book(*temp, answer, nullptr, 0, 0, nullptr);
                utils::add_item(array_ptr, temp);
            }
            else{
                temp = (Book *)(utils::get_item(array_ptr, utils::get_lenght(array_ptr)-1));
                switch(state){
                    case TITLE:
                        temp->title = answer;
                        break;
                    case YEAR:
                        temp->year = std::stoi(answer);
                        delete[] answer;
                        break;
                    case PRICE:
                        temp->price = std::stod(answer);
                        delete[] answer;
                        break;
                    case CATEGORY:
                        temp->category = answer;
                        utils::add_unique_item(set, (void *)str_copy(answer), cmp_str);
                        break;
                }
            }
            state = (SortField)((state + 1) % 5);
        }
    }
    delete[] buffer;

    file.close();

    printf("Каталог пополнен!\n");
}

void print_main_menu(){
    std::cout << "Меню действий:\n"
        << "1. Выписать список книг\n"
        << "2. Добавить книгу\n"
        << "3. Удалить книгу\n"
        << "4. Загрузить список книг из файла\n"
        << "5. Выгрузить книги в файл\n"
        << "6. Сортировать каталог\n"
        << "7. Редактировать книгу\n"
        << "8. Поиск книги\n"
        << "9. Выполнить индивидуальное задание\n"
        << "10. Выход из программы\n";
}

bool is_not_empty(dinamic_array * array_ptr){
    int lenght;
    lenght  = utils::get_lenght(array_ptr);
    if (lenght != 0){
        return true;
    }
    else{
        printf("Список пуст, сначала добавьте книги в каталог\n\n");
        return false;
    }
}

void print_bf_book(void * ptr, int index){
    printf("\nКнига %d:\n", index);
    print_book(*(Book *)(ptr));
}

void print_catalog(dinamic_array * array_ptr){
    void * buffer_ptr;
    printf("Список книг в каталоге:\n");
    for(int i = 0; i < utils::get_lenght(array_ptr); i++){
        buffer_ptr = utils::get_item(array_ptr, i);
        if (buffer_ptr != nullptr){
            print_bf_book(buffer_ptr, i+1);
        }
    }
}

void exit_program(dinamic_array * array_ptr){
    void * buffer_ptr;
    for(int i = 0; i < utils::get_lenght(array_ptr); i++){
        buffer_ptr = utils::get_item(array_ptr, i);
        if (buffer_ptr == nullptr)
            continue;
        delete_book(*(Book *)(buffer_ptr));
        delete (Book *)(buffer_ptr);
    }
    delete[] array_ptr->items;
    delete array_ptr;
}

void delete_book(dinamic_array * array_ptr, int index){
    void * buffer_ptr;
    buffer_ptr = utils::get_item(array_ptr, index);
    utils::delete_item(array_ptr, index);
    delete_book(*(Book *)(buffer_ptr));
    delete (Book *)buffer_ptr;
    utils::garbage_collector(array_ptr);
}

void print_sort_menu(){
    std::cout << "Выберите параметр:\n"
        << "1. Автор\n"
        << "2. Название\n"
        << "3. Год выпуска\n"
        << "4. Цена\n"
        << "5. Жанр\n";
}

void print_search_menu(){
    std::cout << "Выберите параметр:\n"
        << "1. Автор\n"
        << "2. Название\n"
        << "3. Жанр\n";
}

const char * get_parameter(SortField state, void * ptr){
    Book & book = *(Book *)(ptr);
    switch(state){
        case AUTHOR: return book.author;
        case TITLE: return book.title;
        case CATEGORY: return book.category;
    }
    return "";
}

void search_book(dinamic_array * array_ptr, SortField state, const char * search){
    void * ptr;
    int count = 0;
    for (int i = 0; i < utils::get_lenght(array_ptr); i++){
        ptr = utils::get_item(array_ptr, i);
        if (cmp_str((char *)search, (char *)(get_parameter(state, ptr))) == 0){
            print_bf_book(ptr, i+1);
            count++;
        }
    }
    if (count == 0){
        printf("По вашему запросу не получилось найти книги.\n");
    }
}

void edit_parameter(dinamic_array * array_ptr, int index){
    void * ptr;
    ptr = utils::get_item(array_ptr, index);
    edit_book((Book *)ptr);
}

int get_max_year(dinamic_array * array_ptr){
    int m;
    m = ((Book *)(((dinamic_array *)(array_ptr))->items[0]))->year;
    for(int i = 1; i < utils::get_lenght(array_ptr); i++){
        if(m < ((Book *)(((dinamic_array *)(array_ptr))->items[i]))->year)
            m = ((Book *)(((dinamic_array *)(array_ptr))->items[i]))->year;
    }
    return m;
}

int get_min_year(dinamic_array * array_ptr){
    int m;
    m = ((Book *)(((dinamic_array *)(array_ptr))->items[0]))->year;
    for(int i = 1; i < utils::get_lenght(array_ptr); i++){
        if(m > ((Book *)(((dinamic_array *)(array_ptr))->items[i]))->year)
            m = ((Book *)(((dinamic_array *)(array_ptr))->items[i]))->year;
    }
    return m;
}

int mediana(dinamic_array * array_ptr){
    int lenght; // update
    lenght = utils::get_lenght(array_ptr);
    sort_library(YEAR, array_ptr->items, lenght);
    if (lenght % 2 == 0){
        Book * left;
        Book * right;
        left = (Book *)utils::get_item(array_ptr, lenght/2-1);
        right = (Book *)utils::get_item(array_ptr, lenght/2);
        return (left->year + right->year) / 2;
    } else {
        Book * middle;
        middle = (Book *)utils::get_item(array_ptr, lenght/2);
        return middle->year;
    }
}

int halfValue(dinamic_array * array_ptr){
    int count = 0;
    for(int i = 0; i < utils::get_lenght(array_ptr); i++){
        count += ((Book *)(((dinamic_array *)(array_ptr))->items[i]))->year;
    }
    return count / utils::get_lenght(array_ptr);
}

int main() {

    /**
     * Задание 1. Создание «картотеки» книг.
     * «Картотека» — это динамический массив структур.
     * Реализуйте структуру, которая хранит информацию о книгах:
     * название, автор, год издания, жанр, краткое описание.
     *
     * Важно! Массив должен быть динамическим, то есть его размер
     * будет увеличиваться по мере добавления книг. Для этого
     * нужно использовать динамическое выделение памяти с
     * последующим расширением массива по мере необходимости.
     * Старайтесь не выделять память слишком часто,
     * чтобы не ухудшить производительность, используйте стратегию
     * "перераспределения" с увеличением массива на определенный коэффициент
     * (например, на 1.5x).
     *
     * Пользователь должен иметь возможность выполнять следующие действия:
     * 
     * 1. Распечатать содержимое картотеки. +
     * 2. Добавить новую книгу. +
     * 3. Удалить книгу по названию.
     * 4. Изменить информацию о книге (например, изменить описание).
     * 5. Сохранить текущее содержимое картотеки в файл. +
     * 6. Загрузить содержимое картотеки из файла. +
     * 7. Действие по вашему варианту. +
     * 8. Выйти из программы. +
     */

    /**
     * Задание 2. Печать картотеки. +
     *
     * Реализуйте печать картотеки на экран по запросу пользователя.
     */

    /**
     * Задание 3. Добавление новой книги. +
     *
     * Реализуйте для пользователя возможность добавлять новые книги с заполнением полей
     * книги в интерактивном режиме.
     *
     * При этом необходимо обработать некорректный пользовательский ввод. +
     */

    /**
     * Задание 4. Сортировка книг. +-
     *
     * Реализуйте возможность сортировать картотеку по одному из полей по выбору
     * пользователя. Учтите сортировку по возрастанию и убыванию. +
     *
     * Учтите, что сортировка должна быть стабильное, то есть менять порядок
     * книг с одинаковыми значениями критерия.
     *
     * Алгоритм сортировки должен быть выбран согласно вашему варианту. +
     *
     * Задание со * (опционально): реализуйте сортировку по нескольким полям. -
     */

    /**
     * Задание 5. Поиск книг. +
     *
     * Реализуйте поиск книг по одному из критериев:
     * - по названию книги, +
     * - по автору, +
     * - по жанру. +
     */

    /**
     * Задание 6. Удаление книги. +
     *
     * Реализуйте удаление книги из картотеки. При этом следите, чтобы память
     * освобождалась корректно и, когда книг останется меньше, чем выделено памяти,
     * перевыделите память.
     *
     * Задание со * (опционально): реализуйте "отмену" последних k-операций.
     */

    /**
     * Задание 7. Изменение книги. +
     *
     * Реализуйте изменение полей уже добавленной книги. При этом так же, как и при 
     * добавлении книги, обработайте ошибки.
     */

    /**
     * Задание 8. Запись в файл и чтение из файла. +
     *
     * Реализуйте сохранение картотеки в файл и чтение из него. При этом сделайте 
     * возможность пользователю выбрать файл для чтения и записи. +
     *
     * Обработайте ошибки связанные с выбором несуществующего файла или файла с 
     * неверным форматом. +
     */

    dinamic_array * list = new dinamic_array();
    dinamic_array * set = new dinamic_array();
    utils::init_dinamic_array(list);
    utils::init_dinamic_array(set);
    int move = 0;
    const char * ptr;
    void * buffer_ptr;
    int lenght;

    while(true){
        switch(move) {
            case 0:
                print_main_menu();
                move = get_valid_int(1, 10);
                Clear();
                break;
            case 1:
                if(is_not_empty(list))
                    print_catalog(list);
                move = 0;
                break;
            case 2:
                buffer_ptr = (void *)(new Book());
                input_book(*(Book *)(buffer_ptr), set->items, utils::get_lenght(set));
                utils::add_item(list, buffer_ptr);
                utils::add_unique_item(set, (void *)str_copy((char *)(((Book *)(buffer_ptr))->category)), cmp_str);
                buffer_ptr = nullptr;
                move = 0;
                break;
            case 3:
                if(is_not_empty(list)){
                    print_catalog(list);
                    lenght = utils::get_lenght(list);
                    move = get_valid_int(1, lenght);
                    delete_book(list, move - 1);
                    utils::garbage_collector(set);
                }
                move = 0;
                break;
            case 4:
                printf("Введите путь к файлу: ");
                while (getchar() != '\n');
                ptr = const_input();
                read_file(list, ptr, set);
                delete[] ptr;
                move = 0;
                break;
            case 5:
                if(is_not_empty(list)){
                    printf("Введите путь к файлу: ");
                    while (getchar() != '\n');
                    ptr = const_input();
                    write_to_file(list, ptr);
                    delete[] ptr;
                }
                move = 0;
                break;
            case 6:
                print_sort_menu();
                move = get_valid_int(1, 5);
                bool isReverse;
                printf("Сортировать по:\n1. Возрастанию\n2. Убыванию\n");
                isReverse = (bool)(get_valid_int(1, 2) - 1);
                sort_library((SortField)(move - 1), list->items, utils::get_lenght(list), isReverse);
                move = 0;
                break;
            case 7:
                if(is_not_empty(list)){
                    print_catalog(list);
                    lenght = utils::get_lenght(list);
                    move = get_valid_int(1, lenght);
                    edit_parameter(list, move - 1);
                }
                move = 0;
                break;
            case 8:
                if(is_not_empty(list)){
                    print_search_menu();
                    move = get_valid_int(1, 3);
                    if (move == 3)
                        move = 5;
                    printf("Поиск: ");
                    while (getchar() != '\n');
                    ptr = const_input();
                    search_book(list, (SortField)(move - 1), ptr);
                    delete[] ptr;
                }
                move = 0;
                break;
            case 9:
                std::cout << "Min: " << get_min_year(list) << "\n";
                std::cout << "Max: " << get_max_year(list) << "\n"; // max
                std::cout << "Med: " << mediana(list) << "\n";
                std::cout << "Half: " << halfValue(list) << "\n";
                move = 0;
                break;
            case 10:
                for(int i = 0; i < utils::get_lenght(set); i++){
                    delete[] (const char *)utils::get_item(set, i);
                }
                delete[] set->items;
                delete set;
                exit_program(list);
                return 0;
        }
    }

    return 0;
}
