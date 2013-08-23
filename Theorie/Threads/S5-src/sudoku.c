#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SUDOKU_MAX (9)
#define SUDOKU_DIM (SUDOKU_MAX)
#define SUDOKU_BOX (3)

typedef struct {
	int grid[SUDOKU_DIM][SUDOKU_DIM];
} sudoku_t;

static sudoku_t sudokus[] = {
	{ /* First sudoku */
		.grid = {
			{8, 1, 5, 3, 4, 2, 9, 6, 7},
			{6, 0, 9, 7, 8, 1, 4, 2, 0},
			{7, 4, 2, 5, 6, 9, 0, 8, 1},
			{3, 8, 4, 9, 0, 6, 5, 1, 2},
			{9, 7, 1, 2, 5, 4, 6, 3, 8},
			{5, 2, 6, 0, 3, 8, 7, 4, 9},
			{4, 0, 3, 8, 2, 7, 0, 9, 6},
			{2, 9, 7, 6, 1, 3, 8, 5, 4},
			{1, 6, 8, 4, 0, 5, 2, 7, 3},
		}
	},
	/* TODO fill with new sudokus */
};


static void print_sudoku(sudoku_t *s)
{
	int i, j;

	for (i = 0; i < SUDOKU_DIM; ++i) {
		if (!(i % SUDOKU_BOX))
			printf("+-------+-------+-------+\n");
		for (j = 0; j < SUDOKU_DIM; ++j) {
			if (!(j % SUDOKU_BOX))
				printf("| ");
			printf("%d ", s->grid[i][j]);
		}
		printf("|\n");
	}
	printf("+-------+-------+-------+\n");
	fflush(stdout);
}

static int validate_sudoku(sudoku_t *s)
{
	int i, j, k, l;

	/* check sum of rows and columns + check that they only
	 * contain once one number from [1, 9] */
	for (i = 0; i < SUDOKU_DIM; ++i) {
		int used_row[SUDOKU_MAX];
		int used_col[SUDOKU_MAX];
		memset(used_row, 0, sizeof(used_row));
		memset(used_col, 0, sizeof(used_col));
		int sum_row = 0, sum_col = 0;
		for (j = 0; j < SUDOKU_DIM; ++j) {
			if (used_row[s->grid[i][j]-1] > 0)
				return 0;
			if (used_col[s->grid[j][i]-1] > 0)
				return 0;
			sum_row += s->grid[i][j];
			sum_col += s->grid[j][i];
			used_row[s->grid[i][j]-1]++;
			used_col[s->grid[j][i]-1]++;
		}
		if (sum_row != 45 || sum_col != 45)
			return 0;
	}

	/* check sum of boxes */
	for (k = 0; k < SUDOKU_DIM / SUDOKU_BOX; ++k) {
		for (l = 0; l < SUDOKU_DIM / SUDOKU_BOX; ++l) {
			int sum = 0;
			for (i = 0; i < SUDOKU_BOX; ++i)
				for (j = 0; j < SUDOKU_BOX; ++j)
				 	sum += s->grid[SUDOKU_BOX * k + i][SUDOKU_BOX * l + j];
			if (sum != 45)
				return 0;
		}
	}


	return 1;
}


int main(int argc, char *argv[])
{
	/* A COMPLETER */
	print_sudoku(&sudokus[0]);

	return 0;
}
