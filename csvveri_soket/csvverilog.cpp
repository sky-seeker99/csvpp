/*

 * Copyright (c) 2003 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
 *
 *    This source code is free software; you can redistribute it
 *    and/or modify it in source code form under the terms of the GNU
 *    General Public License as published by the Free Software
 *    Foundation; either version 2 of the License, or (at your option)
 *    any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */
//
//  CSV -> Verilog-HDL Soket
//  1.01:#act,#stop 追加
//      :#patern のリングキュー追加
//  1.02:コネクションリスト結合
//  1.03;ステートマシンのリセット優先
//  1.05;#andor 追加
//  1.09:#function_case , #function_direct
//  1.12:#inf_send/#inf_recv/#inf
//  1.14:#coverage
//  1.15:#inf_recvにFIFO機能を追加
//  1.17:#readmemh機能追加
//  1.17a:#readmemh機能修正


#include "csvverilog.h"

#include "../csvveri_core/csvmsg.cpp"
#include "../csvveri_core/csvvinf.cpp"
#include "../csvveri_core/csvclk.cpp"
#include "..\csvveri_core\csvcon.cpp"
#include "../csvveri_core/csvfunc.cpp"
#include "..\csvveri_core\csvgate.cpp"
#include "../csvveri_core/csvlang.cpp"
#include "../csvveri_core/csvparm.cpp"
#include "../csvveri_core/csvptn.cpp"
#include "../csvveri_core/csvstate.cpp"
#include "../csvveri_core/csvsub.cpp"
#include "../csvveri_core/csvtask.cpp"
#include "..\csvveri_core\csvrstate.cpp"
#include "../csvveri_core/csvcover.cpp"
#include "../csvveri_core/csvrmem.cpp"


// # Readmemh ##################################
void VOutReadmem_T::PreOutput(FILE *fp){
  Var_T *var;

  ARY_LOOP(g_rf,CsvRFile_T,ary_fp)
    g_rf->wid_bus = 0;
    ARY_LOOP(var,Var_T,g_rf->var_fp)
      g_rf->wid_bus += SujiConvEx(var->size->c_str()) * 8;
    LOOP_END
  LOOP_END

  bool first=true;
  int count=0;
  ARY_LOOP(g_rf,CsvRFile_T,ary_fp)
	if (first){
	  fprintf(fp,"// # $readmemh Variable ############################\n");
	  first = false;
	}
	fprintf(fp,"  reg [%d:0]FILE_ROM_%05d[0:%d];\n",g_rf->wid_bus-1,count,g_rf->ary_max-1);
	count++;
	fprintf(fp,"  reg [31:0] %s;\n",g_rf->ptr_name->c_str());
	ARY_LOOP(var,Var_T,g_rf->var_fp)
	  int a = SujiConvEx(var->size->c_str());
	  fprintf(fp,"  wire [%d:0] %s;\n",a*8-1,var->name->c_str());
	LOOP_END
  LOOP_END
}

// # Coverage ##################################
void VOutReadmem_T::Output(FILE *fp){
  Var_T *var;

  ARY_LOOP(g_rf,CsvRFile_T,ary_fp)
	g_rf->wid_bus = 0;
	ARY_LOOP(var,Var_T,g_rf->var_fp)
	  g_rf->wid_bus += SujiConvEx(var->size->c_str());
	LOOP_END
  LOOP_END

  bool first=true;
  int count=0;
  ARY_LOOP(g_rf,CsvRFile_T,ary_fp)
	if (first){
	  fprintf(fp,"// # $readmemh ############################\n");
	  first = false;
	  fprintf(fp,"  initial begin\n");
	}
	fprintf(fp,"    $readmemh(\"%s\", FILE_ROM_%05d);\n",g_rf->file_name->c_str(),count);
	fprintf(fp,"    %s=0;\n",g_rf->ptr_name->c_str());
  LOOP_END
  if (first==false) {
	fprintf(fp,"  end\n");
  }


  ARY_LOOP(g_rf,CsvRFile_T,ary_fp)
	fprintf(fp,"  assign {");
	bool flg=true;
	ARY_LOOP(var,Var_T,g_rf->var_fp)
	  if (flg){fprintf(fp," ");  flg=false;}
	  else    {fprintf(fp,",");}
	  fprintf(fp,"%s",var->name->c_str());
	LOOP_END
	fprintf(fp,"} = FILE_ROM_%05d[%s];\n",count,g_rf->ptr_name->c_str());
	count++;
  LOOP_END

}





// # Coverage ##################################
void VOutCover_T::PreOutput(FILE *fp)
  {
  CsvCoverCell_T *ccc;

  bool first=true;
  MEM_LOOP(ccc,CsvCoverCell_T,mem_fp)
	if (first){
	  fprintf(fp,"// # Coverage Variable ############################\n");
	  fprintf(fp,"  reg coverage_enable;\n");
	  first = false;
	}
	fprintf(fp,"  reg cover_%d;\n",ccc->no);
  LOOP_END
  }

void VOutCover_T::Output(FILE *fp)
  {
  CsvCoverCell_T *ccc;

  bool first=true;
  MEM_LOOP(ccc,CsvCoverCell_T,mem_fp)
    if (first){
      fprintf(fp,"// # Coverage ############################\n");
      fprintf(fp,"  initial begin\n");
      fprintf(fp,"    coverage_enable = 0;\n");
      first = false;
    }
    fprintf(fp,"    cover_%d = 0;\n",ccc->no);
  LOOP_END 
  if (first == false){
    fprintf(fp,"  end\n");
  }
  if (first){return;}
  
  MEM_LOOP(ccc,CsvCoverCell_T,mem_fp)
    fprintf(fp,"  always @(posedge %s)\n",ccc->clk->c_str());
    fprintf(fp,"    begin\n");
    fprintf(fp,"      if (coverage_enable) begin\n");
    fprintf(fp,"        if (%s) begin\n",ccc->siki->c_str());
    fprintf(fp,"          cover_%d <= 1;\n",ccc->no);
    fprintf(fp,"        end\n");
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
  LOOP_END

  fprintf(fp,"  task coverage_start;\n");
  fprintf(fp,"    begin\n");
  fprintf(fp,"      coverage_enable = 1;\n");
  fprintf(fp,"    end\n");
  fprintf(fp,"  endtask\n");

  fprintf(fp,"  task coverage_result;\n");
  fprintf(fp,"    input [1:0] mode;\n");
  fprintf(fp,"    integer ng_count;\n");
  fprintf(fp,"    begin\n");
  fprintf(fp,"      ng_count = 0;\n"); 
  MEM_LOOP(ccc,CsvCoverCell_T,mem_fp)
    fprintf(fp,"      if (cover_%d == 0)\n",ccc->no); 
    fprintf(fp,"        begin\n");
    fprintf(fp,"          ng_count = ng_count + 1;\n");
    fprintf(fp,"          if (mode > 0) \n");
    fprintf(fp,"            begin\n");
    fprintf(fp,"              $display(\"#cover,%d,x,%s\");\n",ccc->no,ccc->siki->c_str());
    fprintf(fp,"            end\n");
    fprintf(fp,"        end\n");
    fprintf(fp,"      else\n");
    fprintf(fp,"        begin\n");
    fprintf(fp,"          if (mode > 1)\n"); 
    fprintf(fp,"            begin\n");
    fprintf(fp,"              $display(\"#cover,%d,o,%s\");\n",ccc->no,ccc->siki->c_str());
    fprintf(fp,"            end\n");
    fprintf(fp,"        end\n"); 
  LOOP_END
  fprintf(fp,"      $display(\"result coverage count = %d  non coverage count = %%d\",ng_count );\n",no);
  fprintf(fp,"    end\n");
  fprintf(fp,"  endtask\n");
  }


// # Interface ##################################
bool VOutVInf_T::PortOutput(FILE *fp,int kbn,char *var_name)
  {
  CsvInfParm_T *cip;




  MEM_LOOP(inf,CsvInfSendRecv_T,mem_fp)
    if (inf->enable != NULL){
      if (strcmp(var_name,inf->enable->c_str()) == 0){
        if (inf->send){fprintf(fp,"  input  ");}
        else          {fprintf(fp,"  output ");}
        fprintf(fp," %s;\n",inf->enable->c_str());
        return(true);
      }
    }

    if (inf->send){
      if (kbn != 1){continue;}
    } else {
      if (kbn != 0){continue;}
    }

    if (strcmp(var_name,inf->name->c_str()) == 0){
      if (inf->send){fprintf(fp,"  output  ");}
      else          {fprintf(fp,"  input ");}
      fprintf(fp," %s;\n",inf->name->c_str());
      return(true);
    }


    MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
      if (strcmp(var_name,cip->name->c_str()) == 0){
        if (inf->send){fprintf(fp,"  output  ");}
        else          {fprintf(fp,"  input ");}
        ary_output(fp,cip->size->c_str());
        fprintf(fp," %s;\n",cip->name->c_str());
        return(true);
      }
    LOOP_END
  LOOP_END
  return(true);
  }


void VOutVInf_T::PreOutput(FILE *fp)
  {
  CsvInfParm_T *cip;

  char www[6];
  www[0]=0x00;
  bool first=true;
  MEM_LOOP(inf,CsvInfSendRecv_T,mem_fp)
    if (first){
      fprintf(fp,"// # Interface Variable ############################\n");
      first = false;
    }
    if ((inf->send == false) && (inf->ary != NULL)){
      fprintf(fp,"  integer");
      fprintf(fp," wptr_%s;\n",inf->name->c_str());
      fprintf(fp,"  integer");
      fprintf(fp," rptr_%s;\n",inf->name->c_str());
      MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
        fprintf(fp,"  reg ");
        ary_output(fp,cip->size->c_str());
        fprintf(fp," HOJI_%s[%s:0];\n",cip->name->c_str(),inf->ary->c_str());
      LOOP_END
    }
    else {
      if (inf->send == false){strcpy(www,"HOJI_");}
      else                   {www[0] = 0x00;}
      fprintf(fp,"  reg");
      fprintf(fp," %s%s;\n",www,inf->name->c_str());
      MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
        fprintf(fp,"  reg ");
        ary_output(fp,cip->size->c_str());
        fprintf(fp," %s%s;\n",www,cip->name->c_str());
      LOOP_END
    }

    if (inf->enable != NULL) {
      fprintf(fp,"  wire %s;\n",inf->enable->c_str());  
    }
  LOOP_END
  }


