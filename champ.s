.name "NAME"
.comment "COMMENT"

start:
	sti r1, %:zork, %1
	ld %0, r16
	fork %:zork

zork:
	live %1
	zjmp %:zork
