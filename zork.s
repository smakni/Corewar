.name "korZ"
.comment "i'm Zork"

	sti r1,%0,%1
	ld %0, r16

live:
		live %1
		fork %45
		zjmp %:live
