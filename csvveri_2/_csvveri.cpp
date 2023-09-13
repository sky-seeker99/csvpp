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
//  CSV -> Verilog-HDL
//   1.09 : #body
//


// Parameter Class -----------------
class VOutPara_T {
  public:
  sChar *name;
  sChar *val;

  VOutPara_T(char *p_name,char *p_val){
    name = new sChar(p_name);
    val  = new sChar(p_val);
    }
  ~VOutPara_T(){
    delete name;
    delete val;
    }

  };

// TOP Class -----------------
class VOutTop_T {
  private:
  MemHeader_T  *it;
  CsvLang_T    *v_lang;
  VOutState_T  *v_state;
  VOutSub_T    *v_sub;
  VOutTask_T   *v_task;
  VOutClk_T    *v_clk;
  VOutPtn_T    *v_ptn;
  VOutParm_T   *v_parm;
  VOutFunc_T   *v_func;
  VOutVInf_T   *v_vinf;
  VOutCover_T  *v_cover;
  VOutReadmem_T *v_readmemh;

  Msg_T        *msg;
  sChar        *name;
  CsvAnl_C     *csvi;
  FILE         *fp;
  Read64_C     *file_fp;

  VOutRState_T *v_rstate; // Adding
  VOutCon_T    *v_con;
  VOutGate_T   *v_gate;
  MEM_FP       *in_fp;
  MEM_FP       *out_fp;
  MEM_FP       *io_fp;
  MEM_FP       *head_fp;
  MEM_FP       *body_fp;  // Ver 1.09
  MEM_FP       *parm_fp;

  MEM_FP       *add_wire_fp;
  MEM_FP       *add_delay_fp;

  bool          head_writed_flg;


  public:
  void init();
  void main();
  void output();



  VOutTop_T(char *csv_file,char *v_file){
    csvi     = new CsvAnl_C();
    it       = new MemHeader_T;
    name     = new sChar("???");
    in_fp    = new MEM_FP(it);
    out_fp   = new MEM_FP(it);
    io_fp    = new MEM_FP(it);
    parm_fp  = new MEM_FP(it);
    head_fp  = new MEM_FP(it);
    body_fp  = new MEM_FP(it);   // Ver 1.09

    add_wire_fp  = new MEM_FP(it);
    add_delay_fp = new MEM_FP(it);

    init();
    fp       = fopen(v_file,"wt");
	if (fp == NULL){printf("open error.(file=%s)\n",v_file);}

	file_fp = new Read64_C(csv_file,"rt",10240);
    csvi->setFileName(csv_file);

	if (file_fp->okCheck() == false){printf("open error.(file = %s)\n",csv_file);}
	else                            {printf("%s->%s convert complete.\n",csv_file,v_file); main(); }

	head_writed_flg = false;
	}

  ~VOutTop_T(){
	sChar *str;
	VOutPara_T *p;
	VOutAdding_T *aaa;

	output();
	delete it;
	delete name;
	delete csvi;
    delete file_fp;
	MEM_LOOP(str,sChar,in_fp     ) delete str; LOOP_END
	MEM_LOOP(str,sChar,out_fp    ) delete str; LOOP_END
	MEM_LOOP(str,sChar,io_fp     ) delete str; LOOP_END
	MEM_LOOP(str,sChar,head_fp   ) delete str; LOOP_END
	MEM_LOOP(str,sChar,body_fp   ) delete str; LOOP_END   // Ver 1.09
	MEM_LOOP(p  ,VOutPara_T,parm_fp) delete p;   LOOP_END
	MEM_LOOP(aaa  ,VOutAdding_T,add_delay_fp) delete aaa;   LOOP_END
	MEM_LOOP(aaa  ,VOutAdding_T,add_wire_fp ) delete aaa;   LOOP_END

	delete parm_fp;
	delete in_fp;
	delete out_fp;
	delete io_fp;
	delete head_fp;
	delete body_fp;  // Ver 1.09
	delete add_delay_fp;
	delete add_wire_fp;

	if (fp != NULL){fclose(fp);}
	}
  void port_rtn  (CsvAnl_C *csvi,MEM_FP *mem_fp);
  void header_rtn(CsvAnl_C *csvi);
  void body_rtn  (CsvAnl_C *csvi);      // Ver 1.09
  void parm_rtn  (CsvAnl_C *csvi);
  void delay_rtn (CsvAnl_C *csvi,bool flg);
  void type_update_rtn(CsvAnl_C *csvi,bool flg);
  void def_net_rtn(CsvAnl_C *csvi,int mode);

  };

