// ---------------------
// top module
// ---------------------
module top;

// # wire define ############################
  wire  ack;  // _CELL:[B22]
  wire  [15:0] adr;  // _CELL:[B19]
  wire  clk;  // _CELL:[B4]
  wire  clko;  // _CELL:[B5]
  wire  cs;  // _CELL:[B17]
  wire  [7:0] dtin;  // _CELL:[B20]
  wire  [7:0] dtout;  // _CELL:[B21]
  wire  irq0;  // _CELL:[B7]
  wire  irq1;  // _CELL:[B8]
  wire  irq2;  // _CELL:[B9]
  wire  irq3;  // _CELL:[B10]
  wire  irq_clear0;  // _CELL:[B11]
  wire  irq_clear1;  // _CELL:[B12]
  wire  irq_clear2;  // _CELL:[B13]
  wire  irq_clear3;  // _CELL:[B14]
  wire  rst;  // _CELL:[B6]
  wire  we;  // _CELL:[B18]

initial begin 
 $dumpfile("C:\hpdata\csvpp_source_tc\csvcompiler_2\cpu_maker_2\verilog\cpu_test.dump"); 
 $dumpvars(1,cpu_for_testbench); 
 $dumpvars(1,target); 
end 
// # clk(clk) ###############
  clk clk(  // _CELL:
     .clk(clk)  // _CELL:[F4]
    ,.clko(clko)  // _CELL:[F5]
  );

// # cpu_for_testbench(cpu_for_testbench) ###############
  cpu_for_testbench cpu_for_testbench(  // _CELL:
     .ack(ack)  // _CELL:[D22]
    ,.adr(adr)  // _CELL:[D19]
    ,.clk(clk)  // _CELL:[D4]
    ,.clko(clko)  // _CELL:[D5]
    ,.cs(cs)  // _CELL:[D17]
    ,.dtin(dtout)  // _CELL:[D21]
    ,.dtout(dtin)  // _CELL:[D20]
    ,.irq({irq3,irq2,irq1,irq0})  // _CELL:[D15]
    ,.irq_clear({irq_clear3,irq_clear2,irq_clear1,irq_clear0})  // _CELL:[D16]
    ,.rst(rst)  // _CELL:[D6]
    ,.we(we)  // _CELL:[D18]
  );

// # rst(rst) ###############
  rst rst(  // _CELL:
     .rst(rst)  // _CELL:[G6]
  );

// # target(target) ###############
  target target(  // _CELL:
     .ack(ack)  // _CELL:[E22]
    ,.adr(adr)  // _CELL:[E19]
    ,.clk(clk)  // _CELL:[E4]
    ,.clko(clko)  // _CELL:[E5]
    ,.cs(cs)  // _CELL:[E17]
    ,.dtin(dtin)  // _CELL:[E20]
    ,.dtout(dtout)  // _CELL:[E21]
    ,.irq0(irq0)  // _CELL:[E7]
    ,.irq1(irq1)  // _CELL:[E8]
    ,.irq2(irq2)  // _CELL:[E9]
    ,.irq3(irq3)  // _CELL:[E10]
    ,.irq_clear0(irq_clear0)  // _CELL:[E11]
    ,.irq_clear1(irq_clear1)  // _CELL:[E12]
    ,.irq_clear2(irq_clear2)  // _CELL:[E13]
    ,.irq_clear3(irq_clear3)  // _CELL:[E14]
    ,.rst(rst)  // _CELL:[E6]
    ,.we(we)  // _CELL:[E18]
  );

endmodule

