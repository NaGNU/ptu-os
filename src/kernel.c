#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

int strcmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
    while (n && *s1 && (*s1 == *s2)) {
        s1++;
        s2++;
        n--;
    }
    if (n == 0) return 0;
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

#define VIDEO_MEMORY 0xB8000
#define COLOR 0x07
#define KEYBOARD_PORT 0x60
#define MAX_INPUT_LENGTH 1488

static int cursor_x = 0;
static int cursor_y = 0;
static bool cursor_visible = true;
static char input_buffer[MAX_INPUT_LENGTH];
static int input_length = 0;

uint8_t inb(uint16_t port);
void outb(uint16_t port, uint8_t value);
void update_cursor();
void blink_cursor();
void clear_screen();
void print(const char *str);
void execute_command(const char *command);

void putchar(char c) {
    volatile uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY;

    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else {
        video_memory[cursor_y * 80 + cursor_x] = (COLOR << 8) | c;
        cursor_x++;
    }

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }

    if (cursor_y >= 25) {
        for (int i = 0; i < 24 * 80; i++) {
            video_memory[i] = video_memory[i + 80];
        }
        for (int i = 24 * 80; i < 25 * 80; i++) {
            video_memory[i] = (COLOR << 8) | ' ';
        }
        cursor_y = 24;
    }

    update_cursor();
}

void print(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}

void clear_screen() {
    volatile uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY;
    for (int i = 0; i < 80 * 25; i++) {
        video_memory[i] = (COLOR << 8) | ' ';
    }
    cursor_x = 0;
    cursor_y = 0;
}

void update_cursor() {
    uint16_t position = cursor_y * 80 + cursor_x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(position & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((position >> 8) & 0xFF));
}

void blink_cursor() {
    volatile uint16_t *video_memory = (uint16_t *)VIDEO_MEMORY;
    uint16_t cursor_position = cursor_y * 80 + cursor_x;

    if (cursor_visible) {
        video_memory[cursor_position] = (COLOR << 8) | '_';
    } else {
        video_memory[cursor_position] = (COLOR << 8) | ' ';
    }
    cursor_visible = !cursor_visible;
}

void execute_command(const char *command) {
    if (strcmp(command, "help") == 0) {
        print("Available commands:\n");
        print("  help - Show this help message\n");
        print("  clear - Clear the screen\n");
        print("  echo <text> - Print text\n");
        print("  fetch - Print system information\n");
    } else if (strcmp(command, "clear") == 0) {
        clear_screen();
    } else if (strncmp(command, "echo ", 5) == 0) {
        print(command + 5);
        print("\n");
    } else if (strcmp(command, "fetch") == 0) {
        print("OS: PtuOS\n");
        print("Version: 0.1\n");
        print("Architecture: x86_64\n");
    } else {
        print("Unknown command: ");
        print(command);
        print("\n");
    }
}

void keyboard_handler() {
    uint8_t scancode = inb(KEYBOARD_PORT);
    char c = 0;

    switch (scancode) {
        case 0x02: c = '1'; break;
        case 0x03: c = '2'; break;
        case 0x04: c = '3'; break;
        case 0x05: c = '4'; break;
        case 0x06: c = '5'; break;
        case 0x07: c = '6'; break;
        case 0x08: c = '7'; break;
        case 0x09: c = '8'; break;
        case 0x0A: c = '9'; break;
        case 0x0B: c = '0'; break;
        case 0x10: c = 'q'; break;
        case 0x11: c = 'w'; break;
        case 0x12: c = 'e'; break;
        case 0x13: c = 'r'; break;
        case 0x14: c = 't'; break;
        case 0x15: c = 'y'; break;
        case 0x16: c = 'u'; break;
        case 0x17: c = 'i'; break;
        case 0x18: c = 'o'; break;
        case 0x19: c = 'p'; break;
        case 0x1E: c = 'a'; break;
        case 0x1F: c = 's'; break;
        case 0x20: c = 'd'; break;
        case 0x21: c = 'f'; break;
        case 0x22: c = 'g'; break;
        case 0x23: c = 'h'; break;
        case 0x24: c = 'j'; break;
        case 0x25: c = 'k'; break;
        case 0x26: c = 'l'; break;
        case 0x2C: c = 'z'; break;
        case 0x2D: c = 'x'; break;
        case 0x2E: c = 'c'; break;
        case 0x2F: c = 'v'; break;
        case 0x30: c = 'b'; break;
        case 0x31: c = 'n'; break;
        case 0x32: c = 'm'; break;
        case 0x39: c = ' '; break;
        case 0x1C: c = '\n'; break;
        case 0x0E: c = '\b'; break;
        default: break;
    }

    if (c == '\b') {
        if (input_length > 0) {
            input_length--;
            putchar('\b');
        }
    } else if (c == '\n') {
        putchar('\n');
        input_buffer[input_length] = '\0';
        execute_command(input_buffer);
        input_length = 0;
        print("$ ");
    } else if (c != 0 && input_length < MAX_INPUT_LENGTH - 1) {
        putchar(c);
        input_buffer[input_length++] = c;
    }

    update_cursor();
    outb(0x20, 0x20);
}

uint8_t inb(uint16_t port) {
    uint8_t value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

void outb(uint16_t port, uint8_t value) {
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void init_pic() {
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0xFD);
    outb(0xA1, 0xFF);
}

void kernel_main(void) {
    clear_screen();
    init_pic();

    print("Welcome to PtuOS (64-bit)!\n");
    print("Type 'help' for a list of commands.\n");
    print("$ ");

    while (1) {
        blink_cursor();
        for (volatile int i = 0; i < 1000000; i++);
    }
}
