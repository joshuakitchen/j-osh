[BITS 16]

disk_load:
  pusha
  push dx

  mov ah, 0x02
  mov al, dh
  mov cl, 0x02
  mov ch, 0x00
  mov dh, 0x00

  int 0x13
  jc .disk_error

  pop dx
  cmp al, dh
  jne .sector_error
  popa
  ret

.disk_error:
  mov dx, 0x0001
  call print_error

.sector_error:
  mov dx, 0x0002
  call print_error
