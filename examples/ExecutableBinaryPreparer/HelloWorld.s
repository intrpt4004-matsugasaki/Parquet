# x86-64 Linux Only

.global _start
.file "HelloWorld.s"


.text
_start:
	# write(stdout, txt, 26)
	mov $1, %rax
	mov $1, %rdi
	lea txt(%rip), %rsi
	mov $26, %rdx
	syscall

	# exit(0)
	mov $60, %rax
	mov $0, %rdi
	syscall

	ret


.section .rodata
txt:
	.string "Hello World from Parquet!\n"
