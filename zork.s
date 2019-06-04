.name "korZ"
.comment "i'm Zork"

xxx:
	ld %0,r2
	zjmp %:yyy

yyy:
	zjmp %:xxx
