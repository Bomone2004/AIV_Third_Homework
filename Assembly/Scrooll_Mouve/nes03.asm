; Only for emulator
.DB "NES", $1A, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

.ORG $8000

.DEFINE PPUCTRL $2000
.DEFINE PPUMASK $2001
.DEFINE PPUADDR $2006
.DEFINE PPUDATA $2007
.DEFINE PPUSCRL $2005
.DEFINE JOYPAD1 $4016
.DEFINE BUTTON $09

main:
    ; activate NMI + use right nametable for background
    LDA #%10001000
    STA PPUCTRL
    ; enable background rendering
    LDA #%00001000
    STA PPUMASK
    
    ; write to palette (color 0, palette 0)
    LDA #$3F
    STA PPUADDR
    LDA #$00
    STA PPUADDR
    LDA #$14
    STA PPUDATA

    ; now is possible to write just color because of automatic +1
    LDA #$2C
    STA PPUDATA
    
    LDA #$39
    STA PPUDATA
    
    LDA #$28
    STA PPUDATA
    
    ; Write to nametable
    LDA #$20
    STA PPUADDR
    LDA #$00
    STA PPUADDR
    LDA #$01
    STA PPUDATA

    LDX #%00000001
    STX $0001         ; add 1

    LDX #%11111111
    STX $0003         ; subtract 1


loop:
    JSR read_joypad

    LDA BUTTON       ; read joypad
    AND #%00000001   ; check for Right arrow
    BNE right

    LDA BUTTON      ; read joypad
    AND #%00000010  ; check for Left arrow
    BNE left

    LDA BUTTON      ; read joypad
    AND #%00000100   ; check for Up arrow
    BNE up

    LDA BUTTON       ; read joypad
    AND #%00001000   ; check for Down arrow
    BNE down

    JMP loop    

read_joypad:
    LDA #$01
    STA JOYPAD1
    STA BUTTON
    LSR A
    STA JOYPAD1  

loop_joypad:
    LDA JOYPAD1
    LSR A
    ROL BUTTON
    BCC loop_joypad
    RTS

nmi:
    ;TAX ; pre-amble

    ; LDA #$3F
    ; STA PPUADDR
    ; LDA #$03
    ; STA PPUADDR
    
    ; LDA #$19  ; green
    ; STA PPUDATA
    
    ; Increment with register A
    ; LDA $00
    ; ADC #$01
    ; STA $00
    ; STA PPUDATA
    
    ; INC $00
    ; LDA $00
    ; STA PPUDATA

    ; Manage scrolling
    ; LDA #$00    ; fixed position
    ;INC $01
    ;LDA $01
    ;STA PPUSCRL   ; write X
    ;STA PPUSCRL   ; write Y

    ;JSR read_joypad
    
    STY PPUSCRL ; write X
    STX PPUSCRL ; write Y


    ;TXA ; post-amble

    RTI

right:
    ; LDA #$01
    ; ADC $0001
    ; STA $01
    INC $01
    LDY $01

    JMP loop

left:
    DEC $01
    LDY $01

    JMP loop

down:
    INC $01
    LDX $01

    JMP loop

up:
    DEC $01
    LDX $01

    JMP loop
    
irq:
    RTI

.GOTO $FFFA
.DW nmi
.DW main
.DW irq

; table 1: 4k
.INCBIN "chr01.bin"
; table 2: 4k
.INCBIN "chr02.bin"

