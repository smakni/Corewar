.name "korZ"
.comment "i'm Zork"          

	sti r1,%:live,%42
	ld %0, r16

live:
	live %1
	zjmp %:live

