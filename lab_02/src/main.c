#include <stdio.h>
#include "book.h"
#include "menu.h"
#include "table.h"

/*
 * Ввести список литературы, содержащий фамилию автора, 
 * название книги, издательство, количество страниц, вид 
 * литературы 
 * (1: техническая – отрасль, отечественная, переводная, год издания
 *  2: художественная – роман, пьеса, стихи; 3: детская – сказки, стихи).
 *  Вывести список отечественной технической
 *  литературы по указанной отрасли указанного года. 
 */

int main()
{
    int ec = ok;
    FILE *f = fopen("../tests/input.txt", "r");
    if (f == NULL)
        return -1;
    table_t table = table_read_file(f, 7, &ec);
    table_update_keys(&table, key_lastname);
    table_sort_keys(&table);
    table_print_proxy(&table);
    return ec;
}
