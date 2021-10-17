#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "book.h"
#include "util.h"


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

char *tech_book_serialize(char *buf, tech_book_t *book)
{
    sprintf(buf, "%s\n%d\n%d", book->field, book->year, book->language);
    return buf;
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

char *fiction_book_serialize(char *buf, fiction_book_t *book)
{
    sprintf(buf, "%d", book->genre);
    return buf;
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


char *kid_book_serialize(char *buf, kid_book_t *book)
{
    sprintf(buf, "%d", book->genre);
    return buf;
}

book_t book_read(FILE *fin, FILE *fout, int *ec)
{
    book_t book = {0};
    if (fout)
        fprintf(fout, "Inputting book_t\n");

    read_str(fout, "Enter lastname: ", book.lastname, fin, ec);
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

char *book_show(char *buf, book_t *book)
{
    if (book->type == tech_o)
        sprintf(buf, "%-5d, %-4d, %-40s, %-30s, %-20s, %-5d, %-6d, %-20s", book->pages, book->type, book->title, book->lastname, book->publisher, book->kind.tech.language, book->kind.tech.year, book->kind.tech.field);
    else if (book->type == fiction_o)
        sprintf(buf, "%-5d, %-4d, %-40s, %-30s, %-20s, %-5d", book->pages, book->type, book->title, book->lastname, book->publisher, book->kind.fiction.genre);
    else if (book->type == kid_o)
        sprintf(buf, "%-5d, %-4d, %-40s, %-30s, %-20s, %-5d", book->pages, book->type, book->title, book->lastname, book->publisher, book->kind.kid.genre);
    return buf;
}

char *book_serialize(char *buf, book_t *book)
{
    char var_info[128];
    switch (book->type) 
    {
    case tech_o:
        tech_book_serialize(var_info, &book->kind.tech);
        break;

    case fiction_o:
        fiction_book_serialize(var_info, &book->kind.fiction);
        break;

    case kid_o:
        kid_book_serialize(var_info, &book->kind.kid);
        break;

    default:
        break;
    }
    sprintf(buf, "%s\n%s\n%s\n%d\n%d\n%s\n", book->lastname, book->title, book->publisher, book->pages, book->type, var_info);
    return buf;
}

book_t book_random()
{
    book_t book = {0};
    book.type = random() % 3;
    book.pages = random() % 10000;
    rand_string(book.lastname, 1 + random() % 62);
    rand_string(book.publisher, 1 + random() % 62);
    rand_string(book.title, 1 + random() % 62);
    return book;
}

int book_cmp_pages(const void *a, const void *b)
{
    int p1 = ((book_t*)a)->pages;
    int p2 = ((book_t*)b)->pages;
    return p1-p2;
}

cmp_func_t book_cmp_f()
{
    return book_cmp_pages;
}

void book_get_key(book_t *self, book_key_t *target)
{
    target->key = self->pages;
}