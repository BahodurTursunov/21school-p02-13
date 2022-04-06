#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h> //библиотека управления файлами

#define WIDTH 81
#define HEIGHT 25

void draw(char matrix[HEIGHT][WIDTH]);
void setup(char matrix[HEIGHT][WIDTH]); // standart values
void logic(char matrix[HEIGHT][WIDTH], int *game_over);
int count_neighbors(char field[HEIGHT][WIDTH], int x, int y);
void set_speed(double *speed, char *mode);
void finish();

int main()
{
    FILE *f;
    char field[HEIGHT][WIDTH];
    double speed = 1.0;
    int game_over = 0;
    char mode = '1';
    setup(field);
    f = freopen("/dev/tty", "r", stdin);
    system("stty cbreak");
    while (!game_over)
    {
        draw(field);
        logic(field, &game_over);
        set_speed(&speed, &mode);
        if (mode == 'z')
        {
            game_over = 1;
        }
        usleep(speed * 100000);
    }
    fclose(f);
    finish();
    return 0;
}

void set_speed(double *speed, char *mode)
{
    int old = fcntl(0, F_GETFL);
    fcntl(0, F_SETFL, old | O_NONBLOCK);
    *mode = getchar();
    fcntl(0, F_SETFL, old);
    if (*mode == '1')
    {
        *speed = 1.5;
    }
    else if (*mode == '2')
    {
        *speed = 1.25;
    }
    else if (*mode == '3')
    {
        *speed = 1.0;
    }
    else if (*mode == '4')
    {
        *speed = 0.75;
    }
    else if (*mode == '5')
    {
        *speed = 0.5;
    }
}

void draw(char matrix[HEIGHT][WIDTH])
{
    printf("\e[H\e[2J\e[3J");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", matrix[i][j]);
        }
    }
}

void setup(char matrix[HEIGHT][WIDTH])
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            scanf("%c", &matrix[i][j]);
        }
    }
}

int count_neighbors(char field[HEIGHT][WIDTH], int x, int y)
{
    int sum = 0;
    int col = 0;
    int row = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            col = (x + i + HEIGHT) % HEIGHT;
            row = (y + j + WIDTH - 1) % (WIDTH - 1);
            if (field[col][row] == '*')
            {
                sum++;
            }
        }
    }
    if (field[x][y] == '*')
    {
        sum--;
    }
    return sum;
}

void logic(char matrix[HEIGHT][WIDTH], int *game_over)
{
    char state = ' ';
    int neighbors = 0;
    char next_gen[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH - 1; j++)
        {
            state = matrix[i][j];
            neighbors = count_neighbors(matrix, i, j);
            if (state == '.' && neighbors == 3)
            {
                next_gen[i][j] = '*';
            }
            else if (state == '*' && (neighbors < 2 || neighbors > 3))
            {
                next_gen[i][j] = '.';
            }
            else
            {
                next_gen[i][j] = state;
            }
        }
    }
    int check = 0;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH - 1; j++)
        {
            if (matrix[i][j] != next_gen[i][j])
            {
                check = 1;
            }
            matrix[i][j] = next_gen[i][j];
        }
    }
    if (!check)
    {
        *game_over = 1;
    }
}

void finish()
{
    printf("GAME OVER!!!\n");
}
