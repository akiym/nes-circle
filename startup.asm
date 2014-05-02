;----------------------------------------------------------------------------
;				NES Startup
;					Copyright (C) 2007, Tekepen
;----------------------------------------------------------------------------
.setcpu		"6502"
.autoimport	on
.IMPORTZP	sp

.global	_NesMain

; iNESヘッダ
.segment "HEADER"
	.byte	$4E, $45, $53, $1A	; "NES" Header
	.byte	$02			; PRG-BANKS
	.byte	$01			; CHR-BANKS
	.byte	$01			; 0:Horizontal/1:Vertical/3:Vertical & WRAM Mirror
	.byte	$00			; 
	.byte	$00, $00, $00, $00	; 
	.byte	$00, $00, $00, $00	; 

.segment "STARTUP"
; リセット割り込み
.proc	Reset
	sei
	ldx	#$ff
	txs
	
	; ソフトウェアスタック設定
	lda	#$ff
	sta	sp
	lda	#$03
	sta	sp + 1
	
	jsr	_NesMain
	
.endproc
.proc	NMI
	jsr _NMIProc
.endproc

.segment "VECINFO"
	.word	NMI
	.word	Reset
	.word	$0000

; パターンテーブル
.segment "CHARS"
	.incbin "character.chr"
