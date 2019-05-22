.name "korZ"
.comment "i'm Zork"          

	#live %1
	#ld %5,r2
	#and %514,2,r3
	#or %1,15,r3
	#xor 2,1,r3
	#sti r3, %20, %20
	#zjmp %23
	#ldi 42,%42,r1
	#ld 7, r5
	#sti r5,%20,%21
	#fork %45
	#fork %45
	#fork %45
	#live %1
	#sub r1,r2,r3
	#add r1,r2,r3
	#aff r2
	#lld %2,r2
	#lldi r1,r2,r3
	#lfork %23

