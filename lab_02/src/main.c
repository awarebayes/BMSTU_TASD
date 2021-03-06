#include <stdio.h>
#include "book.h"
#include "menu.h"
#include "table.h"
#include "util.h"

/*
 * Ввести список литературы, содержащий фамилию автора, 
 * название книги, издательство, количество страниц, вид 
 * литературы 
 * (1: техническая – отрасль, отечественная, переводная, год издания
 *  2: художественная – роман, пьеса, стихи; 3: детская – сказки, стихи).
 *  Вывести список отечественной технической
 *  литературы по указанной отрасли указанного года. 
 */

struct test
{
	int a;
	char b;
	char c;
};

int main()
{
    int ec = ok;
    table_t table = {0};
    read_table_given_path(&table, "../tests/input.txt", &ec);
	printf("%ld", sizeof(struct test));
    if (!ec)
        act_on_table(&table);
    return ec;
}
