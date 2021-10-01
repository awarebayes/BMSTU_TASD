#include <stdio.h>
#include <string.h>
#include "book.h"

#define BUFFER_SIZE 64

void read_str(FILE *fout, char *hint_msg, char *target, FILE *fin, int *ec)
{
    if (fout)
        fprintf(fout, "%s", hint_msg);
    fgets(target, BUFFER_SIZE, fin);
    if (ferror(fin))
        *ec = input_err;
    else
    {
        char *newline = strchr(target, '\n');
        if (newline != NULL)
            *newline = '\0'; // delete \n
    }
}

void read_int(FILE *fout, char *hint_msg, int *target, FILE *fin, int *ec)
{
    char buffer[BUFFER_SIZE];
    if (fout)
        fprintf(fout, "%s", hint_msg);
    fgets(buffer, BUFFER_SIZE, fin);
    if (sscanf(buffer, "%d", target) != 1)
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

char *book_show(char *buf, book_t *book)
{
    sprintf(buf, "%s, %s, %s, %d, %d", book->lastname, book->title, book->publisher, book->pages, book->type);
    return buf;
}

int str_cmp(const void *a, const void *b)
{
    char *s1 = (char*)a;
    char *s2 = (char*)b;
    return strcmp(s1, s2);
}

int int_cmp(const void *a, const void *b)
{
    int i1 = (int*)a;
    int i2 = (int*)b;
    return i1-i2;
}

int book_cmp_lastname(const void *a, const void *b)
{
    char *l1 = ((book_t*)a)->lastname;
    char *l2 = ((book_t*)b)->lastname;
    return strcmp(l1, l2);
}

int book_cmp_publisher(const void *a, const void *b)
{
    char *p1 = ((book_t*)a)->publisher;
    char *p2 = ((book_t*)b)->publisher;
    return strcmp(p1, p2);
}

int book_cmp_title(const void *a, const void *b)
{
    char *t1 = ((book_t*)a)->title;
    char *t2 = ((book_t*)b)->title;
    return strcmp(t1, t2);
}

int book_cmp_pages(const void *a, const void *b)
{
    int p1 = ((book_t*)a)->pages;
    int p2 = ((book_t*)b)->pages;
    return p1-p2;
}

int book_cmp_type(const void *a, const void *b)
{
    int t1 = ((book_t*)a)->type;
    int t2 = ((book_t*)b)->type;
    return t1-t2;
}

cmp_func_t book_cmp_f(int type)
{
    switch (key_type)
    {
    case key_lastname:
        return book_cmp_lastname;
    case key_title:
        return book_cmp_publisher;
    case key_publisher:
        return book_cmp_publisher;
    case key_pages:
        return book_cmp_pages;
    case key_type:
        return book_cmp_type;
   default:
        return NULL;
    }
}