void VOutVInf_T::Output(FILE *fp)
  {
  CsvInfParm_T *cip;
  char www[6];
  www[0]=0x00;
  // reset
  MEM_LOOP(inf,CsvInfSendRecv_T,mem_fp)
    if (inf->send == false){strcpy(www,"HOJI_");}
    else                   {www[0] = 0x00;}
    fprintf(fp,"// # Interface (%s) ############################\n",inf->name->c_str());
    fprintf(fp,"// # Initialize #####\n");
    fprintf(fp,"  initial begin\n");
    if (inf->send == false){fprintf(fp,"    #2\n");}

    if ((inf->send == false) && (inf->ary != NULL)){
      fprintf(fp,"    wptr_%s = 0;\n",inf->name->c_str());
      fprintf(fp,"    rptr_%s = 0;\n",inf->name->c_str());
    }
    else {
      fprintf(fp,"    %s%s = 1'b0;\n",www,inf->name->c_str());
      MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
        fprintf(fp,"    %s%s = %s'b0;\n",www,cip->name->c_str(),cip->size->c_str());
      LOOP_END
    }
    fprintf(fp,"  end\n");

    // send
    if  (inf->send){
      if (inf->enable != NULL) {
        fprintf(fp,"// # Send enable #####\n");
        fprintf(fp,"  task %s_send_check;\n",inf->name->c_str());
        fprintf(fp,"    output retcd;\n");
        fprintf(fp,"    begin\n");
        fprintf(fp,"      #1\n");
        fprintf(fp,"      retcd = %s;\n",inf->enable->c_str());
        fprintf(fp,"    end\n");
        fprintf(fp,"  endtask\n");
      }
      fprintf(fp,"// # Send task #####\n");
      fprintf(fp,"  task %s_send;\n",inf->name->c_str());
      MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
        fprintf(fp,"    input ");
        ary_output(fp,cip->size->c_str());
        fprintf(fp,"p_%s;\n",cip->name->c_str());
      LOOP_END
      fprintf(fp,"    begin\n");
      fprintf(fp,"      #1\n");
      fprintf(fp,"      %s <= ~%s;\n",inf->name->c_str(),inf->name->c_str());
      MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
        fprintf(fp,"      %s <= p_%s;\n",cip->name->c_str(),cip->name->c_str());
      LOOP_END
      fprintf(fp,"    end\n");
      fprintf(fp,"  endtask\n");
    }

    // recieve
    if  (inf->send == false)
      {

      if (inf->enable != NULL) {
        fprintf(fp,"// # Recieve enable #####\n");
        if (inf->ary != NULL){
           fprintf(fp,"  assign %s = ~(((((wptr_%s+1)==(%s+1)) && (rptr_%s == 0)) ? 1'b1:1'b0) | (((wptr_%s+1) == rptr_%s) ? 1'b1:1'b0));\n"
                     ,inf->enable->c_str(),inf->name->c_str(),inf->ary->c_str(),inf->name->c_str(),inf->name->c_str(),inf->name->c_str());
        }
        else {
           fprintf(fp,"  assign %s = ~HOJI_%s;\n",inf->enable->c_str(),inf->name->c_str());
        }
      }
      fprintf(fp,"// # Recieve task #####\n");
      fprintf(fp,"  task %s_recv;\n",inf->name->c_str());
      fprintf(fp,"    output valid;\n");
      MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
        fprintf(fp,"    output ");
        ary_output(fp,cip->size->c_str());
        fprintf(fp,"p_%s;\n",cip->name->c_str());
      LOOP_END
      fprintf(fp,"    begin\n");

      if (inf->ary != NULL){
        fprintf(fp,"      if (wptr_%s != rptr_%s) begin\n",inf->name->c_str(),inf->name->c_str());
        fprintf(fp,"        valid = 1'b1;\n");
        MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
          fprintf(fp,"        p_%s = HOJI_%s[rptr_%s];\n",cip->name->c_str(),cip->name->c_str(),inf->name->c_str());
        LOOP_END
        fprintf(fp,"        rptr_%s = rptr_%s + 1;\n",inf->name->c_str(),inf->name->c_str());
        fprintf(fp,"        if (rptr_%s == (%s+1)) rptr_%s = 0;\n",inf->name->c_str(),inf->ary->c_str(),inf->name->c_str());
        fprintf(fp,"      end\n");
        fprintf(fp,"      else begin\n");
        fprintf(fp,"        valid = 1'b0;\n");
        MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
          fprintf(fp,"        p_%s = %s'b0;\n",cip->name->c_str(),cip->size->c_str());
        LOOP_END
        fprintf(fp,"      end\n");
      }
      else {
        fprintf(fp,"      if (HOJI_%s) begin\n",inf->name->c_str());
        fprintf(fp,"        valid = 1'b1;\n");
        fprintf(fp,"        HOJI_%s = 1'b0;\n",inf->name->c_str());
        MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
          fprintf(fp,"        p_%s = HOJI_%s;\n",cip->name->c_str(),cip->name->c_str());
        LOOP_END
        fprintf(fp,"      end\n");
        fprintf(fp,"      else begin\n");
        fprintf(fp,"        valid = 1'b0;\n");
        MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
          fprintf(fp,"        p_%s = %s'b0;\n",cip->name->c_str(),cip->size->c_str());
        LOOP_END
        fprintf(fp,"      end\n");
      }
      fprintf(fp,"    end\n");
      fprintf(fp,"  endtask\n");

      fprintf(fp,"// # Recieve latch #####\n");
      fprintf(fp,"  always @(%s)\n",inf->name->c_str());
      fprintf(fp,"    begin\n");
      if (inf->ary != NULL){
        MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
          fprintf(fp,"      HOJI_%s[wptr_%s] <= %s;\n",cip->name->c_str(),inf->name->c_str(),cip->name->c_str());
        LOOP_END
        fprintf(fp,"      wptr_%s = wptr_%s + 1;\n",inf->name->c_str(),inf->name->c_str());
        fprintf(fp,"      if (wptr_%s == (%s+1)) wptr_%s = 0;\n",inf->name->c_str(),inf->ary->c_str(),inf->name->c_str());
        fprintf(fp,"      if (wptr_%s == rptr_%s) begin $display(\"%s interface fifo over.\"); $finish; end\n",inf->name->c_str(),inf->name->c_str(),inf->name->c_str());
      }
      else {
        fprintf(fp,"      HOJI_%s <= 1'b1;\n",inf->name->c_str());
        MEM_LOOP(cip,CsvInfParm_T,inf->mem_fp)
          fprintf(fp,"      HOJI_%s <= %s;\n",cip->name->c_str(),cip->name->c_str());
        LOOP_END
      }
      fprintf(fp,"    end\n");

      }
  LOOP_END
  }




// -----------------
// Array Output
// -----------------
void VOutVInf_T::ary_output(FILE *fp,char *str)
  {
  int i;
  if (strcmp(str,"1")==0){return;}
  i = SujiConvEx(str);
  if (i > 0){fprintf(fp," [%d:0]",i-1);}
  else      {fprintf(fp," [%s-1:0]",str);}
  }





// # Cycle Task ######################################
// -----------------
// @L,@P Change
// -----------------
void VOutTask_T::rep(sChar *str)
  {
  sChar *local;
  sChar *parm;

  local = new sChar("l_"); local->cat(vct->name->c_str()); local->cat("_");
  parm  = new sChar("p_"); parm->cat(vct->name->c_str());  parm->cat("_");
  grep->set(str->c_str());
  grep->replace_all("@L",local->c_str());
  grep->replace_all("@P",parm->c_str());
  str->set(grep->c_str());
  }

// --------------
// pre output
// --------------
void VOutTask_T::PreOutput(FILE *fp)
  {
  CsvCycParm_T *p;

  if (ExistCheck() == false){return;}
  
  fprintf(fp,"\n// # Cycle Task Variable #################################### \n");
  fprintf(fp,"  integer taskdiff;\n");
  MEM_LOOP(vct,CsvCycTask_T,vct_fp)
    fprintf(fp,"  reg %s_lock;\n",vct->name->c_str());
    if (strcmp(vct->tcnt->c_str(),"")==0){continue;} fprintf(fp,"  integer %s_tcnt;\n",vct->name->c_str());
    if (strcmp(vct->wcnt->c_str(),"")==0){continue;} fprintf(fp,"  integer %s_wcnt;\n",vct->name->c_str());
    if (strcmp(vct->ccnt->c_str(),"")==0){continue;} fprintf(fp,"  integer %s_ccnt;\n",vct->name->c_str());
    MEM_LOOP(p,CsvCycParm_T,vct->parm_fp )
      if (strcmp(p->size->c_str(),"1")==0){fprintf(fp,"  reg p_%s_%s;\n",vct->name->c_str(),p->name->c_str());}
      else                                {fprintf(fp,"  reg[%s-1:0] p_%s_%s;\n",p->size->c_str(),vct->name->c_str(),p->name->c_str());}
    LOOP_END
    MEM_LOOP(p,CsvCycParm_T,vct->local_fp)
      if (strcmp(p->size->c_str(),"1")==0){fprintf(fp,"  reg l_%s_%s;\n",vct->name->c_str(),p->name->c_str());}
      else                                {fprintf(fp,"  reg[%s-1:0] l_%s_%s;\n",p->size->c_str(),vct->name->c_str(),p->name->c_str());}
    LOOP_END
  LOOP_END
  }

// --------------
// output
// --------------
void VOutTask_T::Output(FILE *fp)
  {
  sChar *cmd;
  int    clm;
  CsvCycChg_T *chg;
  int i;
  CsvCycParm_T *p;
  bool first;

  if (ExistCheck() == false){return;}
  fprintf(fp,"\n// # Cycle Task Initialize #################################### \n");
  // Initialize --------
  fprintf(fp,"initial begin\n");
  MEM_LOOP(vct,CsvCycTask_T,vct_fp)
    fprintf(fp,"  %s_lock = 1'b1;\n",vct->name->c_str());
  LOOP_END
  fprintf(fp,"end\n");

  // _stop  --------
  fprintf(fp,"\n// # Cycle Task Stop  #################################### \n");
  MEM_LOOP(vct,CsvCycTask_T,vct_fp)
    fprintf(fp,"task %s_stop;\n",vct->name->c_str());
    fprintf(fp,"  %s_lock = 1'b1;\n",vct->name->c_str());
    fprintf(fp,"endtask\n");
  LOOP_END

  // _start  --------
  fprintf(fp,"\n// # Cycle Task Start  #################################### \n");

  MEM_LOOP(vct,CsvCycTask_T,vct_fp)
    fprintf(fp,"task %s_start;\n",vct->name->c_str());
    MEM_LOOP(p,CsvCycParm_T,vct->parm_fp)
      fprintf(fp,"  input[%s-1:0] p%s;\n",p->size->c_str(),p->name->c_str());
    LOOP_END
    fprintf(fp,"  begin\n");
    MEM_LOOP(p,CsvCycParm_T,vct->parm_fp)
      fprintf(fp,"  p_%s_%s = p%s;\n",vct->name->c_str(),p->name->c_str(),p->name->c_str());
    LOOP_END
    MEM_LOOP(p,CsvCycParm_T,vct->local_fp)
      fprintf(fp,"  l_%s_%s = %s;\n",vct->name->c_str(),p->name->c_str(),p->init->c_str());
    LOOP_END
    fprintf(fp,"    %s_lock = 1'b0;\n",vct->name->c_str());
    if (strcmp(vct->tcnt->c_str(),"")!=0)
      {
      fprintf(fp,"    %s_tcnt = -1;\n",vct->name->c_str());
      if (strcmp(vct->wcnt->c_str(),"")!=0)
        {
        fprintf(fp,"    %s_wcnt = -1;\n",vct->name->c_str());
        if (strcmp(vct->ccnt->c_str(),"")!=0)
          {
          fprintf(fp,"    %s_ccnt = 0;\n",vct->name->c_str());
          }
        }
      }
    fprintf(fp,"  end\n");
    fprintf(fp,"endtask\n");
  LOOP_END

  fprintf(fp,"\n// # Cycle Task #################################### \n");
  // main  --------
  MEM_LOOP(vct,CsvCycTask_T,vct_fp)
    fprintf(fp,"// -----------------------------\n");
    fprintf(fp,"// cycle task (%s)\n",vct->name->c_str());
    fprintf(fp,"// -----------------------------\n");
    clm = 0;
    if (vct->kbn == 0){space(fp,clm); fprintf(fp,"always @(posedge %s) begin\n",vct->clk->c_str());}
    if (vct->kbn == 1){space(fp,clm); fprintf(fp,"always @(negedge %s) begin\n",vct->clk->c_str());}
    if (vct->kbn == 2){space(fp,clm); fprintf(fp,"always @(posedge %s or negedge %s) begin\n",vct->clk->c_str(),vct->clk->c_str());}
    ++clm;
    space(fp,clm); fprintf(fp,"if (%s_lock == 1'b0) begin\n",vct->name->c_str());
    ++clm;
    space(fp,clm); fprintf(fp,"taskdiff = 0;\n");

    if (strcmp(vct->wcnt->c_str(),"")!=0)
      {
      space(fp,clm); fprintf(fp,"%s_wcnt = %s_wcnt + 1;\n",vct->name->c_str(),vct->name->c_str());
      space(fp,clm); fprintf(fp,"if (%s_wcnt == %s) %s_wcnt = 0;\n",vct->name->c_str(),vct->wcnt->c_str(),vct->name->c_str());
      space(fp,clm); fprintf(fp,"if (%s_wcnt == 0)begin\n",vct->name->c_str());
      ++clm;
      }

    if (strcmp(vct->tcnt->c_str(),"")!=0)
      {
      space(fp,clm); fprintf(fp,"%s_tcnt = %s_tcnt + 1;\n",vct->name->c_str(),vct->name->c_str());
      space(fp,clm); fprintf(fp,"if (%s_tcnt == %s)begin\n",vct->name->c_str(),vct->tcnt->c_str());
      ++clm;

      if (strcmp(vct->ccnt->c_str(),"")!=0)
        {
        space(fp,clm); fprintf(fp,"%s_ccnt = %s_ccnt + 1;\n",vct->name->c_str(),vct->name->c_str());
        space(fp,clm); fprintf(fp,"%s_tcnt = 0;\n",vct->name->c_str());
        space(fp,clm); fprintf(fp,"if (%s_ccnt == %s)begin\n",vct->name->c_str(),vct->ccnt->c_str());
        ++clm;
        }

      space(fp,clm); fprintf(fp,"%s_lock = 1'b1;\n",vct->name->c_str());
      space(fp,clm); fprintf(fp,"%s_tcnt = %s -1;\n",vct->name->c_str(),vct->tcnt->c_str());
      if (strcmp(vct->wcnt->c_str(),"")!=0)
        {
        space(fp,clm); fprintf(fp,"%s_wcnt = %s -1;\n",vct->name->c_str(),vct->wcnt->c_str());
        }
      if (strcmp(vct->ccnt->c_str(),"")!=0)
        {
        space(fp,clm); fprintf(fp,"%s_ccnt = %s -1;\n",vct->name->c_str(),vct->ccnt->c_str());
        --clm;
        space(fp,clm); fprintf(fp,"end\n");
        }
      --clm;
      space(fp,clm); fprintf(fp,"end\n");
      space(fp,clm); fprintf(fp,"if (%s_lock == 1'b0)begin\n",vct->name->c_str());
      ++clm;
      }

    MEM_LOOP(cmd,sChar,vct->cmd_fp)
      rep(cmd); space(fp,clm); fprintf(fp,"%s\n",cmd->c_str());
    LOOP_END
    MEM_LOOP(chg,CsvCycChg_T,vct->chg_fp)
      rep(chg->name); rep(chg->val); rep(chg->cyc);
      if (strcmp(chg->name->c_str(),"#diff"    )==0){space(fp,clm); fprintf(fp,"taskdiff = %s;\n"           ,chg->val->c_str()); continue;}
      if (strcmp(chg->name->c_str(),"#diffplus")==0){space(fp,clm); fprintf(fp,"taskdiff = taskdiff + %s;\n",chg->val->c_str()); continue;}
      if (strcmp(chg->name->c_str(),"#cmd"     )==0){space(fp,clm); fprintf(fp,"if (%s_tcnt == %s+taskdiff)begin %s end\n",vct->name->c_str(),chg->cyc->c_str(),chg->val->c_str());}
      else                                          {space(fp,clm); fprintf(fp,"if (%s_tcnt == %s+taskdiff)%s = %s;\n"    ,vct->name->c_str(),chg->cyc->c_str(),chg->name->c_str(),chg->val->c_str());}
    LOOP_END
    if (strcmp(vct->tcnt->c_str(),"")!=0){--clm; space(fp,clm); fprintf(fp,"end\n");}
    if (strcmp(vct->wcnt->c_str(),"")!=0){--clm; space(fp,clm); fprintf(fp,"end\n");}
    --clm; space(fp,clm); fprintf(fp,"end\n");
    --clm; space(fp,clm); fprintf(fp,"end\n");
  LOOP_END
  }    


