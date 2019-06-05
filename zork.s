.name "korZ"
.comment "i'm Zork"

xxx:
	ldi %0,%0,r1
	sti	r1,-10,r99
	zjmp %:xxx
