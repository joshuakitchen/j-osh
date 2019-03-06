[BITS 16]
[ORG 0x7C00]
KERNEL_OFFSET equ 0x1000

start:
  mov [BOOT_DRIVE], dl
  mov bp, 0x9000
  mov sp, bp
  call detect_memory

  mov bx, KERNEL_OFFSET
  mov dh, 32
  mov dl, [BOOT_DRIVE]
  call disk_load

  call switch_to_protected

%include "boot/16/error.asm"
%include "boot/16/disk.asm"
%include "boot/16/memory.asm"
%include "boot/32/gdt.asm"
%include "boot/32/switch.asm"

[BITS 32]
BEGIN_PM:
  call KERNEL_OFFSET
  jmp $

BOOT_DRIVE db 0

times 510-($-$$) db 0
dw 0xAA55
