//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>


#include "..\csvpp_xbase\ztool.h"
#include "..\csvpp_xbase\xread64.h"
#include "..\csvpp_xbase\xcsvi_anl.h"
#include "..\csvpp_xbase\xexec.h"


#include "_csvpp_ini.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
  String str;
  String str2;
  str = ParamStr(0);
  str2 = ParamStr(1);
  int len = strlen(str.c_str());
  dir = new char[len+1];
  strcpy(dir,str.c_str());

  pg_exec = new PgExec_C;
  pg_exec->dirSet(str.c_str());
  for(int i=len-1;i>=0;--i)
    {
    if (*(dir+i) == '\\'){*(dir+i) = 0x00; break;}
    }
  read_file();
  update();

  if (strcmp(str2.c_str(),"-c") == 0){
    tim->Enabled = true;
  }

}
//---------------------------------------------------------------------------
__fastcall TForm1::~TForm1()
  {
  delete [] dir;
  delete pg_exec;
  }

void TForm1::ppush(char *p_str){
  char *str,*str2;

  str  = p_str;
  str2 = p_str;
  for(;;str++){
    if (*str == 0x00){break;}
    if (*str == 0x20){continue;}
    *str2++ = *str;
    }
  *str2 = 0x00;

}

void TForm1::update(){
char buff[4096];
char buff2[4096];
char buff3[4096];
char buff4[10];
char buff5[4096];
int i;

batFile->Lines->Clear();

sprintf(buff,"%s:",WorkDrv->Text.c_str());
//batFile->Lines->Strings[0] = buff;
batFile->Lines->Add(buff);

sprintf(buff,"cd \\");
//batFile->Lines->Strings[1] = buff;
batFile->Lines->Add(buff);

sprintf(buff,"mkdir %s",WorkDir->Text.c_str());
//batFile->Lines->Strings[2] = buff;
batFile->Lines->Add(buff);

sprintf(buff,"del %s:\\%s\\*.csv",WorkDrv->Text.c_str(),WorkDir->Text.c_str());
//batFile->Lines->Strings[3] = buff;
batFile->Lines->Add(buff);

pg_exec->prmInit();
if (csvmake_o_p->Checked){
  pg_exec->prmSet("csvmake_ooo.exe");
  pg_exec->prmSet("%1");
  sprintf(buff,"%s:\\%s",WorkDrv->Text.c_str(),WorkDir->Text.c_str());
  pg_exec->prmSet(buff);
  pg_exec->prmSet(filter_prg->Text.c_str());
  pg_exec->prmSet(filter_ext->Text.c_str());
}
else {
  pg_exec->prmSet("csvmake.exe");
  pg_exec->prmSet("%1");
  sprintf(buff,"%s:\\%s",WorkDrv->Text.c_str(),WorkDir->Text.c_str());
  pg_exec->prmSet(buff);
  if (tmp->Checked ){pg_exec->prmSet("-tmp");}
  if (proc->Checked){pg_exec->prmSet("-proc");}
  pg_exec->prmSet(filter_prg->Text.c_str());
  pg_exec->prmSet(filter_ext->Text.c_str());
}
//batFile->Lines->Strings[4] = pg_exec->getCommand();
batFile->Lines->Add(pg_exec->getCommand());

sprintf(buff2,"-i%s:\\%s",WorkDrv->Text.c_str(),WorkDir->Text.c_str());
for(i=0;i<inc_list->Lines->Count;i++)
  {
  strcat(buff2,";");
  strcat(buff2,inc_list->Lines->Strings[i].c_str());
  }

strcpy(buff3,"-down_xls=%1");
if (csvmake_o_p->Checked){
  strcat(buff3,";office=open");
}
else {
  strcat(buff3,";office=ms");
}
sprintf(buff5,";tmpdir=%s:\\%s",WorkDrv->Text.c_str(),WorkDir->Text.c_str());
strcat(buff3,buff5);
for(i=0;i<env_list->Lines->Count;i++)
  {
  strcat(buff3,";");
  strcat(buff3,env_list->Lines->Strings[i].c_str());
  }

ppush(buff2);
ppush(buff3);
pg_exec->prmInit();
pg_exec->prmSet("csvpp.exe");
sprintf(buff,"%s:\\%s\\cmd.csv",WorkDrv->Text.c_str(),WorkDir->Text.c_str());
pg_exec->prmSet(buff);
pg_exec->prmSet(buff2);
pg_exec->prmSet(buff3);
if (proc->Checked       ){pg_exec->prmSet("-p");}
if (sp_push_flg->Checked){pg_exec->prmSet("-s");}
if (csvmake_o_p->Checked){pg_exec->prmSet("-o");}
if (csvfront->Checked   ){pg_exec->prmSet("-f%1");}
if (log->Checked){
  pg_exec->prmSet(">");
  pg_exec->prmSet(logFile->Text.c_str());
}
if (pipe->Checked){
  pg_exec->prmSet("|");
  pg_exec->prmSet("pipe");
  pg_exec->prmSet(logFile->Text.c_str());
}
if (logWin->Checked){
  pg_exec->prmSet("|");
  pg_exec->prmSet("conoutGet");
}

//batFile->Lines->Strings[5] = pg_exec->getCommand();
batFile->Lines->Add(pg_exec->getCommand());

strcpy(buff,"%2");
//batFile->Lines->Strings[6] = buff;
batFile->Lines->Add(buff);


if (stpp->Checked)
  {
  strcpy(buff,"pause");
  }
else
  {
  buff[0] = 0x00;
  }

//batFile->Lines->Strings[7] = buff;
batFile->Lines->Add(buff);

}

