#include "../inc/menu.h"
#include "../inc/util.h"
#include "../inc/any_matrix.h"
#include "../inc/profile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_CHOICE 123
#define TIMES 50


int get_choice(int argc, char **argv) {
	int choice = -1;
	while (choice < 0) {
		int ec = 0;
		for (int i = 0; i < argc; i++) {
			printf("%d: %s\n", i, argv[i]);
		}
		printf("%d: EXIT\n", EXIT_CHOICE);
		read_int(stdin, stdout, "Your choice: ", &choice, &ec);
		if (ec) {
			choice = -1;
			continue;
		}
		if (choice < 0 || (choice > argc - 1 && choice != EXIT_CHOICE))
			choice = -1;
	}
	return choice;
}

any_matrix_t menu_read_matrix(int *ec) {
	any_matrix_t zero = {0};
	int mat_kind = -1;
	int is_stdin = -1;

	int input_ec = 0;
	while (mat_kind != 0 && mat_kind != 1) {
		input_ec = 0;
		printf("Which kind of matrix do you want to read?\n");
		printf("0 - dense, 1 - sparse\n");
		read_int(stdin, stdout, "Choice: ", &mat_kind, &input_ec);
	}

	while (is_stdin != 0 && is_stdin != 1) {
		input_ec = 0;
		printf("Read from file or stdin?\n");
		printf("0 - file, 1 - stdin\n");
		read_int(stdin, stdout, "Choice: ", &is_stdin, &input_ec);
	}
	if (*ec)
		return zero;

	if (is_stdin)
		return any_matrix_from_file(mat_kind, stdin, stdout, ec);

	char path[BUFFER_SIZE];
	read_str(stdin, stdout, "File path: ", path, ec);

	FILE *fin = fopen(path, "r");
	if (!fin)
		*ec = file_err;

	if (!*ec)
		return any_matrix_from_file(mat_kind, fin, NULL, ec);
	return zero;
}

void menu_read_matrix_handle_errors(any_matrix_t *matrix, int *matrix_read) {
	int ec = 0;
	any_matrix_t temp_matrix = menu_read_matrix(&ec);
	if (!ec) {
		if (*matrix_read)
			any_matrix_delete(matrix);
		*matrix = temp_matrix;
		*matrix_read = 1;
	} else {
		printf("Error occured with code %d\n", ec);
		printf("Your input will be ignored... For now...\n");
	}
}

void menu_matrix_vector_product(any_matrix_t *matrix, any_matrix_t *vector) {
	if (any_matrix_rows(vector) != any_matrix_columns(matrix) || any_matrix_columns(vector) != 1) {
		printf("Error: bad dimensions for vector and matrix!\n");
		return;
	}

	int mat_kind = -1;
	int ec = 0;
	while (mat_kind != 0 && mat_kind != 1) {
		printf("Which kind of matrix do you want as result?\n");
		printf("0 - dense, 1 - sparse\n");
		read_int(stdin, stdout, "Choice: ", &mat_kind, &ec);
	}
	any_matrix_t res = any_matrix_vector_product(mat_kind, matrix, vector);
	any_matrix_print(&res);
	any_matrix_delete(&res);
}

void menu_profile() {
	int n_rows = 10000;
	int n_cols = 1000;
	printf("Matrix vector product time in ms\n");
	printf("Matrix is %dx%d, vector is 1x%d\n", n_rows, n_cols, n_rows);
	printf("full\tdense\tsparse\t\n");
	for (int i = 1; i < 100; i += 5) {
		time_measurement_t m = measure_time(n_rows, n_cols, i);
		printf("%d\t%ld\t%ld\n", i, m.dense, m.sparse);
	}

	printf("Matrix size in bytes\n");
	printf("Matrix is %dx%d\n", n_rows, n_cols);
	printf("full\tdense\tsparse\t\n");
	for (int i = 1; i < 100; i += 5) {
		mem_measurement_t m = measure_memory(n_rows, n_cols, i);
		printf("%d\t%ld\t%ld\n", i, m.dense, m.sparse);
	}
}

void main_loop() {
	int choice = 0;
	char *choices[] = {
			"Read matrix",
			"Read vector",
			"Muiltiply matrix by vector",
			"Profile",
	};

	any_matrix_t vector = {0};
	any_matrix_t matrix = {0};
	int matrix_read = 0;
	int vector_read = 0;

	while (choice != EXIT_CHOICE) {
		printf("\n");
		choice = get_choice(sizeof(choices) / sizeof(char *), choices);
		printf("\n");
		switch (choice) {
			case 0:
				menu_read_matrix_handle_errors(&matrix, &matrix_read);
				break;
			case 1:
				menu_read_matrix_handle_errors(&vector, &vector_read);
				break;
			case 2:
				if (!matrix_read || !vector_read)
					printf("Input matrix and vector first!\n");
				else
					menu_matrix_vector_product(&matrix, &vector);
				break;
			case 3:
				menu_profile();
				break;
			default:
				break;
		}
	}

	if (matrix_read)
		any_matrix_delete(&matrix);
	if (vector_read)
		any_matrix_delete(&vector);
}