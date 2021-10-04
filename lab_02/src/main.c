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

int main()
{
    int ec = ok;
    FILE *f = fopen("../tests/input.txt", "r");
    table_t table = {0};
    if (!f)
        return file_err;
    int n = 0;
    read_int(NULL, "", &n, f, &ec);
    if (!ec || n != 0)
        table = table_read_file(f, n, &ec);
    if (!ec)
        act_on_table(&table);
    return ec;
}
