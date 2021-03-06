#ifndef __BOOK_H__
#define __BOOK_H__

#define _GNU_SOURCE 
#include <stdio.h>
#include "key.h"
#include "util.h"

#define SSIZE 64
enum translation_t
{
    native,
    translated,
};

typedef struct
{
    char field[SSIZE];
    int year;
    int language;
} tech_book_t;

enum genre_t
{
    genre_novel,
    genre_poem,
    genre_play,
};

typedef struct
{
    int genre;
} fiction_book_t;

enum kid_book_e
{
    kid_fairytail,
    kid_poem,
};

typedef struct
{
    int genre;
} kid_book_t;

typedef union
{
    tech_book_t tech;
    fiction_book_t fiction;
    kid_book_t kid;
} book_kind_t;

enum book_kind_e
{
    tech_o,
    fiction_o,
    kid_o,
};

typedef struct
{
    char lastname[SSIZE];
    char title[SSIZE];
    char publisher[SSIZE];
    int pages;
    int type;
    book_kind_t kind;
} book_t;

enum err_t
{
    ok,
    input_err,
    file_err,
};

book_t book_read(FILE *fin, FILE *fout, int *ec);
char *book_show(char *buf, book_t *book);
cmp_func_t book_cmp_f();
void book_get_key(book_t *self, book_key_t *target);
book_t book_random();
char *book_serialize(char *buf, book_t *book);

#endif 