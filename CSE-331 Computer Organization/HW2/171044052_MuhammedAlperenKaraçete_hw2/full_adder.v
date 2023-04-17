module full_adder(
	input A,
	input B,
	input Cin,
	output Sum,
	output Cout
	);

wire w1,w2,w3;
xor (w1,A,B);
xor (Sum,w1,Cin);
and (w2,Cin,w1);
and (w3,A,B);
or (Cout,w2,w3);

endmodule
