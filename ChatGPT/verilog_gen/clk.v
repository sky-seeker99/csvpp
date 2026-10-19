// ---------------------
// clk module
// ---------------------
module clk(
   clk
  ,clko
);
// # port define ########################
// # output ########
  output  clk;
  output  clko;

// # Clock Variable ############################ 
  wire _clk;  // _CELL:[G6]
  reg INNR__clk;
  reg LSTK__clk;
  reg HSTK__clk;
  wire _clko;  // _CELL:[G7]
  reg INNR__clko;
  reg LSTK__clko;
  reg HSTK__clko;


// # Clock Initialize #################################### 
  initial begin
    INNR__clk = 0;  // _CELL:[G6]
    LSTK__clk = 1'b0;
    HSTK__clk = 1'b0;
    INNR__clko = 0;  // _CELL:[G7]
    LSTK__clko = 1'b0;
    HSTK__clko = 1'b0;
  end

// # Clock Generator #################################### 
// # _clk clock #####
  always begin  // _CELL:[G6]
    #500 INNR__clk = ~INNR__clk;
    #1500 INNR__clk = ~INNR__clk;
    #(3000 - 500 - 1500);
  end
  assign _clk = (INNR__clk & ~LSTK__clk) | HSTK__clk;
  assign clk = _clk;

// # _clko clock #####
  always begin  // _CELL:[G7]
    #550 INNR__clko = ~INNR__clko;
    #1500 INNR__clko = ~INNR__clko;
    #(3000 - 550 - 1500);
  end
  assign _clko = (INNR__clko & ~LSTK__clko) | HSTK__clko;
  assign clko = _clko;

endmodule

