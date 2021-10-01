#ifndef __BOOK_H__
#define __BOOK_H__

#include <stdio.h>
#include "key.h"

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
};

typedef int (*cmp_func_t)(const void *, const void *);

//void read_str(FILE *fout, char *hint_msg, char *target, FILE *fin, int *ec);
//void read_int(FILE *fout, char *hint_msg, int *target, FILE *fin, int *ec);
//tech_book_t read_tech_book(FILE *fout, FILE *fin, int *ec);
//fiction_book_t read_fiction_book(FILE *fin, FILE *fout, int *ec);
//kid_book_t read_kid_book(FILE *fin, FILE *fout, int *ec);
book_t book_read(FILE *fin, FILE *fout, int *ec);
char *book_show(char *buf, book_t *book);
cmp_func_t book_cmp_f(int type);

#endif 