	.file "C:\\Users\\DenisT\\Desktop\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\Bulbot_smallRobot-e78442e9752fb87eb975312f2993b3129a8c8ac9\\PropBLDC.X\\globals.c"
	.section	.debug_abbrev,info
.Ldebug_abbrev0:
	.section	.debug_info,info
.Ldebug_info0:
	.section	.debug_line,info
.Ldebug_line0:
	.section	.text,code
.Ltext0:
	.section	.text,code
	.align	2
	.global	_satureAngle	; export
	.type	_satureAngle,@function
_satureAngle:
.LFB0:
.LSM0:
	.set ___PA___,1
	lnk	#4
	mov	w8,[w15++]
	mov.d	w0,[w14]
.LSM1:
	bra	.L2
.L4:
	mov	#4048,w2
	mov	#16585,w3
	mov.d	[w14],w0
	rcall	___subsf3
	mov.d	w0,w4
	mov.d	w4,[w14]
.L2:
	mov.b	#1,w8
	mov	#4048,w2
	mov	#16457,w3
	mov.d	[w14],w0
	rcall	___gtsf2
	mov	w0,w4
	sub	w4,#0,[w15]
	.set ___BP___,0
	bra	gt,.L3
	clr.b	w8
.L3:
	sub.b	w8,#0,[w15]
	.set ___BP___,0
	bra	nz,.L4
.LSM2:
	bra	.L5
.L7:
	mov	#4048,w2
	mov	#16585,w3
	mov.d	[w14],w0
	rcall	___addsf3
	mov.d	w0,w4
	mov.d	w4,[w14]
.L5:
	mov.b	#1,w8
	mov	#4048,w2
	mov	#49225,w3
	mov.d	[w14],w0
	rcall	___ltsf2
	mov	w0,w4
	sub	w4,#0,[w15]
	.set ___BP___,0
	bra	lt,.L6
	clr.b	w8
.L6:
	sub.b	w8,#0,[w15]
	.set ___BP___,0
	bra	nz,.L7
.LSM3:
	mov.d	[w14],w4
.LSM4:
	mov.d	w4,w0
	mov	[--w15],w8
	ulnk	
	return	
	.set ___PA___,0
.LFE0:
	.section	.debug_frame,info
.Lframe0:
	.4byte	.LECIE0-.LSCIE0
.LSCIE0:
	.4byte	0xffffffff
	.byte	0x1
	.byte	0
	.uleb128 0x1
	.sleb128 2
	.byte	0x25
	.byte	0x12
	.uleb128 0xf
	.sleb128 -2
	.byte	0x9
	.uleb128 0x25
	.uleb128 0xf
	.align	4
.LECIE0:
.LSFDE0:
	.4byte	.LEFDE0-.LASFDE0
.LASFDE0:
	.4byte	.Lframe0
	.4byte	.LFB0
	.4byte	.LFE0-.LFB0
	.align	4
.LEFDE0:
	.section	.text,code
.Letext0:
	.section	.debug_info,info
	.4byte	0x13f
	.2byte	0x2
	.4byte	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.asciz	"GNU C 4.5.1 (XC16, Microchip v1_21) (A) Build date: Jan  2 2014"
	.byte	0x1
	.asciz	"globals.c"
	.ascii	"C:\\\\Users\\\\DenisT\\\\Desktop\\\\Bulbot_smallRobot-e78442e9752fb8"
	.ascii	"7eb975312f2993b3129a8c8ac9\\\\Bulbot_smallRobot-e78442e9752fb87eb975"
	.asciz	"312f2993b3129a8c8ac9\\\\PropBLDC.X"
	.4byte	.Ltext0
	.4byte	.Letext0
	.4byte	.Ldebug_line0
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.asciz	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x4
	.asciz	"float"
	.uleb128 0x3
	.byte	0x1
	.asciz	"satureAngle"
	.byte	0x1
	.byte	0x4
	.byte	0x1
	.4byte	0x109
	.4byte	.LFB0
	.4byte	.LFE0
	.byte	0x1
	.byte	0x5e
	.uleb128 0x4
	.asciz	"angle"
	.byte	0x1
	.byte	0x4
	.4byte	0x109
	.byte	0x2
	.byte	0x7e
	.sleb128 0
	.byte	0x0
	.byte	0x0
	.section	.debug_abbrev,info
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0x8
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x1b
	.uleb128 0x8
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0x0
	.byte	0x0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0x0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0x0
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.uleb128 0x4
	.uleb128 0x5
	.byte	0x0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.section	.debug_pubnames,info
	.4byte	0x1e
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x143
	.4byte	0x112
	.asciz	"satureAngle"
	.4byte	0x0
	.section	.debug_pubtypes,info
	.4byte	0xe
	.2byte	0x2
	.4byte	.Ldebug_info0
	.4byte	0x143
	.4byte	0x0
	.section	.debug_aranges,info
	.4byte	0x14
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x4
	.byte	0x0
	.2byte	0x0
	.2byte	0x0
	.4byte	0x0
	.4byte	0x0
	.section	.debug_line,info
	.4byte	.LELT0-.LSLT0
.LSLT0:
	.2byte	0x2
	.4byte	.LELTP0-.LASLTP0
.LASLTP0:
	.byte	0x1
	.byte	0x1
	.byte	0xf6
	.byte	0xf5
	.byte	0xa
	.byte	0x0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x0
	.byte	0x0
	.byte	0x0
	.byte	0x1
	.byte	0x0
	.asciz	"globals.c"
	.uleb128 0x0
	.uleb128 0x0
	.uleb128 0x0
	.byte	0x0
.LELTP0:
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.Letext0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM0
	.byte	0x17
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM1
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM2
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM3
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LSM4
	.byte	0x15
	.byte	0x0
	.uleb128 0x5
	.byte	0x2
	.4byte	.LFE0
	.byte	0x0
	.uleb128 0x1
	.byte	0x1
.LELT0:
	.section	.debug_str,info
	.section	.text,code

	.section __c30_signature, info, data
	.word 0x0001
	.word 0x0000
	.word 0x0000

; MCHP configuration words

	.set ___PA___,0
	.end
