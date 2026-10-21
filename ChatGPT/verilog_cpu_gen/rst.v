// ---------------------
// rst module
// ---------------------
module rst(
   rst
);
// # port define ########################
// # output ########
  output  rst;
// # register define ############################ 
  reg  rst; // _CELL:[B3]

initial begin 
 rst = 1'b1; 
 #10000 
 rst = 1'b0; 
end 

endmodule

