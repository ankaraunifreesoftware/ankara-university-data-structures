#include <stdio.h>
#include <stdlib.h>

int check_row(char **grid, char *word, int wordlen, int sr, int sc, int row, int col, int orientation)
{
    int i = sc, cnt = 0;
    if (orientation == 1)
    {
        while (i < col && cnt < wordlen)
        {
            if (grid[sr][i] != word[cnt])
            {
                return 0;
            }
            i++;
            cnt++;
        }
    }
    else
    {
        while (i >= 0 && cnt < wordlen)
        {
            if (grid[sr][i] != word[cnt])
            {
                return 0;
            }
            i--;
            cnt++;
        }
    }

    if (cnt == wordlen)
    {
        return 1;
    }
    return 0;
}

int check_col(char **grid, char *word, int wordlen, int sr, int sc, int row, int col, int orientation)
{
    int i = sr, cnt = 0;
    if (orientation == 1)
    {
        while (i < row && cnt < wordlen)
        {
            if (grid[i][sc] != word[cnt])
            {
                return 0;
            }
            i++;
            cnt++;
        }
    }
    else
    {
        while (i >= 0 && cnt < wordlen)
        {
            if (grid[i][sc] != word[cnt])
            {
                return 0;
            }
            i--;
            cnt++;
        }
    }

    if (cnt == wordlen)
    {
        return 1;
    }
    return 0;
}

int check_diag(char **grid, char *word, int wordlen, int sr, int sc, int row, int col, int orientationr, int orientationc)
{
    int i = sr, j = sc, cnt = 0;
    if (orientationr == 1 && orientationc == 1)
    {
        while (i < row && j < col && cnt < wordlen)
        {
            if (grid[i][j] != word[cnt])
            {
                return 0;
            }
            i++;
            j++;
            cnt++;
        }
    }
    else if (orientationr == 1 && orientationc == -1)
    {
        while (i < row && j >= 0 && cnt < wordlen)
        {
            if (grid[i][j] != word[cnt])
            {
                return 0;
            }
            i++;
            j--;
            cnt++;
        }
    }
    else if (orientationr == -1 && orientationc == 1)
    {
        while (i >= 0 && j < col && cnt < wordlen)
        {
            if (grid[i][j] != word[cnt])
            {
                return 0;
            }
            i--;
            j++;
            cnt++;
        }
    }
    else
    {
        while (i >= 0 && j >= 0 && cnt < wordlen)
        {
            if (grid[i][j] != word[cnt])
            {
                return 0;
            }
            i--;
            j--;
            cnt++;
        }
    }

    if (cnt == wordlen)
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    char **grid = malloc(15 * (sizeof(char *)));
    int **show = malloc(15 * (sizeof(int *)));
    for (int i = 0; i < 15; i++)
    {
        grid[i] = malloc(15 * sizeof(char));
        show[i] = calloc(15, sizeof(int));
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            scanf("%c ", &grid[i][j]);
        }
    }

    char *userInput;
    char c;
    int i = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            break;
        }
        userInput = realloc(userInput, (i + 1) * sizeof(char));
        userInput[i] = c;
        i++;
    }

    int wordlen = i;

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (check_row(grid, userInput, wordlen, i, j, 15, 15, 1))
            {
                for (int k = j; k < j + wordlen; k++)
                {
                    show[i][k] = 1;
                }
            }
            if (check_row(grid, userInput, wordlen, i, j, 15, 15, -1))
            {
                for (int k = j; k > j - wordlen; k--)
                {
                    show[i][k] = 1;
                }
            }
            if (check_col(grid, userInput, wordlen, i, j, 15, 15, 1))
            {
                for (int k = i; k < i + wordlen; k++)
                {
                    show[k][j] = 1;
                }
            }
            if (check_col(grid, userInput, wordlen, i, j, 15, 15, -1))
            {
                for (int k = i; k > i - wordlen; k--)
                {
                    show[k][j] = 1;
                }
            }
            if (check_diag(grid, userInput, wordlen, i, j, 15, 15, 1, 1))
            {
                for (int k = i, l = j; k < i + wordlen; k++, l++)
                {
                    show[k][l] = 1;
                }
            }
            if (check_diag(grid, userInput, wordlen, i, j, 15, 15, -1, 1))
            {
                for (int k = i, l = j; k > i - wordlen; k--, l++)
                {
                    show[k][l] = 1;
                }
            }
            if (check_diag(grid, userInput, wordlen, i, j, 15, 15, 1, -1))
            {
                for (int k = i, l = j; k < i + wordlen; k++, l--)
                {
                    show[k][l] = 1;
                }
            }
            if (check_diag(grid, userInput, wordlen, i, j, 15, 15, -1, -1))
            {
                for (int k = i, l = j; k > i - wordlen; k--, l--)
                {
                    show[k][l] = 1;
                }
            }
        }
    }

    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (show[i][j] == 1)
            {
                printf("%c", grid[i][j]);
            }
            else
            {
                printf("*");
            }
        }
        printf("\n");
    }

    return 0;
}