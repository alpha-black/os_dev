OBJECTS = src/loader.o src/kmain.o src/io.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector \
		-nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T src/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf

all: kernel.elf

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

rOs.iso: kernel.elf
	mv kernel.elf iso/boot/kernel.elf
	genisoimage -R								\
				-b boot/grub/stage2_eltorito	\
				-no-emul-boot					\
				-boot-load-size 4				\
				-A os							\
				-input-charset utf8				\
				-quiet							\
				-boot-info-table				\
				-o iso/rOs.iso					\
				iso

run: rOs.iso
	bochs -f iso/bochsrc.txt -q

%.o: src/%.c
	$(CC) $(CFLAGS) $< -o src/$@

%.o: src/%.s
	$(AS) $(ASFLAGS) $< -o src/$@

clean:
	rm -rf src/*.o iso/boot/kernel.elf iso/rOs.iso
