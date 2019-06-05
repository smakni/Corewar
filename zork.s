.name "korZ"
.comment "i'm Zork"

xxx:
#	st  r2,0
#	ld	%0,r3
	ldi %-400,%0,r1
	st	r1,10
	zjmp %:xxx
