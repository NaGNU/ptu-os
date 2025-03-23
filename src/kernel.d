extern (C):

void 
kernel_main() 
{
    ubyte* video = cast (ubyte*) 0xB8000;
    const char[] msg = "PTU/OS is best OS for NaGNU system";
    
    foreach (i, c; msg)
    {
        video[i * 2] = cast (ubyte)c;
        video[i * 2 + 1] = 0x0F;
    }

    while (true)
    {
        asm { hlt; }
    }
}
