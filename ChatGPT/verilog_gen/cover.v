// ---------------------
// cover module
// ---------------------
module cover(
   clk
);
// # port define ########################
// # input  ########
  input   clk;

// # Coverage Variable ############################
  reg coverage_enable;
  reg cover_0;
  reg cover_1;
  reg cover_2;
  reg cover_3;
  reg cover_4;
  reg cover_5;
// # Top Initialize ###################### 
 initial begin 
  #10 
  #100000 
  #100000 
  coverage_start; 
  #100000 
  coverage_result(3); 
 end 

// # Coverage ############################
  initial begin
    coverage_enable = 0;
    cover_0 = 0;
    cover_1 = 0;
    cover_2 = 0;
    cover_3 = 0;
    cover_4 = 0;
    cover_5 = 0;
  end
  always @(posedge clk)
    begin
      if (coverage_enable) begin
        if (top.i_model.sample0_fp) begin
          cover_0 <= 1;
        end
      end
    end
  always @(posedge clk)
    begin
      if (coverage_enable) begin
        if (top.i_model.sample1_fp) begin
          cover_1 <= 1;
        end
      end
    end
  always @(posedge clk)
    begin
      if (coverage_enable) begin
        if (top.i_model.sample_acc) begin
          cover_2 <= 1;
        end
      end
    end
  always @(posedge clk)
    begin
      if (coverage_enable) begin
        if (top.i_model.sample_idle) begin
          cover_3 <= 1;
        end
      end
    end
  always @(posedge clk)
    begin
      if (coverage_enable) begin
        if (top.i_model.sample_wait) begin
          cover_4 <= 1;
        end
      end
    end
  always @(posedge clk)
    begin
      if (coverage_enable) begin
        if (top.i_model.sample_wait2) begin
          cover_5 <= 1;
        end
      end
    end
  task coverage_start;
    begin
      coverage_enable = 1;
    end
  endtask
  task coverage_result;
    input [1:0] mode;
    integer ng_count;
    begin
      ng_count = 0;
      if (cover_0 == 0)
        begin
          ng_count = ng_count + 1;
          if (mode > 0) 
            begin
              $display("#cover,0,x,top.i_model.sample0_fp");
            end
        end
      else
        begin
          if (mode > 1)
            begin
              $display("#cover,0,o,top.i_model.sample0_fp");
            end
        end
      if (cover_1 == 0)
        begin
          ng_count = ng_count + 1;
          if (mode > 0) 
            begin
              $display("#cover,1,x,top.i_model.sample1_fp");
            end
        end
      else
        begin
          if (mode > 1)
            begin
              $display("#cover,1,o,top.i_model.sample1_fp");
            end
        end
      if (cover_2 == 0)
        begin
          ng_count = ng_count + 1;
          if (mode > 0) 
            begin
              $display("#cover,2,x,top.i_model.sample_acc");
            end
        end
      else
        begin
          if (mode > 1)
            begin
              $display("#cover,2,o,top.i_model.sample_acc");
            end
        end
      if (cover_3 == 0)
        begin
          ng_count = ng_count + 1;
          if (mode > 0) 
            begin
              $display("#cover,3,x,top.i_model.sample_idle");
            end
        end
      else
        begin
          if (mode > 1)
            begin
              $display("#cover,3,o,top.i_model.sample_idle");
            end
        end
      if (cover_4 == 0)
        begin
          ng_count = ng_count + 1;
          if (mode > 0) 
            begin
              $display("#cover,4,x,top.i_model.sample_wait");
            end
        end
      else
        begin
          if (mode > 1)
            begin
              $display("#cover,4,o,top.i_model.sample_wait");
            end
        end
      if (cover_5 == 0)
        begin
          ng_count = ng_count + 1;
          if (mode > 0) 
            begin
              $display("#cover,5,x,top.i_model.sample_wait2");
            end
        end
      else
        begin
          if (mode > 1)
            begin
              $display("#cover,5,o,top.i_model.sample_wait2");
            end
        end
      $display("result coverage count = 6  non coverage count = %d",ng_count );
    end
  endtask
endmodule

