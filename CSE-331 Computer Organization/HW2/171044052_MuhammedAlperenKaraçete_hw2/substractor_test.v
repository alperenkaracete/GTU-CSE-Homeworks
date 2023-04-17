module substractor_test();

reg [31:0]A;
reg [31:0]B;
reg Cin;
wire [31:0]Substract;
wire Cout;

substractor_32bit start(A,B,Cin,Substract,Cout);

initial begin

A = 32'b0000000000000000000000000001111;
B = 32'b0000000000000000000000000000111;
Cin = 1;

	$monitor(
	   "Input1=%b= %d\nInput2=%b = %d\nSubstract=%b =%d\n",
		   A,A,B,B,Substract,Substract);

end


endmodule
