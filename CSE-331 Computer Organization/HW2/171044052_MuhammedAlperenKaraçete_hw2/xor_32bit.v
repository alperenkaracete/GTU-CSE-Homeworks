module xor_32bit(A,B,Result);

input [31:0] A,B;
output [31:0] Result;

xor xor1(Result[0],A[0],A[0]),
    xor2(Result[1],A[1],A[1]),
    xor3(Result[2],A[2],A[2]),
    xor4(Result[3],A[3],A[3]),
    xor5(Result[4],A[4],A[4]),
    xor6(Result[5],A[5],A[5]),
    xor7(Result[6],A[6],A[6]),
    xor8(Result[7],A[7],A[7]),
    xor9(Result[8],A[8],A[8]),
    xor10(Result[9],A[9],B[9]),
    xor11(Result[10],A[10],B[10]),
    xor12(Result[11],A[11],B[11]),
    xor13(Result[12],A[12],B[12]),
    xor14(Result[13],A[13],B[13]),
    xor15(Result[14],A[14],B[14]),
    xor16(Result[15],A[15],B[15]),
    xor17(Result[16],A[16],B[16]),
    xor18(Result[17],A[17],B[17]),
    xor19(Result[18],A[18],B[18]),
    xor20(Result[19],A[19],B[19]),
    xor21(Result[20],A[20],B[20]),
    xor22(Result[21],A[21],B[21]),
    xor23(Result[22],A[22],B[22]),
    xor24(Result[23],A[23],B[23]),
    xor25(Result[24],A[24],B[24]),
    xor26(Result[25],A[25],B[25]),
    xor27(Result[26],A[26],B[26]),
    xor28(Result[27],A[27],B[27]),
    xor29(Result[28],A[28],B[28]),
    xor30(Result[29],A[29],B[29]),
    xor31(Result[30],A[30],B[30]),
    xor32(Result[31],A[31],B[31]);
	 
endmodule