// # Sub/Func ########################################
// -----------------
// Recurcive Write
// -----------------
void VOutSub_T::StatusWrite(FILE *fp,If_T *p_if,int level)
  {
  sChar      *str;
  If_T       *w_if;
  LinkCell_T *lc;
  MM_PTR_T   *sv_ptr;
  int clm;

  clm = 2;
  if (p_if->up_ptr != NULL) 
    {
    space(fp,level+clm);
    if (strcmp(p_if->str->c_str(),"#else") == 0){fprintf(fp,"else begin  // _CELL:%s\n",p_if->clm_msg->c_str());}
    else                                        {fprintf(fp,"if (%s) begin  // _CELL:%s\n",p_if->str->c_str(),p_if->clm_msg->c_str());}
    }

  MEM_LOOP(lc,LinkCell_T,p_if->link_fp)
    if (lc->kbn == StCmdKbn)
      {
      space(fp,level+clm+1);
      str = (sChar *)lc->ptr;
      fprintf(fp,"%s  // _CELL:%s\n",str->c_str(),lc->clm_msg->c_str());
      }
    if (lc->kbn == StIfKbn ){StatusWrite(fp,(If_T *)lc->ptr,level+1);}
  LOOP_END

  if (p_if->up_ptr != NULL)
    {
    space(fp,level+clm); fprintf(fp,"end\n");
    }
  }


// -----------------
// Main Ouput
// -----------------
void VOutSub_T::Output(FILE *fp)
  {
  StParm_T *p;
  bool dmy_flg;

  if (ExistCheck() == false){return;}

  MEM_LOOP(g_sub,Sub_T,sub_fp)
    if (strcmp(g_sub->sub_name->c_str(),"") == 0) {fprintf(fp,"// # task : [%s] ##############\n",g_sub->name->c_str());}
    else                                          {fprintf(fp,"// # function : [%s] ##############\n",g_sub->name->c_str());}
    if (strcmp(g_sub->sub_name->c_str(),"") == 0) {fprintf(fp,"  task %s;  // _CELL:%s\n",g_sub->name->c_str(),g_sub->clm_msg->c_str());}
    else
      {
      fprintf(fp,"  function ");
      ary_output(fp,g_sub->sub_name->c_str());
      fprintf(fp," %s;  // _CELL:%s\n",g_sub->name->c_str(),g_sub->clm_msg->c_str());
      }
    dmy_flg = true;
    MEM_LOOP(p,StParm_T,g_sub->parm_fp )
      dmy_flg = false;
      fprintf(fp,"    input ");
      ary_output(fp,p->size->c_str());
      fprintf(fp," %s;  // _CELL:%s\n",p->name->c_str(),p->clm_msg->c_str());
    LOOP_END
    if ((dmy_flg == true) && (strcmp(g_sub->sub_name->c_str(),"") != 0)){fprintf(fp,"input dmy;\n");}
    MEM_LOOP(p,StParm_T,g_sub->local_fp)
      fprintf(fp,"    reg ");
      ary_output(fp,p->size->c_str());
      fprintf(fp," %s;  // _CELL:%s\n",p->name->c_str(),p->clm_msg->c_str());
    LOOP_END
    fprintf(fp,"    begin\n");
    MEM_LOOP(p,StParm_T,g_sub->local_fp) fprintf(fp,"      %s = %s;\n",p->name->c_str(),p->init->c_str()       ); LOOP_END
    StatusWrite(fp,g_sub->dmy_if,0);
    fprintf(fp,"    end\n");
    if (strcmp(g_sub->sub_name->c_str(),"") == 0) {fprintf(fp,"  endtask\n\n");}
    else                                          {fprintf(fp,"  endfunction\n\n");}
  LOOP_END
  }

// -----------------
// Array Output
// -----------------
void VOutSub_T::ary_output(FILE *fp,char *str)
  {
  int i;
  if (strcmp(str,"1")==0){return;}
  i = SujiConvEx(str);
  if (i > 0){fprintf(fp," [%d:0]",i-1);}
  else      {fprintf(fp," [%s-1:0]",str);}
  }

// # State Machine Ver 1.01 ###################################
// -----------------
// #chg size check
//  (Ver 1.08)
// -----------------
void VOutState_T::ChgCheck(MEM_FP *reg_fp)
  {
  ChgLineList_T *cll;
  Reg_T *r;
  int size;
  MEM_LOOP(cll,ChgLineList_T,chgline_fp)
    it->srch_key = cll->line->c_str();
    size = -1;
    if (reg_fp->mem_srch() == 0)
      {
      r = (Reg_T *)reg_fp->mem_link_ptr_rd();
      size = SujiConvEx(r->size->c_str());
      }
    if (size > 0)
      {
      cll->size = size;
      }

  LOOP_END
  }

// -----------------
// moving status
// -----------------
void VOutState_T::StatusWrite(FILE *fp,StIf_T *p_stif,int level)
  {
  sChar      *str;
  Chg_T      *chg;
  ValChg_T   *vc;
  StIf_T     *w_stif;
  LinkCell_T *lc;
  MM_PTR_T   *sv_ptr;
  int clm;
  char       *w_ch;
  sChar      *key;
  ChgLineList_T *cll;
  ChgCmdList_T  *ccl;
  ChgCmdCell_T  *ccc;

  clm = 1;
  if (p_stif->no == -1){
	rep(p_stif->str);
	space(fp,level+clm);
/*
	if (strcmp(p_stif->str->c_str(),"#else") == 0){fprintf(fp,"else begin  // _CELL:%s\n",p_stif->clm_msg->c_str());}
	else                                          {fprintf(fp,"if (%s) begin  // _CELL:%s\n",p_stif->str->c_str(),p_stif->clm_msg->c_str());}
*/
	if (p_stif->if_kbn == 2){fprintf(fp,"else begin  // _CELL:%s\n",p_stif->clm_msg->c_str());}
	else if (p_stif->if_kbn == 1) {fprintf(fp,"else if (%s) begin  // _CELL:%s\n",p_stif->str->c_str(),p_stif->clm_msg->c_str());}
	else if (p_stif->if_kbn == 0) {fprintf(fp,"if (%s) begin  // _CELL:%s\n",p_stif->str->c_str(),p_stif->clm_msg->c_str());}

  }

  key = new sChar("");
  MEM_LOOP(lc,LinkCell_T,p_stif->link_fp)
    if (lc->kbn == StCmdKbn)
      {
      space(fp,level+clm+1);
      str = (sChar *)lc->ptr;
      rep(str);
      fprintf(fp,"%s  // _CELL:%s\n",str->c_str(),lc->clm_msg->c_str());
      }
    if (lc->kbn == StChgKbn)
      {
      chg = (Chg_T *)lc->ptr;
      MEM_LOOP(vc,ValChg_T,chg->val_fp)
        rep(vc->cyc);
        rep(vc->val);
        if (strcmp(vc->name->c_str(),"#cmd")==0)
          {
          it->srch_key = chg->clk->c_str();
          chgcmd_fp->mem_srch();
          ccl = (ChgCmdList_T *)chgcmd_fp->mem_link_ptr_rd();
          it->srch_key = vc->val->c_str();
          ccl->cmd_fp->mem_srch();
          ccc = (ChgCmdCell_T *)ccl->cmd_fp->mem_link_ptr_rd();
          space(fp,level+clm+1);
          fprintf(fp,"p_cyc = %s; %s_command_chg(%d);  // _CELL:%s\n",vc->cyc->c_str(),chg->clk->c_str(),ccc->no,lc->clm_msg->c_str());
          }
        else
          {
          key->set(chg->clk->c_str());
          key->cat("_");
          key->cat(vc->name->c_str());
          it->srch_key = key->c_str();
          chgline_fp->mem_srch();
          cll = (ChgLineList_T *)chgline_fp->mem_link_ptr_rd();
          space(fp,level+clm+1);
          fprintf(fp,"p_cyc = %s; %s_%d_chg(%s);  // _CELL:%s\n",vc->cyc->c_str(),chg->clk->c_str(),cll->line_no,vc->val->c_str(),lc->clm_msg->c_str());
          }
      LOOP_END
      }
    if (lc->kbn == StIfKbn )
      {
      StatusWrite(fp,(StIf_T *)lc->ptr,level+1);
      }
    if (lc->kbn == StActKbn ) // #act Ver 1.01
      {
      str = (sChar *)lc->ptr;
      space(fp,level+clm+1);
      fprintf(fp,"set_%s_%s = 1'b1;  // _CELL:%s\n",g_status->name->c_str(),str->c_str(),lc->clm_msg->c_str());
      }
    if (lc->kbn == StExecKbn ) // #exec Ver 1.01
      {
      str = (sChar *)lc->ptr;
      space(fp,level+clm+1);
      fprintf(fp,"%s_%s;  // _CELL:%s\n",g_status->name->c_str(),str->c_str(),lc->clm_msg->c_str());
      }
    if (lc->kbn == StStopKbn ) // #stop Ver 1.01
      {
      str = (sChar *)lc->ptr;
      space(fp,level+clm+1);
      fprintf(fp,"rst_%s_%s = 1'b1;  // _CELL:%s\n",g_status->name->c_str(),str->c_str(),lc->clm_msg->c_str());
      }

  LOOP_END
  delete key;

  if (p_stif->no == -1){space(fp,level+clm); fprintf(fp,"end\n");}
  }


