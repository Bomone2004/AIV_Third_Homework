.ORG $8000

start:
    CLI

    ;                  4 3 2 1 0
    ;  (bitmask: 0b000 S R L D U)

    LDX #%00000001
    STX $0000
    STX $0001

    LDX #%00001111
    STX $0002

    LDX #%11111111
    STX $0003

    LDX #%11110000
    STX $0004

loop:
    LDA $4000       ; read joypad
    AND #%00000001  ; check for Up arrow
    BNE up

    LDA $4000       ; read joypad
    AND #%00000010  ; check for Down arrow
    BNE down

    LDA $4000       ; read joypad
    AND #%00000100  ; check for Left arrow
    BNE left

    LDA $4000       ; read joypad
    AND #%00001000  ; check for Right arrow
    BNE right

    JMP loop


right:
    LDA #$00                 
    STA $0200,X
    CLC

    LDA $0000
    ADC $0001
    STA $0000
    LDA #$02
    LDX $0000
    STA $0200,X 

    JMP loop

left:
    LDA #$00                 
    STA $0200,X
    CLC

    LDA $0000
    ADC $0003
    STA $0000
    LDA #$02
    LDX $0000
    STA $0200,X 

    JMP loop

down:
    LDA #$00
    STA $0200,X
    CLC

    LDA $0000
    ADC $0002
    STA $0000

    LDA $0000
    ADC $0001
    STA $0000

    LDA #$02
    LDX $0000
    STA $0200,X

    JMP loop

up:
    LDA #$00
    STA $0200,X
    CLC

    LDA $0000
    ADC $0004
    STA $0000

    LDA #$02
    LDX $0000
    STA $0200,X

    JMP loop

nmi: 
    RTI

break:
    RTI

.GOTO $FFFA
.DW nmi
.DW start
.DW break