bool TForm1::boolSet(char *str)
  {
  if (strcmp(str,"1") == 0){return(true);}
  return(false);
  }

void TForm1::read_file()
  {
  sChar *file_name = new sChar(dir);
  file_name->cat("\\csvpp_ini.csv");
  Read64_C *fp = new Read64_C(file_name->c_str(),"rt",10240);
  if (fp->okCheck() == false){delete file_name; delete fp; return;}
  CsvAnl_C *csvi = new CsvAnl_C;
  TEXT_READ_LOOP(fp,buff)
    csvi->Exec(buff);
    char *cmd=NULL;
    char *data=NULL;

    CSV_LOOP_(csvi,str,SP_PUSH)
      if (cmd  == NULL) {cmd  = str; continue;}
      if (data == NULL) {data = str; continue;}
    LOOP_END
    if (data == NULL) {continue;}

    // data set
//    if (strcmp(cmd,"#height"    ) == 0){Height       = SujiConvEx(data); continue;}
//    if (strcmp(cmd,"#width"     ) == 0){Width        = SujiConvEx(data); continue;}
//    if (strcmp(cmd,"#top"       ) == 0){Top          = SujiConvEx(data); continue;}
//    if (strcmp(cmd,"#left"      ) == 0){Left         = SujiConvEx(data); continue;}

    if (strcmp(cmd,"#filter"      ) == 0){filter_prg->Text     = data;}
    if (strcmp(cmd,"#filter_ext"  ) == 0){filter_ext->Text     = data;}
    if (strcmp(cmd,"#work_drv"    ) == 0){WorkDrv->Text     = data;}
    if (strcmp(cmd,"#work_dir"    ) == 0){WorkDir->Text     = data;}
    if (strcmp(cmd,"#pause_flg"   ) == 0){stpp->Checked     = boolSet(data);}
    if (strcmp(cmd,"#csvfront_flg") == 0){csvfront->Checked = boolSet(data);}
    if (strcmp(cmd,"#log_flg"     ) == 0){log->Checked      = boolSet(data);}
    if (strcmp(cmd,"#logwin_flg"  ) == 0){logWin->Checked   = boolSet(data);}
    if (strcmp(cmd,"#pipe_flg"    ) == 0){pipe->Checked     = boolSet(data);}
    if (strcmp(cmd,"#sp_push_flg" ) == 0){sp_push_flg->Checked     = boolSet(data);}
    if (strcmp(cmd,"#log_file"    ) == 0){logFile->Text     = data;}
//    if (strcmp(cmd,"#var_len"     ) == 0){varLen->Text      = data; varLenFlg->Checked = true;}
    if (strcmp(cmd,"#env"         ) == 0){env_list->Lines->Add(data);}
    if (strcmp(cmd,"#include"     ) == 0){inc_list->Lines->Add(data);}
    if (strcmp(cmd,"#csvmake_o_flg")== 0){csvmake_o_p->Checked = boolSet(data);}
    if (strcmp(cmd,"#tmp_flg")== 0){tmp->Checked = boolSet(data);}
    if (strcmp(cmd,"#proc_flg")== 0){proc->Checked = boolSet(data);}

  LOOP_END
  delete csvi;
  delete fp;
  delete file_name;
  }

