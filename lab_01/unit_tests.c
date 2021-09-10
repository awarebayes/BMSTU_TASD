#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "big_int.h"
#include "big_float.h"
#include "util.h"


void big_int_read_1()
{
    int ec = 0;
    big_int_t a = bi_sread("12345", &ec);
    big_int_t target = {.p1=0, .p2=12345, .sign=0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_2()
{
    int ec = 0;
    big_int_t a = bi_sread("12345 ", &ec);
    big_int_t target = {.p1=0, .p2=12345, .sign=0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_3()
{
    int ec = 0;
    big_int_t a = bi_sread("   12345   ", &ec);
    big_int_t target = {.p1=0, .p2=12345, .sign=0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_4()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789012345", &ec);
    big_int_t target = {.p1=0, .p2=123456789012345, .sign=0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_5()
{
    int ec = 0;
    big_int_t a = bi_sread("12345678901234567", &ec);
    big_int_t target = {.p1=12, .p2=345678901234567, .sign=0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_6()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789012345678901234567890", &ec);
    big_int_t target = {.p1=123456789012345, .p2=678901234567890, .sign=0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_7()
{
    int ec = 0;
    big_int_t a = bi_sread("-123456789012345678901234567890", &ec);
    big_int_t target = {.p1=123456789012345, .p2=678901234567890, .sign=1};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_8()
{
    int ec = 0;
    big_int_t a = bi_sread("  -123456789012345678901234567890  ", &ec);
    big_int_t target = {.p1=123456789012345, .p2=678901234567890, .sign=1};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
}

void big_int_read_9()
{
    int ec = 0;
    bi_sread("  -123456789012345abc678901234567890  ", &ec);
    assert(ec != 0);
}

void big_int_read_10()
{
    int ec = 0;
    bi_sread("  -123456789012345abc672343243248901234567890  ", &ec);
    assert(ec != 0);
}

void big_int_add_1()
{
    int ec = 0;
    big_int_t a = bi_sread("3", &ec);
    big_int_t b = bi_sread("+4", &ec);
    big_int_t c = bi_sum(&a, &b, &ec);
    big_int_t target = {.p1 = 0, .p2 = 7, .sign = 0};
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
    assert(ec == 0);
}

void big_int_add_2()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789012345678901234567890", &ec);
    big_int_t b = bi_sread("098765432109876543210987654321", &ec);
    big_int_t c = bi_sum(&a, &b, &ec);
    big_int_t target = bi_sread("222222221122222222112222222211", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
    assert(ec == 0);
}

void big_int_add_3()
{
    int ec = 0;
    big_int_t a = bi_sread("999999999999999999999999999999", &ec);
    big_int_t b = bi_sread("999999999999999999999999999999", &ec);
    bi_sum(&a, &b, &ec);
    assert(ec == overflow_err);
}

void big_int_sub_1()
{
    int ec = 0;
    big_int_t a = bi_sread("20", &ec);
    big_int_t b = bi_sread("1", &ec);
    big_int_t c = bi_sub(&a, &b, &ec);
    big_int_t target = bi_sread("19", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
    assert(ec == 0);
}

void big_int_sub_2()
{
    int ec = 0;
    big_int_t a = bi_sread("4", &ec);
    big_int_t b = bi_sread("5", &ec);
    big_int_t c = bi_sub(&a, &b, &ec);
    big_int_t target = bi_sread("-1", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
    assert(ec == 0);
}

void big_int_sub_3()
{
    int ec = 0;
    big_int_t a = bi_sread("99999999999999999999", &ec);
    big_int_t b = bi_sread("12345678901234567890", &ec);
    big_int_t c = bi_sub(&a, &b, &ec);
    big_int_t target = bi_sread("87654321098765432109", &ec);
    assert(ec == 0);
    if (bi_cmp(&c, &target) != eq)
    {
        bi_print(&a);
        bi_print(&b);
        bi_print(&c);
        bi_print(&target);
    }
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_sub_4()
{
    int ec = 0;
    big_int_t a = bi_sread("98752412358439545894", &ec);
    big_int_t b = bi_sread("23499997435712321983", &ec);
    big_int_t c = bi_sub(&a, &b, &ec);
    big_int_t target = bi_sread("75252414922727223911", &ec);
    assert(ec == 0);
    if (bi_cmp(&c, &target) != eq)
    {
        bi_print(&a);
        bi_print(&b);
        bi_print(&c);
        bi_print(&target);
    }
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_sub_5()
{
    int ec = 0;
    big_int_t b = bi_sread("98752412358439545894", &ec);
    big_int_t a = bi_sread("23499997435712321983", &ec);
    big_int_t c = bi_sub(&a, &b, &ec);
    big_int_t target = bi_sread("-75252414922727223911", &ec);
    assert(ec == 0);
    if (bi_cmp(&c, &target) != eq)
    {
        bi_print(&a);
        bi_print(&b);
        bi_print(&c);
        bi_print(&target);
    }
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_ls_1()
{
    int ec = 0;
    big_int_t a = bi_sread("3", &ec);
    a = bi_lshift(&a, &ec);
    big_int_t target = {.p1 = 0, .p2 = 30, .sign = 0};
    assert(ec == 0);
    assert(bi_cmp(&a, &target) == eq);
    assert(ec == 0);
}

void big_int_ls_2()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789012345", &ec);
    a = bi_lshift(&a, &ec);
    big_int_t target = {.p1 = 1, .p2 = 234567890123450, .sign = 0};
    assert(ec == 0);
    if (bi_cmp(&a, &target) != eq)
    {
        bi_print(&a);
        bi_print(&target);
    }
    assert(bi_cmp(&a, &target) == eq);
    assert(ec == 0);
}

void big_int_ls_3()
{
    int ec = 0;
    big_int_t a = bi_sread("1234567890123456", &ec);
    a = bi_lshift(&a, &ec);
    big_int_t target = {.p1 = 12, .p2 = 345678901234560, .sign = 0};
    assert(ec == 0);
    if (bi_cmp(&a, &target) != eq)
    {
        bi_print(&a);
        bi_print(&target);
    }
    assert(bi_cmp(&a, &target) == eq);
    assert(ec == 0);
}

void big_int_rs_1()
{
    int ec = 0;
    big_int_t a = bi_sread("23", &ec);
    a = bi_rshift(&a);
    big_int_t target = {.p1 = 0, .p2 = 2, .sign = 0};
    assert(ec == 0);
    if (bi_cmp(&a, &target) != eq)
    {
        bi_print(&a);
        bi_print(&target);
    }
    assert(bi_cmp(&a, &target) == eq);
    assert(ec == 0);
}

void big_int_rs_2()
{
    int ec = 0;
    big_int_t a = bi_sread("1234567890123456", &ec);
    a = bi_rshift(&a);
    big_int_t target = {.p1 = 0, .p2 = 123456789012345, .sign = 0};
    assert(ec == 0);
    if (bi_cmp(&a, &target) != eq)
    {
        bi_print(&a);
        bi_print(&target);
    }
    assert(bi_cmp(&a, &target) == eq);
    assert(ec == 0);
}

void big_int_rs_3()
{
    int ec = 0;
    big_int_t a = bi_sread("12345678901234567", &ec);
    a = bi_rshift(&a);
    big_int_t target = {.p1 = 1, .p2 = 234567890123456, .sign = 0};
    assert(ec == 0);
    if (bi_cmp(&a, &target) != eq)
    {
        bi_print(&a);
        bi_print(&target);
    }
    assert(bi_cmp(&a, &target) == eq);
    assert(ec == 0);
}

void big_int_mul_dec_1()
{
    int ec = 0;
    big_int_t a = bi_sread("3", &ec);
    int d = 3;
    big_int_t c = bi_mul_dec(&a, d, &ec);
    big_int_t target = bi_sread("9", &ec);
    assert(ec == 0);
    if (bi_cmp(&c, &target) != eq)
    {
        bi_print(&a);
        bi_print(&c);
        bi_print(&target);
    }
    assert(bi_cmp(&c, &target) == eq);
    assert(ec == 0);
}

void big_int_mul_dec_2()
{
    int ec = 0;
    big_int_t a = bi_sread("12345678902134567890", &ec);
    int d = 9;
    big_int_t c = bi_mul_dec(&a, d, &ec);
    big_int_t target = bi_sread("111111110119211111010", &ec);
    assert(ec == 0);
    if (bi_cmp(&c, &target) != eq)
    {
        bi_print(&a);
        printf("*%d\n", d);
        bi_print(&c);
        bi_print(&target);
    }
    assert(bi_cmp(&c, &target) == eq);
    assert(ec == 0);
}

void big_int_mul_dec_3()
{
    int ec = 0;
    big_int_t a = bi_sread("999999999999999999999999999999", &ec);
    int d = 9;
    bi_mul_dec(&a, d, &ec);
    assert(ec == overflow_err);
}

void big_int_mul_1()
{
    int ec = 0;
    big_int_t a = bi_sread("4", &ec);
    big_int_t b = bi_sread("3", &ec);
    big_int_t c = bi_mul(a, b, &ec, 0);
    big_int_t target = bi_sread("12", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_mul_2()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789012345", &ec);
    big_int_t b = bi_sread("19", &ec);
    big_int_t c = bi_mul(a, b, &ec, 0);
    big_int_t target = bi_sread("2345678991234555", &ec);
    assert(ec == 0);
    if (bi_cmp(&c, &target) != eq)
    {
        bi_print(&a);
        bi_print(&c);
        bi_print(&target);
    }
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_mul_3()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789123234", &ec);
    big_int_t b = bi_sread("23412", &ec);
    big_int_t c = bi_mul(a, b, &ec, 0);
    big_int_t target = bi_sread("2890370346953154408", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_mul_4()
{
    int ec = 0;
    big_int_t a = bi_sread("9999999999999999999999999999", &ec);
    big_int_t b = bi_sread("999", &ec);
    bi_mul(a, b, &ec, 0);
    assert(ec == overflow_err);
}

void big_int_mul_5()
{
    int ec = 0;
    big_int_t a = bi_sread("123456789123234", &ec);
    big_int_t b = bi_sread("0", &ec);
    big_int_t c = bi_mul(a, b, &ec, 0);
    big_int_t target = bi_sread("0", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
}

void big_int_mul_6()
{
    int ec = 0;
    int overflow = 0;
    int overflow_target = 3;
    big_int_t a = bi_sread("9999999999999999999999999999", &ec);
    big_int_t b = bi_sread("99999", &ec);
    big_int_t c = bi_mul(a, b, &ec, &overflow);
    big_int_t target = bi_sread("999989999999999999999999999900", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
    assert(overflow == overflow_target);
}

void big_int_mul_7()
{
    int ec = 0;
    int overflow = 0;
    int overflow_target = 2;
    big_int_t a = bi_sread("999999999999999999999999999911", &ec);
    big_int_t b = bi_sread("99", &ec);
    big_int_t c = bi_mul(a, b, &ec, &overflow);

    // 98999999999999999999999999991189 -> 
    // 9899999999999999999999999999119 ->
    // 98999999999999999999999999991182
    big_int_t target = bi_sread("989999999999999999999999999912", &ec);
    assert(ec == 0);
    assert(bi_cmp(&c, &target) == eq);
    assert(overflow == overflow_target);
}

void big_float_read_1()
{
    int ec = 0;
    big_float_t a = bf_sread("12345", &ec);
    big_float_t target = {.m = {.p1=0, .p2=12345, .sign=0}, .exp=0};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_read_2()
{
    int ec = 0;
    char a_str[] = "12345 E -3";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t target = {.m = {.p1=0, .p2=12345, .sign=0}, .exp=-3};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_read_3()
{
    int ec = 0;
    char a_str[] = "12.345 E -3";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t target = {.m = {.p1=0, .p2=12345, .sign=0}, .exp=-6};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_read_4()
{
    int ec = 0;
    char a_str[] = "-.00025";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t target = {.m = {.p1=0, .p2=25, .sign=1}, .exp=-5};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_read_5()
{
    int ec = 0;
    char a_str[] = "-123001.";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t target = {.m = {.p1=0, .p2=123001, .sign=1}, .exp=0};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_read_6()
{
    int ec = 0;
    char a_str[] = "-123001.abc";
    big_float_t a = bf_sread(a_str, &ec);
    assert(ec == read_err);
}

void big_float_read_7()
{
    int ec = 0;
    char a_str[] = "-123001.34 E abc";
    big_float_t a = bf_sread(a_str, &ec);
    assert(ec == read_err);
}

void big_float_read_8()
{
    int ec = 0;
    char a_str[] = "-123001.34 E ";
    big_float_t a = bf_sread(a_str, &ec);
    assert(ec == read_err);
}

void big_float_read_9()
{
    int ec = 0;
    char a_str[] = "";
    big_float_t a = bf_sread(a_str, &ec);
    assert(ec == read_err);
}

void big_float_read_10()
{
    int ec = 0;
    char a_str[] = "        .   ";
    big_float_t a = bf_sread(a_str, &ec);
    assert(ec == read_err);
}

void big_float_read_11()
{
    int ec = 0;
    char a_str[] = "        e   ";
    big_float_t a = bf_sread(a_str, &ec);
    assert(ec == read_err);
}

void big_float_read_12()
{
    int ec = 0;
    char a_str[] = "0.01";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t target = {.m = {.p1=0, .p2=1, .sign=0}, .exp=-2};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_read_13()
{
    int ec = 0;
    char a_str[] = "0.1";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t target = {.m = {.p1=0, .p2=1, .sign=0}, .exp=-1};
    assert(ec == 0);
    assert(bf_exact_eq(&a, &target));
}

void big_float_add_1()
{
    int ec = 0;
    char a_str[] = "0.2";
    char b_str[] = "0.1";
    char t_str[] = "0.3";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sum(&a, &b);
    assert(bf_exact_eq(&res, &target));
}



void big_float_add_2()
{
    int ec = 0;
    char a_str[] = "0.2";
    char b_str[] = "0.01";
    char t_str[] = "0.21";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sum(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_add_3()
{
    int ec = 0;
    char a_str[] = "0.2 E -3";
    char b_str[] = "0.01 E 4";
    char t_str[] = "100.0002";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sum(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_add_4()
{
    int ec = 0;
    char a_str[] = "0.2 E -300";
    char b_str[] = "0.01 E 4";
    char t_str[] = "0.01 E 4";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sum(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_add_5()
{
    // maybe another test?
    int ec = 0;
    char a_str[] = "123456789012345678901234567899 E -300";
    char b_str[] = "123456789012345678901234567899 E -300";
    char t_str[] = "246913578024691357802469135798 E -300";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sum(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_norm_1()
{
    int ec = 0;
    char t_str[] = "1";
    big_float_t a = {.m = {.p1=0, .p2=1000, .sign=0}, .exp=-3};
    big_float_t target = bf_sread(t_str, &ec);
    bf_normalize(&a);
    assert(bf_exact_eq(&a, &target));
}

void big_float_sub_1()
{
    int ec = 0;
    char a_str[] = "0.2";
    char b_str[] = "0.1";
    char t_str[] = "0.1";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sub(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_sub_2()
{
    int ec = 0;
    char a_str[] = "0.2";
    char b_str[] = "0.01";
    char t_str[] = "0.19";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sub(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_sub_3()
{
    int ec = 0;
    char a_str[] = "0.2 E -3";
    char b_str[] = "0.01 E 4";
    char t_str[] = "-99.9998";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sub(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_sub_4()
{
    int ec = 0;
    char b_str[] = "0.2 E -300";
    char a_str[] = "0.01 E 4";
    char t_str[] = "0.01 E 4";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sub(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_sub_5()
{
    int ec = 0;
    char a_str[] = "1 E -20";
    char b_str[] = "1";
    char t_str[] = "-0.99999999999999999999";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_sub(&a, &b);
    assert(bf_exact_eq(&res, &target));
}

void big_float_mul_1()
{
    int ec = 0;
    char a_str[] = "1 E -1";
    char b_str[] = "1 E -1";
    char t_str[] = "1 E -2";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_mul(&a, &b, &ec);
    assert(bf_exact_eq(&res, &target));
}


void big_float_mul_2()
{
    int ec = 0;
    char a_str[] = "1 E -1";
    char b_str[] = "0";
    char t_str[] = "0";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_mul(&a, &b, &ec);
    assert(bf_exact_eq(&res, &target));
}

void big_float_mul_3()
{
    int ec = 0;
    char a_str[] = "0.123";
    char b_str[] = "0.234234";
    char t_str[] = "0.028810782";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_mul(&a, &b, &ec);
    assert(bf_exact_eq(&res, &target));
}

void big_float_mul_4()
{
    int ec = 0;
    char a_str[] = "0.123456789012345678901234567890";
    char b_str[] = "0.2";
    char t_str[] = "0.024691357802469135780246913578";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_mul(&a, &b, &ec);
    assert(bf_exact_eq(&res, &target));
}

void big_float_mul_5()
{
    int ec = 0;
    char a_str[] = "0.12345678901234567890123456789";
    char b_str[] = "0.12";
    char t_str[] = "0.0148148146814814814681481481468";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_mul(&a, &b, &ec);
    assert(bf_exact_eq(&res, &target));
}

void big_float_mul_6()
{
    int ec = 0;
    char a_str[] = "0.123456789012345678901234567891";
    char b_str[] = "0.123";
    char t_str[] = "0.015185185048518518504851851851";
    big_float_t a = bf_sread(a_str, &ec);
    big_float_t b = bf_sread(b_str, &ec);
    big_float_t target = bf_sread(t_str, &ec);
    big_float_t res = bf_mul(&a, &b, &ec);
    assert(bf_exact_eq(&res, &target));
}



int run_tests()
{
    big_int_read_1();
    big_int_read_2();
    big_int_read_3();
    big_int_read_4();
    big_int_read_5();
    big_int_read_6();
    big_int_read_7();
    big_int_read_8();
    big_int_read_9();
    big_int_read_10();

    big_int_add_1();
    big_int_add_2();
    big_int_add_3();

    big_int_sub_1();
    big_int_sub_2();
    big_int_sub_3();
    big_int_sub_4();
    big_int_sub_5();

    big_int_ls_1();
    big_int_ls_2();
    big_int_ls_3();

    big_int_rs_1();
    big_int_rs_2();
    big_int_rs_3();

    big_int_mul_dec_1();
    big_int_mul_dec_2();
    big_int_mul_dec_3();

    big_int_mul_1();
    big_int_mul_2();
    big_int_mul_3();
    big_int_mul_4();
    big_int_mul_5();
    big_int_mul_6();
    big_int_mul_7();

    big_float_read_1();
    big_float_read_2();
    big_float_read_3();
    big_float_read_4();
    big_float_read_5();
    big_float_read_6();
    big_float_read_7();
    big_float_read_8();
    big_float_read_9();
    big_float_read_10();
    big_float_read_11();
    big_float_read_12();
    big_float_read_13();

    big_float_add_1();
    big_float_add_2();
    big_float_add_3();
    big_float_add_4();
    big_float_add_5();

    big_float_norm_1();

    big_float_sub_1();
    big_float_sub_2();
    big_float_sub_3();
    big_float_sub_4();
    big_float_sub_5();

    big_float_mul_1();
    big_float_mul_2();
    big_float_mul_3();
    big_float_mul_4();
    big_float_mul_5();
    big_float_mul_6();

    printf("Tests passed!");
    return 0;
}