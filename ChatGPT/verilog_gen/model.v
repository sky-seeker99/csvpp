// ########################################################################
// FunctionName : sample model
// File    Name : model.v
// Module  Name : model
// Version      : 1.00
// Author       : S.Kasuya
// ########################################################################
// ---------------------
// model module
// ---------------------
module model(
   clk
  ,reset_n
  ,cs
  ,ad
  ,ack_i
  ,ack
  ,cs_o
  ,add
  ,data
);
// # port define ########################
// # input  ########
  input   clk;
  input   reset_n;
  input   cs;
  input   [31:0] ad;
  input   ack_i;
// # output ########
  output  ack;
  output  cs_o;
  output  [31:0] add;
  output  [31:0] data;
// # register define ############################ 
  reg  sample_acc; // _CELL:[B35](*1)
  reg  sample_idle; // _CELL:[B30](*1)
  reg  sample_wait; // _CELL:[B40](*1)
  reg  sample_wait2; // _CELL:[B47](*1)
  reg  ack; // _CELL:[B18]
  reg  [31:0] add; // _CELL:[B22]
  reg  [31:0] add_fp; // _CELL:[B27]
  reg  cs_o; // _CELL:[B20]
  reg  [31:0] data; // _CELL:[B24]
  reg  [31:0] r; // _CELL:[B28]
  reg  sample0_fp; // _CELL:[B35](*2)
  reg  sample1_fp; // _CELL:[B41](*2)
// # wire define ############################ 
  wire  sample0_p; // _CELL:[B35](*3)
  wire  sample1_p; // _CELL:[B31](*3)
  wire  sample2_p; // _CELL:[B41](*3)
  wire  sample3_p; // _CELL:[B47](*3)

// # wire assign ############################ 
  assign sample0_p = (sample_acc); // _CELL:[B35](*3)
  assign sample1_p = (sample_idle) && (~cs); // _CELL:[B31](*3)
  assign sample2_p = (sample_wait) && (~ack_i); // _CELL:[B41](*3)
  assign sample3_p = (sample_wait2); // _CELL:[B47](*3)

// # sample_acc register (statemachine register) ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      sample_acc <= 1'b0; // _CELL:[B29]
    end
    else if (sample1_p) begin
      sample_acc <= 1'b1; // _CELL:[B31]
    end
    else if (sample0_p) begin
      sample_acc <= 1'b0; // _CELL:[B35]
    end
  end

// # sample_idle register (statemachine register) ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      sample_idle <= 1'b1; // _CELL:[B29]
    end
    else if (sample3_p) begin
      sample_idle <= 1'b1; // _CELL:[B47]
    end
    else if (sample1_p) begin
      sample_idle <= 1'b0; // _CELL:[B31]
    end
  end

// # sample_wait register (statemachine register) ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      sample_wait <= 1'b0; // _CELL:[B29]
    end
    else if (sample0_p) begin
      sample_wait <= 1'b1; // _CELL:[B35]
    end
    else if (sample2_p) begin
      sample_wait <= 1'b0; // _CELL:[B41]
    end
  end

// # sample_wait2 register (statemachine register) ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      sample_wait2 <= 1'b0; // _CELL:[B29]
    end
    else if (sample2_p) begin
      sample_wait2 <= 1'b1; // _CELL:[B41]
    end
    else if (sample3_p) begin
      sample_wait2 <= 1'b0; // _CELL:[B47]
    end
  end

// # ack register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      ack <= 1'b1; // _CELL:[B18]
    end
    else if (sample2_p) begin
      ack <= 1'b0; // _CELL:[C42]
    end
    else if (sample1_fp) begin
      ack <= 1'b1; // _CELL:[D42]
    end
  end

// # add register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      add <= 32'b0; // _CELL:[B22]
    end
    else if (sample0_p) begin
      add <= add_fp; // _CELL:[C36]
    end
    else if (sample2_p) begin
      add <= 32'h0; // _CELL:[C43]
    end
  end

// # add_fp register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      add_fp <= 32'b0; // _CELL:[B27]
    end
    else if (sample1_p) begin
      add_fp <= ad; // _CELL:[C32]
    end
  end

// # cs_o register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      cs_o <= 1'b1; // _CELL:[B20]
    end
    else if (sample0_p) begin
      cs_o <= 1'b0; // _CELL:[C38]
    end
    else if (sample0_fp) begin
      cs_o <= 1'b1; // _CELL:[D38]
    end
  end

// # data register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      data <= 32'b0; // _CELL:[B24]
    end
    else if (sample0_p) begin
      data <= ad; // _CELL:[C37]
    end
    else if (sample2_p) begin
      data <= 32'h0; // _CELL:[C44]
    end
    else  begin
      data <= 32'hxxxxxxxx; // _CELL:[B24]
    end
  end

// # r register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      r <= 32'b0; // _CELL:[B28]
    end
    else  begin
      r <= add_fp; // _CELL:[B28]
    end
  end

// # sample0_fp register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      sample0_fp <= 1'b0; // _CELL:
    end
    else  begin
      sample0_fp <= sample0_p; // _CELL:[B35]
    end
  end

// # sample1_fp register ######
  always @(posedge clk or negedge reset_n) begin
    if (~reset_n) begin
      sample1_fp <= 1'b0; // _CELL:
    end
    else  begin
      sample1_fp <= sample2_p; // _CELL:[B41]
    end
  end

endmodule