// ----------------------
// Variable define Ouput
// ----------------------
void VOutState_T::PreOutput(FILE *fp)
  {
  int i;
  StParm_T *p;
  ChgLineList_T *cll;
  ChgCmdList_T  *ccl;
  ChgClkList_T  *clk;
  bool first;

  if (ExistCheck() == false){return;}
  first = true;
  MEM_LOOP(cll,ChgLineList_T,chgline_fp)
    if (first == true)
      {
      first = false;
      fprintf(fp,"// # Schedule Variable ############################ \n");
      fprintf(fp,"  parameter ARY_MAX=%s;\n",ary_max->c_str());
      fprintf(fp,"  integer target_ptr;\n");
      fprintf(fp,"  integer next_top_ptr;\n");
      fprintf(fp,"  integer dust_top_ptr;\n");
      fprintf(fp,"  integer p_cyc;\n");
      MEM_LOOP(clk,ChgClkList_T,chgclk_fp)
        fprintf(fp,"  integer total_cyc_%s;\n",clk->clk->c_str());
      LOOP_END
      }
    fprintf(fp,"  integer cyc_%s_%d   [ARY_MAX:0]; // %s\n",cll->clk->c_str(),cll->line_no,cll->line->c_str());
    fprintf(fp,"  integer next_%s_%d  [ARY_MAX:0];\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"  integer before_%s_%d[ARY_MAX:0];\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"  reg [%d-1:0] value_%s_%d [ARY_MAX:0];\n",cll->size,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"  integer cur_%s_%d;\n" ,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"  integer dust_%s_%d;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"  integer top_%s_%d;\n" ,cll->clk->c_str(),cll->line_no);
  LOOP_END
  MEM_LOOP(ccl,ChgCmdList_T,chgcmd_fp)
    fprintf(fp,"  integer cyc_%s_command   [ARY_MAX:0];\n",ccl->clk->c_str());
    fprintf(fp,"  integer next_%s_command  [ARY_MAX:0];\n",ccl->clk->c_str());
    fprintf(fp,"  integer before_%s_command[ARY_MAX:0];\n",ccl->clk->c_str());
    fprintf(fp,"  reg [%d-1:0] value_%s_command [ARY_MAX:0];\n",ccl->cmd_no,ccl->clk->c_str());
    fprintf(fp,"  reg [%d-1:0] work_%s_command;\n",ccl->cmd_no,ccl->clk->c_str());
    fprintf(fp,"  integer cur_%s_command;\n" ,ccl->clk->c_str());
    fprintf(fp,"  integer dust_%s_command;\n",ccl->clk->c_str());
    fprintf(fp,"  integer top_%s_command;\n" ,ccl->clk->c_str());
  LOOP_END

  // Ver 1.01
  fprintf(fp,"// # State Machine Variable ############################ \n");
  MEM_LOOP(g_status,Status_T,status_fp)
    fprintf(fp,"  reg reset_%s,stop_%s;  // _CELL:%s\n",g_status->name->c_str(),g_status->name->c_str(),g_status->clm_msg->c_str());
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
      fprintf(fp,"  reg ");
      fprintf(fp,"st_%s_%s,",g_status->name->c_str(),g_stif->str->c_str());
      fprintf(fp,"rst_%s_%s,",g_status->name->c_str(),g_stif->str->c_str());
      fprintf(fp,"set_%s_%s;",g_status->name->c_str(),g_stif->str->c_str());
      fprintf(fp,"  // _CELL:%s\n",g_stif->clm_msg->c_str());
    LOOP_END
  LOOP_END


  first = true;
  MEM_LOOP(g_status,Status_T,status_fp)
    // local variable
    MEM_LOOP(p,StParm_T,g_status->local_fp)
      if (first == true){first = false; fprintf(fp,"// # State Machine Variable(Local/Parm) ################ \n");}
      fprintf(fp,"  reg[%s-1:0] l_%s_%s;  // _CELL:%s\n",p->size->c_str(),g_status->name->c_str(),p->name->c_str(),p->clm_msg->c_str());
    LOOP_END
    // parameter variable
    MEM_LOOP(p,StParm_T,g_status->parm_fp)
      if (first == true){first = false; fprintf(fp,"// # State Machine Variable(Local/Parm) ################ \n");}
      fprintf(fp,"  reg[%s-1:0] p_%s_%s;  // _CELL:%s\n",p->size->c_str(),g_status->name->c_str(),p->name->c_str(),p->clm_msg->c_str());
    LOOP_END
  LOOP_END
  }

// -----------------
// Main Ouput
// -----------------
void VOutState_T::Output(FILE *fp)
  {
  Chg_T *chg;
  ValChg_T *vc;
  StIf_T   *w_stif;
  int max;
  StParm_T *p;
  bool first;
  bool top_first;
  bool err_flg;
  ChgLineList_T *cll;
  ChgCmdList_T  *ccl;
  ChgCmdCell_T  *ccc;
  ChgClkList_T  *clk;
  char wno[10];
  bool f_flg;

  if (ExistCheck() == false){return;}


  // Schedule Initialize ------------------------------
  first = true;
  MEM_LOOP(cll,ChgLineList_T,chgline_fp)
    if (first == true)
      {
      first = false;
      fprintf(fp,"\n// # schedule variable initialize ################\n");
      fprintf(fp,"  initial begin\n");
      }
    fprintf(fp,"    for(cur_%s_%d=0;cur_%s_%d<ARY_MAX;cur_%s_%d=cur_%s_%d+1) begin\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      next_%s_%d[cur_%s_%d] = cur_%s_%d + 1;\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      before_%s_%d[cur_%s_%d] = cur_%s_%d - 1;\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"    end\n");
  LOOP_END
  MEM_LOOP(ccl,ChgCmdList_T,chgcmd_fp)
    fprintf(fp,"    for(cur_%s_command=0;cur_%s_command<ARY_MAX;cur_%s_command=cur_%s_command+1) begin\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      next_%s_command[cur_%s_command] = cur_%s_command + 1;\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      before_%s_command[cur_%s_command] = cur_%s_command - 1;\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"    end\n");
  LOOP_END
  MEM_LOOP(cll,ChgLineList_T,chgline_fp)
    fprintf(fp,"    next_%s_%d[ARY_MAX-1] = -1;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"    cur_%s_%d  = -1;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"    top_%s_%d  = -1;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"    dust_%s_%d =  0;\n",cll->clk->c_str(),cll->line_no);
  LOOP_END
  MEM_LOOP(ccl,ChgCmdList_T,chgcmd_fp)
    fprintf(fp,"    next_%s_command[ARY_MAX-1] = -1;\n",ccl->clk->c_str());
    fprintf(fp,"    cur_%s_command  = -1;\n",ccl->clk->c_str());
    fprintf(fp,"    top_%s_command  = -1;\n",ccl->clk->c_str());
    fprintf(fp,"    dust_%s_command =  0;\n",ccl->clk->c_str());
  LOOP_END

  if (first == false){fprintf(fp,"  end\n");}

  // Ver 1.01 
  first = true;
  MEM_LOOP(g_status,Status_T,status_fp)
    if (first == true)
      {
      first = false;
      fprintf(fp,"\n// # state machine variable initialize ################\n");
      fprintf(fp,"  initial begin\n");
      }
    fprintf(fp,"    stop_%s  = 1;\n",g_status->name->c_str());
    fprintf(fp,"    reset_%s = 0;\n",g_status->name->c_str());
  LOOP_END
  if (first == false){fprintf(fp,"  end\n");}

  // Main write ------------------------------
  MEM_LOOP(g_status,Status_T,status_fp)
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
      fprintf(fp,"\n// # state machine (%s/%s) #####\n",g_status->name->c_str(),g_stif->str->c_str());
      fprintf(fp,"  task %s_%s;  // _CELL:%s\n",g_status->name->c_str(),g_stif->str->c_str(),g_stif->clm_msg->c_str());
      fprintf(fp,"    begin\n");
      StatusWrite(fp,g_stif,1);
      fprintf(fp,"    end\n");
      fprintf(fp,"  endtask\n");
    LOOP_END
  LOOP_END


  // Ver 1.01
  // Main write ------------------------------
  first = true;
  MEM_LOOP(g_status,Status_T,status_fp)
    if (first == true){first = false; fprintf(fp,"\n// # state machine main loop #####\n");}
    fprintf(fp,"  always @(posedge %s)  // _CELL:%s\n",g_status->clk->c_str(),g_status->clm_msg->c_str());
    fprintf(fp,"    begin\n");
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
    fprintf(fp,"      set_%s_%s = 1'b0;\n",g_status->name->c_str(),g_stif->str->c_str());
    LOOP_END
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
    fprintf(fp,"      rst_%s_%s = 1'b0;\n",g_status->name->c_str(),g_stif->str->c_str());
    LOOP_END
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
    fprintf(fp,"      if (st_%s_%s)%s_%s;\n",g_status->name->c_str(),g_stif->str->c_str(),g_status->name->c_str(),g_stif->str->c_str());
    LOOP_END
    fprintf(fp,"      if (reset_%s) begin\n",g_status->name->c_str());
    fprintf(fp,"        reset_%s = 1'b0;\n",g_status->name->c_str());
    fprintf(fp,"        stop_%s = 1'b0;\n",g_status->name->c_str());
    f_flg = true;
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
      if (f_flg == true)
        {
        f_flg = false;
    fprintf(fp,"        st_%s_%s = 1'b1;\n",g_status->name->c_str(),g_stif->str->c_str());
        }
      else
        {
    fprintf(fp,"        st_%s_%s = 1'b0;\n",g_status->name->c_str(),g_stif->str->c_str());
        }
    LOOP_END
    fprintf(fp,"      end\n");
    fprintf(fp,"      else if (stop_%s) begin\n",g_status->name->c_str());
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
    fprintf(fp,"        st_%s_%s = 1'b0;\n",g_status->name->c_str(),g_stif->str->c_str());
    LOOP_END
    fprintf(fp,"      end\n");
    fprintf(fp,"      else begin\n");
    MEM_LOOP(g_stif,StIf_T,g_status->st_sub_fp)
    fprintf(fp,"        if      (set_%s_%s)st_%s_%s = 1'b1;\n",g_status->name->c_str(),g_stif->str->c_str(),g_status->name->c_str(),g_stif->str->c_str());
    fprintf(fp,"        else if (rst_%s_%s)st_%s_%s = 1'b0;\n",g_status->name->c_str(),g_stif->str->c_str(),g_status->name->c_str(),g_stif->str->c_str());
    LOOP_END
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
  LOOP_END

  MEM_LOOP(g_status,Status_T,status_fp)
    fprintf(fp,"\n// # reset/stop #####  // _CELL:%s\n",g_status->clm_msg->c_str());
    fprintf(fp,"  task %s_rst;\n",g_status->name->c_str());
    MEM_LOOP(p,StParm_T,g_status->parm_fp)
    fprintf(fp,"    input[%s-1:0] %s;\n",p->size->c_str(),p->name->c_str());
    LOOP_END
    fprintf(fp,"    begin\n");
    fprintf(fp,"      reset_%s = 1'b1;\n",g_status->name->c_str());
    MEM_LOOP(p,StParm_T,g_status->parm_fp)
    fprintf(fp,"      p_%s_%s <= %s;  // _CELL:%s\n",g_status->name->c_str(),p->name->c_str(),p->name->c_str(),p->clm_msg->c_str());
    LOOP_END
    MEM_LOOP(p,StParm_T,g_status->local_fp)
    fprintf(fp,"      l_%s_%s <= %s;  // _CELL:%s\n",g_status->name->c_str(),p->name->c_str(),p->init->c_str(),p->clm_msg->c_str());
    LOOP_END
    fprintf(fp,"    end\n");

    fprintf(fp,"  endtask\n");
    fprintf(fp,"  task %s_stop;\n",g_status->name->c_str());
    fprintf(fp,"    begin\n");
    fprintf(fp,"      stop_%s = 1'b1;\n",g_status->name->c_str());
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");
  LOOP_END

  // schedule ------------------------------
  top_first = true;
  MEM_LOOP(cll,ChgLineList_T,chgline_fp)
    if (top_first == true){fprintf(fp,"\n// # schedule task ############################\n"); top_first = false;}
    sprintf(wno,"%d",cll->line_no);

    OutputSub(fp,cll->clk->c_str(),wno,cll->size,cll->line->c_str(),true);

    fprintf(fp,"// # check & exec [%s] #####\n",cll->line->c_str());
    fprintf(fp,"  always @(posedge %s) begin\n",cll->clk->c_str());
    fprintf(fp,"    if (top_%s_%d != -1) begin\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      if (total_cyc_%s == cyc_%s_%d[top_%s_%d]) begin\n",cll->clk->c_str(),cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        %s = value_%s_%d[top_%s_%d];\n",cll->line->c_str(),cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        target_ptr   = top_%s_%d;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        dust_top_ptr = dust_%s_%d;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        if (top_%s_%d == -1) next_top_ptr = -1;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        else                 next_top_ptr = next_%s_%d[top_%s_%d];\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no );
    fprintf(fp,"        target_ptr = top_%s_%d;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        top_%s_%d = next_%s_%d[top_%s_%d];\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        if (top_%s_%d != -1) before_%s_%d[top_%s_%d] = -1;\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        dust_top_ptr = dust_%s_%d;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        dust_%s_%d = target_ptr;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        before_%s_%d[target_ptr] = -1;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        next_%s_%d[target_ptr]   = dust_top_ptr;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        if (dust_top_ptr != -1) before_%s_%d[dust_top_ptr] = target_ptr;\n",cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        if (cur_%s_%d == target_ptr) cur_%s_%d = top_%s_%d;\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  end\n");
  LOOP_END

  MEM_LOOP(ccl,ChgCmdList_T,chgcmd_fp)
    if (top_first == true){fprintf(fp,"\n// # schedule task ##########\n"); top_first = false;}
    OutputSub(fp,ccl->clk->c_str(),"command",ccl->cmd_no,"command",false);
    fprintf(fp,"// # check & exec #####\n");
    fprintf(fp,"  always @(posedge %s) begin\n",ccl->clk->c_str());
    fprintf(fp,"    if (top_%s_command != -1) begin\n",ccl->clk->c_str());
    fprintf(fp,"      if (total_cyc_%s == cyc_%s_command[top_%s_command]) begin\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"        work_%s_command = value_%s_command[top_%s_command];\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    MEM_LOOP(ccc,ChgCmdCell_T,ccl->cmd_fp)
      fprintf(fp,"        if (work_%s_command[%d] == 1'b1) begin %s end\n",ccl->clk->c_str(),ccc->no,ccc->cmd->c_str());
    LOOP_END
    fprintf(fp,"        target_ptr = top_%s_command;\n",ccl->clk->c_str());
    fprintf(fp,"        top_%s_command = next_%s_command[top_%s_command];\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"        if (top_%s_command != -1) before_%s_command[top_%s_command] = -1;\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"        dust_top_ptr = dust_%s_command;\n",ccl->clk->c_str());
    fprintf(fp,"        dust_%s_command = target_ptr;\n",ccl->clk->c_str());
    fprintf(fp,"        before_%s_command[target_ptr] = -1;\n",ccl->clk->c_str());
    fprintf(fp,"        next_%s_command[target_ptr]   = dust_top_ptr;\n",ccl->clk->c_str());
    fprintf(fp,"        if (dust_top_ptr != -1) before_%s_command[dust_top_ptr] = target_ptr;\n",ccl->clk->c_str());
    fprintf(fp,"        if (cur_%s_command == target_ptr) cur_%s_command = top_%s_command;\n",ccl->clk->c_str(),ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  end\n");
  LOOP_END

  top_first = true;
  MEM_LOOP(clk,ChgClkList_T,chgclk_fp)
    if (top_first == true){fprintf(fp,"\n// # schedule task #####\n"); top_first = false;}
    fprintf(fp,"  always @(posedge %s) total_cyc_%s <= total_cyc_%s + 1;\n",clk->clk->c_str(),clk->clk->c_str(),clk->clk->c_str());
  LOOP_END

  top_first = true;
  MEM_LOOP(clk,ChgClkList_T,chgclk_fp)
    if (top_first == true)
      {
      top_first = false;
      fprintf(fp,"\n  initial begin\n");
      }
    fprintf(fp,"    total_cyc_%s = 0;\n",clk->clk->c_str());
  LOOP_END
  if (top_first == false){fprintf(fp,"  end\n");}

  top_first = true;
  MEM_LOOP(cll,ChgLineList_T,chgline_fp)
    if (top_first == true){fprintf(fp,"\n// # schedule list printf #####\n"); top_first = false;}
    fprintf(fp,"  task %s_%d_printf; // %s\n",cll->clk->c_str(),cll->line_no,cll->line->c_str());
    fprintf(fp,"    integer i;\n");
    fprintf(fp,"    begin\n");
    fprintf(fp,"      $display(\"<%s>\");\n",cll->line->c_str());
    fprintf(fp,"      $display(\"cur_%s_%d  = %%x\",cur_%s_%d );\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      $display(\"dust_%s_%d = %%x\",dust_%s_%d);\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      $display(\"top_%s_%d  = %%x\",top_%s_%d );\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      for(i=0;i<ARY_MAX;i=i+1) begin \n");
    fprintf(fp,"        $display(\"cyc_%s_%d   [%%d]=%%d\",i,cyc_%s_%d[i]   );\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        $display(\"value_%s_%d [%%d]=%%x\",i,value_%s_%d[i] );\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        $display(\"before_%s_%d[%%d]=%%x\",i,before_%s_%d[i]);\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"        $display(\"next_%s_%d  [%%d]=%%x\",i,next_%s_%d[i]  );\n",cll->clk->c_str(),cll->line_no,cll->clk->c_str(),cll->line_no);
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");
  LOOP_END

  MEM_LOOP(ccl,ChgCmdList_T,chgcmd_fp)
    if (top_first == true){fprintf(fp,"\n// # schedule list printf #####\n"); top_first = false;}
    fprintf(fp,"  task %s_command_printf; // %s_command\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"    integer i;\n");
    fprintf(fp,"    begin\n");
    fprintf(fp,"      $display(\"<%s_command>\");\n",ccl->clk->c_str());
    fprintf(fp,"      $display(\"cur_%s_command  = %%x\",cur_%s_command );\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      $display(\"dust_%s_command = %%x\",dust_%s_command);\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      $display(\"top_%s_command  = %%x\",top_%s_command );\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      for(i=0;i<ARY_MAX;i=i+1) begin \n");
    fprintf(fp,"        $display(\"cyc_%s_command   [%%d]=%%d\",i,cyc_%s_command[i]   );\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"        $display(\"value_%s_command [%%d]=%%x\",i,value_%s_command[i] );\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"        $display(\"before_%s_command[%%d]=%%x\",i,before_%s_command[i]);\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"        $display(\"next_%s_command  [%%d]=%%x\",i,next_%s_command[i]  );\n",ccl->clk->c_str(),ccl->clk->c_str());
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");
  LOOP_END
  }

// -----------------
// Main Ouput Sub
// -----------------
void VOutState_T::OutputSub(FILE *fp,char *clk,char *no,int size,char *line,bool kbn)
  {
  sChar *ss;
  char *w;
  ss = new sChar(clk);
  ss->cat("_");
  ss->cat(no);
  w = ss->c_str();

  fprintf(fp,"// # store [%s] #####\n",line);
  fprintf(fp,"  task %s_chg;\n",w);
  if (kbn == true){fprintf(fp,"    input [%d-1:0] p_val;\n",size);}
  else            {fprintf(fp,"    input [31:0] p_val;\n");}
  fprintf(fp,"    integer srch_kbn;\n");
  fprintf(fp,"    integer rtn_cd;\n");
  fprintf(fp,"    integer cyc;\n");
  fprintf(fp,"    integer addin;\n");
  fprintf(fp,"    integer loop_flg;\n");
  fprintf(fp,"    integer ret_flg;\n");
  fprintf(fp,"    integer sv_ptr;\n");
  if (kbn == false){fprintf(fp,"    reg[%d-1:0] w;\n",size);}
  fprintf(fp,"    begin\n");
  fprintf(fp,"      ret_flg = 0;\n");
  fprintf(fp,"      loop_flg = 0;\n");
  if (strcmp(chg_trap->c_str(),"") != 0)
    {
    fprintf(fp,"      if (p_cyc >= %s) ret_flg = 1;\n",chg_trap->c_str());
    }
  fprintf(fp,"      if (dust_%s == -1) begin $display(\"index over (line=%s)\\n\"); ret_flg = 1; end\n",w,line);
  fprintf(fp,"      if (ret_flg == 0) begin\n");
  fprintf(fp,"        cyc = p_cyc + total_cyc_%s;\n",clk);
  fprintf(fp,"        if (cur_%s == -1) cur_%s = top_%s;\n",w,w,w);
  fprintf(fp,"        addin = 0;\n");
  fprintf(fp,"        srch_kbn = 2;\n");
  fprintf(fp,"        rtn_cd = -1;\n");
  fprintf(fp,"        loop_flg = 1;\n");
  fprintf(fp,"      end\n");
  fprintf(fp,"      while(loop_flg) begin\n");
  fprintf(fp,"        if (top_%s == -1) begin addin = 1; loop_flg = 0; end\n",w);
  fprintf(fp,"        if (loop_flg == 1) begin\n");
  fprintf(fp,"          rtn_cd = 1;\n");
  fprintf(fp,"          if (cyc_%s[cur_%s] == cyc) rtn_cd = 0;\n",w,w);
  fprintf(fp,"          if (cyc_%s[cur_%s] >  cyc) rtn_cd = -1;\n",w,w);
  fprintf(fp,"          if (rtn_cd == 0) loop_flg = 0;\n");
  fprintf(fp,"        end\n");
  fprintf(fp,"        if (loop_flg == 1) begin\n");
  fprintf(fp,"          if (srch_kbn == 2) srch_kbn = rtn_cd;\n");
  fprintf(fp,"          if (srch_kbn != rtn_cd) begin \n");
  fprintf(fp,"            if (rtn_cd == 1) cur_%s = next_%s[cur_%s];\n",w,w,w);
  fprintf(fp,"            loop_flg = 0;\n");
  fprintf(fp,"          end\n");
  fprintf(fp,"        end\n");
  fprintf(fp,"        if (loop_flg == 1) begin\n");
  fprintf(fp,"          if (rtn_cd == 1) begin\n");
  fprintf(fp,"            if (next_%s[cur_%s] == -1) begin addin = 1; loop_flg = 0; end\n",w,w);
  fprintf(fp,"            else  cur_%s = next_%s[cur_%s];\n",w,w,w);
  fprintf(fp,"          end\n");
  fprintf(fp,"          else begin\n");
  fprintf(fp,"            if (before_%s[cur_%s] == -1) loop_flg = 0;\n",w,w);
  fprintf(fp,"            else  cur_%s = before_%s[cur_%s];\n",w,w,w);
  fprintf(fp,"          end\n");
  fprintf(fp,"        end\n");
  fprintf(fp,"      end\n");

  fprintf(fp,"      if (ret_flg == 0) begin\n");
  if (kbn == true){fprintf(fp,"        if (rtn_cd == 0) begin value_%s[cur_%s] = p_val; ret_flg = 1; end\n",w,w);}
  else            {fprintf(fp,"        if (rtn_cd == 0) begin w = value_%s[cur_%s];  w[p_val] = 1'b1; value_%s[cur_%s] = w; ret_flg = 1; end\n",w,w,w,w);}
  fprintf(fp,"      end\n");
  fprintf(fp,"      if (ret_flg == 0) begin\n");
  fprintf(fp,"        target_ptr = dust_%s;\n",w);
  fprintf(fp,"        dust_%s = next_%s[dust_%s];\n",w,w,w);
  fprintf(fp,"        if (dust_%s != -1) before_%s[dust_%s] = -1;\n",w,w,w);
  fprintf(fp,"        cyc_%s[target_ptr] = cyc;\n",w);
  if (kbn == true){fprintf(fp,"        value_%s[target_ptr] = p_val;\n",w);}
  else            {fprintf(fp,"        w = 0; w[p_val] = 1'b1; value_%s[target_ptr] = w;\n",w);}
  fprintf(fp,"      end\n");
  fprintf(fp,"      if (ret_flg == 0) begin\n");
  fprintf(fp,"        if (cur_%s == -1) begin\n",w);
  fprintf(fp,"          top_%s = target_ptr;\n",w);
  fprintf(fp,"          before_%s[target_ptr] = -1;\n",w);
  fprintf(fp,"          next_%s[target_ptr] = -1;\n",w);
  fprintf(fp,"          ret_flg = 1;\n");
  fprintf(fp,"        end\n");
  fprintf(fp,"      end\n");
  fprintf(fp,"      if (ret_flg == 0) begin\n");
  fprintf(fp,"        if (addin == 1) begin\n");
  fprintf(fp,"          next_%s[cur_%s]   = target_ptr;\n",w,w);
  fprintf(fp,"          before_%s[target_ptr] = cur_%s;\n",w,w);
  fprintf(fp,"          next_%s[target_ptr] = -1;\n",w);
  fprintf(fp,"        end\n");
  fprintf(fp,"        else begin\n");
  fprintf(fp,"          sv_ptr = before_%s[cur_%s];\n",w,w);
  fprintf(fp,"          next_top_ptr = before_%s[cur_%s];\n",w,w);
  fprintf(fp,"          before_%s[cur_%s]   = target_ptr;\n",w,w);
  fprintf(fp,"          next_%s[target_ptr] = cur_%s;\n",w,w);
  fprintf(fp,"          before_%s[target_ptr] = sv_ptr;\n",w);
  fprintf(fp,"          if (next_top_ptr == -1) top_%s = target_ptr;\n",w);
  fprintf(fp,"          else                    next_%s[next_top_ptr] = target_ptr;\n",w);
  fprintf(fp,"        end\n");
  fprintf(fp,"      end\n");
  fprintf(fp,"//    %s_printf;\n",w);
  fprintf(fp,"    end\n");
  fprintf(fp,"  endtask\n");
  delete ss;
  }

// # RTL State Machine ###############################
// ----------------------
// Port define Ouput
// ----------------------
bool VOutRState_T::PortOutput(FILE *fp,int kbn,char *var_name)
  {
  char   *name;
  char   *size;
  Reg_T  *reg;
  Wire_T *wire;

  it->srch_key = var_name;
  for(;;)
    {
    if (reg_fp->mem_srch() == 0)
      {
      reg = (Reg_T *)reg_fp->mem_link_ptr_rd();
      name = reg->name->c_str();
      size = reg->size->c_str();
//      reg->defined_flg = true;
      break;
      }
    if (wire_fp->mem_srch() == 0)
      {
      wire = (Wire_T *)wire_fp->mem_link_ptr_rd();
      name = wire->name->c_str();
      size = wire->size->c_str();
      wire->defined_flg = true;
      break;
      }
    return(false);
    }
  if (kbn == 0){fprintf(fp,"  input  ");}
  if (kbn == 1){fprintf(fp,"  output ");}
  if (kbn == 2){fprintf(fp,"  inout  ");}
  ary_output(fp,size);
  fprintf(fp," %s;\n",name);
  return(true);
  }


// ----------------------
// Variable define Ouput
// ----------------------
void VOutRState_T::PreOutput(FILE *fp,MEM_FP *add_fp)
  {
  int i;
  char *ww;
  Reg_T *reg;
  Wire_T *wire;
  bool first;

  if (ExistCheck() == false){return;}
  // register define
  first = true;
  MEM_LOOP(reg,Reg_T,reg_fp)
    if (reg->defined_flg == true){continue;}
    else                         {reg->defined_flg = true;}
    if (first == true){first = false; fprintf(fp,"// # register define ############################ \n");}
//  fprintf(fp,"  reg ");
    fprintf(fp,"  %s ",rtype_name->c_str()); // Ver 1.27
    ary_output(fp,reg->size->c_str());

    if (*reg->name->c_str() == '?')
      {
      fprintf(fp," %s",reg->name->c_str()+1);
      }
    else
      {
      fprintf(fp," %s",reg->name->c_str());
      }
    if (strcmp(reg->idx->c_str(),"") != 0){ary_output(fp,reg->idx->c_str());}
    fprintf(fp,"; // _CELL:%s\n",reg->clm_msg->c_str());
  LOOP_END
//  if (first == false){fprintf(fp,"\n// _COMMENT:  *1.state machine register  *2.timing control register\n\n");}
  // wire define
  first = true;
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (wire->defined_flg == true){continue;}
    else                          {wire->defined_flg = true;}
    if (first == true){first = false; fprintf(fp,"// # wire define ############################ \n");}

    it->srch_key = wire->name->c_str();
    if (add_fp->mem_srch() == 0)
      {
      VOutAdding_T *aaa = (VOutAdding_T *)add_fp->mem_link_ptr_rd();
      fprintf(fp,"  %s ",aaa->val->c_str());
      }
    else
      {
//    fprintf(fp,"  wire ");
      fprintf(fp,"  %s ",wtype_name->c_str()); // Ver 1.27
      }

    ary_output(fp,wire->size->c_str());
    fprintf(fp," %s; // _CELL:%s\n",wire->name->c_str(),wire->clm_msg->c_str());
  LOOP_END
//  if (first == false){fprintf(fp,"\n// _COMMENT:  *3.state decord wire\n\n");}
  }

// -----------------
// Array Output
// -----------------
void VOutRState_T::ary_output(FILE *fp,char *str)
  {
  int i;
  if (strcmp(str,"1")==0){return;}
  i = SujiConvEx(str);
  if (i > 0){fprintf(fp," [%d:0]",i-1);}
  else      {fprintf(fp," [%s-1:0]",str);}
  }


// -----------------
// Register Output
// -----------------
void VOutRState_T::reg_output(FILE *fp,Reg_T *reg)
  {
  Siki_T *siki;
  char *ww;
  bool first;
  
  
  // Ver 1.01  条件式がないsikiは最後に追加する
  MEM_LOOP(siki,Siki_T,reg->body_fp)
    if (strcmp(siki->siki->c_str(),"") != 0){continue;}
    reg->body_fp->mem_del();
    it->alloc_ptr = siki;
    reg->body_fp->mem_alloc();
  LOOP_END      
  
  
  if (reg->use_flg == true){return;}
  if (strcmp(reg->clk->c_str(),"") == 0){return;}
  reg->use_flg = true;
  // header
  if (*reg->name->c_str() == '?')  // Ver 1.01
    {
    fprintf(fp,"// # %s register (statemachine register) ######\n",reg->name->c_str()+1);
    }
  else
    {
    fprintf(fp,"// # %s register ######\n",reg->name->c_str());
    }
  ww = reg->clk->c_str();
  if ((*ww == '~') || (*ww == '!')){fprintf(fp,"  always @(negedge %s",ww+1);}
  else                             {fprintf(fp,"  always @(posedge %s",ww);}
  MEM_LOOP(siki,Siki_T,reg->body_fp)
    if (siki->sync == true){continue;}
    ww = siki->siki->c_str();
    if ((*ww == '~') || (*ww == '!')){fprintf(fp," or negedge %s",ww+1);}
    else                             {fprintf(fp," or posedge %s",ww);}
  LOOP_END
  fprintf(fp,") begin\n");

  first = true;
  if (*reg->name->c_str() == '?')  // Ver 1.01
    {
    for(int mode=0;mode<3;++mode)   // Ver 1.03
      {
      MEM_LOOP(siki,Siki_T,reg->body_fp)
        if (mode == 0)
          {
          if (!siki->reset){continue;}
          }
        if (mode == 1)
          {
          if (siki->reset){continue;}
          if (strcmp(siki->val->c_str(),"1'b0") == 0){continue;}
          }
        if (mode == 2)
          {
          if (siki->reset){continue;}
          if (strcmp(siki->val->c_str(),"1'b1") == 0){continue;}
          }

        if (strcmp(siki->siki->c_str(),"") == 0)
          {
          if (first == false){fprintf(fp,"    else  begin\n  ");}
          }
        else
          {
          if (first == true ){fprintf(fp,"    if (%s) begin\n  ",siki->siki->c_str());}
          else               {fprintf(fp,"    else if (%s) begin\n  ",siki->siki->c_str());}
          }
        fprintf(fp,"    %s%s <= %s; // _CELL:%s\n",reg->name->c_str()+1,siki->idx->c_str(),siki->val->c_str(),siki->clm_msg->c_str());
        if ((strcmp(siki->siki->c_str(),"") != 0) || (first == false))
          {
          fprintf(fp,"    end\n");
          }
        first = false;
      LOOP_END
      }
    }
  else
    {
    // Ver 1.05
    bool w_flg;
    bool w_first;
    sChar *w;
    w_flg = true;
    w_first = true;

    if (reg->andor_flg)
      {
      w = new sChar("");
      MEM_LOOP(siki,Siki_T,reg->body_fp)

        if (strcmp(siki->s_name->c_str(),"") != 0){w_flg = false;}
        if (w_flg)
          {
          if (strcmp(siki->siki->c_str(),"") == 0)
            {
            if (first == false){fprintf(fp,"    else  begin\n  ");}
            }
          else
            {
            if (first == true ){fprintf(fp,"    if (%s) begin\n  ",siki->siki->c_str());}
            else               {fprintf(fp,"    else if (%s) begin\n  ",siki->siki->c_str());}
            }
          fprintf(fp,"    %s%s <= %s; // _CELL:%s\n",reg->name->c_str(),siki->idx->c_str(),siki->val->c_str(),siki->clm_msg->c_str());
          if ((strcmp(siki->siki->c_str(),"") != 0) || (first == false))
            {
            fprintf(fp,"    end\n");
            }
          first = false;
          }
        else
          {
          if (strcmp(siki->val->c_str(),reg->andor_def->c_str()) != 0)
            {
            if (w_first)
              {
              MM_PTR_T *sv_ptr;
              sChar *ww;
              bool ww_first;
              Siki_T *ww_siki;
              ww_first = true;
              ww = new sChar("");
              sv_ptr = (unsigned char *)reg->body_fp->mem_mcb_ptr_rd();
              MEM_LOOP(ww_siki,Siki_T,reg->body_fp)
                if (strcmp(ww_siki->s_name->c_str(),"") == 0){continue;}
                if (ww_first){ww_first = false; ww->set(ww_siki->siki->c_str());}
                else         {ww->cat(" | "); ww->cat(ww_siki->siki->c_str());}
              LOOP_END
              if (!first){fprintf(fp,"    else if (%s)  begin\n",ww->c_str()); w->set("      ");}
              else       {fprintf(fp,"    if (%s) begin\n",ww->c_str());       w->set("      ");}
              reg->body_fp->mem_mcb_ptr_wr((McbArea_C *)sv_ptr);
              fprintf(fp,"%s%s%s <=  // _CELL:%s\n",w->c_str(),reg->name->c_str(),siki->idx->c_str(),siki->clm_msg->c_str());
              fprintf(fp,"  %s   (%s ? %s : %s)",w->c_str(),siki->siki->c_str(),siki->val->c_str(),reg->andor_def->c_str());
              w_first = false;
              delete ww;
              }
            else
              {
              fprintf(fp,"\n  %s| (%s ? %s : %s)",w->c_str(),siki->siki->c_str(),siki->val->c_str(),reg->andor_def->c_str());
              }
            }
          }
      LOOP_END
      if (w_first == false)
        {
        fprintf(fp,";\n    end\n");               
        }
      else
        {
        fprintf(fp,"(#reg_andor error!!)\n");
        }
      delete w;
      }
    else
      {
      MEM_LOOP(siki,Siki_T,reg->body_fp)
        if (strcmp(siki->siki->c_str(),"") == 0)
          {
          if (first == false){fprintf(fp,"    else  begin\n  ");}
          }
        else
          {
          if (first == true ){fprintf(fp,"    if (%s) begin\n  ",siki->siki->c_str());}
          else               {fprintf(fp,"    else if (%s) begin\n  ",siki->siki->c_str());}
          }
        fprintf(fp,"    %s%s <= %s; // _CELL:%s\n",reg->name->c_str(),siki->idx->c_str(),siki->val->c_str(),siki->clm_msg->c_str());
        if ((strcmp(siki->siki->c_str(),"") != 0) || (first == false))
          {
          fprintf(fp,"    end\n");
          }
        first = false;
      LOOP_END
      }
    }

  fprintf(fp,"  end\n\n");
  }


// -----------------
// Main Ouput
// -----------------
void VOutRState_T::Output(FILE *fp,MEM_FP *add_fp)
  {
  bool first;
  Reg_T *reg;
  Wire_T *wire;

  if (ExistCheck() == false){return;}

  first = true;
  MEM_LOOP(wire,Wire_T,wire_fp)
    if (strcmp(wire->val->c_str(),"")==0){continue;}
    if (first == true){first = false; fprintf(fp,"// # wire assign ############################ \n");}

    it->srch_key = wire->name->c_str();
    if (add_fp->mem_srch() == 0)
      {
      VOutAdding_T *aaa = (VOutAdding_T *)add_fp->mem_link_ptr_rd();
      fprintf(fp,"  assign %s %s = %s; // _CELL:%s\n",aaa->val->c_str(),wire->name->c_str(),wire->val->c_str(),wire->clm_msg->c_str());
      }
    else
      {
      fprintf(fp,"  assign %s = %s; // _CELL:%s\n",wire->name->c_str(),wire->val->c_str(),wire->clm_msg->c_str());
      }



  LOOP_END
  fprintf(fp,"\n");
  MEM_LOOP(reg,Reg_T,reg_fp)
    reg_output(fp,reg);
  LOOP_END
  }

// # RTL Connection ##################################
// ------------------
// Port define
// ------------------
bool VOutCon_T::PortOutput(FILE *fp,int kbn,char *var_name)
  {
  ConWire_T *wire;

  it->srch_key = var_name;
  if (wire_def_fp->mem_srch() != 0){return(false);}
  wire = (ConWire_T *)wire_def_fp->mem_link_ptr_rd();
  wire->defined_flg = true;
  if (kbn == 0){fprintf(fp,"  input  ");}
  if (kbn == 1){fprintf(fp,"  output ");}
  if (kbn == 2){fprintf(fp,"  inout  ");}
  AryOutput(fp,wire->size);
  fprintf(fp," %s;\n",wire->name->c_str());
  return(true);
  }


// ------------------
// Varriable define
// ------------------
void VOutCon_T::PreOutput(FILE *fp,MEM_FP *add_fp)
  {
  ConWire_T *wire;
  bool first;

  first = true;
  MEM_LOOP(wire,ConWire_T,wire_def_fp)
    if (wire->defined_flg == true){continue;}
    else                          {wire->defined_flg = true;}
    if (first == true){first = false; fprintf(fp,"\n// # wire define ############################\n");}


    it->srch_key = wire->name->c_str();
    if (add_fp->mem_srch() == 0)
      {
      VOutAdding_T *aaa = (VOutAdding_T *)add_fp->mem_link_ptr_rd();
      fprintf(fp,"  %s ",aaa->val->c_str());
      }
    else
      {
//    fprintf(fp,"  wire ");
      fprintf(fp,"  %s ",type_name->c_str());  // Ver 1.27
      }


    AryOutput(fp,wire->size);
    fprintf(fp," %s;  // _CELL:%s\n",wire->name->c_str(),wire->clm_msg->c_str());
  LOOP_END
  fprintf(fp,"\n");
  }

// ------------------
// Varriable define
// ------------------
void VOutCon_T::AryOutput(FILE *fp,int size)
  {
  if (size == 1) {return;}
  fprintf(fp," [%d:0]",size-1);
  }


// ------------------
// output (Ver 1.02)
// ------------------
void VOutCon_T::Output(FILE *out_fp)
  {
//  InstPtr_T  *ip_cell;
  Inst_T     *inst;
  Con_T      *con;
  int         i;
  int         first;
  sChar      *ww;

// MEM_LOOP(vc,VtCon_T,vc_fp)
//   for(i=0;i<vc->ip_max;++i)
//     {
//     ip_cell = *(vc->ip+i);
//     inst = ip_cell->inst;
  ww = new sChar("");
  MEM_LOOP(inst,Inst_T,inst_fp)
    fprintf(out_fp,"// # %s(%s) ###############\n",inst->mod_name->c_str(),inst->inst_name->c_str());
    fprintf(out_fp,"  %s %s(  // _CELL:%s\n",inst->mod_name->c_str(),inst->inst_name->c_str(),inst->clm_msg->c_str());
    first = 1;
    MEM_LOOP(con,Con_T,inst->con_fp)
      ww->set(con->wire_name->c_str());
      if (strcmp(con->index->c_str() ,"")!=0){ww->cat("["); ww->cat(con->index->c_str()); ww->cat("]");}
      if (strcmp(con->adding->c_str(),"")!=0){ww->cat(con->adding->c_str());}
      if (first == 1){fprintf(out_fp,"     .%s(%s)  // _CELL:%s\n",con->port_name->c_str(),ww->c_str(),con->clm_msg->c_str()); first = 0;}
      else           {fprintf(out_fp,"    ,.%s(%s)  // _CELL:%s\n",con->port_name->c_str(),ww->c_str(),con->clm_msg->c_str());}
    LOOP_END
    fprintf(out_fp,"  );\n\n");
  LOOP_END
  delete ww;

//      }
//  LOOP_END
  }

// # Clock ###########################################
// ----------------------
// Variable define Ouput
// ----------------------
void VOutClk_T::PreOutput(FILE *fp)
  {
  if (ExistCheck() == false){return;}

  fprintf(fp,"// # Clock Variable ############################ \n");
  MEM_LOOP(clk,Clk_T,clk_fp)
    fprintf(fp,"  wire %s;  // _CELL:%s\n",clk->name->c_str(),clk->clm_msg->c_str());
    fprintf(fp,"  reg INNR_%s;\n",clk->name->c_str());
    fprintf(fp,"  reg LSTK_%s;\n",clk->name->c_str());
    fprintf(fp,"  reg HSTK_%s;\n",clk->name->c_str());
  LOOP_END
  }

// -----------------
// output
// -----------------
void VOutClk_T::Output(FILE *fp)
  {
  if (ExistCheck() == false){return;}

  // Initialize write ------------------------------
  fprintf(fp,"\n// # Clock Initialize #################################### \n");
  fprintf(fp,"  initial begin\n");
  MEM_LOOP(clk,Clk_T,clk_fp)
    fprintf(fp,"    INNR_%s = %s;  // _CELL:%s\n",clk->name->c_str(),clk->init->c_str(),clk->clm_msg->c_str());
    fprintf(fp,"    LSTK_%s = 1'b0;\n",clk->name->c_str());
    fprintf(fp,"    HSTK_%s = 1'b0;\n",clk->name->c_str());
  LOOP_END
  fprintf(fp,"  end\n");

  // Main write ------------------------------
  fprintf(fp,"\n// # Clock Generator #################################### \n");
  MEM_LOOP(clk,Clk_T,clk_fp)
    fprintf(fp,"// # %s clock #####\n",clk->name->c_str());
    fprintf(fp,"  always begin  // _CELL:%s\n",clk->clm_msg->c_str());
    fprintf(fp,"    #%s INNR_%s = ~INNR_%s;\n",clk->chg1->c_str(),clk->name->c_str(),clk->name->c_str());
    fprintf(fp,"    #%s INNR_%s = ~INNR_%s;\n",clk->chg2->c_str(),clk->name->c_str(),clk->name->c_str());
    fprintf(fp,"    #(%s - %s - %s);\n",clk->cyc->c_str(),clk->chg1->c_str(),clk->chg2->c_str());
    fprintf(fp,"  end\n");
    fprintf(fp,"  assign %s = (INNR_%s & ~LSTK_%s) | HSTK_%s;\n",clk->name->c_str(),clk->name->c_str(),clk->name->c_str(),clk->name->c_str());
    fprintf(fp,"  assign %s = %s;\n\n",clk->line->c_str(),clk->name->c_str());
  LOOP_END
  }

// # Function Table ###########################################
// ------------------------
// output
// ------------------------
void VOutFunc_T::Output(FILE *fp)
  {
  sChar *str;
  Func_T *fn;
  StrSrchInf_T *ssc;
  bool first;
  Tbl_T *tbl;
  bool  default_flg;
  sChar *clm;

  ssc = new StrSrchInf_T();
  ssc->Set('[');

  MEM_LOOP(fn,Func_T,func_fp)
    ssc->Main(fn->name->c_str());
    fprintf(fp,"// # function : [%s] ##############\n",skin(ssc->Get(0)));
    if (ssc->GetSu() == 1){fprintf(fp,"  function %s;  // _CELL:%s\n",skin(ssc->Get(0)),fn->clm_msg->c_str());}
    else                  {fprintf(fp,"  function [%s %s;  // _CELL:%s\n",skin(ssc->Get(1)),skin(ssc->Get(0)),fn->clm_msg->c_str());}
    MEM_LOOP(clm,sChar,fn->in_fp)
      ssc->Main(clm->c_str());
      if (ssc->GetSu() == 0){continue;}
      if (ssc->GetSu() == 1){fprintf(fp,"    input %s;\n",skin(ssc->Get(0)));}
      else                  {fprintf(fp,"    input [%s %s;\n",skin(ssc->Get(1)),skin(ssc->Get(0)));}
    LOOP_END
    //fprintf(fp,"    case ({");
    fprintf(fp,"    %s ({",fn->case_str->c_str());  // Ver 1.09
    first = true;
    MEM_LOOP(clm,sChar,fn->in_fp)
      ssc->Main(clm->c_str());
      if (ssc->GetSu() == 0){continue;}
      if (first == true){first = false;}
      else              {fprintf(fp,",");}
      fprintf(fp,"%s",skin(ssc->Get(0)));
    LOOP_END
    if (strcmp(fn->direct->c_str(),"") == 0){fprintf(fp,"})\n");}                               // Ver 1.09
    else                                    {fprintf(fp,"}) // %s\n",fn->direct->c_str());}     // Ver 1.09


    MEM_LOOP(tbl,Tbl_T,fn->table_fp)
      first = true;
      default_flg = false;
      MEM_LOOP(str,sChar,tbl->inptn_fp)
        if (strcmp(str->c_str(),"")==0){continue;}
        if (strcmp(str->c_str(),"default")==0){default_flg = true;}
        if (first == true)
          {
          if (default_flg == false){fprintf(fp,"      {");}
          else                     {fprintf(fp,"      ");}
          first = false;
          }
        else              {fprintf(fp,",");}
        fprintf(fp,"%s",str->c_str());
        if (default_flg == true){break;}
      LOOP_END
      if (default_flg == false){fprintf(fp,"}");}
      ssc->Main(fn->name->c_str());
      fprintf(fp," : %s = %s;  // _CELL:%s\n",skin(ssc->Get(0)),tbl->val->c_str(),tbl->clm_msg->c_str());
    LOOP_END

    fprintf(fp,"    endcase\n");
    fprintf(fp,"  endfunction\n\n");
  LOOP_END

  delete ssc;
  }

// # Gate ###########################################
// ----------
// output
// ----------
void VOutGate_T::Output(FILE *out_fp)
  {
  sChar *str;
  bool first;

  first = true;
  MEM_LOOP(str,sChar,verilog_fp)
    if (first == true){first = false; fprintf(out_fp,"// # gate ############################ \n");}
    fprintf(out_fp,"  %s\n",str->c_str());
  LOOP_END
  if (first == false){fprintf(out_fp,"\n");}
  }

// # Parameter ###########################################
// ----------------------
// Variable define Ouput
// ----------------------
void VOutParm_T::Output(FILE *fp)
  {
  sChar *str;
  sChar *clm;

  if (ExistCheck() == false){return;}

  fprintf(fp,"// # Patern Making ############################ \n");
  fprintf(fp,"  initial begin\n");
  fprintf(fp,"    #1\n");
  MEM_LOOP(vtp,CsvParm_T,vtp_fp)
    vtp->clm_fp->mem_mcb_top_set();
    MEM_LOOP(str,sChar,vtp->mem_fp)
      clm = (sChar *)vtp->clm_fp->mem_link_ptr_rd();
      fprintf(fp,"    %s  // _CELL:%s\n",str->c_str(),clm->c_str());
      vtp->clm_fp->mem_mcb_next_set();
    LOOP_END
  LOOP_END
  fprintf(fp,"  end\n");
  }

// # Patern ###########################################
// ----------------------
// Pre Ouput
// ----------------------
void VOutPtn_T::PreOutput(FILE *fp)
  {
  Var_T *var;
  
  if (ExistCheck() == false){return;}

  fprintf(fp,"// # Patern Variable ############################ \n");
  MEM_LOOP(vtp,CsvPtn_T,vtp_fp)
    fprintf(fp,"  integer pidx_%s;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"  integer pmax_%s;\n",vtp->name->c_str());
    fprintf(fp,"  integer psize_%s;\n",vtp->name->c_str());
    fprintf(fp,"  integer prptr_%s;\n",vtp->name->c_str());
    fprintf(fp,"  integer pwptr_%s;\n",vtp->name->c_str());
  LOOP_END
  MEM_LOOP(vtp,CsvPtn_T,vtp_fp)
    MEM_LOOP(var,Var_T,vtp->var_fp)
      if (strcmp(var->size->c_str(),"1")==0){fprintf(fp,"  reg ary_%s[%s-1:0];  // _CELL:%s\n",var->name->c_str(),vtp->ary_max->c_str(),var->clm_msg->c_str());}
      else                                  {fprintf(fp,"  reg[%s-1:0] ary_%s[%s-1:0];  // _CELL:%s\n",var->size->c_str(),var->name->c_str(),vtp->ary_max->c_str(),var->clm_msg->c_str());}
    LOOP_END
  LOOP_END
  MEM_LOOP(vtp,CsvPtn_T,vtp_fp)
    MEM_LOOP(var,Var_T,vtp->var_fp)
      if (strcmp(var->size->c_str(),"1")==0){fprintf(fp,"  reg %s;  // _CELL:%s\n",var->name->c_str(),var->clm_msg->c_str());}
      else                                  {fprintf(fp,"  reg[%s-1:0] %s;  // _CELL:%s\n",var->size->c_str(),var->name->c_str(),var->clm_msg->c_str());}
    LOOP_END
  LOOP_END
  }

// ----------------------
// Main Ouput
// ----------------------
void VOutPtn_T::Output(FILE *fp)
  {
  Var_T *var;
  bool first;

  if (ExistCheck() == false){return;}
  fprintf(fp,"// # Patern Index Initialize ############################ \n",vtp->name->c_str());
  fprintf(fp,"  initial begin\n");
  MEM_LOOP(vtp,CsvPtn_T,vtp_fp)
    fprintf(fp,"    pidx_%s = 0;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    pmax_%s = 0;\n",vtp->name->c_str());
    fprintf(fp,"    psize_%s = 0;\n",vtp->name->c_str());
    fprintf(fp,"    prptr_%s = 0;\n",vtp->name->c_str());
    fprintf(fp,"    pwptr_%s = 0;\n",vtp->name->c_str());
  LOOP_END
  fprintf(fp,"  end\n");

  MEM_LOOP(vtp,CsvPtn_T,vtp_fp)
    fprintf(fp,"// # Patern Task (%s)############################ \n",vtp->name->c_str());
    fprintf(fp,"// # Ring Queue Get ##### \n");
    fprintf(fp,"  task %s_ring_get;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    begin\n");
    fprintf(fp,"      if (pidx_%s == pmax_%s) pidx_%s = 0;\n",vtp->name->c_str(),vtp->name->c_str(),vtp->name->c_str());
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"      %s = ary_%s[pidx_%s];\n",var->name->c_str(),var->name->c_str(),vtp->name->c_str());
    LOOP_END
    fprintf(fp,"      pidx_%s = pidx_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      if (pidx_%s == %s-1) pidx_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");


    fprintf(fp,"// # FIFO Read ##### \n");
    fprintf(fp,"  task %s_fifo_rd;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    begin\n");
    if (strcmp(vtp->end_rtn->c_str(),"")==0)
      {
      fprintf(fp,"      if (prptr_%s == pwptr_%s) $finish;\n",vtp->name->c_str(),vtp->name->c_str());
      }
    else
      {
      fprintf(fp,"      if (prptr_%s == pwptr_%s) begin %s; $finish; end\n",vtp->name->c_str(),vtp->name->c_str(),vtp->end_rtn->c_str());
      }
    fprintf(fp,"      else begin\n");
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"        %s = ary_%s[prptr_%s];\n",var->name->c_str(),var->name->c_str(),vtp->name->c_str());
    LOOP_END
    fprintf(fp,"        prptr_%s = prptr_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"        if (prptr_%s == %s) prptr_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");

    fprintf(fp,"// # FIFO Write #####\n");
    fprintf(fp,"  task %s_fifo_wr;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"  input[%s-1:0] p_%s;\n",var->size->c_str(),var->name->c_str());
    LOOP_END
    fprintf(fp,"    begin\n");
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"      ary_%s[pwptr_%s] = p_%s;\n",var->name->c_str(),vtp->name->c_str(),var->name->c_str());
    LOOP_END
    fprintf(fp,"      pwptr_%s = pwptr_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      if (pwptr_%s == %s) pwptr_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    if (strcmp(vtp->end_rtn->c_str(),"")==0)
      {
      fprintf(fp,"      if (prptr_%s == pwptr_%s) $finish;\n",vtp->name->c_str(),vtp->name->c_str());
      }
    else
      {
      fprintf(fp,"      if (prptr_%s == pwptr_%s) begin %s; $finish; end\n",vtp->name->c_str(),vtp->name->c_str(),vtp->end_rtn->c_str());
      }
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");


    fprintf(fp,"// # Get ##### \n");
    fprintf(fp,"  task %s_get;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    begin\n");
    if (strcmp(vtp->end_rtn->c_str(),"")==0)
      {
      fprintf(fp,"      if (pidx_%s == pmax_%s) $finish;\n",vtp->name->c_str(),vtp->name->c_str());
      }
    else
      {
      fprintf(fp,"      if (pidx_%s == pmax_%s) begin %s; $finish; end\n",vtp->name->c_str(),vtp->name->c_str(),vtp->end_rtn->c_str());
      }
    fprintf(fp,"      else begin\n");
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"        %s = ary_%s[pidx_%s];\n",var->name->c_str(),var->name->c_str(),vtp->name->c_str());
    LOOP_END
    fprintf(fp,"        pidx_%s = pidx_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"        if (pidx_%s == %s-1) pidx_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"        psize_%s = psize_%s - 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");

    fprintf(fp,"// # Put #####\n");
    fprintf(fp,"  task %s_put;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"  input[%s-1:0] p_%s;\n",var->size->c_str(),var->name->c_str());
    LOOP_END
    fprintf(fp,"    begin\n");
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"      ary_%s[pmax_%s] = p_%s;\n",var->name->c_str(),vtp->name->c_str(),var->name->c_str());
    LOOP_END
    fprintf(fp,"      pmax_%s = pmax_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      if (pmax_%s == %s-1) pmax_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"      psize_%s = psize_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      if (psize_%s >= %s) $display(\"%s patern queue over.\");\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");

    fprintf(fp,"// # Push #####\n");
    fprintf(fp,"  task %s_push;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    begin\n");
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"      ary_%s[pmax_%s] = %s;\n",var->name->c_str(),vtp->name->c_str(),var->name->c_str());
    LOOP_END
    fprintf(fp,"      pmax_%s = pmax_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      if (pmax_%s == %s-1) pmax_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"      psize_%s = psize_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      if (psize_%s >= %s) $display(\"%s patern queue over.\");\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");

    fprintf(fp,"// # Pop #####\n");
    fprintf(fp,"  function %s_pop;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    input dmy;\n");
    fprintf(fp,"    begin\n");
    fprintf(fp,"      if (pidx_%s == pmax_%s) %s_pop = 1'b0;\n",vtp->name->c_str(),vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"      else begin\n");
    MEM_LOOP(var,Var_T,vtp->var_fp)
      fprintf(fp,"        %s = ary_%s[pidx_%s];\n",var->name->c_str(),var->name->c_str(),vtp->name->c_str());
    LOOP_END
    fprintf(fp,"        pidx_%s = pidx_%s + 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"        if (pidx_%s == %s-1) pidx_%s = 0;\n",vtp->name->c_str(),vtp->ary_max->c_str(),vtp->name->c_str());
    fprintf(fp,"        psize_%s = psize_%s - 1;\n",vtp->name->c_str(),vtp->name->c_str());
    fprintf(fp,"        %s_pop = 1'b1;\n",vtp->name->c_str());
    fprintf(fp,"      end\n");
    fprintf(fp,"    end\n");
    fprintf(fp,"  endfunction\n");

    fprintf(fp,"// # Clear #####\n");
    fprintf(fp,"  task %s_clr;  // _CELL:%s\n",vtp->name->c_str(),vtp->clm_msg->c_str());
    fprintf(fp,"    begin\n");
    fprintf(fp,"      pmax_%s  = 0;\n",vtp->name->c_str());
    fprintf(fp,"      pidx_%s  = 0;\n",vtp->name->c_str());
    fprintf(fp,"      psize_%s = 0;\n",vtp->name->c_str());
    fprintf(fp,"    end\n");
    fprintf(fp,"  endtask\n");

  LOOP_END
  }

