_put:
 push rbp
 mov rbp, rsp 
 sub rsp, 0 
push rax
push rsi
push rdi

lea rsi, [rbp+16]
mov rdi, 1
mov rax, 1
mov rdx, 1
    syscall
 
pop rax
pop rsi
pop rdi
mov rsp, rbp
 pop rbp
ret
_start:
 push 'a'
push  1
call _put
add rsp, 16
