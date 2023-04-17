module adder_32bit(
	input [31:0]A,
	input [31:0]B,
	input Cin,
	output [31:0]Sum,
	output Cout
	);
	
	full_adder FA0(A[0],B[0],Cin,Sum[0],Cout0),
				  FA1(A[1],B[1],Cout0,Sum[1],Cout1),
				  FA2(A[2],B[2],Cout1,Sum[2],Cout2),
				  FA3(A[3],B[3],Cout2,Sum[3],Cout3),
				  FA4(A[4],B[4],Cout3,Sum[4],Cout4),
				  FA5(A[5],B[5],Cout4,Sum[5],Cout5),
				  FA6(A[6],B[6],Cout5,Sum[6],Cout6),
				  FA7(A[7],B[7],Cout6,Sum[7],Cout7),
				  FA8(A[8],B[8],Cout7,Sum[8],Cout8),
				  FA9(A[9],B[9],Cout8,Sum[9],Cout9),
				  FA10(A[10],B[10],Cout9,Sum[10],Cout10),
				  FA11(A[11],B[11],Cout10,Sum[11],Cout11),
				  FA12(A[12],B[12],Cout11,Sum[12],Cout12),
				  FA13(A[13],B[13],Cout12,Sum[13],Cout13),
				  FA14(A[14],B[14],Cout13,Sum[14],Cout14),
				  FA15(A[15],B[15],Cout14,Sum[15],Cout15),
				  FA16(A[16],B[16],Cout15,Sum[16],Cout16),
				  FA17(A[17],B[17],Cout16,Sum[17],Cout17),
				  FA18(A[18],B[18],Cout17,Sum[18],Cout18),
				  FA19(A[19],B[19],Cout18,Sum[19],Cout19),
				  FA20(A[20],B[20],Cout19,Sum[20],Cout20),
				  FA21(A[21],B[21],Cout20,Sum[21],Cout21),
				  FA22(A[22],B[22],Cout21,Sum[22],Cout22),
				  FA23(A[23],B[23],Cout22,Sum[23],Cout23),
				  FA24(A[24],B[24],Cout23,Sum[24],Cout24),
				  FA25(A[25],B[25],Cout24,Sum[25],Cout25),
				  FA26(A[26],B[26],Cout25,Sum[26],Cout26),
				  FA27(A[27],B[27],Cout26,Sum[27],Cout27),
				  FA28(A[28],B[28],Cout27,Sum[28],Cout28),
				  FA29(A[29],B[29],Cout28,Sum[29],Cout29),
				  FA30(A[30],B[30],Cout29,Sum[30],Cout30),
				  FA31(A[31],B[31],Cout30,Sum[31],Cout31);
endmodule
				  