#ifndef BOOK_H
#define BOOK_H

struct Book {
    const char * author;
    const char * title;
    int year;
    double price;
    const char * category;
};

union BookAsArray{
    void ** items;
};

void init_book(Book& obj, const char * author, const char * title, int year, double price, const char * category);

void print_book(Book& obj);

void input_book(Book& obj);

#endif