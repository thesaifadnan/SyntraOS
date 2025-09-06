bits 32
section .text
	align 4
	dd 0x1BADB002
	dd 0x00
	dd - (0x1BADB002 + 0x00)

global start
extern kernelMain

start:
	cli
	mov esp, stackSpace
	call kernelMain
	hlt

section .bss
resb 8192

stackSpace:

readPort:
	mov edx, [esp + 4]
	in al, dx
	ret

writePort:
	mov al, [esp + 4]
	mov dx, [esp + 4 + 4]
	out dx, al
	ret