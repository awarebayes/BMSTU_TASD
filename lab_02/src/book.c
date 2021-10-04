#include <stdio.h>
#include <string.h>
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
    sprintf(buf, "%-5d, %-4d, %-40s, %-30s, %-20s", book->pages, book->type, book->title, book->lastname, book->publisher);
    return buf;
}

book_t book_random()
{
    book_t book = {0};
    book.type = rand() % 3;
    book.pages = rand() % 10000;
    rand_string(book.lastname, rand() % 63);
    rand_string(book.publisher, rand() % 63);
    rand_string(book.title, rand() % 63);
    return book;
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
    switch (type)
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

book_key_t book_get_key(book_t *self, int type)
{
    void *key_ptr = NULL;
    switch (type)
    {
        case key_lastname:
            key_ptr = self->lastname;
            break;
        case key_title:
            key_ptr = self->title;
            break;
        case key_publisher:
            key_ptr = self->publisher;
            break;
        case key_pages:
            key_ptr = &self->pages;
            break;
        case key_type:
            key_ptr = &self->type;
            break;
    }
    return key_new(type, key_ptr, 0);
}