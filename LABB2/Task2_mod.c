.global main
.extern printf 

.data
value: .word 10 @ skapar int variabel
string: .asciz "%x"     @display it with hex

.text
main:
    push {lr}            @ save return address

    ldr r0, =string        @ hämta addressen som string ligger i minnet
    ldr r1, =value        @ hämta addressen som value ligger i minnet
    ldr r1, [r1]        @ hämta värdet från addressen


    bl printf         @ anropa printf("%x", 10)

    pop {lr}
    bx lr