#include <stdio.h>
#include "read.h"

void read_str(int hint, char *hint_msg, char *target, FILE *f, int *ec)
{
    if (hint)
        fprintf(f, "%s", hint_msg);
    if (fscanf(f, "%s", target) != 1)
        *ec = input_err;
}

void read_int(int hint, char *hint_msg, int *target, FILE *f, int *ec)
{
    if (hint)
        fprintf(f, "%s", hint_msg);
    if (fscanf(f, "%d", target) != 1)
        *ec = input_err;
}

tech_book_t read_tech_book(int hint, FILE *f, int *ec)
{
    tech_book_t book = {0};
    if (hint)
        fprintf(f, "Inputting tech_book_t\n");

    read_str(hint, "Field: ", book.field, f, ec);
    read_int(hint, "Year: ", &book.year, f, ec);
    read_int(hint, "Is language native? 1/0: ", &book.language, f, ec);

    if (book.language != native && book.language != translated)
        *ec = input_err;
    return book;
}

fiction_book_t read_fiction_book(int hint, FILE *f, int *ec)
{
    fiction_book_t book = {0};
    if (hint)
        fprintf(f, "Inputting fiction_book_t\n");

    read_int(hint, "Enter book kind | 0-novel, 1-poem, 3-play: ", &book.genre, f, ec);

    if (book.genre != genre_novel && book.genre != genre_poem && book.genre != genre_play)
        *ec = input_err;
    return book;
}

kid_book_t read_kid_book(int hint, FILE *f, int *ec)
{
    kid_book_t book = {0};
    if (hint)
        fprintf(f, "Inputting kid_book_t\n");

    read_int(hint, "Enter book kind | 0-fairytals, 1-poem: ", &book.genre, f, ec);

    if (book.genre != kid_fairytail && book.genre != kid_poem)
        *ec = input_err;
    return book;
}

book_t input_book(int hint, FILE *f, int *ec)
{
    book_t book = {0};
    if (hint)
        fprintf(f, "Inputting kid_book_t\n");

    read_str(hint, "Enter last name: ", &book.lastname, f, ec);
    read_str(hint, "Enter publisher: ", &book.publisher, f, ec);
    read_int(hint, "Enter #pages: ", &book.pages, f, ec);
    read_int(hint, "Enter book type | 1-tech, 2-fiction, 3-children: ", &book.type, f, ec);

    if (book.type == tech_o)
        book.kind.tech = read_tech_book(hint, f, ec);
    if (book.type == fiction_o)
        book.kind.fiction = read_fiction_book(hint, f, ec);
    if (book.type == kid_o)
        book.kind.kid = read_kid_book(hint, f, ec);

    return book;
}