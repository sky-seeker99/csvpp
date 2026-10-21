// ---------------------
// target module
// ---------------------
module target(
   clk
  ,clko
  ,rst
  ,irq_clear0
  ,irq_clear1
  ,irq_clear2
  ,irq_clear3
  ,cs
  ,we
  ,adr
  ,dtin
  ,irq0
  ,irq1
  ,irq2
  ,irq3
  ,dtout
  ,ack
);
// # port define ########################
// # input  ########
  input   clk;
  input   clko;
  input   rst;
  input   irq_clear0;
  input   irq_clear1;
  input   irq_clear2;
  input   irq_clear3;
  input   cs;
  input   we;
  input   [15:0] adr;
  input   [7:0] dtin;
// # output ########
  output  irq0;
  output  irq1;
  output  irq2;
  output  irq3;
  output  [7:0] dtout;
  output  ack;
// # register define ############################ 
  reg  ack; // _CELL:[B47]
  reg  [7:0] cnt; // _CELL:[B49]
  reg  [7:0] cnt0; // _CELL:[B50]
  reg  [7:0] cnt1; // _CELL:[B51]
  reg  [7:0] cnt2; // _CELL:[B52]
  reg  [7:0] cnt3; // _CELL:[B53]
  reg  [7:0] dtout; // _CELL:[B43]
  reg  irq0; // _CELL:[B21]
  reg  irq1; // _CELL:[B25]
  reg  irq2; // _CELL:[B29]
  reg  irq3; // _CELL:[B33]
  reg  [7:0] mem [65535:0]; // _CELL:[B48]

// # Schedule Variable ############################ 
  parameter ARY_MAX=50;
  integer target_ptr;
  integer next_top_ptr;
  integer dust_top_ptr;
  integer p_cyc;
  integer total_cyc_clko;
  integer cyc_clko_1   [ARY_MAX:0]; // ack
  integer next_clko_1  [ARY_MAX:0];
  integer before_clko_1[ARY_MAX:0];
  reg [1-1:0] value_clko_1 [ARY_MAX:0];
  integer cur_clko_1;
  integer dust_clko_1;
  integer top_clko_1;
  integer cyc_clko_0   [ARY_MAX:0]; // dtout
  integer next_clko_0  [ARY_MAX:0];
  integer before_clko_0[ARY_MAX:0];
  reg [8-1:0] value_clko_0 [ARY_MAX:0];
  integer cur_clko_0;
  integer dust_clko_0;
  integer top_clko_0;
// # State Machine Variable ############################ 
  reg reset_irq_task0,stop_irq_task0;  // _CELL:[C83]
  reg st_irq_task0_rst_wait,rst_irq_task0_rst_wait,set_irq_task0_rst_wait;  // _CELL:[B84]
  reg st_irq_task0_main,rst_irq_task0_main,set_irq_task0_main;  // _CELL:[B88]
  reg st_irq_task0_wait,rst_irq_task0_wait,set_irq_task0_wait;  // _CELL:[B97]
  reg reset_irq_task1,stop_irq_task1;  // _CELL:[C104]
  reg st_irq_task1_rst_wait,rst_irq_task1_rst_wait,set_irq_task1_rst_wait;  // _CELL:[B105]
  reg st_irq_task1_main,rst_irq_task1_main,set_irq_task1_main;  // _CELL:[B109]
  reg st_irq_task1_wait,rst_irq_task1_wait,set_irq_task1_wait;  // _CELL:[B118]
  reg reset_irq_task2,stop_irq_task2;  // _CELL:[C125]
  reg st_irq_task2_rst_wait,rst_irq_task2_rst_wait,set_irq_task2_rst_wait;  // _CELL:[B126]
  reg st_irq_task2_main,rst_irq_task2_main,set_irq_task2_main;  // _CELL:[B130]
  reg st_irq_task2_wait,rst_irq_task2_wait,set_irq_task2_wait;  // _CELL:[B139]
  reg reset_irq_task3,stop_irq_task3;  // _CELL:[C146]
  reg st_irq_task3_rst_wait,rst_irq_task3_rst_wait,set_irq_task3_rst_wait;  // _CELL:[B147]
  reg st_irq_task3_main,rst_irq_task3_main,set_irq_task3_main;  // _CELL:[B151]
  reg st_irq_task3_wait,rst_irq_task3_wait,set_irq_task3_wait;  // _CELL:[B160]
  reg reset_target_task,stop_target_task;  // _CELL:[C54]
  reg st_target_task_rst_wait,rst_target_task_rst_wait,set_target_task_rst_wait;  // _CELL:[B55]
  reg st_target_task_main,rst_target_task_main,set_target_task_main;  // _CELL:[B60]
  reg st_target_task_wait,rst_target_task_wait,set_target_task_wait;  // _CELL:[B69]
  reg st_target_task_wait2,rst_target_task_wait2,set_target_task_wait2;  // _CELL:[B81]
