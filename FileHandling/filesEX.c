#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void tail(char *file_name, int N)
{
    int char_to_print_on_screen;
    int line_counter = 0;
    int loop_offset = -1;

    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        perror("fopen read");
        return;
    }

    fseek(fp, -1, SEEK_END);

    while (line_counter < N && (ftell(fp) != 0))
    {
        int ch = fgetc(fp);
        if (ch == '\n')
        {
            line_counter++;
        }
        loop_offset--;
        fseek(fp, loop_offset, SEEK_END);
    }

    while ((char_to_print_on_screen = fgetc(fp)) != EOF)
    {
        putchar(char_to_print_on_screen);
    }

    fclose(fp);
}

void wc(char *file_name)
{
    int line_counter = 0;
    int byte_counter = 0;
    int word_counter = 0;
    int ch;
    bool in_word = false;

    FILE *fp = fopen(file_name, "r");
    if (!fp)
    {
        perror("fopen read");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (!isspace(ch))
        {
            in_word = true;
        }
        else
        {
            if (in_word == true)
            {
                word_counter++;
                in_word = false;
            }
        }

        if (ch == '\n')
        {
            line_counter++;
        }
        byte_counter++;
    }

    if (in_word == true)
    {
        word_counter++;
    }

    printf("%d, %d, %d\n", line_counter, word_counter, byte_counter);
    fclose(fp);
}

int main()
{
    // tail("sherlock.txt", 10);
    wc("sherlock.txt");
    return 0;
}