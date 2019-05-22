.name "korZ_live"
.comment "i'm Zork"          

	zjmp %:live
l2:	sti r1,%:live,%1
	ldi 4, %0, r4
	ldi %2,%0, r16
	sti r4,%45,%45
	sti r16,%30,%30
live:
	live %1
	zjmp %:l2

