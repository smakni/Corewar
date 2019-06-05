.name "korZ"
.comment "i'm Zork"

xxx:
	lldi %0,%0,r3
	st	r3,10
	zjmp %:xxx
