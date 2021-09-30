#include <stdio.h>
#include "book.h"

void read_str(FILE *fout, char *hint_msg, char *target, FILE *fin, int *ec)
{
    if (fout)
        fprintf(fout, "%s", hint_msg);
    if (fscanf(fin, "%s", target) != 1)
        *ec = input_err;
}

void read_int(FILE *fout, char *hint_msg, int *target, FILE *fin, int *ec)
{
    if (fout)
        fprintf(fout, "%s", hint_msg);
    if (fscanf(fin, "%d", target) != 1)
        *ec = input_err;
}

tech_book_t read_tech_book(FILE *fin, FILE *fout, int *ec)
{
    tech_book_t book = {0};
    if (fout)
        fprintf(fout, "Inputting tech_book_t\n");

    read_str(fout, "Field: ", book.field, fin, ec);
    read_int(fout, "Year: ", &book.year, fin, ec);
    read_int(fout, "Is language native? 1/0: ", &book.language, fin, ec);

    if (book.language != native && book.language != translated)
        *ec = input_err;
    return book;
}

fiction_book_t read_fiction_book(FILE *fin, FILE *fout, int *ec)
{
    fiction_book_t book = {0};
    if (fout)
        fprintf(fout, "Inputting fiction_book_t\n");

    read_int(fout, "Enter book kind | 0-novel, 1-poem, 2-play: ", &book.genre, fin, ec);

    if (book.genre != genre_novel && book.genre != genre_poem && book.genre != genre_play)
        *ec = input_err;
    return book;
}

kid_book_t read_kid_book(FILE *fin, FILE *fout, int *ec)
{
    kid_book_t book = {0};
    if (fout)
        fprintf(fout, "Inputting kid_book_t\n");

    read_int(fout, "Enter book kind | 0-fairytals, 1-poem: ", &book.genre, fin, ec);

    if (book.genre != kid_fairytail && book.genre != kid_poem)
        *ec = input_err;
    return book;
}

book_t book_read(FILE *fin, FILE *fout, int *ec)
{
    book_t book = {0};
    if (fout)
        fprintf(fout, "Inputting book_t\n");

    read_str(fout, "Enter last name: ", book.lastname, fin, ec);
    read_str(fout, "Enter title: ", book.title, fin, ec);
    read_str(fout, "Enter publisher: ", book.publisher, fin, ec);
    read_int(fout, "Enter #pages: ", &book.pages, fin, ec);
    read_int(fout, "Enter book type | 0-tech, 1-fiction, 2-children: ", &book.type, fin, ec);

    if (book.type == tech_o)
        book.kind.tech = read_tech_book(fin, fout, ec);
    else if (book.type == fiction_o)
        book.kind.fiction = read_fiction_book(fin, fout, ec);
    else if (book.type == kid_o)
        book.kind.kid = read_kid_book(fin, fout, ec);
    else
        *ec = input_err;

    return book;
}

void book_show(FILE *fout, book_t *book)
{
    fprintf(fout, "%s, %s, %s, %d, %d\n", book->lastname, book->title, book->publisher, book->pages, book->type);
}
