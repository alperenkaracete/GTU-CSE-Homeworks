module adder_test();

reg [31:0]A;
reg [31:0]B;
reg Cin;
wire [31:0]Sum;
wire Cout;

adder_32bit start(A,B,Cin,Sum,Cout);

initial begin

A = 32'b0000000000000000000000000000001;
B = 32'b0000000000000000000000000000111;
Cin = 0;

	$monitor(
	   "Input1=%b= %d\nInput2=%b = %d\nSum=%b =%d\n",
		   A,A,B,B,Sum,Sum);

end


endmodule
