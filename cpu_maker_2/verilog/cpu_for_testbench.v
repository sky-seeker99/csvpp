// ---------------------
// cpu_for_testbench module
// ---------------------
module cpu_for_testbench(
   clk
  ,clko
  ,rst
  ,irq
  ,dtin
  ,ack
  ,irq_clear
  ,cs
  ,we
  ,adr
  ,dtout
);
// # port define ########################
// # input  ########
  input   clk;
  input   clko;
  input   rst;
  input   [3:0] irq;
  input   [7:0] dtin;
  input   ack;
// # output ########
  output  [3:0] irq_clear;
  output  cs;
  output  we;
  output  [15:0] adr;
  output  [7:0] dtout;
// # register define ############################ 
  reg  [15:0] adr; // _CELL:[B17]
  reg  cs; // _CELL:[B13]
  reg  [31:0] curr_irq_level; // _CELL:[B135]
  reg  [7:0] dtout; // _CELL:[B21]
  reg  [31:0] err_cnt; // _CELL:[B134]
  reg  [31:0] func_no; // _CELL:[B33]
  reg  [31:0] guard_func_no; // _CELL:[B130]
  reg  [31:0] guard_parm_su; // _CELL:[B129]
  reg  [3:0] irq_clear; // _CELL:[B11]
  reg  [31:0] parm_su; // _CELL:[B34]
  reg  [191:0] prg_area [107:0]; // _CELL:[B131]
  reg  [31:0] reg_area [13:0]; // _CELL:[B133]
  reg  [31:0] start_reg; // _CELL:[B35]
  reg  [31:0] stk_area [4096:0]; // _CELL:[B132]
  reg  [31:0] sv_irq_area [1:0]; // _CELL:[B137]
  reg  [31:0] sv_vec_area [1:0]; // _CELL:[B136]
  reg  we; // _CELL:[B15]

// # Schedule Variable ############################ 
  parameter ARY_MAX=50;
  integer target_ptr;
  integer next_top_ptr;
  integer dust_top_ptr;
  integer p_cyc;
  integer total_cyc_clko;
  integer cyc_clko_2   [ARY_MAX:0]; // adr
  integer next_clko_2  [ARY_MAX:0];
  integer before_clko_2[ARY_MAX:0];
  reg [16-1:0] value_clko_2 [ARY_MAX:0];
  integer cur_clko_2;
  integer dust_clko_2;
  integer top_clko_2;
  integer cyc_clko_0   [ARY_MAX:0]; // cs
  integer next_clko_0  [ARY_MAX:0];
  integer before_clko_0[ARY_MAX:0];
  reg [1-1:0] value_clko_0 [ARY_MAX:0];
  integer cur_clko_0;
  integer dust_clko_0;
  integer top_clko_0;
  integer cyc_clko_3   [ARY_MAX:0]; // dtout
  integer next_clko_3  [ARY_MAX:0];
  integer before_clko_3[ARY_MAX:0];
  reg [8-1:0] value_clko_3 [ARY_MAX:0];
  integer cur_clko_3;
  integer dust_clko_3;
  integer top_clko_3;
  integer cyc_clko_4   [ARY_MAX:0]; // irq_clear
  integer next_clko_4  [ARY_MAX:0];
  integer before_clko_4[ARY_MAX:0];
  reg [4-1:0] value_clko_4 [ARY_MAX:0];
  integer cur_clko_4;
  integer dust_clko_4;
  integer top_clko_4;
  integer cyc_clko_1   [ARY_MAX:0]; // we
  integer next_clko_1  [ARY_MAX:0];
  integer before_clko_1[ARY_MAX:0];
  reg [1-1:0] value_clko_1 [ARY_MAX:0];
  integer cur_clko_1;
  integer dust_clko_1;
  integer top_clko_1;
// # State Machine Variable ############################ 
  reg reset_cpu_task,stop_cpu_task;  // _CELL:[C36]
  reg st_cpu_task_rst_wait,rst_cpu_task_rst_wait,set_cpu_task_rst_wait;  // _CELL:[B42]
  reg st_cpu_task_main,rst_cpu_task_main,set_cpu_task_main;  // _CELL:[B47]
  reg st_cpu_task_nop,rst_cpu_task_nop,set_cpu_task_nop;  // _CELL:[B94]
  reg st_cpu_task_read_acc,rst_cpu_task_read_acc,set_cpu_task_read_acc;  // _CELL:[B100]
  reg st_cpu_task_write_acc,rst_cpu_task_write_acc,set_cpu_task_write_acc;  // _CELL:[B109]
// # State Machine Variable(Local/Parm) ################ 
  reg[32-1:0] l_cpu_task_cnt;  // _CELL:[D37]
  reg[32-1:0] l_cpu_task_p0;  // _CELL:[D38]
  reg[32-1:0] l_cpu_task_p1;  // _CELL:[D39]
  reg[32-1:0] l_cpu_task_p2;  // _CELL:[D40]
  reg[32-1:0] l_cpu_task_sv_area;  // _CELL:[D41]
