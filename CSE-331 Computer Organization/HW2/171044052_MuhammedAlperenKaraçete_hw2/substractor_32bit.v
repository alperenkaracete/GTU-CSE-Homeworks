module substractor_32bit (
   input [31:0]A,
	input [31:0]B,
   input Cin,
   output [31:0]Substract,
   output Cout
	);
   wire [31:0]Bor;
	wire [31:0]notB;
	
	
   not(notB[0],B[0]);
	not(notB[1],B[1]);
	not(notB[2],B[2]);
	not(notB[3],B[3]);
	not(notB[4],B[4]);
	not(notB[5],B[5]);
	not(notB[6],B[6]);
	not(notB[7],B[7]);
	not(notB[8],B[8]);
	not(notB[9],B[9]);
	not(notB[10],B[10]);
	not(notB[11],B[11]);
	not(notB[12],B[12]);
	not(notB[13],B[13]);
	not(notB[14],B[14]);
	not(notB[15],B[15]);
	not(notB[16],B[16]);
	not(notB[17],B[17]);
	not(notB[18],B[18]);
	not(notB[19],B[19]);
	not(notB[20],B[20]);
	not(notB[21],B[21]);
	not(notB[22],B[22]);
	not(notB[23],B[23]);
	not(notB[24],B[24]);
	not(notB[25],B[25]);
	not(notB[26],B[26]);
	not(notB[27],B[27]);
	not(notB[28],B[28]);
	not(notB[29],B[29]);
	not(notB[30],B[30]);
	not(notB[31],B[31]); 
	
	full_adder FA0(A[0],notB[0],Cin,Substract[0],Cout0),
				  FA1(A[1],notB[1],Cout0,Substract[1],Cout1),
				  FA2(A[2],notB[2],Cout1,Substract[2],Cout2),
				  FA3(A[3],notB[3],Cout2,Substract[3],Cout3),
				  FA4(A[4],notB[4],Cout3,Substract[4],Cout4),
				  FA5(A[5],notB[5],Cout4,Substract[5],Cout5),
				  FA6(A[6],notB[6],Cout5,Substract[6],Cout6),
				  FA7(A[7],notB[7],Cout6,Substract[7],Cout7),
				  FA8(A[8],notB[8],Cout7,Substract[8],Cout8),
				  FA9(A[9],notB[9],Cout8,Substract[9],Cout9),
				  FA10(A[10],notB[10],Cout9,Substract[10],Cout10),
				  FA11(A[11],notB[11],Cout10,Substract[11],Cout11),
				  FA12(A[12],notB[12],Cout11,Substract[12],Cout12),
				  FA13(A[13],notB[13],Cout12,Substract[13],Cout13),
				  FA14(A[14],notB[14],Cout13,Substract[14],Cout14),
				  FA15(A[15],notB[15],Cout14,Substract[15],Cout15),
				  FA16(A[16],notB[16],Cout15,Substract[16],Cout16),
				  FA17(A[17],notB[17],Cout16,Substract[17],Cout17),
				  FA18(A[18],notB[18],Cout17,Substract[18],Cout18),
				  FA19(A[19],notB[19],Cout18,Substract[19],Cout19),
				  FA20(A[20],notB[20],Cout19,Substract[20],Cout20),
				  FA21(A[21],notB[21],Cout20,Substract[21],Cout21),
				  FA22(A[22],notB[22],Cout21,Substract[22],Cout22),
				  FA23(A[23],notB[23],Cout22,Substract[23],Cout23),
				  FA24(A[24],notB[24],Cout23,Substract[24],Cout24),
				  FA25(A[25],notB[25],Cout24,Substract[25],Cout25),
				  FA26(A[26],notB[26],Cout25,Substract[26],Cout26),
				  FA27(A[27],notB[27],Cout26,Substract[27],Cout27),
				  FA28(A[28],notB[28],Cout27,Substract[28],Cout28),
				  FA29(A[29],notB[29],Cout28,Substract[29],Cout29),
				  FA30(A[30],notB[30],Cout29,Substract[30],Cout30),
				  FA31(A[31],notB[31],Cout30,Substract[31],Cout31);
	
endmodule