// # Initialize ###################### 
initial begin 
 #1 
 target_task_rst; 
 irq_task0_rst; 
 irq_task1_rst; 
 irq_task2_rst; 
 irq_task3_rst; 
end 

// # ack register ######
  always @(posedge clk) begin
    if (rst) begin
      ack <= 1'b0; // _CELL:[B47]
    end
  end

// # dtout register ######
  always @(posedge clk) begin
    if (rst) begin
      dtout <= 8'b0; // _CELL:[B43]
    end
  end

// # irq0 register ######
  always @(posedge clk) begin
    if (rst) begin
      irq0 <= 1'b0; // _CELL:[B21]
    end
  end

// # irq1 register ######
  always @(posedge clk) begin
    if (rst) begin
      irq1 <= 1'b0; // _CELL:[B25]
    end
  end

// # irq2 register ######
  always @(posedge clk) begin
    if (rst) begin
      irq2 <= 1'b0; // _CELL:[B29]
    end
  end

// # irq3 register ######
  always @(posedge clk) begin
    if (rst) begin
      irq3 <= 1'b0; // _CELL:[B33]
    end
  end


// # schedule variable initialize ################
  initial begin
    for(cur_clko_1=0;cur_clko_1<ARY_MAX;cur_clko_1=cur_clko_1+1) begin
      next_clko_1[cur_clko_1] = cur_clko_1 + 1;
      before_clko_1[cur_clko_1] = cur_clko_1 - 1;
    end
    for(cur_clko_0=0;cur_clko_0<ARY_MAX;cur_clko_0=cur_clko_0+1) begin
      next_clko_0[cur_clko_0] = cur_clko_0 + 1;
      before_clko_0[cur_clko_0] = cur_clko_0 - 1;
    end
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
    stop_irq_task0  = 1;
    reset_irq_task0 = 0;
    stop_irq_task1  = 1;
    reset_irq_task1 = 0;
    stop_irq_task2  = 1;
    reset_irq_task2 = 0;
    stop_irq_task3  = 1;
    reset_irq_task3 = 0;
    stop_target_task  = 1;
    reset_target_task = 0;
  end

// # state machine (irq_task0/rst_wait) #####
  task irq_task0_rst_wait;  // _CELL:[B84]
    begin
      if (~rst) begin  // _CELL:[A85]
        set_irq_task0_main = 1'b1;  // _CELL:[B86]
        rst_irq_task0_rst_wait = 1'b1;  // _CELL:[B86]
      end
    end
  endtask

// # state machine (irq_task0/main) #####
  task irq_task0_main;  // _CELL:[B88]
    begin
      if (~irq0) begin  // _CELL:[A89]
        cnt0 = $random+100;   // _CELL:[B90]
        set_irq_task0_wait = 1'b1;  // _CELL:[B91]
        rst_irq_task0_main = 1'b1;  // _CELL:[B91]
      end
      else begin  // _CELL:[A92]
        if (irq_clear0) begin  // _CELL:[A93]
          irq0 = 0;   // _CELL:[B94]
        end
      end
    end
  endtask

// # state machine (irq_task0/wait) #####
  task irq_task0_wait;  // _CELL:[B97]
    begin
      if (cnt0 == 0) begin  // _CELL:[A98]
        irq0 = 1;   // _CELL:[B99]
        set_irq_task0_main = 1'b1;  // _CELL:[B100]
        rst_irq_task0_wait = 1'b1;  // _CELL:[B100]
      end
      else begin  // _CELL:[A101]
        cnt0 = cnt0 - 1;   // _CELL:[B102]
      end
    end
  endtask

