#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>


struct Book {
    const char * author;
    const char * title;
    int year;
    double price;
    const char * category;
};

struct BookAsArray{
    void ** items;
};

static union {
    Book book;
    BookAsArray array;
};

void init_book(Book& obj, const char * author, const char * title, int year, double price, const char * category);

void print_book(const Book& obj);

void input_book(Book& obj, void ** categories, int lenght);

enum SortField { AUTHOR = 0, TITLE = 1, YEAR = 2, PRICE = 3, CATEGORY = 4 };

void delete_book(Book& obj);

void print_all_parameters();

void edit_book(Book * ptr);

#endif