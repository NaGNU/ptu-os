void kernel_main(void) {
    volatile unsigned char *video_memory = (unsigned char *)0xB8000;
    const char *message = "Hello, Kernel World!";
    for (int i = 0; message[i] != '\0'; i++) {
        video_memory[i * 2] = message[i];      // Символ
        video_memory[i * 2 + 1] = 0x07;        // Атрибуты (цвет)
    }
    while (1);
}