// -----------------
// Initialize
// -----------------
void VOutTop_T::init()
  {
  msg     = new Msg_T();
  v_lang  = new CsvLang_T  (it,msg);
  v_state = new VOutState_T(it,msg);
  v_task  = new VOutTask_T (it,msg);
  v_clk   = new VOutClk_T  (it,msg);
  v_ptn   = new VOutPtn_T  (it,msg);
  v_parm  = new VOutParm_T (it,msg);
  v_sub   = new VOutSub_T  (it,msg);
  v_func  = new VOutFunc_T (it,msg);
  v_vinf  = new VOutVInf_T (it,msg);
  v_cover = new VOutCover_T(it,msg);
  v_readmemh = new  VOutReadmem_T(msg);
  v_rstate= new VOutRState_T(it,msg); // Add
  v_con   = new VOutCon_T  (it,msg);
  v_gate  = new VOutGate_T (it,msg);

  }

// -----------------
// End
// -----------------
void VOutTop_T::output()
  {
  MEM_FP *msg_fp;
  char   *str;
  bool   first;
  bool   top_first;
  sChar *sstr;
  int i;
  MEM_FP *mem_fp;
  VOutPara_T *p;
  Wire_T *wire;
  ConWire_T *c_wire;
  char buff[255];
  VOutAdding_T *aaa;
/*
  msg_fp = csvi->GetMsg();
  MEM_LOOP(str,char,msg_fp)
	printf("%s\n",str);
  LOOP_END
*/
  if (fp == NULL){return;}
  if (msg->err_cnt != 0){printf("error exist.(error count=%d,module=%s)\n",msg->err_cnt,name->c_str());}
  else
	{
	// header ----------
	if (head_writed_flg == false)
	  {
	  head_writed_flg = true;
	  MEM_LOOP(sstr,sChar,head_fp)
		fprintf(fp,"// %s\n",sstr->c_str());
	  LOOP_END
	  MEM_LOOP(sstr,sChar,head_fp)  // Ver 1.09
		delete sstr;
	  LOOP_END
	  head_fp->mem_del_all();
//      fprintf(fp,"\n");
	  }

	// output ----------

	// Ver 1.09
	MEM_LOOP(sstr,sChar,body_fp)
	  fprintf(fp,"%s\n",sstr->c_str());
	LOOP_END
	MEM_LOOP(sstr,sChar,body_fp)
	  delete sstr;
	LOOP_END
	body_fp->mem_del_all();

	if (strcmp(name->c_str(),"")!=0)
	  {
	  fprintf(fp,"// ---------------------\n");
	  fprintf(fp,"// %s module\n",name->c_str());
	  fprintf(fp,"// ---------------------\n");
	  fprintf(fp,"module %s",name->c_str());
	  }
	top_first = true;

	for(i=0;i<3;++i)
	  {
	  if (i==0){mem_fp = in_fp; }
	  if (i==1){mem_fp = out_fp;}
	  if (i==2){mem_fp = io_fp; }
	  //first = true;
	  MEM_LOOP(sstr,sChar,mem_fp)
		if (top_first == true){fprintf(fp,"(\n   "); top_first = false;}
		else                  {fprintf(fp,"  ,");}
		fprintf(fp,"%s\n",sstr->c_str());
	  LOOP_END
	  }
	if (strcmp(name->c_str(),"")!=0)
	  {
	  if (top_first == false){fprintf(fp,");\n");}
	  else                  {fprintf(fp,";\n");}
	  }
	first = true;
	MEM_LOOP(p,VOutPara_T,parm_fp)
	  if (first == true){first = false; fprintf(fp,"// # parameter ########################\n");}
	  fprintf(fp,"  parameter %s = %s;\n",p->name->c_str(),p->val->c_str());
	LOOP_END
	if (first == false){fprintf(fp,"\n");}

	top_first = true;
	for(i=0;i<3;++i)
	  {
	  if (i==0){mem_fp = in_fp; }
	  if (i==1){mem_fp = out_fp;}
	  if (i==2){mem_fp = io_fp; }
	  first = true;
	  MEM_LOOP(sstr,sChar,mem_fp)
		if (top_first == true)
		  {
		  top_first = false;
		  fprintf(fp,"// # port define ########################\n");
		  }
		if (first     == true)
		  {
		  first = false;
		  if (i==0) {fprintf(fp,"// # input  ########\n");}
		  if (i==1) {fprintf(fp,"// # output ########\n");}
		  if (i==2) {fprintf(fp,"// # inout  ########\n");}
		  }

		for(;;)
		  {
		  if (v_rstate->PortOutput(fp,i,sstr->c_str()) == true){break;}
		  if (v_con->PortOutput   (fp,i,sstr->c_str()) == true){break;}
		  if (v_vinf->PortOutput  (fp,i,sstr->c_str()) == true){break;}

		  fprintf(fp,"   Undefine [%s]\n",sstr->c_str());
		  break;
		  }
	  LOOP_END
	  }


	MEM_LOOP(wire,Wire_T,v_rstate->wire_fp)
	  v_con->it->srch_key = wire->name->c_str();
	  if (v_con->wire_def_fp->mem_srch() != 0) {continue;}
	  c_wire = (ConWire_T *)v_con->wire_def_fp->mem_link_ptr_rd();
	  sprintf(buff,"%d",c_wire->size);
	  if (strcmp(buff,wire->size->c_str()) == 0)
		{
		c_wire->defined_flg = true;
		}
	  else
		{
		sprintf(buff," net=%s",v_con->it->srch_key);
		msg->ErrMsg(E008,"#con",buff);
		}

	LOOP_END


	v_con->complete_rtn(  );
	v_rstate->CsvPost  (  );
	v_rstate->PreOutput(fp,add_wire_fp);

	v_state->ChgCheck(v_rstate->reg_fp);

	v_con->PreOutput   (fp,add_wire_fp);
	v_state->PreOutput (fp);
	v_task->PreOutput  (fp);
	v_ptn->PreOutput   (fp);
	v_readmemh->PreOutput(fp);
	v_clk->PreOutput   (fp);
	v_vinf->PreOutput  (fp);
	v_cover->PreOutput (fp);

	v_func->Output     (fp);
	v_sub->Output      (fp);
	v_lang->Output     (fp);
	v_rstate->Output   (fp,add_delay_fp);
	v_con->Output      (fp);
	v_gate->Output     (fp);
	v_ptn->Output      (fp);
	v_readmemh->Output (fp);
	v_clk->Output      (fp);
	v_state->Output    (fp);
	v_task->Output     (fp);
	v_parm->Output     (fp);
	v_vinf->Output     (fp);
	v_cover->Output    (fp);

	if (strcmp(name->c_str(),"")!=0){fprintf(fp,"endmodule\n\n");}
	}

  // delete
  delete v_lang;
  delete v_rstate;
  delete v_func;
  delete v_vinf;
  delete v_cover;
  delete v_con;
  delete v_gate;
  delete v_sub;
  delete v_state;
  delete v_task;
  delete v_clk;
  delete v_ptn;
  delete v_readmemh;
  delete v_parm;
  delete msg;
  MEM_LOOP(sstr,sChar,in_fp ) delete sstr; LOOP_END
  MEM_LOOP(sstr,sChar,out_fp) delete sstr; LOOP_END
  MEM_LOOP(sstr,sChar,io_fp ) delete sstr; LOOP_END
  MEM_LOOP(p   ,VOutPara_T,parm_fp ) delete p; LOOP_END
  MEM_LOOP(aaa  ,VOutAdding_T,add_delay_fp) delete aaa;   LOOP_END
  MEM_LOOP(aaa  ,VOutAdding_T,add_wire_fp ) delete aaa;   LOOP_END

  in_fp->mem_del_all();
  out_fp->mem_del_all();
  io_fp->mem_del_all();
  parm_fp->mem_del_all();
  add_wire_fp->mem_del_all();
  add_delay_fp->mem_del_all();
  }

