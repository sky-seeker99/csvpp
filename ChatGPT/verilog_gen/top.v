// ---------------------
// top module
// ---------------------
module top;

// # wire define ############################
  wire  ack;  // _CELL:[B9]
  wire  ack_i;  // _CELL:[B13]
  wire  [31:0] ad;  // _CELL:[B8]
  wire  [31:0] add;  // _CELL:[B11]
  wire  clk;  // _CELL:[B5]
  wire  clko;  // _CELL:[B4]
  wire  cs;  // _CELL:[B7]
  wire  cs_o;  // _CELL:[B10]
  wire  [31:0] data;  // _CELL:[B12]
  wire  reset_n;  // _CELL:[B6]
  wire  [31:0] s2_dt0;  // _CELL:[B26]
  wire  [15:0] s2_dt1;  // _CELL:[B27]
  wire  [7:0] s2_dt2;  // _CELL:[B28]
  wire  [31:0] s_dt0;  // _CELL:[B16]
  wire  [15:0] s_dt1;  // _CELL:[B17]
  wire  [7:0] s_dt2;  // _CELL:[B18]
  wire  ss;  // _CELL:[B14]
  wire  ss2;  // _CELL:[B24]
  wire  ss2_enable;  // _CELL:[B25]
  wire  ss_enable;  // _CELL:[B15]

// # $readmemh Variable ############################
  reg [199:0]FILE_ROM_00000[0:99];
  reg [31:0] ptr;
  wire [7:0] ww0;
  wire [39:0] ww1;
  wire [15:0] ww2;
  wire [63:0] ww3;
  wire [63:0] ww4;
  wire [7:0] ww5;
  reg [47:0]FILE_ROM_00001[0:199];
  reg [31:0] ptr_2;
  wire [7:0] aa0;
  wire [39:0] aa1;
  reg [143:0]FILE_ROM_00002[0:49];
  reg [31:0] ptr_3;
  wire [7:0] bb0;
  wire [39:0] bb1;
  wire [71:0] bb2;
  wire [7:0] bb3;
  wire [15:0] bb4;
initial begin 
 $dumpfile("c:\csv\aaa.dump"); 
 $dumpvars(1,i_model); 
 $dumpvars(1,i_main); 
end 
// # clk(i_clk) ###############
  clk i_clk(  // _CELL:
     .clk(clk)  // _CELL:[F5]
    ,.clko(clko)  // _CELL:[F4]
  );

// # cover(i_cover) ###############
  cover i_cover(  // _CELL:
     .clk(clk)  // _CELL:[G5]
  );

// # model(i_model) ###############
  model i_model(  // _CELL:
     .ack(ack)  // _CELL:[E9]
    ,.ack_i(ack_i)  // _CELL:[E13]
    ,.ad(ad)  // _CELL:[E8]
    ,.add(add)  // _CELL:[E11]
    ,.clk(clk)  // _CELL:[E5]
    ,.cs(cs)  // _CELL:[E7]
    ,.cs_o(cs_o)  // _CELL:[E10]
    ,.data(data)  // _CELL:[E12]
    ,.reset_n(reset_n)  // _CELL:[E6]
  );

// # test(i_test) ###############
  test i_test(  // _CELL:
     .ack(ack)  // _CELL:[D9]
    ,.ack_i(ack_i)  // _CELL:[D13]
    ,.ad(ad)  // _CELL:[D8]
    ,.add(add)  // _CELL:[D11]
    ,.clk(clk)  // _CELL:[D5]
    ,.clko(clko)  // _CELL:[D4]
    ,.cs(cs)  // _CELL:[D7]
    ,.cs_o(cs_o)  // _CELL:[D10]
    ,.data(data)  // _CELL:[D12]
    ,.r2_dt0(s2_dt0)  // _CELL:[D31]
    ,.r2_dt1(s2_dt1)  // _CELL:[D32]
    ,.r2_dt2(s2_dt2)  // _CELL:[D33]
    ,.r_dt0(s_dt0)  // _CELL:[D21]
    ,.r_dt1(s_dt1)  // _CELL:[D22]
    ,.r_dt2(s_dt2)  // _CELL:[D23]
    ,.reset_n(reset_n)  // _CELL:[D6]
    ,.rr(ss)  // _CELL:[D19]
    ,.rr2(ss2)  // _CELL:[D29]
    ,.rr2_enable(ss2_enable)  // _CELL:[D30]
    ,.rr_enable(ss_enable)  // _CELL:[D20]
    ,.s2_dt0(s2_dt0)  // _CELL:[D26]
    ,.s2_dt1(s2_dt1)  // _CELL:[D27]
    ,.s2_dt2(s2_dt2)  // _CELL:[D28]
    ,.s_dt0(s_dt0)  // _CELL:[D16]
    ,.s_dt1(s_dt1)  // _CELL:[D17]
    ,.s_dt2(s_dt2)  // _CELL:[D18]
    ,.ss(ss)  // _CELL:[D14]
    ,.ss2(ss2)  // _CELL:[D24]
    ,.ss2_enable(ss2_enable)  // _CELL:[D25]
    ,.ss_enable(ss_enable)  // _CELL:[D15]
  );

// # $readmemh ############################
  initial begin
    $readmemh("aaa.hex", FILE_ROM_00000);
    ptr=0;
    $readmemh("bbb.hex", FILE_ROM_00000);
    ptr_2=0;
    $readmemh("ccc.hex", FILE_ROM_00000);
    ptr_3=0;
  end
  assign { ww0,ww1,ww2,ww3,ww4,ww5} = FILE_ROM_00000[ptr];
  assign { aa0,aa1} = FILE_ROM_00001[ptr_2];
  assign { bb0,bb1,bb2,bb3,bb4} = FILE_ROM_00002[ptr_3];
endmodule

