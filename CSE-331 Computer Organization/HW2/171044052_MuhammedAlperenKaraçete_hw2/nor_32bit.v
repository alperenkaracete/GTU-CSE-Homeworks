module nor_32bit(A,B,Result);

input [31:0] A,B;
output [31:0] Result;

nor nor1(Result[0],A[0],B[0]),
    nor2(Result[1],A[1],B[1]),
    nor3(Result[2],A[2],B[2]),
    nor4(Result[3],A[3],B[3]),
    nor5(Result[4],A[4],B[4]),
    nor6(Result[5],A[5],B[5]),
    nor7(Result[6],A[6],B[6]),
    nor8(Result[7],A[7],B[7]),
    nor9(Result[8],A[8],B[8]),
    nor10(Result[9],A[9],B[9]),
    nor11(Result[10],A[10],B[10]),
    nor12(Result[11],A[11],B[11]),
    nor13(Result[12],A[12],B[12]),
    nor14(Result[13],A[13],B[13]),
    nor15(Result[14],A[14],B[14]),
    nor16(Result[15],A[15],B[15]),
    nor17(Result[16],A[16],B[16]),
    nor18(Result[17],A[17],B[17]),
    nor19(Result[18],A[18],B[18]),
    nor20(Result[19],A[19],B[19]),
    nor21(Result[20],A[20],B[20]),
    nor22(Result[21],A[21],B[21]),
    nor23(Result[22],A[22],B[22]),
    nor24(Result[23],A[23],B[23]),
    nor25(Result[24],A[24],B[24]),
    nor26(Result[25],A[25],B[25]),
    nor27(Result[26],A[26],B[26]),
    nor28(Result[27],A[27],B[27]),
    nor29(Result[28],A[28],B[28]),
    nor30(Result[29],A[29],B[29]),
    nor31(Result[30],A[30],B[30]),
    nor32(Result[31],A[31],B[31]);
	 
endmodule
