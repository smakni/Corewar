.name "korZ"
.comment "i'm Zork"          

	#live %1
	#sub r1,r2,r3
	#and %2,23,r3
	#or %2,23,r3
	#xor %2,23,r3
	#zjmp %23
	#ldi 42,%42,r1
	ld %42, r10
	ld %21, r11
	sti r1,r10,r11
	#fork %45
	#live %1
	#ld %10,r5
	#st r1,r10
	#add r1,r2,r3
	#aff r2
	#lld %2,r2
	#lldi r1,r2,r3
	#lfork %23

