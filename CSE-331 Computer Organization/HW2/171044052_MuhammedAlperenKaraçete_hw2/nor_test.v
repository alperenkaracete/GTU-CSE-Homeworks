module nor_test();

reg [31:0]A;
reg [31:0]B;
wire [31:0]Result;

nor_32bit start(A,B,Result);

initial begin

A = 32'b0000001100010010000100010000001;
B = 32'b0000001010000010100010010000111;

	$monitor(
	   "Input1=%b= %d\nInput2=%b = %d\nSum=%b =%d\n",
		   A,A,B,B,Result,Result);

end

endmodule