// # task : [program_end] ##############
  task program_end;  // _CELL:[B138]
    begin
      if (err_cnt == 0) begin  // _CELL:[A139]
        $display("[Result-All OK].");   // _CELL:[A139]
      end
      else begin  // _CELL:[A140]
        $display("[Result-NG (cnt=%d) ]",err_cnt);   // _CELL:[A140]
      end
      $finish;   // _CELL:[A141]
    end
  endtask

// # task : [program_load] ##############
  task program_load;  // _CELL:[B142]
    reg  [31:0] cmd;  // _CELL:[D143]
    reg  [31:0] parm0;  // _CELL:[D144]
    reg  [31:0] parm1;  // _CELL:[D145]
    reg  [31:0] parm2;  // _CELL:[D146]
    reg  [31:0] parm3;  // _CELL:[D147]
    reg  [31:0] parm4;  // _CELL:[D148]
    begin
      cmd = 0;
      parm0 = 0;
      parm1 = 0;
      parm2 = 0;
      parm3 = 0;
      parm4 = 0;
      $readmemh("cpu_for_testbench.cod",prg_area);   // _CELL:[A149]
      reg_area[0] = 32'h00000000;   // _CELL:[A150]
      reg_area[1] = 32'h00000001;   // _CELL:[A151]
      {cmd,parm0,parm1,parm2,parm3,parm4} = prg_area[101];   // _CELL:[A152]
      if ((parm0 !== 537985574) || (parm1 !== 386138112)) begin  // _CELL:[A153]
        $display("addr=101 parm0=%x parm1=%x",parm0,parm1);   // _CELL:[A154]
        $display("[code file(cpu_for_testbench.cod)] and [verilog file(cpu_for_testbench.v)] miss match error!!");   // _CELL:[A155]
        $finish;   // _CELL:[A156]
      end
    end
  endtask

// # function : [program_exec] ##############
  function  [95:0] program_exec;  // _CELL:[B158]
