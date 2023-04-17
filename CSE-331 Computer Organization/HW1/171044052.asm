.data

numArr:		.word 1, 3, 2, 6, 1, 2,	#  declare 24 bytes of storage to hold array of 6 integers
k:		.word 3  	#  k divisor
n:		.word 6		#  size of array

i:		.word 0		#  use it for navigate in array
array:		.asciiz "ar"    #  assigned this charachters to register and use them from this registers.
squareBracketOpen:	.asciiz "["
squareBracketClose:	.asciiz "]"
plus: 		.asciiz "+"
equal:		.asciiz "="
comma:		.asciiz ","
totalPairs:	.asciiz "The count of pairs is: "
.text

#For use numArr is my array you can change array inputs from there.
#k is my divisor.If the result of sum mod is equal to k then I take this numbers as pair
#n is size of array
#You can execcute program with changing numArr inputs, k and n values.
.globl main

main:

	la $a1, numArr  #assign values to register for sending funtion to parameters
	la $t2, k
	la $t3, n		  
	lw $a2, ($t2)   #used a register for sending parameters to function
	lw $a3, ($t3)
	jal divisibleSumPairs 
	la  $s3, totalPairs
	li      $v0, 4    #printing part.
	move    $a0, $s3
	syscall 	
	li      $v0, 1    #printing part.
	move    $a0, $v1
	syscall 
	j end
	
	
divisibleSumPairs:	#my funnction for find printing divisible sum pairs.
	lw  $t5, ($t3)
	la  $t6, i
	subi $s1, $a3, 1  #assign array size - 1 to s1 register for execute loop1 size - 1 time
	la $s5, array  	#assign charachters and strings to registers for print operations
	la $s7, squareBracketOpen
	la $t8, squareBracketClose
	la $t9, plus
	la $s4, equal	
  	la $t3, comma						
	j loop1	#executes loop1	

	
loop1:
	bge     $t0, $s1, exit  #executes loop1 until both value in register t0 beomes equal value in register s1 register.When equal, exit from loop.

	# load word from addrs and goes to the next addrs
	move 	$t4, $t0	#save my first loop counter in register for printings.
	addi    $t0, $t0, 1	#first loop counter.same as 'i' in for loop
	subi    $t5, $t0, 1	#my second loop ounter.same as 'j' in nested for loops
	sub	$t6, $a3, $t0   #navigate counter for navigate in array.return last position + 1 in every loop2 end.
	mul	$t6, $t6, 4	#calculate navigate counter for point other value in array.When second loop ends, array shows last number.When I subtract this value from my array, array points value in t0 register.
	lw      $s6, 0($a1)  	#assaign array value to a1 register.	
	j 	loop2		#jump to loop2
assignArray:	
	sub     $a1, $a1, $t6	#substract from my array value from t6 register to point array value position on t0 register.
	j 	loop1		#execute loop1 again
    
loop2:
	beq $t5, $a3, assignArray	#executes loop2 until both value in register t5 beomes equal value in register a3 register.When equal
	addi    $a1, $a1, 4		#finds second value from array for calculation
	lw 	$t7, 0($a1)		#assign array value to t7 register
	move 	$s2, $t7		#move t7 register value to s2 register for printing a[j] value.
	beq	$t5, $s1, assignArray	#if t5 register value is equal to s1 register value finish loop and jump back assignArray 
	add     $t7, $s6, $t7		#find sum of value arr[i]+arr[j]
	div     $t7, $a2		#find division of sum
	mfhi	$t1			#find modular of division
	move    $s0, $t1		#hide modular in s0 register
	bne	$s0, 0,   incrementSecondCounter2	#if modular is equal to 0 then sum can be divisible by k.So go and print.If not go incrementSecondCounter2 and calculate other pairs.
	addi	$t2, $t5, 1		#add t5 register value to 1 for find a[j] value's j position.
print:	
	li      $v0, 11      #printing part.
	li    $a0, '('
	syscall
	li      $v0, 1      #print a[i] value's position
	move    $a0, $t4
	syscall
	li      $v0, 4
    	move    $a0, $t3  
    	syscall
	li      $v0, 1      #print a[j] value's position
	move    $a0, $t2
	syscall
	li      $v0, 11      
	li    $a0, ')'
	syscall
	li      $a0, 32	   #printing spaces
    	li      $v0, 11  
    	syscall
    	li      $v0, 11     
	li    $a0, '-'
	syscall
	li      $v0, 11      
	li    $a0, '>'
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall	
	li      $v0, 4      
	move    $a0, $s5
	syscall
	li      $v0, 4      
	move    $a0, $s7
	syscall
	li      $v0, 1      
	move    $a0, $t4
	syscall
	li      $v0, 4      
	move    $a0, $t8
	syscall	
  	li      $a0, 32
    	li      $v0, 11  
    	syscall
	li      $v0, 4      
	move    $a0, $t9
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall
	li      $v0, 4      
	move    $a0, $s5
	syscall    	
	li      $v0, 4      
	move    $a0, $s7
	syscall
	li      $v0, 1      
	move    $a0, $t2
	syscall
	li      $v0, 4      
	move    $a0, $t8
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall
	li      $v0, 4      
	move    $a0, $s4
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall	
	li      $v0, 1      
	move    $a0, $s6	#print a[i] value 
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall	
	li      $v0, 4      
	move    $a0, $t9
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall			
	li      $v0, 1     	#print a[j] value 
	move    $a0, $s2
	syscall
  	li      $a0, 32
    	li      $v0, 11  
    	syscall
	li      $v0, 4      
	move    $a0, $s4
	syscall
  	li      $a0, 32		#print spaces
    	li      $v0, 11  
    	syscall	
	li      $v0, 1        #print a[i] + a[j] value
	move    $a0, $t7
	syscall	    			
    	li      $v0, 11  
    	li    $a0, '\n'
    	syscall
    	addi	$v1,$v1,1

incrementSecondCounter2:  	#increase t5 register value for ending loop2.As same as j value in nested loops.
	addi    $t5, $t5, 1
    	j       loop2
    	
exit:
	jr $ra   	

end:

