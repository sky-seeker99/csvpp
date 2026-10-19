// ---------------------
// test module
// ---------------------
module test(
   clk
  ,clko
  ,ack
  ,cs_o
  ,add
  ,data
  ,ss_enable
  ,rr
  ,r_dt0
  ,r_dt1
  ,r_dt2
  ,ss2_enable
  ,rr2
  ,r2_dt0
  ,r2_dt1
  ,r2_dt2
  ,reset_n
  ,cs
  ,ad
  ,ack_i
  ,ss
  ,s_dt0
  ,s_dt1
  ,s_dt2
  ,rr_enable
  ,ss2
  ,s2_dt0
  ,s2_dt1
  ,s2_dt2
  ,rr2_enable
);
// # port define ########################
// # input  ########
  input   clk;
  input   clko;
  input   ack;
  input   cs_o;
  input   [31:0] add;
  input   [31:0] data;
  input   ss_enable;
  input  rr;
  input  [31:0] r_dt0;
  input  [15:0] r_dt1;
  input  [7:0] r_dt2;
  input   ss2_enable;
  input  rr2;
  input  [31:0] r2_dt0;
  input  [15:0] r2_dt1;
  input  [7:0] r2_dt2;
// # output ########
  output  reset_n;
  output  cs;
  output  [31:0] ad;
  output  ack_i;
  output   ss;
  output   [31:0] s_dt0;
  output   [15:0] s_dt1;
  output   [7:0] s_dt2;
  output  rr_enable;
  output   ss2;
  output   [31:0] s2_dt0;
  output   [15:0] s2_dt1;
  output   [7:0] s2_dt2;
  output  rr2_enable;
// # register define ############################ 
  reg  ack_i; // _CELL:[B237]
  reg  [31:0] ad; // _CELL:[B227]
  reg  cs; // _CELL:[B225]
  reg  reset_n; // _CELL:[B223]
  reg  [31:0] rr_dt0; // _CELL:[B261]
  reg  [15:0] rr_dt1; // _CELL:[B262]
  reg  [7:0] rr_dt2; // _CELL:[B263]
  reg  s_valid; // _CELL:[B264]
  reg  valid; // _CELL:[B260]

// # Schedule Variable ############################ 
  parameter ARY_MAX=10;
  integer target_ptr;
  integer next_top_ptr;
  integer dust_top_ptr;
  integer p_cyc;
  integer total_cyc_clko;
  integer cyc_clko_2   [ARY_MAX:0]; // ack_i
  integer next_clko_2  [ARY_MAX:0];
  integer before_clko_2[ARY_MAX:0];
  reg [1-1:0] value_clko_2 [ARY_MAX:0];
  integer cur_clko_2;
  integer dust_clko_2;
  integer top_clko_2;
  integer cyc_clko_1   [ARY_MAX:0]; // ad
  integer next_clko_1  [ARY_MAX:0];
  integer before_clko_1[ARY_MAX:0];
  reg [32-1:0] value_clko_1 [ARY_MAX:0];
  integer cur_clko_1;
  integer dust_clko_1;
  integer top_clko_1;
  integer cyc_clko_0   [ARY_MAX:0]; // cs
  integer next_clko_0  [ARY_MAX:0];
  integer before_clko_0[ARY_MAX:0];
  reg [1-1:0] value_clko_0 [ARY_MAX:0];
  integer cur_clko_0;
  integer dust_clko_0;
  integer top_clko_0;
// # State Machine Variable ############################ 
  reg reset_test_a,stop_test_a;  // _CELL:[C297]
  reg st_test_a_asrt,rst_test_a_asrt,set_test_a_asrt;  // _CELL:[B299]
  reg st_test_a_ack_wait,rst_test_a_ack_wait,set_test_a_ack_wait;  // _CELL:[B346]
  reg st_test_a_acc_wait,rst_test_a_acc_wait,set_test_a_acc_wait;  // _CELL:[B351]
  reg reset_test_b,stop_test_b;  // _CELL:[C354]
  reg st_test_b_ack_wait,rst_test_b_ack_wait,set_test_b_ack_wait;  // _CELL:[B356]
  reg st_test_b_wait,rst_test_b_wait,set_test_b_wait;  // _CELL:[B380]
// # State Machine Variable(Local/Parm) ################ 
  reg[32-1:0] l_test_a_cnt;  // _CELL:[D298]
  reg[32-1:0] l_test_b_cnt;  // _CELL:[D355]
// # Patern Variable ############################ 
  integer pidx_a_parm;  // _CELL:[B265]
  integer pmax_a_parm;
  integer psize_a_parm;
  integer prptr_a_parm;
  integer pwptr_a_parm;
  integer pidx_b_parm;  // _CELL:[B270]
  integer pmax_b_parm;
  integer psize_b_parm;
  integer prptr_b_parm;
  integer pwptr_b_parm;
  integer pidx_c_parm;  // _CELL:[B273]
  integer pmax_c_parm;
  integer psize_c_parm;
  integer prptr_c_parm;
  integer pwptr_c_parm;
  reg[32-1:0] ary_a_add[500-1:0];  // _CELL:[C267]
  reg[32-1:0] ary_a_data[500-1:0];  // _CELL:[C268]
  reg[8-1:0] ary_a_tim[500-1:0];  // _CELL:[C269]
  reg[8-1:0] ary_b_tim[500-1:0];  // _CELL:[C272]
  reg[32-1:0] ary_c_data[20-1:0];  // _CELL:[C275]
  reg[16-1:0] ary_c_add[20-1:0];  // _CELL:[C276]
  reg[8-1:0] ary_c_tim[20-1:0];  // _CELL:[C277]
  reg[32-1:0] a_add;  // _CELL:[C267]
  reg[32-1:0] a_data;  // _CELL:[C268]
  reg[8-1:0] a_tim;  // _CELL:[C269]
  reg[8-1:0] b_tim;  // _CELL:[C272]
  reg[32-1:0] c_data;  // _CELL:[C275]
  reg[16-1:0] c_add;  // _CELL:[C276]
  reg[8-1:0] c_tim;  // _CELL:[C277]
// # Interface Variable ############################
  reg HOJI_rr;
  reg  [31:0] HOJI_r_dt0;
  reg  [15:0] HOJI_r_dt1;
  reg  [7:0] HOJI_r_dt2;
  wire rr_enable;
  integer wptr_rr2;
  integer rptr_rr2;
  reg  [31:0] HOJI_r2_dt0[8:0];
  reg  [15:0] HOJI_r2_dt1[8:0];
  reg  [7:0] HOJI_r2_dt2[8:0];
  wire rr2_enable;
  reg ss;
  reg  [31:0] s_dt0;
  reg  [15:0] s_dt1;
  reg  [7:0] s_dt2;
  wire ss_enable;
  reg ss2;
  reg  [31:0] s2_dt0;
  reg  [15:0] s2_dt1;
  reg  [7:0] s2_dt2;
  wire ss2_enable;
// # Top Initialize ###################### 
 initial begin 
  #10 
  $display("initialize\n"); 
    reset_n=1'b0; 
      cs = 1'b1; 
    ad = 32'hzzzzzzzz; 
    ack_i = 1'b1; 
  #100000 
    reset_n =1'b1; 
  #100000 
  test_a_rst; 
  test_b_rst; 
  $display("initialize end\n"); 
 end 

// # Patern Index Initialize ############################ 
  initial begin
    pidx_a_parm = 0;  // _CELL:[B265]
    pmax_a_parm = 0;
    psize_a_parm = 0;
    prptr_a_parm = 0;
    pwptr_a_parm = 0;
    pidx_b_parm = 0;  // _CELL:[B270]
    pmax_b_parm = 0;
    psize_b_parm = 0;
    prptr_b_parm = 0;
    pwptr_b_parm = 0;
    pidx_c_parm = 0;  // _CELL:[B273]
    pmax_c_parm = 0;
    psize_c_parm = 0;
    prptr_c_parm = 0;
    pwptr_c_parm = 0;
  end
// # Patern Task (a_parm)############################ 
// # Ring Queue Get ##### 
  task a_parm_ring_get;  // _CELL:[B265]
    begin
      if (pidx_a_parm == pmax_a_parm) pidx_a_parm = 0;
      a_add = ary_a_add[pidx_a_parm];
      a_data = ary_a_data[pidx_a_parm];
      a_tim = ary_a_tim[pidx_a_parm];
      pidx_a_parm = pidx_a_parm + 1;
      if (pidx_a_parm == 500-1) pidx_a_parm = 0;
    end
  endtask
// # FIFO Read ##### 
  task a_parm_fifo_rd;  // _CELL:[B265]
    begin
      if (prptr_a_parm == pwptr_a_parm) $finish;
      else begin
        a_add = ary_a_add[prptr_a_parm];
        a_data = ary_a_data[prptr_a_parm];
        a_tim = ary_a_tim[prptr_a_parm];
        prptr_a_parm = prptr_a_parm + 1;
        if (prptr_a_parm == 500) prptr_a_parm = 0;
      end
    end
  endtask
// # FIFO Write #####
  task a_parm_fifo_wr;  // _CELL:[B265]
  input[32-1:0] p_a_add;
  input[32-1:0] p_a_data;
  input[8-1:0] p_a_tim;
    begin
      ary_a_add[pwptr_a_parm] = p_a_add;
      ary_a_data[pwptr_a_parm] = p_a_data;
      ary_a_tim[pwptr_a_parm] = p_a_tim;
      pwptr_a_parm = pwptr_a_parm + 1;
      if (pwptr_a_parm == 500) pwptr_a_parm = 0;
      if (prptr_a_parm == pwptr_a_parm) $finish;
    end
  endtask
// # Get ##### 
  task a_parm_get;  // _CELL:[B265]
    begin
      if (pidx_a_parm == pmax_a_parm) $finish;
      else begin
        a_add = ary_a_add[pidx_a_parm];
        a_data = ary_a_data[pidx_a_parm];
        a_tim = ary_a_tim[pidx_a_parm];
        pidx_a_parm = pidx_a_parm + 1;
        if (pidx_a_parm == 500-1) pidx_a_parm = 0;
        psize_a_parm = psize_a_parm - 1;
      end
    end
  endtask
// # Put #####
  task a_parm_put;  // _CELL:[B265]
  input[32-1:0] p_a_add;
  input[32-1:0] p_a_data;
  input[8-1:0] p_a_tim;
    begin
      ary_a_add[pmax_a_parm] = p_a_add;
      ary_a_data[pmax_a_parm] = p_a_data;
      ary_a_tim[pmax_a_parm] = p_a_tim;
      pmax_a_parm = pmax_a_parm + 1;
      if (pmax_a_parm == 500-1) pmax_a_parm = 0;
      psize_a_parm = psize_a_parm + 1;
      if (psize_a_parm >= 500) $display("a_parm patern queue over.");
    end
  endtask
// # Push #####
  task a_parm_push;  // _CELL:[B265]
    begin
      ary_a_add[pmax_a_parm] = a_add;
      ary_a_data[pmax_a_parm] = a_data;
      ary_a_tim[pmax_a_parm] = a_tim;
      pmax_a_parm = pmax_a_parm + 1;
      if (pmax_a_parm == 500-1) pmax_a_parm = 0;
      psize_a_parm = psize_a_parm + 1;
      if (psize_a_parm >= 500) $display("a_parm patern queue over.");
    end
  endtask
// # Pop #####
  function a_parm_pop;  // _CELL:[B265]
    input dmy;
    begin
      if (pidx_a_parm == pmax_a_parm) a_parm_pop = 1'b0;
      else begin
        a_add = ary_a_add[pidx_a_parm];
        a_data = ary_a_data[pidx_a_parm];
        a_tim = ary_a_tim[pidx_a_parm];
        pidx_a_parm = pidx_a_parm + 1;
        if (pidx_a_parm == 500-1) pidx_a_parm = 0;
        psize_a_parm = psize_a_parm - 1;
        a_parm_pop = 1'b1;
      end
    end
  endfunction
// # Clear #####
  task a_parm_clr;  // _CELL:[B265]
    begin
      pmax_a_parm  = 0;
      pidx_a_parm  = 0;
      psize_a_parm = 0;
    end
  endtask
// # Patern Task (b_parm)############################ 
// # Ring Queue Get ##### 
  task b_parm_ring_get;  // _CELL:[B270]
    begin
      if (pidx_b_parm == pmax_b_parm) pidx_b_parm = 0;
      b_tim = ary_b_tim[pidx_b_parm];
      pidx_b_parm = pidx_b_parm + 1;
      if (pidx_b_parm == 500-1) pidx_b_parm = 0;
    end
  endtask
// # FIFO Read ##### 
  task b_parm_fifo_rd;  // _CELL:[B270]
    begin
      if (prptr_b_parm == pwptr_b_parm) $finish;
      else begin
        b_tim = ary_b_tim[prptr_b_parm];
        prptr_b_parm = prptr_b_parm + 1;
        if (prptr_b_parm == 500) prptr_b_parm = 0;
      end
    end
  endtask
// # FIFO Write #####
  task b_parm_fifo_wr;  // _CELL:[B270]
  input[8-1:0] p_b_tim;
    begin
      ary_b_tim[pwptr_b_parm] = p_b_tim;
      pwptr_b_parm = pwptr_b_parm + 1;
      if (pwptr_b_parm == 500) pwptr_b_parm = 0;
      if (prptr_b_parm == pwptr_b_parm) $finish;
    end
  endtask
// # Get ##### 
  task b_parm_get;  // _CELL:[B270]
    begin
      if (pidx_b_parm == pmax_b_parm) $finish;
      else begin
        b_tim = ary_b_tim[pidx_b_parm];
        pidx_b_parm = pidx_b_parm + 1;
        if (pidx_b_parm == 500-1) pidx_b_parm = 0;
        psize_b_parm = psize_b_parm - 1;
      end
    end
  endtask
// # Put #####
  task b_parm_put;  // _CELL:[B270]
  input[8-1:0] p_b_tim;
    begin
      ary_b_tim[pmax_b_parm] = p_b_tim;
      pmax_b_parm = pmax_b_parm + 1;
      if (pmax_b_parm == 500-1) pmax_b_parm = 0;
      psize_b_parm = psize_b_parm + 1;
      if (psize_b_parm >= 500) $display("b_parm patern queue over.");
    end
  endtask
// # Push #####
  task b_parm_push;  // _CELL:[B270]
    begin
      ary_b_tim[pmax_b_parm] = b_tim;
      pmax_b_parm = pmax_b_parm + 1;
      if (pmax_b_parm == 500-1) pmax_b_parm = 0;
      psize_b_parm = psize_b_parm + 1;
      if (psize_b_parm >= 500) $display("b_parm patern queue over.");
    end
  endtask
// # Pop #####
  function b_parm_pop;  // _CELL:[B270]
    input dmy;
    begin
      if (pidx_b_parm == pmax_b_parm) b_parm_pop = 1'b0;
      else begin
        b_tim = ary_b_tim[pidx_b_parm];
        pidx_b_parm = pidx_b_parm + 1;
        if (pidx_b_parm == 500-1) pidx_b_parm = 0;
        psize_b_parm = psize_b_parm - 1;
        b_parm_pop = 1'b1;
      end
    end
  endfunction
// # Clear #####
  task b_parm_clr;  // _CELL:[B270]
    begin
      pmax_b_parm  = 0;
      pidx_b_parm  = 0;
      psize_b_parm = 0;
    end
  endtask
// # Patern Task (c_parm)############################ 
// # Ring Queue Get ##### 
  task c_parm_ring_get;  // _CELL:[B273]
    begin
      if (pidx_c_parm == pmax_c_parm) pidx_c_parm = 0;
      c_data = ary_c_data[pidx_c_parm];
      c_add = ary_c_add[pidx_c_parm];
      c_tim = ary_c_tim[pidx_c_parm];
      pidx_c_parm = pidx_c_parm + 1;
      if (pidx_c_parm == 20-1) pidx_c_parm = 0;
    end
  endtask
// # FIFO Read ##### 
  task c_parm_fifo_rd;  // _CELL:[B273]
    begin
      if (prptr_c_parm == pwptr_c_parm) $finish;
      else begin
        c_data = ary_c_data[prptr_c_parm];
        c_add = ary_c_add[prptr_c_parm];
        c_tim = ary_c_tim[prptr_c_parm];
        prptr_c_parm = prptr_c_parm + 1;
        if (prptr_c_parm == 20) prptr_c_parm = 0;
      end
    end
  endtask
// # FIFO Write #####
  task c_parm_fifo_wr;  // _CELL:[B273]
  input[32-1:0] p_c_data;
  input[16-1:0] p_c_add;
  input[8-1:0] p_c_tim;
    begin
      ary_c_data[pwptr_c_parm] = p_c_data;
      ary_c_add[pwptr_c_parm] = p_c_add;
      ary_c_tim[pwptr_c_parm] = p_c_tim;
      pwptr_c_parm = pwptr_c_parm + 1;
      if (pwptr_c_parm == 20) pwptr_c_parm = 0;
      if (prptr_c_parm == pwptr_c_parm) $finish;
    end
  endtask
// # Get ##### 
  task c_parm_get;  // _CELL:[B273]
    begin
      if (pidx_c_parm == pmax_c_parm) $finish;
      else begin
        c_data = ary_c_data[pidx_c_parm];
        c_add = ary_c_add[pidx_c_parm];
        c_tim = ary_c_tim[pidx_c_parm];
        pidx_c_parm = pidx_c_parm + 1;
        if (pidx_c_parm == 20-1) pidx_c_parm = 0;
        psize_c_parm = psize_c_parm - 1;
      end
    end
  endtask
// # Put #####
  task c_parm_put;  // _CELL:[B273]
  input[32-1:0] p_c_data;
  input[16-1:0] p_c_add;
  input[8-1:0] p_c_tim;
    begin
      ary_c_data[pmax_c_parm] = p_c_data;
      ary_c_add[pmax_c_parm] = p_c_add;
      ary_c_tim[pmax_c_parm] = p_c_tim;
      pmax_c_parm = pmax_c_parm + 1;
      if (pmax_c_parm == 20-1) pmax_c_parm = 0;
      psize_c_parm = psize_c_parm + 1;
      if (psize_c_parm >= 20) $display("c_parm patern queue over.");
    end
  endtask
// # Push #####
  task c_parm_push;  // _CELL:[B273]
    begin
      ary_c_data[pmax_c_parm] = c_data;
      ary_c_add[pmax_c_parm] = c_add;
      ary_c_tim[pmax_c_parm] = c_tim;
      pmax_c_parm = pmax_c_parm + 1;
      if (pmax_c_parm == 20-1) pmax_c_parm = 0;
      psize_c_parm = psize_c_parm + 1;
      if (psize_c_parm >= 20) $display("c_parm patern queue over.");
    end
  endtask
// # Pop #####
  function c_parm_pop;  // _CELL:[B273]
    input dmy;
    begin
      if (pidx_c_parm == pmax_c_parm) c_parm_pop = 1'b0;
      else begin
        c_data = ary_c_data[pidx_c_parm];
        c_add = ary_c_add[pidx_c_parm];
        c_tim = ary_c_tim[pidx_c_parm];
        pidx_c_parm = pidx_c_parm + 1;
        if (pidx_c_parm == 20-1) pidx_c_parm = 0;
        psize_c_parm = psize_c_parm - 1;
        c_parm_pop = 1'b1;
      end
    end
  endfunction
// # Clear #####
  task c_parm_clr;  // _CELL:[B273]
    begin
      pmax_c_parm  = 0;
      pidx_c_parm  = 0;
      psize_c_parm = 0;
    end
  endtask

// # schedule variable initialize ################
  initial begin
    for(cur_clko_2=0;cur_clko_2<ARY_MAX;cur_clko_2=cur_clko_2+1) begin
      next_clko_2[cur_clko_2] = cur_clko_2 + 1;
      before_clko_2[cur_clko_2] = cur_clko_2 - 1;
    end
    for(cur_clko_1=0;cur_clko_1<ARY_MAX;cur_clko_1=cur_clko_1+1) begin
      next_clko_1[cur_clko_1] = cur_clko_1 + 1;
      before_clko_1[cur_clko_1] = cur_clko_1 - 1;
    end
    for(cur_clko_0=0;cur_clko_0<ARY_MAX;cur_clko_0=cur_clko_0+1) begin
      next_clko_0[cur_clko_0] = cur_clko_0 + 1;
      before_clko_0[cur_clko_0] = cur_clko_0 - 1;
    end
    next_clko_2[ARY_MAX-1] = -1;
    cur_clko_2  = -1;
    top_clko_2  = -1;
    dust_clko_2 =  0;
    next_clko_1[ARY_MAX-1] = -1;
    cur_clko_1  = -1;
    top_clko_1  = -1;
    dust_clko_1 =  0;
    next_clko_0[ARY_MAX-1] = -1;
    cur_clko_0  = -1;
    top_clko_0  = -1;
    dust_clko_0 =  0;
  end

// # state machine variable initialize ################
  initial begin
    stop_test_a  = 1;
    reset_test_a = 0;
    stop_test_b  = 1;
    reset_test_b = 0;
  end

