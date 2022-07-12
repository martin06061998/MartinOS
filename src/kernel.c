#include "kernel.h"
#include <stddef.h>
#include <stdint.h>

uint16_t *video_memmory = 0;
uint16_t terminal_row = 0;
uint16_t terminal_column = 0;
uint16_t terminal_make_char(char c, char color)
{
    return (color << 8) | c;
}

void terminal_putchar(int x, int y, char c, char color)
{
    video_memmory[(y * VGA_WIDTH) + x] = terminal_make_char(c, color);
}

void terminal_initialize()
{
    video_memmory = (uint16_t *)(0xB8000);
    for (int y = 0; y < VGA_HEIGHT; y++)
    {
        for (int x = 0; x < VGA_WIDTH; x++)
        {
            terminal_putchar(x, y, ' ', 0);
        }
    }
}

size_t strlen(const char *str)
{
    size_t len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}

void terminal_writechar(char c, char color)
{
    if (c == '\n')
    {
        terminal_column = 0;
        terminal_row++;
        return;
    }
    terminal_putchar(terminal_column, terminal_row, c, color);
    terminal_column++;
    if (terminal_column >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row++;
    }
}

void print(const char *str)
{
    size_t len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        terminal_writechar(str[i], 15);
    }
}

void kernel_main()
{
    terminal_initialize();
    print("Hello World!");
}