// -----------------
// Main Loop
// -----------------
void VOutTop_T::main(){
  char *str;
  int   i;
  bool non_flg;

  csvi->initLineNum();
  TEXT_READ_LOOP(file_fp,buff)
	csvi->Exec(buff);
	csvi->plusLineNum();

	if ((str = csvi->CsvSel_Rd(0)) == MM_NULL) {continue;}

	if ((strcmp(str,"#wr") != 0) && (strcmp(str,"#body") != 0)) {
	  for(i=1;i<csvi->CsvSelSu_Rd();++i){
		char *w_str;
		if ((w_str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
		sp_push(w_str); sp_push2(w_str);
	  }
	}

	if (strcmp(str,"#module")==0){
	  non_flg = true;
	  for(i=1;i<csvi->CsvSelSu_Rd();++i){
		if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
		if (strcmp(name->c_str(),"???") != 0){output(); init();}
		name->set(str);
		non_flg = false;
		break;
	  }
	  if (non_flg == true){
		if (strcmp(name->c_str(),"???") != 0){output(); init();}
		name->set("");
	  }
	  continue;
	}

	if (strcmp(str,"#header") == 0){header_rtn(csvi); continue;}
	if (strcmp(str,"#body") == 0){body_rtn(csvi); continue;}  // Ver 1.09
	if (strcmp(str,"#wire_type" ) == 0){type_update_rtn(csvi,true); continue;}
	if (strcmp(str,"#reg_type"  ) == 0){type_update_rtn(csvi,false); continue;}
	if (strcmp(str,"#default_net"  ) == 0){def_net_rtn(csvi,0); continue;}
	if (strcmp(str,"#gate_inst" ) == 0){def_net_rtn(csvi,1); continue;}
	if (strcmp(name->c_str(),"???") == 0) {msg->ErrMsg(csvi,E090,0); continue;}

	if (strcmp(str,"#input"     ) == 0){port_rtn (csvi,in_fp );  continue;}
	if (strcmp(str,"#output"    ) == 0){port_rtn (csvi,out_fp); continue;}
	if (strcmp(str,"#inout"     ) == 0){port_rtn (csvi,io_fp );  continue;}
	if (strcmp(str,"#parameter" ) == 0){parm_rtn (csvi       );  continue;}
	if (strcmp(str,"#delay"     ) == 0){delay_rtn(csvi,true  );  continue;}
	if (strcmp(str,"#wire_attr" ) == 0){delay_rtn(csvi,false );  continue;}

	if (v_rstate->CsvRead(csvi) == true){continue;}
	if (v_lang->CsvRead  (csvi) == true){continue;}
	if (v_sub->CsvRead   (csvi) == true){continue;}
	if (v_func->CsvRead  (csvi) == true){continue;}
	if (v_gate->CsvRead  (csvi) == true){continue;}
	if (v_con->CsvRead   (csvi) == true){continue;}

	if (v_lang->CsvRead  (csvi) == true){continue;}
	if (v_sub->CsvRead   (csvi) == true){continue;}
	if (v_state->CsvRead (csvi) == true){continue;}
	if (v_func->CsvRead  (csvi) == true){continue;}
	if (v_task->CsvRead  (csvi) == true){continue;}
	if (v_clk->CsvRead   (csvi) == true){continue;}
	if (v_ptn->CsvRead   (csvi) == true){continue;}
	if (v_readmemh->CsvRead   (csvi) == true){continue;}
	if (v_parm->CsvRead  (csvi) == true){continue;}
	if (v_cover->CsvRead (csvi) == true){continue;}

	if (v_vinf->CsvRead  (csvi,it,in_fp,out_fp) == true){continue;}

	msg->ErrMsg(csvi,E000,0);
  }
}

// ----------------------
// #input/#output/#inout
// ----------------------
void VOutTop_T::port_rtn(CsvAnl_C *csvi,MEM_FP *mem_fp)
  {
  int i;
  char *str;

  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    it->alloc_ptr = (MM_PTR_T *)new sChar(str);
    mem_fp->mem_alloc();
    }
  }

