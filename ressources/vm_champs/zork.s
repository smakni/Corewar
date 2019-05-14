.name "korZ"
.comment "i'm Zork"          

	sti r1,%:live,%65536
	ld %0, r16
	or	r1,%:live,r2

live:
	live %10
	zjmp %:live

