ARCH=i386
ARCHDIR=kernel/arch/${ARCH}

C_SOURCES = $(wildcard kernel/include/*.c kernel/include/drivers/*.c kernel/include/cpu/*.c kernel/*.c kernel/shell/*.c $(ARCHDIR)/*.c $(ARCHDIR)/drivers/*.c $(ARCHDIR)/cpu/*.c)
HEADERS = $(wildcard kernel/include/*.h kernel/include/drivers/*.h kernel/include/cpu/*.h kernel/*.h kernel/shell/*.h $(ARCHDIR)/*.h $(ARCHDIR)/drivers/*.h $(ARCHDIR)/cpu/*.h)
OBJS = ${C_SOURCES:.c=.o $(ARCHDIR)/drivers/interrupt.o}

CC = gcc
LINKER = ld

CFLAGS = -g -m32 -fno-stack-protector -nostdlib -I kernel/include/
LINKER_FLAGS = -m elf_i386

.PHONY: clean

all: os.bin

os.bin: boot/bootsect.o kernel.bin
	dd if=/dev/zero of=$@ bs=1kB count=1440
	dd conv=notrunc if=boot/bootsect.o of=$@
	dd conv=notrunc if=kernel.bin of=$@ seek=1

boot/bootsect.o: boot/bootsect.asm
	nasm -f bin $< -o $@

kernel.bin: boot/kernel_entry.o ${OBJS}
	${LINKER} ${LINKER_FLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

run: all
	qemu-system-i386 -drive file=os.bin,if=floppy,format=raw

%.o: %.c
	${CC} ${CFLAGS} -ffreestanding -fno-pie -c $< -o $@

%.o: %.asm
	nasm $< -f elf -o $@

clean:
	rm -r *.bin boot/*.o kernel/*.o
