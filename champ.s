.name "Donatello"
.comment "KOWABUNGAAAA !!!"

	ld %654860, r2
	st r1, 112
	st r1, 332
	st r1, 124
	st r1, 108
	st r1, 81
	ld %0, r15
	fork %:factory2

getout:
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	
	st r2, -174	

factory:
	live %42
	fork %:divide
	zjmp %:factory

factory2:
	live %42
	fork %:divide
	zjmp %:factory2

divide:
	live %42
	fork %:def
	zjmp %:zork

def:
	live %42
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	st r1, 372
	zjmp %:def

zork:
	live %42
	zjmp %:zork