// # state machine (test_a/asrt) #####
  task test_a_asrt;  // _CELL:[B299]
    begin
      a_parm_get;   // _CELL:[B300]
      p_cyc = 0; clko_0_chg(1'b0);  // _CELL:[D301]
      p_cyc = 1; clko_0_chg(1'b1);  // _CELL:[D301]
      p_cyc = 0; clko_1_chg(a_add);  // _CELL:[D301]
      p_cyc = 1; clko_1_chg(a_data);  // _CELL:[D301]
      l_test_a_cnt = 0;   // _CELL:[B303]
      ss_send_check(s_valid);   // _CELL:[B304]
      $display("send OK(before) = %d",s_valid);   // _CELL:[B305]
      ss_send(a_data,a_add,30);   // _CELL:[B306]
      ss_send_check(s_valid);   // _CELL:[B307]
      $display("send OK(after) = %d",s_valid);   // _CELL:[B308]
      ss2_send_check(s_valid);   // _CELL:[B309]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B310]
      ss2_send(a_data,a_add,0);   // _CELL:[B311]
      ss2_send_check(s_valid);   // _CELL:[B312]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B313]
      ss2_send_check(s_valid);   // _CELL:[B314]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B315]
      ss2_send(a_data,a_add,1);   // _CELL:[B316]
      ss2_send_check(s_valid);   // _CELL:[B317]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B318]
      ss2_send_check(s_valid);   // _CELL:[B319]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B320]
      ss2_send(a_data,a_add,2);   // _CELL:[B321]
      ss2_send_check(s_valid);   // _CELL:[B322]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B323]
      ss2_send_check(s_valid);   // _CELL:[B324]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B325]
      ss2_send(a_data,a_add,3);   // _CELL:[B326]
      ss2_send_check(s_valid);   // _CELL:[B327]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B328]
      ss2_send_check(s_valid);   // _CELL:[B329]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B330]
      ss2_send(a_data,a_add,4);   // _CELL:[B331]
      ss2_send_check(s_valid);   // _CELL:[B332]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B333]
      ss2_send_check(s_valid);   // _CELL:[B334]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B335]
      ss2_send(a_data,a_add,5);   // _CELL:[B336]
      ss2_send_check(s_valid);   // _CELL:[B337]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B338]
      ss2_send_check(s_valid);   // _CELL:[B339]
      $display("send(2) OK(before) = %d",s_valid);   // _CELL:[B340]
      ss2_send(a_data,a_add,6);   // _CELL:[B341]
      ss2_send_check(s_valid);   // _CELL:[B342]
      $display("send(2) OK(after) = %d",s_valid);   // _CELL:[B343]
      c_parm_fifo_wr(a_data,a_add,30);   // _CELL:[B344]
      set_test_a_ack_wait = 1'b1;  // _CELL:[B345]
      rst_test_a_asrt = 1'b1;  // _CELL:[B345]
    end
  endtask

// # state machine (test_a/ack_wait) #####
  task test_a_ack_wait;  // _CELL:[B346]
    begin
      if (ack == 1'b0) begin  // _CELL:[A347]
        if (a_tim == 0) begin  // _CELL:[A348]
          set_test_a_asrt = 1'b1;  // _CELL:[D348]
          rst_test_a_ack_wait = 1'b1;  // _CELL:[D348]
        end
        else begin  // _CELL:[A349]
          set_test_a_acc_wait = 1'b1;  // _CELL:[D349]
          rst_test_a_ack_wait = 1'b1;  // _CELL:[D349]
        end
      end
    end
  endtask

// # state machine (test_a/acc_wait) #####
  task test_a_acc_wait;  // _CELL:[B351]
    begin
      if (l_test_a_cnt == a_tim-1) begin  // _CELL:[A352]
        set_test_a_asrt = 1'b1;  // _CELL:[D352]
        rst_test_a_acc_wait = 1'b1;  // _CELL:[D352]
      end
      else begin  // _CELL:[A353]
        l_test_a_cnt = l_test_a_cnt + 1;   // _CELL:[D353]
      end
    end
  endtask

// # state machine (test_b/ack_wait) #####
  task test_b_ack_wait;  // _CELL:[B356]
    begin
      if (cs_o == 1'b0) begin  // _CELL:[A357]
        b_parm_get;   // _CELL:[B358]
        l_test_b_cnt = 0;   // _CELL:[B359]
        set_test_b_wait = 1'b1;  // _CELL:[B360]
        rst_test_b_ack_wait = 1'b1;  // _CELL:[B360]
        rr_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B361]
        $display("channel  : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B362]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B363]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B364]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B365]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B366]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B367]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B368]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B369]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B370]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B371]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B372]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B373]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B374]
        rr2_recv(valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B375]
        $display("channel (2) : %d %x %x %x",valid,rr_dt0,rr_dt1,rr_dt2);   // _CELL:[B376]
        c_parm_fifo_rd;   // _CELL:[B377]
        $display("fifo : %x %x %x",c_data,c_add,c_tim);   // _CELL:[B378]
      end
    end
  endtask

// # state machine (test_b/wait) #####
  task test_b_wait;  // _CELL:[B380]
    begin
      if (l_test_b_cnt == b_tim) begin  // _CELL:[A381]
        p_cyc = 0; clko_2_chg(1'b0);  // _CELL:[D382]
        p_cyc = 1; clko_2_chg('b1);  // _CELL:[D382]
        set_test_b_ack_wait = 1'b1;  // _CELL:[B383]
        rst_test_b_wait = 1'b1;  // _CELL:[B383]
      end
      else begin  // _CELL:[A384]
        l_test_b_cnt = l_test_b_cnt + 1;   // _CELL:[B385]
      end
    end
  endtask

// # state machine main loop #####
  always @(posedge clk)  // _CELL:[C297]
    begin
      set_test_a_asrt = 1'b0;
      set_test_a_ack_wait = 1'b0;
      set_test_a_acc_wait = 1'b0;
      rst_test_a_asrt = 1'b0;
      rst_test_a_ack_wait = 1'b0;
      rst_test_a_acc_wait = 1'b0;
      if (st_test_a_asrt)test_a_asrt;
      if (st_test_a_ack_wait)test_a_ack_wait;
      if (st_test_a_acc_wait)test_a_acc_wait;
      if (reset_test_a) begin
        reset_test_a = 1'b0;
        stop_test_a = 1'b0;
        st_test_a_asrt = 1'b1;
        st_test_a_ack_wait = 1'b0;
        st_test_a_acc_wait = 1'b0;
      end
      else if (stop_test_a) begin
        st_test_a_asrt = 1'b0;
        st_test_a_ack_wait = 1'b0;
        st_test_a_acc_wait = 1'b0;
      end
      else begin
        if      (set_test_a_asrt)st_test_a_asrt = 1'b1;
        else if (rst_test_a_asrt)st_test_a_asrt = 1'b0;
        if      (set_test_a_ack_wait)st_test_a_ack_wait = 1'b1;
        else if (rst_test_a_ack_wait)st_test_a_ack_wait = 1'b0;
        if      (set_test_a_acc_wait)st_test_a_acc_wait = 1'b1;
        else if (rst_test_a_acc_wait)st_test_a_acc_wait = 1'b0;
      end
    end
  always @(posedge clk)  // _CELL:[C354]
    begin
      set_test_b_ack_wait = 1'b0;
      set_test_b_wait = 1'b0;
      rst_test_b_ack_wait = 1'b0;
      rst_test_b_wait = 1'b0;
      if (st_test_b_ack_wait)test_b_ack_wait;
      if (st_test_b_wait)test_b_wait;
      if (reset_test_b) begin
        reset_test_b = 1'b0;
        stop_test_b = 1'b0;
        st_test_b_ack_wait = 1'b1;
        st_test_b_wait = 1'b0;
      end
      else if (stop_test_b) begin
        st_test_b_ack_wait = 1'b0;
        st_test_b_wait = 1'b0;
      end
      else begin
        if      (set_test_b_ack_wait)st_test_b_ack_wait = 1'b1;
        else if (rst_test_b_ack_wait)st_test_b_ack_wait = 1'b0;
        if      (set_test_b_wait)st_test_b_wait = 1'b1;
        else if (rst_test_b_wait)st_test_b_wait = 1'b0;
      end
    end

// # reset/stop #####  // _CELL:[C297]
  task test_a_rst;
    begin
      reset_test_a = 1'b1;
      l_test_a_cnt <= 0;  // _CELL:[D298]
    end
  endtask
  task test_a_stop;
    begin
      stop_test_a = 1'b1;
    end
  endtask

// # reset/stop #####  // _CELL:[C354]
  task test_b_rst;
    begin
      reset_test_b = 1'b1;
      l_test_b_cnt <= 0;  // _CELL:[D355]
    end
  endtask
  task test_b_stop;
    begin
      stop_test_b = 1'b1;
    end
  endtask

// # schedule task ############################
// # store [ack_i] #####
  task clko_2_chg;
    input [1-1:0] p_val;
    integer srch_kbn;
    integer rtn_cd;
    integer cyc;
    integer addin;
    integer loop_flg;
    integer ret_flg;
    integer sv_ptr;
    begin
      ret_flg = 0;
      loop_flg = 0;
      if (p_cyc >= 99) ret_flg = 1;
      if (dust_clko_2 == -1) begin $display("index over (line=ack_i)\n"); ret_flg = 1; end
      if (ret_flg == 0) begin
        cyc = p_cyc + total_cyc_clko;
        if (cur_clko_2 == -1) cur_clko_2 = top_clko_2;
        addin = 0;
        srch_kbn = 2;
        rtn_cd = -1;
        loop_flg = 1;
      end
      while(loop_flg) begin
        if (top_clko_2 == -1) begin addin = 1; loop_flg = 0; end
        if (loop_flg == 1) begin
          rtn_cd = 1;
          if (cyc_clko_2[cur_clko_2] == cyc) rtn_cd = 0;
          if (cyc_clko_2[cur_clko_2] >  cyc) rtn_cd = -1;
          if (rtn_cd == 0) loop_flg = 0;
        end
        if (loop_flg == 1) begin
          if (srch_kbn == 2) srch_kbn = rtn_cd;
          if (srch_kbn != rtn_cd) begin 
            if (rtn_cd == 1) cur_clko_2 = next_clko_2[cur_clko_2];
            loop_flg = 0;
          end
        end
        if (loop_flg == 1) begin
          if (rtn_cd == 1) begin
            if (next_clko_2[cur_clko_2] == -1) begin addin = 1; loop_flg = 0; end
            else  cur_clko_2 = next_clko_2[cur_clko_2];
          end
          else begin
            if (before_clko_2[cur_clko_2] == -1) loop_flg = 0;
            else  cur_clko_2 = before_clko_2[cur_clko_2];
          end
        end
      end
      if (ret_flg == 0) begin
        if (rtn_cd == 0) begin value_clko_2[cur_clko_2] = p_val; ret_flg = 1; end
      end
      if (ret_flg == 0) begin
        target_ptr = dust_clko_2;
        dust_clko_2 = next_clko_2[dust_clko_2];
        if (dust_clko_2 != -1) before_clko_2[dust_clko_2] = -1;
        cyc_clko_2[target_ptr] = cyc;
        value_clko_2[target_ptr] = p_val;
      end
      if (ret_flg == 0) begin
        if (cur_clko_2 == -1) begin
          top_clko_2 = target_ptr;
          before_clko_2[target_ptr] = -1;
          next_clko_2[target_ptr] = -1;
          ret_flg = 1;
        end
      end
      if (ret_flg == 0) begin
        if (addin == 1) begin
          next_clko_2[cur_clko_2]   = target_ptr;
          before_clko_2[target_ptr] = cur_clko_2;
          next_clko_2[target_ptr] = -1;
        end
        else begin
          sv_ptr = before_clko_2[cur_clko_2];
          next_top_ptr = before_clko_2[cur_clko_2];
          before_clko_2[cur_clko_2]   = target_ptr;
          next_clko_2[target_ptr] = cur_clko_2;
          before_clko_2[target_ptr] = sv_ptr;
          if (next_top_ptr == -1) top_clko_2 = target_ptr;
          else                    next_clko_2[next_top_ptr] = target_ptr;
        end
      end
//    clko_2_printf;
    end
  endtask
// # check & exec [ack_i] #####
  always @(posedge clko) begin
    if (top_clko_2 != -1) begin
      if (total_cyc_clko == cyc_clko_2[top_clko_2]) begin
        ack_i = value_clko_2[top_clko_2];
        target_ptr   = top_clko_2;
        dust_top_ptr = dust_clko_2;
        if (top_clko_2 == -1) next_top_ptr = -1;
        else                 next_top_ptr = next_clko_2[top_clko_2];
        target_ptr = top_clko_2;
        top_clko_2 = next_clko_2[top_clko_2];
        if (top_clko_2 != -1) before_clko_2[top_clko_2] = -1;
        dust_top_ptr = dust_clko_2;
        dust_clko_2 = target_ptr;
        before_clko_2[target_ptr] = -1;
        next_clko_2[target_ptr]   = dust_top_ptr;
        if (dust_top_ptr != -1) before_clko_2[dust_top_ptr] = target_ptr;
        if (cur_clko_2 == target_ptr) cur_clko_2 = top_clko_2;
      end
    end
  end
// # store [ad] #####
  task clko_1_chg;
    input [32-1:0] p_val;
    integer srch_kbn;
    integer rtn_cd;
    integer cyc;
    integer addin;
    integer loop_flg;
    integer ret_flg;
    integer sv_ptr;
    begin
      ret_flg = 0;
      loop_flg = 0;
      if (p_cyc >= 99) ret_flg = 1;
      if (dust_clko_1 == -1) begin $display("index over (line=ad)\n"); ret_flg = 1; end
      if (ret_flg == 0) begin
        cyc = p_cyc + total_cyc_clko;
        if (cur_clko_1 == -1) cur_clko_1 = top_clko_1;
        addin = 0;
        srch_kbn = 2;
        rtn_cd = -1;
        loop_flg = 1;
      end
      while(loop_flg) begin
        if (top_clko_1 == -1) begin addin = 1; loop_flg = 0; end
        if (loop_flg == 1) begin
          rtn_cd = 1;
          if (cyc_clko_1[cur_clko_1] == cyc) rtn_cd = 0;
          if (cyc_clko_1[cur_clko_1] >  cyc) rtn_cd = -1;
          if (rtn_cd == 0) loop_flg = 0;
        end
        if (loop_flg == 1) begin
          if (srch_kbn == 2) srch_kbn = rtn_cd;
          if (srch_kbn != rtn_cd) begin 
            if (rtn_cd == 1) cur_clko_1 = next_clko_1[cur_clko_1];
            loop_flg = 0;
          end
        end
        if (loop_flg == 1) begin
          if (rtn_cd == 1) begin
            if (next_clko_1[cur_clko_1] == -1) begin addin = 1; loop_flg = 0; end
            else  cur_clko_1 = next_clko_1[cur_clko_1];
          end
          else begin
            if (before_clko_1[cur_clko_1] == -1) loop_flg = 0;
            else  cur_clko_1 = before_clko_1[cur_clko_1];
          end
        end
      end
      if (ret_flg == 0) begin
        if (rtn_cd == 0) begin value_clko_1[cur_clko_1] = p_val; ret_flg = 1; end
      end
      if (ret_flg == 0) begin
        target_ptr = dust_clko_1;
        dust_clko_1 = next_clko_1[dust_clko_1];
        if (dust_clko_1 != -1) before_clko_1[dust_clko_1] = -1;
        cyc_clko_1[target_ptr] = cyc;
        value_clko_1[target_ptr] = p_val;
      end
      if (ret_flg == 0) begin
        if (cur_clko_1 == -1) begin
          top_clko_1 = target_ptr;
          before_clko_1[target_ptr] = -1;
          next_clko_1[target_ptr] = -1;
          ret_flg = 1;
        end
      end
      if (ret_flg == 0) begin
        if (addin == 1) begin
          next_clko_1[cur_clko_1]   = target_ptr;
          before_clko_1[target_ptr] = cur_clko_1;
          next_clko_1[target_ptr] = -1;
        end
        else begin
          sv_ptr = before_clko_1[cur_clko_1];
          next_top_ptr = before_clko_1[cur_clko_1];
          before_clko_1[cur_clko_1]   = target_ptr;
          next_clko_1[target_ptr] = cur_clko_1;
          before_clko_1[target_ptr] = sv_ptr;
          if (next_top_ptr == -1) top_clko_1 = target_ptr;
          else                    next_clko_1[next_top_ptr] = target_ptr;
        end
      end
//    clko_1_printf;
    end
  endtask
// # check & exec [ad] #####
  always @(posedge clko) begin
    if (top_clko_1 != -1) begin
      if (total_cyc_clko == cyc_clko_1[top_clko_1]) begin
        ad = value_clko_1[top_clko_1];
        target_ptr   = top_clko_1;
        dust_top_ptr = dust_clko_1;
        if (top_clko_1 == -1) next_top_ptr = -1;
        else                 next_top_ptr = next_clko_1[top_clko_1];
        target_ptr = top_clko_1;
        top_clko_1 = next_clko_1[top_clko_1];
        if (top_clko_1 != -1) before_clko_1[top_clko_1] = -1;
        dust_top_ptr = dust_clko_1;
        dust_clko_1 = target_ptr;
        before_clko_1[target_ptr] = -1;
        next_clko_1[target_ptr]   = dust_top_ptr;
        if (dust_top_ptr != -1) before_clko_1[dust_top_ptr] = target_ptr;
        if (cur_clko_1 == target_ptr) cur_clko_1 = top_clko_1;
      end
    end
  end
// # store [cs] #####
  task clko_0_chg;
    input [1-1:0] p_val;
    integer srch_kbn;
    integer rtn_cd;
    integer cyc;
    integer addin;
    integer loop_flg;
    integer ret_flg;
    integer sv_ptr;
    begin
      ret_flg = 0;
      loop_flg = 0;
      if (p_cyc >= 99) ret_flg = 1;
      if (dust_clko_0 == -1) begin $display("index over (line=cs)\n"); ret_flg = 1; end
      if (ret_flg == 0) begin
        cyc = p_cyc + total_cyc_clko;
        if (cur_clko_0 == -1) cur_clko_0 = top_clko_0;
        addin = 0;
        srch_kbn = 2;
        rtn_cd = -1;
        loop_flg = 1;
      end
      while(loop_flg) begin
        if (top_clko_0 == -1) begin addin = 1; loop_flg = 0; end
        if (loop_flg == 1) begin
          rtn_cd = 1;
          if (cyc_clko_0[cur_clko_0] == cyc) rtn_cd = 0;
          if (cyc_clko_0[cur_clko_0] >  cyc) rtn_cd = -1;
          if (rtn_cd == 0) loop_flg = 0;
        end
        if (loop_flg == 1) begin
          if (srch_kbn == 2) srch_kbn = rtn_cd;
          if (srch_kbn != rtn_cd) begin 
            if (rtn_cd == 1) cur_clko_0 = next_clko_0[cur_clko_0];
            loop_flg = 0;
          end
        end
        if (loop_flg == 1) begin
          if (rtn_cd == 1) begin
            if (next_clko_0[cur_clko_0] == -1) begin addin = 1; loop_flg = 0; end
            else  cur_clko_0 = next_clko_0[cur_clko_0];
          end
          else begin
            if (before_clko_0[cur_clko_0] == -1) loop_flg = 0;
            else  cur_clko_0 = before_clko_0[cur_clko_0];
          end
        end
      end
      if (ret_flg == 0) begin
        if (rtn_cd == 0) begin value_clko_0[cur_clko_0] = p_val; ret_flg = 1; end
      end
      if (ret_flg == 0) begin
        target_ptr = dust_clko_0;
        dust_clko_0 = next_clko_0[dust_clko_0];
        if (dust_clko_0 != -1) before_clko_0[dust_clko_0] = -1;
        cyc_clko_0[target_ptr] = cyc;
        value_clko_0[target_ptr] = p_val;
      end
      if (ret_flg == 0) begin
        if (cur_clko_0 == -1) begin
          top_clko_0 = target_ptr;
          before_clko_0[target_ptr] = -1;
          next_clko_0[target_ptr] = -1;
          ret_flg = 1;
        end
      end
      if (ret_flg == 0) begin
        if (addin == 1) begin
          next_clko_0[cur_clko_0]   = target_ptr;
          before_clko_0[target_ptr] = cur_clko_0;
          next_clko_0[target_ptr] = -1;
        end
        else begin
          sv_ptr = before_clko_0[cur_clko_0];
          next_top_ptr = before_clko_0[cur_clko_0];
          before_clko_0[cur_clko_0]   = target_ptr;
          next_clko_0[target_ptr] = cur_clko_0;
          before_clko_0[target_ptr] = sv_ptr;
          if (next_top_ptr == -1) top_clko_0 = target_ptr;
          else                    next_clko_0[next_top_ptr] = target_ptr;
        end
      end
//    clko_0_printf;
    end
  endtask
// # check & exec [cs] #####
  always @(posedge clko) begin
    if (top_clko_0 != -1) begin
      if (total_cyc_clko == cyc_clko_0[top_clko_0]) begin
        cs = value_clko_0[top_clko_0];
        target_ptr   = top_clko_0;
        dust_top_ptr = dust_clko_0;
        if (top_clko_0 == -1) next_top_ptr = -1;
        else                 next_top_ptr = next_clko_0[top_clko_0];
        target_ptr = top_clko_0;
        top_clko_0 = next_clko_0[top_clko_0];
        if (top_clko_0 != -1) before_clko_0[top_clko_0] = -1;
        dust_top_ptr = dust_clko_0;
        dust_clko_0 = target_ptr;
        before_clko_0[target_ptr] = -1;
        next_clko_0[target_ptr]   = dust_top_ptr;
        if (dust_top_ptr != -1) before_clko_0[dust_top_ptr] = target_ptr;
        if (cur_clko_0 == target_ptr) cur_clko_0 = top_clko_0;
      end
    end
  end

// # schedule task #####
  always @(posedge clko) total_cyc_clko <= total_cyc_clko + 1;

  initial begin
    total_cyc_clko = 0;
  end

// # schedule list printf #####
  task clko_2_printf; // ack_i
    integer i;
    begin
      $display("<ack_i>");
      $display("cur_clko_2  = %x",cur_clko_2 );
      $display("dust_clko_2 = %x",dust_clko_2);
      $display("top_clko_2  = %x",top_clko_2 );
      for(i=0;i<ARY_MAX;i=i+1) begin 
        $display("cyc_clko_2   [%d]=%d",i,cyc_clko_2[i]   );
        $display("value_clko_2 [%d]=%x",i,value_clko_2[i] );
        $display("before_clko_2[%d]=%x",i,before_clko_2[i]);
        $display("next_clko_2  [%d]=%x",i,next_clko_2[i]  );
      end
    end
  endtask
  task clko_1_printf; // ad
    integer i;
    begin
      $display("<ad>");
      $display("cur_clko_1  = %x",cur_clko_1 );
      $display("dust_clko_1 = %x",dust_clko_1);
      $display("top_clko_1  = %x",top_clko_1 );
      for(i=0;i<ARY_MAX;i=i+1) begin 
        $display("cyc_clko_1   [%d]=%d",i,cyc_clko_1[i]   );
        $display("value_clko_1 [%d]=%x",i,value_clko_1[i] );
        $display("before_clko_1[%d]=%x",i,before_clko_1[i]);
        $display("next_clko_1  [%d]=%x",i,next_clko_1[i]  );
      end
    end
  endtask
  task clko_0_printf; // cs
    integer i;
    begin
      $display("<cs>");
      $display("cur_clko_0  = %x",cur_clko_0 );
      $display("dust_clko_0 = %x",dust_clko_0);
      $display("top_clko_0  = %x",top_clko_0 );
      for(i=0;i<ARY_MAX;i=i+1) begin 
        $display("cyc_clko_0   [%d]=%d",i,cyc_clko_0[i]   );
        $display("value_clko_0 [%d]=%x",i,value_clko_0[i] );
        $display("before_clko_0[%d]=%x",i,before_clko_0[i]);
        $display("next_clko_0  [%d]=%x",i,next_clko_0[i]  );
      end
    end
  endtask
// # Patern Making ############################ 
  initial begin
    #1
    a_parm_put(32'haaaaaaaa,32'hdddddddd,4);  // _CELL:[A3]
    a_parm_put(32'h55555555,32'h33333333,2);  // _CELL:[A7]
    a_parm_put(32'hffffffff,32'h00000000,4);  // _CELL:[A11]
    a_parm_put(32'h12345678,32'h87654321,3);  // _CELL:[A15]
    a_parm_put(64'h59a4799659a47996,64'h232c38de232c38de,1);  // _CELL:[A19]
    a_parm_put(64'h483c0550483c0550,64'h1524686115246861,5);  // _CELL:[A23]
    a_parm_put(64'h69ef7ad169ef7ad1,64'h1c1636a11c1636a1,2);  // _CELL:[A27]
    a_parm_put(64'h762c67cb762c67cb,64'h39bb4d6839bb4d68,3);  // _CELL:[A31]
    a_parm_put(64'h464b5c29464b5c29,64'h0e9633fe0e9633fe,1);  // _CELL:[A35]
    a_parm_put(64'h3cc93edc3cc93edc,64'h48392c1848392c18,2);  // _CELL:[A39]
    a_parm_put(64'h1704362717043627,64'h58ee14f458ee14f4,5);  // _CELL:[A43]
    a_parm_put(64'h4fcb00644fcb0064,64'h64c3226c64c3226c,0);  // _CELL:[A47]
    a_parm_put(64'h303b4a62303b4a62,64'h4d3e23d14d3e23d1,3);  // _CELL:[A51]
    a_parm_put(64'h25c22abd25c22abd,64'h344e1ec6344e1ec6,5);  // _CELL:[A55]
    a_parm_put(64'h3f3e7de93f3e7de9,64'h0035347500353475,5);  // _CELL:[A59]
    a_parm_put(64'h208d7cc1208d7cc1,64'h2d7433d42d7433d4,4);  // _CELL:[A63]
    a_parm_put(64'h1b181fe01b181fe0,64'h610a71d6610a71d6,3);  // _CELL:[A67]
    a_parm_put(64'h3b0c440a3b0c440a,64'h048410b7048410b7,2);  // _CELL:[A71]
    a_parm_put(64'h4c6920694c692069,64'h0eab59c50eab59c5,5);  // _CELL:[A75]
    a_parm_put(64'h7012057970120579,64'h46d9415f46d9415f,3);  // _CELL:[A79]
    a_parm_put(64'h20781bc720781bc7,64'h1e352af11e352af1,2);  // _CELL:[A83]
    a_parm_put(64'h4e9e03fa4e9e03fa,64'h796e1b3a796e1b3a,0);  // _CELL:[A87]
    a_parm_put(64'h5b875dbf5b875dbf,64'h46a6492a46a6492a,2);  // _CELL:[A91]
    a_parm_put(64'h6f4c69876f4c6987,64'h4eaf7a0e4eaf7a0e,0);  // _CELL:[A95]
    a_parm_put(64'h5e6841405e684140,64'h25cf5be825cf5be8,5);  // _CELL:[A99]
    a_parm_put(64'h3f07166c3f07166c,64'h4793312447933124,4);  // _CELL:[A103]
    a_parm_put(64'h534f1044534f1044,64'h128c2b0c128c2b0c,5);  // _CELL:[A107]
    a_parm_put(64'h53015acb53015acb,64'h53e854a853e854a8,3);  // _CELL:[A111]
    a_parm_put(64'h35e747f635e747f6,64'h30387de730387de7,0);  // _CELL:[A115]
    a_parm_put(64'h39e51e6039e51e60,64'h45ef3f4d45ef3f4d,2);  // _CELL:[A119]
    a_parm_put(64'h4aa965164aa96516,64'h375c0079375c0079,3);  // _CELL:[A123]
    a_parm_put(64'h7e4c3a867e4c3a86,64'h2d2a78362d2a7836,4);  // _CELL:[A127]
    a_parm_put(64'h59691c9b59691c9b,64'h27a872fc27a872fc,1);  // _CELL:[A131]
    a_parm_put(64'h4e6f0a7b4e6f0a7b,64'h6c725d126c725d12,5);  // _CELL:[A135]
    a_parm_put(64'h3f3324973f332497,64'h572627a2572627a2,1);  // _CELL:[A139]
    a_parm_put(64'h7d1c75e17d1c75e1,64'h1f4d34861f4d3486,1);  // _CELL:[A143]
    a_parm_put(64'h2b5671612b567161,64'h12aa129b12aa129b,3);  // _CELL:[A147]
    a_parm_put(64'h4feb79874feb7987,64'h227f0cd1227f0cd1,5);  // _CELL:[A151]
    a_parm_put(64'h1bbf0aee1bbf0aee,64'h438e705c438e705c,4);  // _CELL:[A155]
    a_parm_put(64'h4eb372674eb37267,64'h53e00aac53e00aac,0);  // _CELL:[A159]
    a_parm_put(64'h6c895e816c895e81,64'h4e9d461c4e9d461c,4);  // _CELL:[A163]
    a_parm_put(64'h08382ef008382ef0,64'h5d6e0c705d6e0c70,0);  // _CELL:[A167]
    a_parm_put(64'h0ed230850ed23085,64'h204d409f204d409f,0);  // _CELL:[A171]
    a_parm_put(64'h00280a8700280a87,64'h1fa4457c1fa4457c,1);  // _CELL:[A175]
    a_parm_put(64'h3ad112b73ad112b7,64'h1a3235381a323538,0);  // _CELL:[A179]
    a_parm_put(64'h3a4617493a461749,64'h0f0b35d70f0b35d7,4);  // _CELL:[A183]
    a_parm_put(64'h3126028931260289,64'h55af490a55af490a,0);  // _CELL:[A187]
    a_parm_put(64'h16e61a1316e61a13,64'h1910221219102212,2);  // _CELL:[A191]
    a_parm_put(64'h5f7313c35f7313c3,64'h6ff002906ff00290,5);  // _CELL:[A195]
    a_parm_put(64'h74995cc574995cc5,64'h64166f7164166f71,1);  // _CELL:[A199]
    a_parm_put(64'h7c294b6d7c294b6d,64'h5316495d5316495d,5);  // _CELL:[A203]
    a_parm_put(64'h4b2b1ac34b2b1ac3,64'h7ecc084b7ecc084b,0);  // _CELL:[A207]
    a_parm_put(64'h6da60eea6da60eea,64'h30b3182530b31825,0);  // _CELL:[A211]
    a_parm_put(64'h33cb0bbe33cb0bbe,64'h52c12caf52c12caf,1);  // _CELL:[A215]
    b_parm_put(4);  // _CELL:[A5]
    b_parm_put(4);  // _CELL:[A9]
    b_parm_put(1);  // _CELL:[A13]
    b_parm_put(1);  // _CELL:[A17]
    b_parm_put(1);  // _CELL:[A21]
    b_parm_put(3);  // _CELL:[A25]
    b_parm_put(5);  // _CELL:[A29]
    b_parm_put(1);  // _CELL:[A33]
    b_parm_put(5);  // _CELL:[A37]
    b_parm_put(0);  // _CELL:[A41]
    b_parm_put(1);  // _CELL:[A45]
    b_parm_put(0);  // _CELL:[A49]
    b_parm_put(1);  // _CELL:[A53]
    b_parm_put(3);  // _CELL:[A57]
    b_parm_put(4);  // _CELL:[A61]
    b_parm_put(2);  // _CELL:[A65]
    b_parm_put(1);  // _CELL:[A69]
    b_parm_put(1);  // _CELL:[A73]
    b_parm_put(0);  // _CELL:[A77]
    b_parm_put(1);  // _CELL:[A81]
    b_parm_put(3);  // _CELL:[A85]
    b_parm_put(4);  // _CELL:[A89]
    b_parm_put(1);  // _CELL:[A93]
    b_parm_put(2);  // _CELL:[A97]
    b_parm_put(2);  // _CELL:[A101]
    b_parm_put(4);  // _CELL:[A105]
    b_parm_put(1);  // _CELL:[A109]
    b_parm_put(3);  // _CELL:[A113]
    b_parm_put(0);  // _CELL:[A117]
    b_parm_put(2);  // _CELL:[A121]
    b_parm_put(1);  // _CELL:[A125]
    b_parm_put(1);  // _CELL:[A129]
    b_parm_put(3);  // _CELL:[A133]
    b_parm_put(1);  // _CELL:[A137]
    b_parm_put(2);  // _CELL:[A141]
    b_parm_put(1);  // _CELL:[A145]
    b_parm_put(0);  // _CELL:[A149]
    b_parm_put(5);  // _CELL:[A153]
    b_parm_put(5);  // _CELL:[A157]
    b_parm_put(4);  // _CELL:[A161]
    b_parm_put(5);  // _CELL:[A165]
    b_parm_put(2);  // _CELL:[A169]
    b_parm_put(2);  // _CELL:[A173]
    b_parm_put(0);  // _CELL:[A177]
    b_parm_put(1);  // _CELL:[A181]
    b_parm_put(1);  // _CELL:[A185]
    b_parm_put(5);  // _CELL:[A189]
    b_parm_put(4);  // _CELL:[A193]
    b_parm_put(5);  // _CELL:[A197]
    b_parm_put(0);  // _CELL:[A201]
    b_parm_put(4);  // _CELL:[A205]
    b_parm_put(2);  // _CELL:[A209]
    b_parm_put(2);  // _CELL:[A213]
    b_parm_put(5);  // _CELL:[A217]
  end
// # Interface (rr) ############################
// # Initialize #####
  initial begin
    #2
    HOJI_rr = 1'b0;
    HOJI_r_dt0 = 32'b0;
    HOJI_r_dt1 = 16'b0;
    HOJI_r_dt2 = 8'b0;
  end
// # Recieve enable #####
  assign rr_enable = ~HOJI_rr;
// # Recieve task #####
  task rr_recv;
    output valid;
    output  [31:0]p_r_dt0;
    output  [15:0]p_r_dt1;
    output  [7:0]p_r_dt2;
    begin
      if (HOJI_rr) begin
        valid = 1'b1;
        HOJI_rr = 1'b0;
        p_r_dt0 = HOJI_r_dt0;
        p_r_dt1 = HOJI_r_dt1;
        p_r_dt2 = HOJI_r_dt2;
      end
      else begin
        valid = 1'b0;
        p_r_dt0 = 32'b0;
        p_r_dt1 = 16'b0;
        p_r_dt2 = 8'b0;
      end
    end
  endtask
// # Recieve latch #####
  always @(rr)
    begin
      HOJI_rr <= 1'b1;
      HOJI_r_dt0 <= r_dt0;
      HOJI_r_dt1 <= r_dt1;
      HOJI_r_dt2 <= r_dt2;
    end
// # Interface (rr2) ############################
// # Initialize #####
  initial begin
    #2
    wptr_rr2 = 0;
    rptr_rr2 = 0;
  end
// # Recieve enable #####
  assign rr2_enable = ~(((((wptr_rr2+1)==(8+1)) && (rptr_rr2 == 0)) ? 1'b1:1'b0) | (((wptr_rr2+1) == rptr_rr2) ? 1'b1:1'b0));
// # Recieve task #####
  task rr2_recv;
    output valid;
    output  [31:0]p_r2_dt0;
    output  [15:0]p_r2_dt1;
    output  [7:0]p_r2_dt2;
    begin
      if (wptr_rr2 != rptr_rr2) begin
        valid = 1'b1;
        p_r2_dt0 = HOJI_r2_dt0[rptr_rr2];
        p_r2_dt1 = HOJI_r2_dt1[rptr_rr2];
        p_r2_dt2 = HOJI_r2_dt2[rptr_rr2];
        rptr_rr2 = rptr_rr2 + 1;
        if (rptr_rr2 == (8+1)) rptr_rr2 = 0;
      end
      else begin
        valid = 1'b0;
        p_r2_dt0 = 32'b0;
        p_r2_dt1 = 16'b0;
        p_r2_dt2 = 8'b0;
      end
    end
  endtask
// # Recieve latch #####
  always @(rr2)
    begin
      HOJI_r2_dt0[wptr_rr2] <= r2_dt0;
      HOJI_r2_dt1[wptr_rr2] <= r2_dt1;
      HOJI_r2_dt2[wptr_rr2] <= r2_dt2;
      wptr_rr2 = wptr_rr2 + 1;
      if (wptr_rr2 == (8+1)) wptr_rr2 = 0;
      if (wptr_rr2 == rptr_rr2) begin $display("rr2 interface fifo over."); $finish; end
    end
// # Interface (ss) ############################
// # Initialize #####
  initial begin
    ss = 1'b0;
    s_dt0 = 32'b0;
    s_dt1 = 16'b0;
    s_dt2 = 8'b0;
  end
// # Send enable #####
  task ss_send_check;
    output retcd;
    begin
      #1
      retcd = ss_enable;
    end
  endtask
// # Send task #####
  task ss_send;
    input  [31:0]p_s_dt0;
    input  [15:0]p_s_dt1;
    input  [7:0]p_s_dt2;
    begin
      #1
      ss <= ~ss;
      s_dt0 <= p_s_dt0;
      s_dt1 <= p_s_dt1;
      s_dt2 <= p_s_dt2;
    end
  endtask
// # Interface (ss2) ############################
// # Initialize #####
  initial begin
    ss2 = 1'b0;
    s2_dt0 = 32'b0;
    s2_dt1 = 16'b0;
    s2_dt2 = 8'b0;
  end
// # Send enable #####
  task ss2_send_check;
    output retcd;
    begin
      #1
      retcd = ss2_enable;
    end
  endtask
// # Send task #####
  task ss2_send;
    input  [31:0]p_s2_dt0;
    input  [15:0]p_s2_dt1;
    input  [7:0]p_s2_dt2;
    begin
      #1
      ss2 <= ~ss2;
      s2_dt0 <= p_s2_dt0;
      s2_dt1 <= p_s2_dt1;
      s2_dt2 <= p_s2_dt2;
    end
  endtask
endmodule