// # state machine (irq_task1/rst_wait) #####
  task irq_task1_rst_wait;  // _CELL:[B105]
    begin
      if (~rst) begin  // _CELL:[A106]
        set_irq_task1_main = 1'b1;  // _CELL:[B107]
        rst_irq_task1_rst_wait = 1'b1;  // _CELL:[B107]
      end
    end
  endtask

// # state machine (irq_task1/main) #####
  task irq_task1_main;  // _CELL:[B109]
    begin
      if (~irq1) begin  // _CELL:[A110]
        cnt1 = $random+100;   // _CELL:[B111]
        set_irq_task1_wait = 1'b1;  // _CELL:[B112]
        rst_irq_task1_main = 1'b1;  // _CELL:[B112]
      end
      else begin  // _CELL:[A113]
        if (irq_clear1) begin  // _CELL:[A114]
          irq1 = 0;   // _CELL:[B115]
        end
      end
    end
  endtask

// # state machine (irq_task1/wait) #####
  task irq_task1_wait;  // _CELL:[B118]
    begin
      if (cnt1 == 0) begin  // _CELL:[A119]
        irq1 = 1;   // _CELL:[B120]
        set_irq_task1_main = 1'b1;  // _CELL:[B121]
        rst_irq_task1_wait = 1'b1;  // _CELL:[B121]
      end
      else begin  // _CELL:[A122]
        cnt1 = cnt1 - 1;   // _CELL:[B123]
      end
    end
  endtask

// # state machine (irq_task2/rst_wait) #####
  task irq_task2_rst_wait;  // _CELL:[B126]
    begin
      if (~rst) begin  // _CELL:[A127]
        set_irq_task2_main = 1'b1;  // _CELL:[B128]
        rst_irq_task2_rst_wait = 1'b1;  // _CELL:[B128]
      end
    end
  endtask

// # state machine (irq_task2/main) #####
  task irq_task2_main;  // _CELL:[B130]
    begin
      if (~irq2) begin  // _CELL:[A131]
        cnt2 = $random+100;   // _CELL:[B132]
        set_irq_task2_wait = 1'b1;  // _CELL:[B133]
        rst_irq_task2_main = 1'b1;  // _CELL:[B133]
      end
      else begin  // _CELL:[A134]
        if (irq_clear2) begin  // _CELL:[A135]
          irq2 = 0;   // _CELL:[B136]
        end
      end
    end
  endtask

// # state machine (irq_task2/wait) #####
  task irq_task2_wait;  // _CELL:[B139]
    begin
      if (cnt2 == 0) begin  // _CELL:[A140]
        irq2 = 1;   // _CELL:[B141]
        set_irq_task2_main = 1'b1;  // _CELL:[B142]
        rst_irq_task2_wait = 1'b1;  // _CELL:[B142]
      end
      else begin  // _CELL:[A143]
        cnt2 = cnt2 - 1;   // _CELL:[B144]
      end
    end
  endtask

// # state machine (irq_task3/rst_wait) #####
  task irq_task3_rst_wait;  // _CELL:[B147]
    begin
      if (~rst) begin  // _CELL:[A148]
        set_irq_task3_main = 1'b1;  // _CELL:[B149]
        rst_irq_task3_rst_wait = 1'b1;  // _CELL:[B149]
      end
    end
  endtask

// # state machine (irq_task3/main) #####
  task irq_task3_main;  // _CELL:[B151]
    begin
      if (~irq3) begin  // _CELL:[A152]
        cnt3 = $random+100;   // _CELL:[B153]
        set_irq_task3_wait = 1'b1;  // _CELL:[B154]
        rst_irq_task3_main = 1'b1;  // _CELL:[B154]
      end
      else begin  // _CELL:[A155]
        if (irq_clear3) begin  // _CELL:[A156]
          irq3 = 0;   // _CELL:[B157]
        end
      end
    end
  endtask

// # state machine (irq_task3/wait) #####
  task irq_task3_wait;  // _CELL:[B160]
    begin
      if (cnt3 == 0) begin  // _CELL:[A161]
        irq3 = 1;   // _CELL:[B162]
        set_irq_task3_main = 1'b1;  // _CELL:[B163]
        rst_irq_task3_wait = 1'b1;  // _CELL:[B163]
      end
      else begin  // _CELL:[A164]
        cnt3 = cnt3 - 1;   // _CELL:[B165]
      end
    end
  endtask

