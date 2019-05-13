.name "korZ"
.comment "i'm Zork"          

	sub r1,r2,r3
	and %2,23,r3
	or %2,23,r3
	xor %2,23,r3
	zjmp %23
	ldi 42,%42,r1
	sti r1,16,%16
	fork %45