input dmy;
    reg  extend_flg;  // _CELL:[D159]
    reg  [31:0] cmd;  // _CELL:[D160]
    reg  [31:0] parm0;  // _CELL:[D161]
    reg  [31:0] parm1;  // _CELL:[D162]
    reg  [31:0] parm2;  // _CELL:[D163]
    reg  [31:0] parm3;  // _CELL:[D164]
    reg  [31:0] parm4;  // _CELL:[D165]
    reg  [31:0] cnt;  // _CELL:[D166]
    reg  [31:0] i;  // _CELL:[D167]
    reg  [31:0] sv_cnt;  // _CELL:[D168]
    reg  [31:0] p0;  // _CELL:[D169]
    reg  [31:0] p1;  // _CELL:[D170]
    begin
      extend_flg = 1;
      cmd = 0;
      parm0 = 0;
      parm1 = 0;
      parm2 = 0;
      parm3 = 0;
      parm4 = 0;
      cnt = 0;
      i = 0;
      sv_cnt = 0;
      p0 = 0;
      p1 = 0;
      while(extend_flg) begin   // _CELL:[A171]
      {cmd,parm0,parm1,parm2,parm3,parm4} = prg_area[reg_area[0]];   // _CELL:[A172]
      if (reg_area[0] === 32'hxxxxxxxx) begin  // _CELL:[A173]
        $display("program counter abnormal."); $finish;   // _CELL:[A174]
      end
      sv_cnt = reg_area[0];   // _CELL:[A176]
      extend_flg = 0;   // _CELL:[A177]
      if (cmd ==  7) begin  // _CELL:[A178]
        if (curr_irq_level != parm1) begin  // _CELL:[A179]
          $display("program irq abnormal. irq=%d  expect_irq=%d",curr_irq_level,parm1); $finish;   // _CELL:[A180]
        end
        for(i=0;i<13;i=i+1) begin   // _CELL:[A182]
        reg_area[i] = sv_vec_area[14*parm0+i];   // _CELL:[A183]
        end   // _CELL:[A184]
        curr_irq_level = sv_irq_area[parm0];   // _CELL:[A185]
      end
      if (cmd ==  6) begin  // _CELL:[A187]
        extend_flg = 1;   // _CELL:[A188]
        reg_area[0] = reg_area[0] + 1;   // _CELL:[A189]
      end
      if (cmd ==  2) begin  // _CELL:[A191]
        if (reg_area[3] == 1) begin  // _CELL:[A192]
          reg_area[0] = parm0;   // _CELL:[A193]
        end
        else begin  // _CELL:[A194]
          reg_area[0] = parm1;   // _CELL:[A195]
        end
        extend_flg = 1;   // _CELL:[A197]
      end
      if (cmd ==  1) begin  // _CELL:[A199]
        p0 = reg_area[parm1+0];   // _CELL:[A200]
        p1 = reg_area[parm1+1];   // _CELL:[A201]
        case(parm0)   // _CELL:[A202]
        {32'h0} : reg_area[parm1] = p0;   // _CELL:[A203]
        {32'h3} : reg_area[parm1] = p0!=p1;   // _CELL:[A204]
        {32'h2} : reg_area[parm1] = p0+p1;   // _CELL:[A205]
        {32'h1} : reg_area[parm1] = p0<(p1);   // _CELL:[A206]
        default:reg_area[parm1] = 32'h0;   // _CELL:[A207]
        endcase   // _CELL:[A208]
        reg_area[0] = reg_area[0] + 1;   // _CELL:[A209]
        extend_flg = 1;   // _CELL:[A210]
      end
      if (cmd ==  4) begin  // _CELL:[A212]
        case(parm0)   // _CELL:[A213]
        {32'h2} : $display("Result - Good");   // _CELL:[A214]
        {32'h1} : $display("Result - NG");   // _CELL:[A215]
        {32'h0} : $display("data unmatch (read data = %x  expect data = %x)",reg_area[parm1+0],reg_area[parm1+1]);   // _CELL:[A216]
        default:$display("printf error.");   // _CELL:[A217]
        endcase   // _CELL:[A218]
        reg_area[0] = reg_area[0] + 1;   // _CELL:[A219]
        extend_flg = 1;   // _CELL:[A220]
      end
      if (cmd ==  5) begin  // _CELL:[A222]
        case(parm0)   // _CELL:[A223]
        default:$display("extend error.");   // _CELL:[A224]
        endcase   // _CELL:[A225]
        reg_area[0] = reg_area[0] + 1;   // _CELL:[A226]
        extend_flg = 1;   // _CELL:[A227]
      end
      if (cmd == 0) begin  // _CELL:[A229]
        reg_area[0] = reg_area[0] + 1;   // _CELL:[A230]
        if (parm0 == 0) begin  // _CELL:[A231]
          reg_area[parm1] = parm2 + parm3 - parm4;   // _CELL:[A232]
        end
        if (parm0 == 2) begin  // _CELL:[A234]
          reg_area[parm1] = reg_area[parm2] + parm3 - parm4;   // _CELL:[A235]
        end
        if (parm0 == 1) begin  // _CELL:[A237]
          reg_area[parm1] = stk_area[reg_area[parm2]] + parm3 - parm4;   // _CELL:[A238]
        end
        if (parm0 == 3) begin  // _CELL:[A240]
          stack_area_write(reg_area[parm1],parm2 + parm3 - parm4);   // _CELL:[A241]
        end
        if (parm0 == 4) begin  // _CELL:[A243]
          stack_area_write(reg_area[parm1],reg_area[parm2] + parm3 - parm4);   // _CELL:[A244]
        end
        if (parm0 == 5) begin  // _CELL:[A246]
          reg_area[parm1] = reg_area[parm1] + reg_area[parm2] * parm3 - parm4;   // _CELL:[A247]
        end
        extend_flg = 1;   // _CELL:[A249]
      end
      if (cmd == 3) begin  // _CELL:[A251]
        guard_parm_su = parm2;   // _CELL:[A252]
        guard_func_no = parm0;   // _CELL:[A253]
        program_exec = {parm0,parm1,parm2};   // _CELL:[A254]
        reg_area[0] = reg_area[0] + 1;   // _CELL:[A255]
      end
      end   // _CELL:[A257]
    end
  endfunction

// # task : [stack_area_write] ##############
  task stack_area_write;  // _CELL:[B258]
    input  [31:0] addr;  // _CELL:[C259]
    input  [31:0] data;  // _CELL:[C260]
    begin
      if (addr >= 4096) begin  // _CELL:[A261]
        $display("stack over flow error!!  load_file[cpu_for_testbench.cod]  stack_area=[1000]  write_addr=[%x]",addr);   // _CELL:[A262]
        $finish;   // _CELL:[A263]
      end
      stk_area[addr] = data;   // _CELL:[A265]
    end
  endtask

// # function : [variable_read] ##############
  function  [31:0] variable_read;  // _CELL:[B266]
    input  [31:0] parm_no;  // _CELL:[C267]
    begin
      if (parm_no >= guard_parm_su) begin  // _CELL:[A268]
        $display("interface parameter error!!   load_file[cpu_for_testbench.cod]  task_name[variable_read]  func_no[%d]   interface side parm_no[%d]   program side parm_count[%d]",guard_func_no,parm_no,guard_parm_su);   // _CELL:[A269]
        $finish;   // _CELL:[A270]
      end
      variable_read = reg_area[start_reg+parm_no];   // _CELL:[A272]
    end
  endfunction

// # task : [variable_write] ##############
  task variable_write;  // _CELL:[B273]
    input  [31:0] parm_no;  // _CELL:[C274]
    input  [31:0] write_data;  // _CELL:[C275]
    begin
      if (parm_no >= guard_parm_su) begin  // _CELL:[A276]
        $display("interface parameter error!!   load_file[cpu_for_testbench.cod]  task_name[variable_write]  func_no[%d]   interface side parm_no[%d]   program side parm_count[%d]  write_data[%d]",guard_func_no,parm_no,guard_parm_su,write_data);   // _CELL:[A277]
        $finish;   // _CELL:[A278]
      end
      stack_area_write(reg_area[start_reg+parm_no],write_data);   // _CELL:[A280]
    end
  endtask

// # function : [variable_write_area_get] ##############
  function  [31:0] variable_write_area_get;  // _CELL:[B281]
    input  [31:0] parm_no;  // _CELL:[C282]
    begin
      if (parm_no >= guard_parm_su) begin  // _CELL:[A283]
        $display("interface parameter error!!   load_file[cpu_for_testbench.cod]  task_name[variable_write_area_get]  func_no[%d]   interface side parm_no[%d]   program side parm_count[%d]",guard_func_no,parm_no,guard_parm_su);   // _CELL:[A284]
        $finish;   // _CELL:[A285]
      end
      variable_write_area_get = reg_area[start_reg+parm_no];   // _CELL:[A287]
    end
  endfunction

// # task : [variable_write_area] ##############
  task variable_write_area;  // _CELL:[B288]
    input  [31:0] area;  // _CELL:[C289]
    input  [31:0] write_data;  // _CELL:[C290]
    begin
      stack_area_write(area,write_data);   // _CELL:[A291]
    end
  endtask

// # Initialize ###################### 
initial begin 
 #1 
 cpu_task_rst; 
 
end 
// # program load ###################### 
 initial begin 
  #1 
  program_load; 
  err_cnt = 0; 
  curr_irq_level = 0; 
 end 

// # adr register ######
  always @(posedge clk) begin
    if (rst) begin
      adr <= 16'b0; // _CELL:[B17]
    end
  end

// # cs register ######
  always @(posedge clk) begin
    if (rst) begin
      cs <= 1'b0; // _CELL:[B13]
    end
  end

// # dtout register ######
  always @(posedge clk) begin
    if (rst) begin
      dtout <= 8'b0; // _CELL:[B21]
    end
  end

// # irq_clear register ######
  always @(posedge clk) begin
    if (rst) begin
      irq_clear <= 4'b0; // _CELL:[B11]
    end
  end

// # we register ######
  always @(posedge clk) begin
    if (rst) begin
      we <= 1'b0; // _CELL:[B15]
    end
  end


// # schedule variable initialize ################
  initial begin
    for(cur_clko_2=0;cur_clko_2<ARY_MAX;cur_clko_2=cur_clko_2+1) begin
      next_clko_2[cur_clko_2] = cur_clko_2 + 1;
      before_clko_2[cur_clko_2] = cur_clko_2 - 1;
    end
    for(cur_clko_0=0;cur_clko_0<ARY_MAX;cur_clko_0=cur_clko_0+1) begin
      next_clko_0[cur_clko_0] = cur_clko_0 + 1;
      before_clko_0[cur_clko_0] = cur_clko_0 - 1;
    end
    for(cur_clko_3=0;cur_clko_3<ARY_MAX;cur_clko_3=cur_clko_3+1) begin
      next_clko_3[cur_clko_3] = cur_clko_3 + 1;
      before_clko_3[cur_clko_3] = cur_clko_3 - 1;
    end
    for(cur_clko_4=0;cur_clko_4<ARY_MAX;cur_clko_4=cur_clko_4+1) begin
      next_clko_4[cur_clko_4] = cur_clko_4 + 1;
      before_clko_4[cur_clko_4] = cur_clko_4 - 1;
    end
    for(cur_clko_1=0;cur_clko_1<ARY_MAX;cur_clko_1=cur_clko_1+1) begin
      next_clko_1[cur_clko_1] = cur_clko_1 + 1;
      before_clko_1[cur_clko_1] = cur_clko_1 - 1;
    end
    next_clko_2[ARY_MAX-1] = -1;
    cur_clko_2  = -1;
    top_clko_2  = -1;
    dust_clko_2 =  0;
    next_clko_0[ARY_MAX-1] = -1;
    cur_clko_0  = -1;
    top_clko_0  = -1;
    dust_clko_0 =  0;
    next_clko_3[ARY_MAX-1] = -1;
    cur_clko_3  = -1;
    top_clko_3  = -1;
    dust_clko_3 =  0;
    next_clko_4[ARY_MAX-1] = -1;
    cur_clko_4  = -1;
    top_clko_4  = -1;
    dust_clko_4 =  0;
    next_clko_1[ARY_MAX-1] = -1;
    cur_clko_1  = -1;
    top_clko_1  = -1;
    dust_clko_1 =  0;
  end

// # state machine variable initialize ################
  initial begin
    stop_cpu_task  = 1;
    reset_cpu_task = 0;
  end

// # state machine (cpu_task/rst_wait) #####
  task cpu_task_rst_wait;  // _CELL:[B42]
    begin
      if (~rst) begin  // _CELL:[A43]
        $display("cpu_for_testbench cpu start!!\n");   // _CELL:[B44]
        set_cpu_task_main = 1'b1;  // _CELL:[B45]
        rst_cpu_task_rst_wait = 1'b1;  // _CELL:[B45]
      end
    end
  endtask

// # state machine (cpu_task/main) #####
  task cpu_task_main;  // _CELL:[B47]
    begin
      {func_no,start_reg,parm_su} = program_exec(0);   // _CELL:[B48]
      if (func_no == 0) begin  // _CELL:[A49]
        l_cpu_task_p0 = variable_read(0);   // _CELL:[B50]
        l_cpu_task_cnt  = 0;   // _CELL:[B51]
        set_cpu_task_nop = 1'b1;  // _CELL:[B52]
        rst_cpu_task_main = 1'b1;  // _CELL:[B52]
      end
      if (func_no == 1) begin  // _CELL:[A54]
        l_cpu_task_p0 = variable_read(0);   // _CELL:[B55]
        variable_write(1,$random % l_cpu_task_p0);   // _CELL:[B56]
      end
      if (func_no == 2) begin  // _CELL:[A58]
        $display("simlation complete.(cpu_for_testbench)");   // _CELL:[B59]
        $finish;   // _CELL:[B60]
      end
      if (func_no == 10) begin  // _CELL:[A62]
        l_cpu_task_p0 = variable_read(0);   // _CELL:[B63]
        l_cpu_task_sv_area = variable_write_area_get(1);   // _CELL:[B64]
        p_cyc = 0; clko_0_chg(1'b1);  // _CELL:[D65]
        p_cyc = 0; clko_1_chg(1'b0);  // _CELL:[D65]
        p_cyc = 0; clko_2_chg(l_cpu_task_p0);  // _CELL:[D65]
        set_cpu_task_read_acc = 1'b1;  // _CELL:[B68]
        rst_cpu_task_main = 1'b1;  // _CELL:[B68]
      end
      if (func_no == 11) begin  // _CELL:[A70]
        l_cpu_task_p0 = variable_read(0);   // _CELL:[B71]
        l_cpu_task_p1 = variable_read(1);   // _CELL:[B72]
        p_cyc = 0; clko_0_chg(1'b1);  // _CELL:[D73]
        p_cyc = 0; clko_1_chg(1'b1);  // _CELL:[D73]
        p_cyc = 0; clko_2_chg(l_cpu_task_p0);  // _CELL:[D73]
        p_cyc = 0; clko_3_chg(l_cpu_task_p1);  // _CELL:[D73]
        set_cpu_task_write_acc = 1'b1;  // _CELL:[B77]
        rst_cpu_task_main = 1'b1;  // _CELL:[B77]
      end
      if (func_no == 12) begin  // _CELL:[A79]
        l_cpu_task_p0 = variable_read(0);   // _CELL:[B80]
        if (l_cpu_task_p0 == 0) begin  // _CELL:[A81]
          p_cyc = 0; clko_4_chg(4'b0001);  // _CELL:[D82]
          p_cyc = 1; clko_4_chg(4'b0000);  // _CELL:[D82]
        end
        if (l_cpu_task_p0 == 1) begin  // _CELL:[A84]
          p_cyc = 0; clko_4_chg(4'b0010);  // _CELL:[D85]
          p_cyc = 1; clko_4_chg(4'b0000);  // _CELL:[D85]
        end
        if (l_cpu_task_p0 == 2) begin  // _CELL:[A87]
          p_cyc = 0; clko_4_chg(4'b0100);  // _CELL:[D88]
          p_cyc = 1; clko_4_chg(4'b0000);  // _CELL:[D88]
        end
        if (l_cpu_task_p0 == 3) begin  // _CELL:[A90]
          p_cyc = 0; clko_4_chg(4'b1000);  // _CELL:[D91]
          p_cyc = 1; clko_4_chg(4'b0000);  // _CELL:[D91]
        end
      end
    end
  endtask

// # state machine (cpu_task/nop) #####
  task cpu_task_nop;  // _CELL:[B94]
    begin
      if (l_cpu_task_cnt == l_cpu_task_p0) begin  // _CELL:[A95]
        set_cpu_task_main = 1'b1;  // _CELL:[B96]
        rst_cpu_task_nop = 1'b1;  // _CELL:[B96]
      end
      else begin  // _CELL:[A97]
        l_cpu_task_cnt = l_cpu_task_cnt + 1;   // _CELL:[B98]
      end
    end
  endtask

// # state machine (cpu_task/read_acc) #####
  task cpu_task_read_acc;  // _CELL:[B100]
    begin
      if (ack) begin  // _CELL:[A101]
        variable_write_area(l_cpu_task_sv_area,dtin);   // _CELL:[B102]
        p_cyc = 0; clko_0_chg(1'b0);  // _CELL:[D103]
        p_cyc = 0; clko_1_chg(1'b0);  // _CELL:[D103]
        p_cyc = 0; clko_2_chg(16'h0);  // _CELL:[D103]
        $display("Read Access [addr:%x][data:%x]",adr,dtin);   // _CELL:[B106]
        set_cpu_task_main = 1'b1;  // _CELL:[B107]
        rst_cpu_task_read_acc = 1'b1;  // _CELL:[B107]
      end
    end
  endtask

// # state machine (cpu_task/write_acc) #####
  task cpu_task_write_acc;  // _CELL:[B109]
    begin
      if (ack) begin  // _CELL:[A110]
        p_cyc = 0; clko_0_chg(1'b0);  // _CELL:[D111]
        p_cyc = 0; clko_1_chg(1'b0);  // _CELL:[D111]
        p_cyc = 0; clko_2_chg(16'h0);  // _CELL:[D111]
        p_cyc = 0; clko_3_chg(8'h0);  // _CELL:[D111]
        $display("Write Access [addr:%x][data:%x]",adr,dtout);   // _CELL:[B115]
        set_cpu_task_main = 1'b1;  // _CELL:[B116]
        rst_cpu_task_write_acc = 1'b1;  // _CELL:[B116]
      end
    end
  endtask

// # state machine main loop #####
  always @(posedge clk)  // _CELL:[C36]
    begin
      set_cpu_task_rst_wait = 1'b0;
      set_cpu_task_main = 1'b0;
      set_cpu_task_nop = 1'b0;
      set_cpu_task_read_acc = 1'b0;
      set_cpu_task_write_acc = 1'b0;
      rst_cpu_task_rst_wait = 1'b0;
      rst_cpu_task_main = 1'b0;
      rst_cpu_task_nop = 1'b0;
      rst_cpu_task_read_acc = 1'b0;
      rst_cpu_task_write_acc = 1'b0;
      if (st_cpu_task_rst_wait)cpu_task_rst_wait;
      if (st_cpu_task_main)cpu_task_main;
      if (st_cpu_task_nop)cpu_task_nop;
      if (st_cpu_task_read_acc)cpu_task_read_acc;
      if (st_cpu_task_write_acc)cpu_task_write_acc;
      if (reset_cpu_task) begin
        reset_cpu_task = 1'b0;
        stop_cpu_task = 1'b0;
        st_cpu_task_rst_wait = 1'b1;
        st_cpu_task_main = 1'b0;
        st_cpu_task_nop = 1'b0;
        st_cpu_task_read_acc = 1'b0;
        st_cpu_task_write_acc = 1'b0;
      end
      else if (stop_cpu_task) begin
        st_cpu_task_rst_wait = 1'b0;
        st_cpu_task_main = 1'b0;
        st_cpu_task_nop = 1'b0;
        st_cpu_task_read_acc = 1'b0;
        st_cpu_task_write_acc = 1'b0;
      end
      else begin
        if      (set_cpu_task_rst_wait)st_cpu_task_rst_wait = 1'b1;
        else if (rst_cpu_task_rst_wait)st_cpu_task_rst_wait = 1'b0;
        if      (set_cpu_task_main)st_cpu_task_main = 1'b1;
        else if (rst_cpu_task_main)st_cpu_task_main = 1'b0;
        if      (set_cpu_task_nop)st_cpu_task_nop = 1'b1;
        else if (rst_cpu_task_nop)st_cpu_task_nop = 1'b0;
        if      (set_cpu_task_read_acc)st_cpu_task_read_acc = 1'b1;
        else if (rst_cpu_task_read_acc)st_cpu_task_read_acc = 1'b0;
        if      (set_cpu_task_write_acc)st_cpu_task_write_acc = 1'b1;
        else if (rst_cpu_task_write_acc)st_cpu_task_write_acc = 1'b0;
      end
    end

// # reset/stop #####  // _CELL:[C36]
  task cpu_task_rst;
    begin
      reset_cpu_task = 1'b1;
      l_cpu_task_cnt <= 0;  // _CELL:[D37]
      l_cpu_task_p0 <= 0;  // _CELL:[D38]
      l_cpu_task_p1 <= 0;  // _CELL:[D39]
      l_cpu_task_p2 <= 0;  // _CELL:[D40]
      l_cpu_task_sv_area <= 0;  // _CELL:[D41]
    end
  endtask
  task cpu_task_stop;
    begin
      stop_cpu_task = 1'b1;
    end
  endtask

// # schedule task ############################
// # store [adr] #####
  task clko_2_chg;
    input [16-1:0] p_val;
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
      if (dust_clko_2 == -1) begin $display("index over (line=adr)\n"); ret_flg = 1; end
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
// # check & exec [adr] #####
  always @(posedge clko) begin
    if (top_clko_2 != -1) begin
      if (total_cyc_clko == cyc_clko_2[top_clko_2]) begin
        adr = value_clko_2[top_clko_2];
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
// # store [dtout] #####
  task clko_3_chg;
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
      if (dust_clko_3 == -1) begin $display("index over (line=dtout)\n"); ret_flg = 1; end
      if (ret_flg == 0) begin
        cyc = p_cyc + total_cyc_clko;
        if (cur_clko_3 == -1) cur_clko_3 = top_clko_3;
        addin = 0;
        srch_kbn = 2;
        rtn_cd = -1;
        loop_flg = 1;
      end
      while(loop_flg) begin
        if (top_clko_3 == -1) begin addin = 1; loop_flg = 0; end
        if (loop_flg == 1) begin
          rtn_cd = 1;
          if (cyc_clko_3[cur_clko_3] == cyc) rtn_cd = 0;
          if (cyc_clko_3[cur_clko_3] >  cyc) rtn_cd = -1;
          if (rtn_cd == 0) loop_flg = 0;
        end
        if (loop_flg == 1) begin
          if (srch_kbn == 2) srch_kbn = rtn_cd;
          if (srch_kbn != rtn_cd) begin 
            if (rtn_cd == 1) cur_clko_3 = next_clko_3[cur_clko_3];
            loop_flg = 0;
          end
        end
        if (loop_flg == 1) begin
          if (rtn_cd == 1) begin
            if (next_clko_3[cur_clko_3] == -1) begin addin = 1; loop_flg = 0; end
            else  cur_clko_3 = next_clko_3[cur_clko_3];
          end
          else begin
            if (before_clko_3[cur_clko_3] == -1) loop_flg = 0;
            else  cur_clko_3 = before_clko_3[cur_clko_3];
          end
        end
      end
      if (ret_flg == 0) begin
        if (rtn_cd == 0) begin value_clko_3[cur_clko_3] = p_val; ret_flg = 1; end
      end
      if (ret_flg == 0) begin
        target_ptr = dust_clko_3;
        dust_clko_3 = next_clko_3[dust_clko_3];
        if (dust_clko_3 != -1) before_clko_3[dust_clko_3] = -1;
        cyc_clko_3[target_ptr] = cyc;
        value_clko_3[target_ptr] = p_val;
      end
      if (ret_flg == 0) begin
        if (cur_clko_3 == -1) begin
          top_clko_3 = target_ptr;
          before_clko_3[target_ptr] = -1;
          next_clko_3[target_ptr] = -1;
          ret_flg = 1;
        end
      end
      if (ret_flg == 0) begin
        if (addin == 1) begin
          next_clko_3[cur_clko_3]   = target_ptr;
          before_clko_3[target_ptr] = cur_clko_3;
          next_clko_3[target_ptr] = -1;
        end
        else begin
          sv_ptr = before_clko_3[cur_clko_3];
          next_top_ptr = before_clko_3[cur_clko_3];
          before_clko_3[cur_clko_3]   = target_ptr;
          next_clko_3[target_ptr] = cur_clko_3;
          before_clko_3[target_ptr] = sv_ptr;
          if (next_top_ptr == -1) top_clko_3 = target_ptr;
          else                    next_clko_3[next_top_ptr] = target_ptr;
        end
      end
//    clko_3_printf;
    end
  endtask
// # check & exec [dtout] #####
  always @(posedge clko) begin
    if (top_clko_3 != -1) begin
      if (total_cyc_clko == cyc_clko_3[top_clko_3]) begin
        dtout = value_clko_3[top_clko_3];
        target_ptr   = top_clko_3;
        dust_top_ptr = dust_clko_3;
        if (top_clko_3 == -1) next_top_ptr = -1;
        else                 next_top_ptr = next_clko_3[top_clko_3];
        target_ptr = top_clko_3;
        top_clko_3 = next_clko_3[top_clko_3];
        if (top_clko_3 != -1) before_clko_3[top_clko_3] = -1;
        dust_top_ptr = dust_clko_3;
        dust_clko_3 = target_ptr;
        before_clko_3[target_ptr] = -1;
        next_clko_3[target_ptr]   = dust_top_ptr;
        if (dust_top_ptr != -1) before_clko_3[dust_top_ptr] = target_ptr;
        if (cur_clko_3 == target_ptr) cur_clko_3 = top_clko_3;
      end
    end
  end
// # store [irq_clear] #####
  task clko_4_chg;
    input [4-1:0] p_val;
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
      if (dust_clko_4 == -1) begin $display("index over (line=irq_clear)\n"); ret_flg = 1; end
      if (ret_flg == 0) begin
        cyc = p_cyc + total_cyc_clko;
        if (cur_clko_4 == -1) cur_clko_4 = top_clko_4;
        addin = 0;
        srch_kbn = 2;
        rtn_cd = -1;
        loop_flg = 1;
      end
      while(loop_flg) begin
        if (top_clko_4 == -1) begin addin = 1; loop_flg = 0; end
        if (loop_flg == 1) begin
          rtn_cd = 1;
          if (cyc_clko_4[cur_clko_4] == cyc) rtn_cd = 0;
          if (cyc_clko_4[cur_clko_4] >  cyc) rtn_cd = -1;
          if (rtn_cd == 0) loop_flg = 0;
        end
        if (loop_flg == 1) begin
          if (srch_kbn == 2) srch_kbn = rtn_cd;
          if (srch_kbn != rtn_cd) begin 
            if (rtn_cd == 1) cur_clko_4 = next_clko_4[cur_clko_4];
            loop_flg = 0;
          end
        end
        if (loop_flg == 1) begin
          if (rtn_cd == 1) begin
            if (next_clko_4[cur_clko_4] == -1) begin addin = 1; loop_flg = 0; end
            else  cur_clko_4 = next_clko_4[cur_clko_4];
          end
          else begin
            if (before_clko_4[cur_clko_4] == -1) loop_flg = 0;
            else  cur_clko_4 = before_clko_4[cur_clko_4];
          end
        end
      end
      if (ret_flg == 0) begin
        if (rtn_cd == 0) begin value_clko_4[cur_clko_4] = p_val; ret_flg = 1; end
      end
      if (ret_flg == 0) begin
        target_ptr = dust_clko_4;
        dust_clko_4 = next_clko_4[dust_clko_4];
        if (dust_clko_4 != -1) before_clko_4[dust_clko_4] = -1;
        cyc_clko_4[target_ptr] = cyc;
        value_clko_4[target_ptr] = p_val;
      end
      if (ret_flg == 0) begin
        if (cur_clko_4 == -1) begin
          top_clko_4 = target_ptr;
          before_clko_4[target_ptr] = -1;
          next_clko_4[target_ptr] = -1;
          ret_flg = 1;
        end
      end
      if (ret_flg == 0) begin
        if (addin == 1) begin
          next_clko_4[cur_clko_4]   = target_ptr;
          before_clko_4[target_ptr] = cur_clko_4;
          next_clko_4[target_ptr] = -1;
        end
        else begin
          sv_ptr = before_clko_4[cur_clko_4];
          next_top_ptr = before_clko_4[cur_clko_4];
          before_clko_4[cur_clko_4]   = target_ptr;
          next_clko_4[target_ptr] = cur_clko_4;
          before_clko_4[target_ptr] = sv_ptr;
          if (next_top_ptr == -1) top_clko_4 = target_ptr;
          else                    next_clko_4[next_top_ptr] = target_ptr;
        end
      end
//    clko_4_printf;
    end
  endtask
// # check & exec [irq_clear] #####
  always @(posedge clko) begin
    if (top_clko_4 != -1) begin
      if (total_cyc_clko == cyc_clko_4[top_clko_4]) begin
        irq_clear = value_clko_4[top_clko_4];
        target_ptr   = top_clko_4;
        dust_top_ptr = dust_clko_4;
        if (top_clko_4 == -1) next_top_ptr = -1;
        else                 next_top_ptr = next_clko_4[top_clko_4];
        target_ptr = top_clko_4;
        top_clko_4 = next_clko_4[top_clko_4];
        if (top_clko_4 != -1) before_clko_4[top_clko_4] = -1;
        dust_top_ptr = dust_clko_4;
        dust_clko_4 = target_ptr;
        before_clko_4[target_ptr] = -1;
        next_clko_4[target_ptr]   = dust_top_ptr;
        if (dust_top_ptr != -1) before_clko_4[dust_top_ptr] = target_ptr;
        if (cur_clko_4 == target_ptr) cur_clko_4 = top_clko_4;
      end
    end
  end
// # store [we] #####
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
      if (dust_clko_1 == -1) begin $display("index over (line=we)\n"); ret_flg = 1; end
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
// # check & exec [we] #####
  always @(posedge clko) begin
    if (top_clko_1 != -1) begin
      if (total_cyc_clko == cyc_clko_1[top_clko_1]) begin
        we = value_clko_1[top_clko_1];
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

// # schedule task #####
  always @(posedge clko) total_cyc_clko <= total_cyc_clko + 1;

  initial begin
    total_cyc_clko = 0;
  end

// # schedule list printf #####
  task clko_2_printf; // adr
    integer i;
    begin
      $display("<adr>");
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
  task clko_3_printf; // dtout
    integer i;
    begin
      $display("<dtout>");
      $display("cur_clko_3  = %x",cur_clko_3 );
      $display("dust_clko_3 = %x",dust_clko_3);
      $display("top_clko_3  = %x",top_clko_3 );
      for(i=0;i<ARY_MAX;i=i+1) begin 
        $display("cyc_clko_3   [%d]=%d",i,cyc_clko_3[i]   );
        $display("value_clko_3 [%d]=%x",i,value_clko_3[i] );
        $display("before_clko_3[%d]=%x",i,before_clko_3[i]);
        $display("next_clko_3  [%d]=%x",i,next_clko_3[i]  );
      end
    end
  endtask
  task clko_4_printf; // irq_clear
    integer i;
    begin
      $display("<irq_clear>");
      $display("cur_clko_4  = %x",cur_clko_4 );
      $display("dust_clko_4 = %x",dust_clko_4);
      $display("top_clko_4  = %x",top_clko_4 );
      for(i=0;i<ARY_MAX;i=i+1) begin 
        $display("cyc_clko_4   [%d]=%d",i,cyc_clko_4[i]   );
        $display("value_clko_4 [%d]=%x",i,value_clko_4[i] );
        $display("before_clko_4[%d]=%x",i,before_clko_4[i]);
        $display("next_clko_4  [%d]=%x",i,next_clko_4[i]  );
      end
    end
  endtask
  task clko_1_printf; // we
    integer i;
    begin
      $display("<we>");
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
endmodule

