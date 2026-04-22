.global main
.extern int_out

.data
value: .word 0xBD5B7DDE @ skapar hex variabel

.text
main:
    push {ip, lr}

    ldr r0, =value @ hämta addressen som value ligger i minnet
    ldr r0, [r0]   @ gå till addressen och hämta värdet

    asr r1, r0, #1  @hoppa över sign med att skifta ett steg åt höger
    mov r0, r1

    bl int_out         @ hoppa till int_out funktionen

    pop {ip, pc}