// ----------------------
// #header
// ----------------------
void VOutTop_T::header_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *sstr;

  sstr = new sChar("");
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    sstr->cat(str);
    }
  it->alloc_ptr = (MM_PTR_T *)sstr;
  head_fp->mem_alloc();
  }


// ----------------------
// #body (Ver 1.09)
// ----------------------
void VOutTop_T::body_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  sChar *sstr;

  sstr = new sChar("");
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    sstr->cat(str);
    }
  it->alloc_ptr = (MM_PTR_T *)sstr;
  body_fp->mem_alloc();
  }

// ----------------------
// #parameter
// ----------------------
void VOutTop_T::parm_rtn(CsvAnl_C *csvi)
  {
  int i;
  char *str;
  char *name;
  sChar *sstr;

  sstr = new sChar("");
  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (name == NULL){name = str; continue;}
    sstr->cat(str);
    }
  it->alloc_ptr = (MM_PTR_T *)new VOutPara_T(name,sstr->c_str());
  parm_fp->mem_alloc();
  }


// ----------------------
// #delay / #wire_attr
// ----------------------
void VOutTop_T::delay_rtn(CsvAnl_C *csvi,bool flg)
  {
  int i;
  char *str;
  char *name;
  sChar *sstr;
  MEM_FP *mem_fp;
  VOutAdding_T *aa;

  sstr = new sChar("");
  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (name == NULL){name = str; continue;}
    sstr->cat(str);
    }
  if (flg){mem_fp = add_delay_fp;}
  else    {mem_fp = add_wire_fp;}

  it->srch_key = name;
  if (mem_fp->mem_srch() == 0)
    {
    aa = (VOutAdding_T *)mem_fp->mem_link_ptr_rd();
    aa->val->set(sstr->c_str());
    }
  else
    {
    it->alloc_ptr = (MM_PTR_T *)new VOutAdding_T(name,sstr->c_str());
    mem_fp->mem_srch_alloc();
    }
    
  delete sstr;
  }


// ----------------------
// #reg_type / #wire_type (Ver 1.27)
// ----------------------
void VOutTop_T::type_update_rtn(CsvAnl_C *csvi,bool flg)
  {
  int i;
  char *str;
  char *name;

  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (name == NULL){name = str; break;}
    }

  if (name == NULL){return;}

  if (flg)
    {
    v_rstate->wtype_name->set(name);
    v_con->type_name->set(name);
    }
  else
    {
    v_rstate->rtype_name->set(name);
    }

  }

// ----------------------
// #default_net/#default_gate (Ver 1.27,1.28)
// ----------------------
void VOutTop_T::def_net_rtn(CsvAnl_C *csvi,int mode)
  {
  int i;
  char *str;
  char *name;

  name = NULL;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (name == NULL){name = str; break;}
    }

  if (name == NULL){return;}

  if (mode == 0)
    {
    v_con->default_net->set(name);
    v_con->default_net_cnt = 0;
    }
  else
    {
    v_gate->sv_default_inst_cnt = v_gate->default_inst_cnt+1;
    v_gate->default_inst_cnt = -1;
    v_gate->default_inst->set(name);
    }
  }

