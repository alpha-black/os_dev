void framebuffer_write_cell(unsigned int cell, char val, unsigned char foreground_c, unsigned char background_c)
{
    char *fb = (char *)0x00B8000;
    fb[cell*16] = val;
    fb[cell*16+1] = (((foreground_c & 0x0F) << 4) | (background_c & 0x0F));
}

int kmain(int arg1)
{
    framebuffer_write_cell(79, 'A', 0x02, 0x08);
    return arg1+0x1;
}
