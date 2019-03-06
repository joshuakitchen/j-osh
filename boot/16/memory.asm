[BITS 16]

mmap_ent equ 0x8000
detect_memory:
  mov di, 0x8004
  xor ebx, ebx
  xor bp, bp
  mov edx, 0x0534D4150
  mov eax, 0xe820
  mov [es:di + 20], dword 1
  mov ecx, 24
  int 0x15
  jc short .failed_a
  mov edx, 0x0534D4150
  cmp eax, edx
  jne short .failed_b
  test ebx, ebx
  je short .failed_b
  jmp short .jmpin
.e820lp:
	mov eax, 0xe820
	mov [es:di + 20], dword 1
	mov ecx, 24
	int 0x15
	jc short .e820f
	mov edx, 0x0534D4150
.jmpin:
  jcxz .skipent
  cmp cl, 20
  jbe short .notext
  test byte [es:di + 20], 1
  je short .skipent
.notext:
	mov ecx, [es:di + 8]
	or ecx, [es:di + 12]
	jz .skipent
	inc bp
	add di, 24
.skipent:
	test ebx, ebx
	jne short .e820lp

.e820f:
	mov [mmap_ent], bp
	clc
	ret

.failed_a:
  mov dx, 0x0003
  call print_error

.failed_b:
  mov dx, 0x0004
  call print_error
