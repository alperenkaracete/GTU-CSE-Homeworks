module and_32bit(A,B,Result);

input [31:0] A,B;
output [31:0] Result;

and and1(Result[0],A[0],B[0]),
    and2(Result[1],A[1],B[1]),
    and3(Result[2],A[2],B[2]),
    and4(Result[3],A[3],B[3]),
    and5(Result[4],A[4],B[4]),
    and6(Result[5],A[5],B[5]),
    and7(Result[6],A[6],B[6]),
    and8(Result[7],A[7],B[7]),
    and9(Result[8],A[8],B[8]),
    and10(Result[9],A[9],B[9]),
    and11(Result[10],A[10],B[10]),
    and12(Result[11],A[11],B[11]),
    and13(Result[12],A[12],B[12]),
    and14(Result[13],A[13],B[13]),
    and15(Result[14],A[14],B[14]),
    and16(Result[15],A[15],B[15]),
    and17(Result[16],A[16],B[16]),
    and18(Result[17],A[17],B[17]),
    and19(Result[18],A[18],B[18]),
    and20(Result[19],A[19],B[19]),
    and21(Result[20],A[20],B[20]),
    and22(Result[21],A[21],B[21]),
    and23(Result[22],A[22],B[22]),
    and24(Result[23],A[23],B[23]),
    and25(Result[24],A[24],B[24]),
    and26(Result[25],A[25],B[25]),
    and27(Result[26],A[26],B[26]),
    and28(Result[27],A[27],B[27]),
    and29(Result[28],A[28],B[28]),
    and30(Result[29],A[29],B[29]),
    and31(Result[30],A[30],B[30]),
    and32(Result[31],A[31],B[31]);

endmodule
