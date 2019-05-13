.name "korZ"
.comment "i'm Zork"          

	sti r1,%:live,%65536
	ld %0, r16

live:
	live %10
	zjmp %:live