void TForm1::update_file()
  {
  char *file_name;
  file_name = new char[strlen(dir)+20];
  strcpy(file_name,dir);
  strcat(file_name,"\\csv.bat");
  FILE *fp;
  fp = fopen(file_name,"wt");

  for(int i=0;i<batFile->Lines->Count;i++)
    {
    fprintf(fp,"%s\n",batFile->Lines->Strings[i].c_str());
    }
  fclose(fp);

  strcpy(file_name,dir);
  strcat(file_name,"\\csvpp_ini.csv");
  fp = fopen(file_name,"wt");

  fprintf(fp,"#height,%d\n",Height);
  fprintf(fp,"#width,%d\n",Width);
  fprintf(fp,"#top,%d\n",Top);
  fprintf(fp,"#left,%d\n",Left);

  fprintf(fp,"#filter,%s\n",filter_prg->Text.c_str());
  fprintf(fp,"#filter_ext,%s\n",filter_ext->Text.c_str());

  fprintf(fp,"#work_drv,%s\n",WorkDrv->Text.c_str());
  fprintf(fp,"#work_dir,%s\n",WorkDir->Text.c_str());
  fprintf(fp,"#pause_flg,%d\n",stpp->Checked);
  fprintf(fp,"#csvfront_flg,%d\n",csvfront->Checked);
  fprintf(fp,"#log_flg,%d\n",log->Checked);
  fprintf(fp,"#logwin_flg,%d\n",logWin->Checked);
  fprintf(fp,"#pipe_flg,%d\n",pipe->Checked);
  fprintf(fp,"#sp_push_flg,%d\n",sp_push_flg->Checked);
  fprintf(fp,"#csvmake_o_flg,%d\n",csvmake_o_p->Checked);
  fprintf(fp,"#log_file,%s\n",logFile->Text.c_str());
  fprintf(fp,"#tmp_flg,%d\n",tmp->Checked);
  fprintf(fp,"#proc_flg,%d\n",proc->Checked);

/*  if (varLenFlg->Checked){
    fprintf(fp,"#var_len,%s\n",varLen->Text.c_str());
    }
*/
  for(int i=0;i<inc_list->Lines->Count;i++)
    {
    fprintf(fp,"#include,%s\n",inc_list->Lines->Strings[i].c_str());
    }

  for(int i=0;i<env_list->Lines->Count;i++)
    {
    fprintf(fp,"#env,%s\n",env_list->Lines->Strings[i].c_str());
    }

  fclose(fp);
  delete [] file_name;
  }

void __fastcall TForm1::WorkDrvChange(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::WorkDirChange(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::stppClick(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::csvmake_o_pClick(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::csvfrontClick(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::procClick(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::tmpClick(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::logClick(TObject *Sender)
{
if (log->Checked){pipe->Checked = false; logWin->Checked = false;}
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::pipeClick(TObject *Sender)
{
if (pipe->Checked){log->Checked = false; logWin->Checked = false;}
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::logWinClick(TObject *Sender)
{
if (logWin->Checked){pipe->Checked = false; log->Checked = false;}
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::logFileChange(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::sp_push_flgClick(TObject *Sender)
{
update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::filter_prgChange(TObject *Sender)
{
  update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::filter_extChange(TObject *Sender)
{
  update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::env_listChange(TObject *Sender)
{
  update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::inc_listChange(TObject *Sender)
{
  update();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
update();
update_file();	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
update();
update_file();
exit(0);
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
exit(0);	
        
}
//---------------------------------------------------------------------------
void __fastcall TForm1::timTimer(TObject *Sender)
{
update_file();
exit(0);
}
//---------------------------------------------------------------------------