// # state machine (target_task/rst_wait) #####
  task target_task_rst_wait;  // _CELL:[B55]
    begin
      if (~rst) begin  // _CELL:[A56]
        $display("target start!!\n");   // _CELL:[B57]
        set_target_task_main = 1'b1;  // _CELL:[B58]
        rst_target_task_rst_wait = 1'b1;  // _CELL:[B58]
      end
    end
  endtask

// # state machine (target_task/main) #####
  task target_task_main;  // _CELL:[B60]
    begin
      if (cs & we) begin  // _CELL:[A61]
        cnt = $random;   // _CELL:[B62]
        set_target_task_wait = 1'b1;  // _CELL:[B63]
        rst_target_task_main = 1'b1;  // _CELL:[B63]
      end
      if (cs & ~we) begin  // _CELL:[A65]
        cnt = $random;   // _CELL:[B66]
        set_target_task_wait = 1'b1;  // _CELL:[B67]
        rst_target_task_main = 1'b1;  // _CELL:[B67]
      end
    end
  endtask

// # state machine (target_task/wait) #####
  task target_task_wait;  // _CELL:[B69]
    begin
      if (cnt == 0) begin  // _CELL:[A70]
        if (we) begin  // _CELL:[A71]
          mem[adr] = dtin;   // _CELL:[B72]
        end
        else begin  // _CELL:[A73]
          p_cyc = 0; clko_0_chg(mem[adr]);  // _CELL:[D74]
          p_cyc = 1; clko_0_chg(8'hxx);  // _CELL:[D74]
        end
        p_cyc = 0; clko_1_chg(1'b1);  // _CELL:[D76]
        p_cyc = 1; clko_1_chg(1'b0);  // _CELL:[D76]
        set_target_task_wait2 = 1'b1;  // _CELL:[B77]
        rst_target_task_wait = 1'b1;  // _CELL:[B77]
      end
      else begin  // _CELL:[A78]
        cnt = cnt - 1;   // _CELL:[B79]
      end
    end
  endtask

// # state machine (target_task/wait2) #####
  task target_task_wait2;  // _CELL:[B81]
    begin
      set_target_task_main = 1'b1;  // _CELL:[B82]
      rst_target_task_wait2 = 1'b1;  // _CELL:[B82]
    end
  endtask

// # state machine main loop #####
  always @(posedge clk)  // _CELL:[C83]
    begin
      set_irq_task0_rst_wait = 1'b0;
      set_irq_task0_main = 1'b0;
      set_irq_task0_wait = 1'b0;
      rst_irq_task0_rst_wait = 1'b0;
      rst_irq_task0_main = 1'b0;
      rst_irq_task0_wait = 1'b0;
      if (st_irq_task0_rst_wait)irq_task0_rst_wait;
      if (st_irq_task0_main)irq_task0_main;
      if (st_irq_task0_wait)irq_task0_wait;
      if (reset_irq_task0) begin
        reset_irq_task0 = 1'b0;
        stop_irq_task0 = 1'b0;
        st_irq_task0_rst_wait = 1'b1;
        st_irq_task0_main = 1'b0;
        st_irq_task0_wait = 1'b0;
      end
      else if (stop_irq_task0) begin
        st_irq_task0_rst_wait = 1'b0;
        st_irq_task0_main = 1'b0;
        st_irq_task0_wait = 1'b0;
      end
      else begin
        if      (set_irq_task0_rst_wait)st_irq_task0_rst_wait = 1'b1;
        else if (rst_irq_task0_rst_wait)st_irq_task0_rst_wait = 1'b0;
        if      (set_irq_task0_main)st_irq_task0_main = 1'b1;
        else if (rst_irq_task0_main)st_irq_task0_main = 1'b0;
        if      (set_irq_task0_wait)st_irq_task0_wait = 1'b1;
        else if (rst_irq_task0_wait)st_irq_task0_wait = 1'b0;
      end
    end
  always @(posedge clk)  // _CELL:[C104]
    begin
      set_irq_task1_rst_wait = 1'b0;
      set_irq_task1_main = 1'b0;
      set_irq_task1_wait = 1'b0;
      rst_irq_task1_rst_wait = 1'b0;
      rst_irq_task1_main = 1'b0;
      rst_irq_task1_wait = 1'b0;
      if (st_irq_task1_rst_wait)irq_task1_rst_wait;
      if (st_irq_task1_main)irq_task1_main;
      if (st_irq_task1_wait)irq_task1_wait;
      if (reset_irq_task1) begin
        reset_irq_task1 = 1'b0;
        stop_irq_task1 = 1'b0;
        st_irq_task1_rst_wait = 1'b1;
        st_irq_task1_main = 1'b0;
        st_irq_task1_wait = 1'b0;
      end
      else if (stop_irq_task1) begin
        st_irq_task1_rst_wait = 1'b0;
        st_irq_task1_main = 1'b0;
        st_irq_task1_wait = 1'b0;
      end
      else begin
        if      (set_irq_task1_rst_wait)st_irq_task1_rst_wait = 1'b1;
        else if (rst_irq_task1_rst_wait)st_irq_task1_rst_wait = 1'b0;
        if      (set_irq_task1_main)st_irq_task1_main = 1'b1;
        else if (rst_irq_task1_main)st_irq_task1_main = 1'b0;
        if      (set_irq_task1_wait)st_irq_task1_wait = 1'b1;
        else if (rst_irq_task1_wait)st_irq_task1_wait = 1'b0;
      end
    end
  always @(posedge clk)  // _CELL:[C125]
    begin
      set_irq_task2_rst_wait = 1'b0;
      set_irq_task2_main = 1'b0;
      set_irq_task2_wait = 1'b0;
      rst_irq_task2_rst_wait = 1'b0;
      rst_irq_task2_main = 1'b0;
      rst_irq_task2_wait = 1'b0;
      if (st_irq_task2_rst_wait)irq_task2_rst_wait;
      if (st_irq_task2_main)irq_task2_main;
      if (st_irq_task2_wait)irq_task2_wait;
      if (reset_irq_task2) begin
        reset_irq_task2 = 1'b0;
        stop_irq_task2 = 1'b0;
        st_irq_task2_rst_wait = 1'b1;
        st_irq_task2_main = 1'b0;
        st_irq_task2_wait = 1'b0;
      end
      else if (stop_irq_task2) begin
        st_irq_task2_rst_wait = 1'b0;
        st_irq_task2_main = 1'b0;
        st_irq_task2_wait = 1'b0;
      end
      else begin
        if      (set_irq_task2_rst_wait)st_irq_task2_rst_wait = 1'b1;
        else if (rst_irq_task2_rst_wait)st_irq_task2_rst_wait = 1'b0;
        if      (set_irq_task2_main)st_irq_task2_main = 1'b1;
        else if (rst_irq_task2_main)st_irq_task2_main = 1'b0;
        if      (set_irq_task2_wait)st_irq_task2_wait = 1'b1;
        else if (rst_irq_task2_wait)st_irq_task2_wait = 1'b0;
      end
    end
  always @(posedge clk)  // _CELL:[C146]
    begin
      set_irq_task3_rst_wait = 1'b0;
      set_irq_task3_main = 1'b0;
      set_irq_task3_wait = 1'b0;
      rst_irq_task3_rst_wait = 1'b0;
      rst_irq_task3_main = 1'b0;
      rst_irq_task3_wait = 1'b0;
      if (st_irq_task3_rst_wait)irq_task3_rst_wait;
      if (st_irq_task3_main)irq_task3_main;
      if (st_irq_task3_wait)irq_task3_wait;
      if (reset_irq_task3) begin
        reset_irq_task3 = 1'b0;
        stop_irq_task3 = 1'b0;
        st_irq_task3_rst_wait = 1'b1;
        st_irq_task3_main = 1'b0;
        st_irq_task3_wait = 1'b0;
      end
      else if (stop_irq_task3) begin
        st_irq_task3_rst_wait = 1'b0;
        st_irq_task3_main = 1'b0;
        st_irq_task3_wait = 1'b0;
      end
      else begin
        if      (set_irq_task3_rst_wait)st_irq_task3_rst_wait = 1'b1;
        else if (rst_irq_task3_rst_wait)st_irq_task3_rst_wait = 1'b0;
        if      (set_irq_task3_main)st_irq_task3_main = 1'b1;
        else if (rst_irq_task3_main)st_irq_task3_main = 1'b0;
        if      (set_irq_task3_wait)st_irq_task3_wait = 1'b1;
        else if (rst_irq_task3_wait)st_irq_task3_wait = 1'b0;
      end
    end
  always @(posedge clk)  // _CELL:[C54]
    begin
      set_target_task_rst_wait = 1'b0;
      set_target_task_main = 1'b0;
      set_target_task_wait = 1'b0;
      set_target_task_wait2 = 1'b0;
      rst_target_task_rst_wait = 1'b0;
      rst_target_task_main = 1'b0;
      rst_target_task_wait = 1'b0;
      rst_target_task_wait2 = 1'b0;
      if (st_target_task_rst_wait)target_task_rst_wait;
      if (st_target_task_main)target_task_main;
      if (st_target_task_wait)target_task_wait;
      if (st_target_task_wait2)target_task_wait2;
      if (reset_target_task) begin
        reset_target_task = 1'b0;
        stop_target_task = 1'b0;
        st_target_task_rst_wait = 1'b1;
        st_target_task_main = 1'b0;
        st_target_task_wait = 1'b0;
        st_target_task_wait2 = 1'b0;
      end
      else if (stop_target_task) begin
        st_target_task_rst_wait = 1'b0;
        st_target_task_main = 1'b0;
        st_target_task_wait = 1'b0;
        st_target_task_wait2 = 1'b0;
      end
      else begin
        if      (set_target_task_rst_wait)st_target_task_rst_wait = 1'b1;
        else if (rst_target_task_rst_wait)st_target_task_rst_wait = 1'b0;
        if      (set_target_task_main)st_target_task_main = 1'b1;
        else if (rst_target_task_main)st_target_task_main = 1'b0;
        if      (set_target_task_wait)st_target_task_wait = 1'b1;
        else if (rst_target_task_wait)st_target_task_wait = 1'b0;
        if      (set_target_task_wait2)st_target_task_wait2 = 1'b1;
        else if (rst_target_task_wait2)st_target_task_wait2 = 1'b0;
      end
    end

// # reset/stop #####  // _CELL:[C83]
  task irq_task0_rst;
    begin
      reset_irq_task0 = 1'b1;
    end
  endtask
  task irq_task0_stop;
    begin
      stop_irq_task0 = 1'b1;
    end
  endtask

// # reset/stop #####  // _CELL:[C104]
  task irq_task1_rst;
    begin
      reset_irq_task1 = 1'b1;
    end
  endtask
  task irq_task1_stop;
    begin
      stop_irq_task1 = 1'b1;
    end
  endtask

// # reset/stop #####  // _CELL:[C125]
  task irq_task2_rst;
    begin
      reset_irq_task2 = 1'b1;
    end
  endtask
  task irq_task2_stop;
    begin
      stop_irq_task2 = 1'b1;
    end
  endtask

// # reset/stop #####  // _CELL:[C146]
  task irq_task3_rst;
    begin
      reset_irq_task3 = 1'b1;
    end
  endtask
  task irq_task3_stop;
    begin
      stop_irq_task3 = 1'b1;
    end
  endtask

// # reset/stop #####  // _CELL:[C54]
  task target_task_rst;
    begin
      reset_target_task = 1'b1;
    end
  endtask
  task target_task_stop;
    begin
      stop_target_task = 1'b1;
    end
  endtask

// # schedule task ############################
// # store [ack] #####
  task clko_1_chg;
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
      if (dust_clko_1 == -1) begin $display("index over (line=ack)\n"); ret_flg = 1; end
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
// # check & exec [ack] #####
  always @(posedge clko) begin
    if (top_clko_1 != -1) begin
      if (total_cyc_clko == cyc_clko_1[top_clko_1]) begin
        ack = value_clko_1[top_clko_1];
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
// # store [dtout] #####
  task clko_0_chg;
    input [8-1:0] p_val;
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
      if (dust_clko_0 == -1) begin $display("index over (line=dtout)\n"); ret_flg = 1; end
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
// # check & exec [dtout] #####
  always @(posedge clko) begin
    if (top_clko_0 != -1) begin
      if (total_cyc_clko == cyc_clko_0[top_clko_0]) begin
        dtout = value_clko_0[top_clko_0];
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
  task clko_1_printf; // ack
    integer i;
    begin
      $display("<ack>");
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
  task clko_0_printf; // dtout
    integer i;
    begin
      $display("<dtout>");
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
endmodule

