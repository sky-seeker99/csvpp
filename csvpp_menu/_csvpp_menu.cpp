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
//---------------------------------------------------------------------------

#include <process.h>
#include <stdio.h>
#include <dir.h>
#include <vcl.h>
#pragma hdrstop

#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\zfilename_anl.h"
#include "..\csvpp_xbase\xcsvi_anl.h"
#include "..\csvpp_xbase\xwrite64.h"

#define VERSION "CSV-Preprocessor Menu Version 1.09"

#include "menu_list.h"
#include "menu_list.cpp"
#include "_csvpp_menu.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
DragAcceptFiles(Handle, true);
AnsiString cmd;
FileNameSep_T *fn;

excel_install_xla_file = new sChar("");
excel_install_xla_org_file = new sChar("");

excel_install_file = new sChar("");
readme_file = new sChar("");
config_file = new sChar("");
csvbat_file = new sChar("");
csvpp_ini_file = new sChar("");
csvpp_con_file = new sChar("");
csvpp_ini_csvfile = new sChar("");
own_dir     = new sChar("");
group       = new sChar("default");
csvpp_work  = new sChar("");
csvi = new CsvAnl_C;

fn  = new FileNameSep_T();
cmd = ParamStr(0);
fn->Set(cmd.c_str());
config_file->cat(fn->DrvGet());
config_file->cat(fn->DirGet());
config_file->cat("csvpp_menu.csv");
csvpp_ini_file->cat(fn->DrvGet());
csvpp_ini_file->cat(fn->DirGet());
csvpp_ini_file->cat("csvpp_ini.exe");
csvpp_con_file->cat(fn->DrvGet());
csvpp_con_file->cat(fn->DirGet());
csvpp_con_file->cat("conoutwind.exe");
csvpp_ini_csvfile->cat(fn->DrvGet());
csvpp_ini_csvfile->cat(fn->DirGet());
csvpp_ini_csvfile->cat("csvpp_ini.csv");
csvbat_file->cat(fn->DrvGet());
csvbat_file->cat(fn->DirGet());
csvbat_file->cat("csv.bat");
readme_file->cat(fn->DrvGet());
readme_file->cat(fn->DirGet());
readme_file->cat("readme_csvpp.txt");
excel_install_file->cat(fn->DrvGet());
excel_install_file->cat(fn->DirGet());
excel_install_file->cat("install_csvpp.xls");
excel_install_xla_file->cat(fn->DrvGet());
excel_install_xla_file->cat(fn->DirGet());
excel_install_xla_file->cat("install_csvpp.xla");
excel_install_xla_org_file->cat(fn->DrvGet());
excel_install_xla_org_file->cat(fn->DirGet());
excel_install_xla_org_file->cat("install_csvpp_org.xla");



own_dir->cat(fn->DrvGet());
own_dir->cat(fn->DirGet());

mm = new menu_inf;
confFileRead();

getVersion();

if (list->Items->Count > 0) {
  list->ItemIndex = 0;
  list->Selected[list->ItemIndex]=1;
}

TrayMessage(NIM_ADD);
TrayMessage(NIM_MODIFY);
delete fn;
}


//---------------------------------------------------------------------------

__fastcall TForm1::~TForm1()
{
confFileWrite();
delete mm;
delete config_file;
delete csvbat_file;
delete csvpp_ini_file;
delete csvpp_con_file;
delete group;
delete own_dir;
delete csvpp_ini_csvfile;
delete csvpp_work;
delete csvi;
delete readme_file;
delete excel_install_file;
delete excel_install_xla_file;
delete excel_install_xla_org_file;

TrayMessage(NIM_DELETE);
}

void __fastcall	TForm1::WMQueryEndSession(TWMQueryEndSession &WMQES)
{
//ここにＷindows終了直前にやりたいことを書く
//最後に、Ｗindowsが終了してもいいかを指定

confFileWrite();

	WMQES.Result = TRUE;	//Ｗindowsに「終了してもいいよ」と伝える
//	WMQES.Result = FALSE;	//Ｗindowsの終了を禁止する
}








void __fastcall TForm1::WMDropFiles(TWMDropFiles & Msg)
{
  group_check();
  char Buff[MAX_PATH]; //ファイル名
  int Count; //Dropされたファイル数

  Count = DragQueryFile((void*)Msg.Drop, -1, NULL, NULL ); //ファイルの数を得る
  for (int i = 0; i < Count; i++) {  //ファイルの数だけ繰り返す
    DragQueryFile((void*)Msg.Drop, i, Buff, sizeof(Buff)); //i番目のファイル名をBuffに格納
    char *key = mm->add_cel(Buff);
    if (list_check(key) < 0){
      list->Items->Add(key);
      list->ItemIndex = list->Items->Count-1;
    }
  }


  DragQueryFile((void*)Msg.Drop, 0, Buff, sizeof(Buff));
  DragFinish((void*)Msg.Drop); //終了処理
  TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------
int TForm1::list_check(char *key)
{
group_check();
  int hit = -1;
  for(int k=0;k<list->Items->Count;k++){
    if (strcmp(list->Items->Strings[k].c_str(),key) == 0){
      hit = k;
      list->ItemIndex = k;
      break;
    }
  }
  return(hit);
}







void __fastcall TForm1::SpeedButton5Click(TObject *Sender)
{
  int sv = list->ItemIndex;
  for(int k=list->Items->Count-1;k>=0;k--){
    if (list->Selected[k]){
      mm->delete_cel(list->Items->Strings[k].c_str());
      list->Items->Delete(k);
    }
  }
  if (sv > list->Items->Count-1) {
	sv = list->Items->Count-1;
  }
  list->Selected[sv]=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
group_check();
if (list->ItemIndex <= 0){return;}
String sv = list->Items->Strings[list->ItemIndex-1];
list->Items->Strings[list->ItemIndex-1] = list->Items->Strings[list->ItemIndex];
list->Items->Strings[list->ItemIndex]   = sv;
list->ItemIndex--;
list->Selected[list->ItemIndex]=1;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
group_check();
if (list->ItemIndex >= list->Items->Count-1){return;}
String sv = list->Items->Strings[list->ItemIndex+1];
list->Items->Strings[list->ItemIndex+1] = list->Items->Strings[list->ItemIndex];
list->Items->Strings[list->ItemIndex]   = sv;
list->ItemIndex++;
list->Selected[list->ItemIndex]=1;
}
//---------------------------------------------------------------------------

void TForm1::exec_rtn(char *key)
{
group_check();
    char *path = mm->srch_cel(key);
    if (path == NULL){return;}
    sprintf(cmdLine,"/C \"\"%s\" \"%s\"\"",csvbat_file->c_str(),path);
    ShellExecute(NULL,NULL,"cmd",cmdLine,NULL,SW_SHOWNORMAL);
}

void TForm1::exec_repeat_rtn(char *key)
{
group_check();
    char *path = mm->srch_cel(key);
    if (path == NULL){return;}
    sprintf(cmdLine,"\"\"%s\" \"%s\"\"",csvbat_file->c_str(),path);
    system(cmdLine);
}

void TForm1::excel_rtn(char *key)
{
group_check();
    char *path = mm->srch_cel(key);
    if (path == NULL){return;}
    if (excel_call_flg->Checked)
      {
      ShellExecute(NULL,NULL,path,NULL,NULL,SW_SHOWNORMAL);
      }
    else
      {
      sprintf(cmdLine,"\"%s\"",path);
      ShellExecute(NULL,NULL,cmdLine,NULL,NULL,SW_SHOWNORMAL);
      }
}

void TForm1::csvpp_ini_rtn(void)
{
group_check();
    sprintf(cmdLine,"\"%s\"",csvpp_ini_file->c_str());
    ShellExecute(NULL,NULL,cmdLine,NULL,NULL,SW_SHOWNORMAL);
}

void TForm1::excel_install_rtn(void)
{
group_check();
	FILE *n = fopen(excel_install_xla_file->c_str(),"wt");
	fclose(n);

	Read64_C *in_fp = new Read64_C(excel_install_xla_org_file->c_str(),"rb",10240);
	Write64_C *out_fp = new Write64_C(excel_install_xla_file->c_str(),"wb",10240);

	for(;;){
	  unsigned char c;
	  if (in_fp->read(&c,1) == 0){break;}
	  out_fp->write(&c,1);
	}
	delete in_fp;
	delete out_fp;

	sprintf(cmdLine,"\"%s\"",excel_install_file->c_str());
	ShellExecute(NULL,NULL,cmdLine,NULL,NULL,SW_SHOWNORMAL);
}


void TForm1::csvpp_con_rtn(void)
{
group_check();
	sprintf(cmdLine,"\"%s\"",csvpp_con_file->c_str());
	ShellExecute(NULL,NULL,cmdLine,NULL,NULL,SW_SHOWNORMAL);

	Read64_C *in_fp = new Read64_C(csvpp_ini_csvfile->c_str(),"rt",10240);
    bool hit = false;
	for(;;){
	  char *buff = in_fp->read();
	  if (buff == NULL) {
		  break;
	  }
	  if (strcmp(buff,"csvpp_menu write.")==0) {
		hit = true;
		break;
	  }
	}

	delete in_fp;

	if (hit == false) {
	  FILE *out_fp = fopen(csvpp_ini_csvfile->c_str(),"at");
	  fprintf(out_fp,"#logwin_flg,1\n");
	  fprintf(out_fp,"csvpp_menu write.\n");
	  fclose(out_fp);
	}
}




void __fastcall TForm1::listDblClick(TObject *Sender)
{
exec_rtn(list->Items->Strings[list->ItemIndex].c_str());
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton6Click(TObject *Sender)
{
  for(int k=0;k<list->Items->Count;k++){
    if (list->Selected[k]){
      exec_repeat_rtn(list->Items->Strings[k].c_str());
    }
  }
}
//---------------------------------------------------------------------------
void TForm1::group_check()
{
  if (strcmp(group_name->Text.c_str(),group->c_str()) != 0)
  {
    group_name->Text = group->c_str();
    //group_name->Width = group_name->Text.Length() * 7+30;
  }
}


void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
  int hit = -1;
  for(int k=0;k<group_name->Items->Count;k++){
    if (strcmp(group_name->Items->Strings[k].c_str(),group->c_str()) == 0){
      hit = k;
      break;
    }
  }
  if (hit == -1){
    group_name->Items->Add(group->c_str());
  }
list->ShowHint = false;
file_write();
group->set(group_name->Text.c_str());
list->Items->Clear();
mm->all_clear();
file_read();

if (list->Items->Count > 0) {
  list->ItemIndex = 0;
  list->Selected[list->ItemIndex]=1;
}

}
//---------------------------------------------------------------------------

void __fastcall TForm1::listClick(TObject *Sender)
{
group_check();

char *path = mm->srch_cel(list->Items->Strings[list->ItemIndex].c_str());
list->Hint = path;
list->ShowHint = true;

}
//---------------------------------------------------------------------------
void TForm1::file_read()
{
sChar *file = new sChar(own_dir);
file->cat(group->c_str());
file->cat("##.csv");
CsvInf_T *csvinf = new CsvInf_T(file->c_str());
char *str;
if (csvinf->CsvError_Rd() != 0){delete file; delete csvinf; return;}
for(;;)
  {
  if (csvinf->CsvFgets() == -1){break;}
  if (csvinf->CsvSelSu_Rd() == 0) {continue;}
  if ((str = csvinf->CsvSel_Rd(0)) == NULL) {continue;}
  char *w_str = csvinf->CsvSel_Rd(1);
  sp_push(str);    sp_push2(str);
  sp_push(w_str);  sp_push2(w_str);
  if (mm->file_read(csvinf)){continue;}
  if (strcmp(str,"#key") == 0){list->Items->Add(w_str); continue;}
  }
delete file;
delete csvinf;
}
//---------------------------------------------------------------------------
void TForm1::file_write()
{
  sChar *file = new sChar(own_dir);
  file->cat(group->c_str());
  file->cat("##.csv");
  FILE *fp = fopen(file->c_str(),"wt");
  if (fp == NULL){return;}
  for(int k=0;k<list->Items->Count;k++){
      fprintf(fp,"#key,%s\n",list->Items->Strings[k].c_str());
    }
  mm->file_write(fp);
  fclose(fp);
  delete file;
}
//---------------------------------------------------------------------------
void TForm1::confFileRead()
  {
  CsvInf_T *csvinf = new CsvInf_T(config_file->c_str());
  char *str;

  if (csvinf->CsvError_Rd() == 0)
    {
    for(;;)
      {
      if (csvinf->CsvFgets() == -1){break;}
      if (csvinf->CsvSelSu_Rd() == 0) {continue;}
      if ((str = csvinf->CsvSel_Rd(0)) == NULL) {continue;}
      char *w_str = csvinf->CsvSel_Rd(1);
      sp_push(str);
      sp_push2(str);
      if (strcmp(str,"#group"     ) == 0){group->set(w_str);  group_name->Text = w_str; continue;}
      if (strcmp(str,"#group_hist") == 0){group_name->Items->Add(w_str); continue;}
      if (strcmp(str,"#height"    ) == 0){Height       = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#width"     ) == 0){Width        = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#top"       ) == 0){Top          = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#left"      ) == 0){Left         = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#font_size" ) == 0)
        {
        list->Font->Size = SujiConvEx(w_str);
        continue;
        }
      if (strcmp(str,"#back_color" ) == 0)
        {
        int ii = SujiConvEx(w_str);
        if (ii < 0){ii = 16777215;}
        list->Color = (TColor)ii;
        continue;
        }
      if (strcmp(str,"#font_color" ) == 0)
        {
        int ii = SujiConvEx(w_str);
        if (ii < 0){ii = 0;}
        list->Font->Color = (TColor)ii;
        continue;
        }
      if (strcmp(str,"#font_name") == 0)
        {
        list->Font->Name = w_str;
        continue;
        }
      if (strcmp(str,"#stay"      ) == 0)
        {
        if (strcmp(w_str,"0") == 0){stay->Checked = false; FormStyle = fsNormal;}
        else                       {stay->Checked = true;  FormStyle = fsStayOnTop;}
        continue;
        }
      if (strcmp(str,"#excel_call"      ) == 0)
        {
        if (strcmp(w_str,"0") == 0){excel_call_flg->Checked = false; }
        else                       {excel_call_flg->Checked = true;  }
        continue;
        }
      }
    }

  delete csvinf;
  csvinf = new CsvInf_T(csvpp_ini_csvfile->c_str());
  if (csvinf->CsvError_Rd() == 0)
    {
    for(;;)
      {
      if (csvinf->CsvFgets() == -1){break;}
      if (csvinf->CsvSelSu_Rd() == 0) {continue;}
      if ((str = csvinf->CsvSel_Rd(0)) == NULL) {continue;}
      char *w_str = csvinf->CsvSel_Rd(1);
      sp_push(str);
      sp_push2(str);
      if (strcmp(str,"#work_drv") == 0)
        {
        csvpp_work->set(w_str);
        csvpp_work->cat(":");
        continue;
        }
      if (strcmp(str,"#work_dir") == 0)
        {
        csvpp_work->cat("\\");
        csvpp_work->cat(w_str);
        continue;
        }
      }
    }



  file_read();
  DragAcceptFiles(Handle, true);
  delete csvinf;
  }



//---------------------------------------------------------------------------
// # config file write #####
void TForm1::confFileWrite()
  {
  FILE *fp;
  fp = fopen(config_file->c_str(),"wt");

  fprintf(fp,"#group,%s\n",group->c_str());
  for(int k=0;k<group_name->Items->Count;k++){
    fprintf(fp,"#group_hist,%s\n",group_name->Items->Strings[k].c_str());
  }
  fprintf(fp,"#height,%d\n",Height);
  fprintf(fp,"#width,%d\n",Width);
  fprintf(fp,"#top,%d\n",Top);
  fprintf(fp,"#left,%d\n",Left);
  fprintf(fp,"#back_color,%d\n",list->Color );
  fprintf(fp,"#font_color,%d\n",list->Font->Color );
  fprintf(fp,"#font_style,%d\n",list->Font->Style );
  fprintf(fp,"#font_size,%d\n",list->Font->Size );
  fprintf(fp,"#font_name,%s\n",list->Font->Name.c_str());
  if (stay->Checked){fprintf(fp,"#stay,1\n");}
  else              {fprintf(fp,"#stay,0\n");}
  if (excel_call_flg->Checked){fprintf(fp,"#excel_call,1\n");}
  else                        {fprintf(fp,"#excel_call,0\n");}

  fclose(fp);
  file_write();
  }



void __fastcall TForm1::stayClick(TObject *Sender)
{
 if (stay->Checked){stay->Checked = false; FormStyle = fsNormal;}
 else              {stay->Checked = true;  FormStyle = fsStayOnTop;}
 DragAcceptFiles(Handle, true);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::font1Click(TObject *Sender)
{
font_diag->Font = list->Font;
if (font_diag->Execute() == false){return;}
list->Font = font_diag->Font;
Visible = false;
Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::backcolor1Click(TObject *Sender)
{
color_diag->Color = list->Color;
if (color_diag->Execute() == false){return;}
list->Color = color_diag->Color;
Visible = false;
Visible = true;
}
//---------------------------------------------------------------------------

void TForm1::getVersion(){
Read64_C *in_fp = new Read64_C(readme_file->c_str(),"rt",10240);

sCharGrep *grep = new sCharGrep("");
strcpy(csvpp_version,"CSV-Preprocessor Language System Version ???");

for(;;){
  char *buff = in_fp->read();
  if (buff == NULL) {
	break;
  }
  if (*buff == 0x00) {continue;}
  if (*buff == ' ' ) {continue;}
  grep->set(buff);
  int ptr = grep->grep("->",0);
  if (ptr < 0) {continue;}
  sprintf(csvpp_version,"CSV-Preprocessor Language System Version %s",buff+ptr+2);
  }
delete in_fp;
delete grep;
}


void __fastcall TForm1::version1Click(TObject *Sender)
{
MessageDlg(csvpp_version, mtInformation	,TMsgDlgButtons() << mbOK, 0);
}



//---------------------------------------------------------------------------

void __fastcall TForm1::excel1Click(TObject *Sender)
{
  for(int k=0;k<list->Items->Count;k++){
    if (list->Selected[k]){
      excel_rtn(list->Items->Strings[k].c_str());
    }
  }
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton7Click(TObject *Sender)
{
  for(int k=0;k<list->Items->Count;k++){
    if (list->Selected[k]){
      excel_rtn(list->Items->Strings[k].c_str());
    }
  }	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::csvpp1Click(TObject *Sender)
{
  for(int k=0;k<list->Items->Count;k++){
    if (list->Selected[k]){
      exec_repeat_rtn(list->Items->Strings[k].c_str());
    }
  }	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::csvppini1Click(TObject *Sender)
{
csvpp_ini_rtn();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8Click(TObject *Sender)
{
csvpp_ini_rtn();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::DrawItem(TMessage& Msg)
{
     IconDrawItem((LPDRAWITEMSTRUCT)Msg.LParam);
     TForm::Dispatch(&Msg);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::MyNotify(TMessage& Msg)
{
    POINT MousePos;

    switch(Msg.LParam)
    {

        case WM_RBUTTONUP:
            if (GetCursorPos(&MousePos))
            {
            tray_pop->PopupComponent = Form1;
            //SetForegroundWindow(Handle);
            tray_pop->Popup(MousePos.x, MousePos.y);
            }
            break;

        case WM_LBUTTONUP:
             if (Visible)
               {
               Hide();
             //  confFileWrite();
               }
             else
               {
               SetForegroundWindow(Handle);
               Show();
               }
           break;
        default:
           break;
    }
    TForm::Dispatch(&Msg);
}


//---------------------------------------------------------------------------
bool __fastcall TForm1::TrayMessage(DWORD dwMessage)
{
   NOTIFYICONDATA tnd;
   PSTR pszTip;

   pszTip = TipText();

   tnd.cbSize          = sizeof(NOTIFYICONDATA);
   tnd.hWnd            = Handle;
   tnd.uID             = IDC_MYICON;
   tnd.uFlags          = NIF_MESSAGE | NIF_ICON | NIF_TIP;
   tnd.uCallbackMessage	= MYWM_NOTIFY;

   if (dwMessage == NIM_MODIFY)
    {
        tnd.hIcon		= (HICON)IconHandle();
        if (pszTip)
           lstrcpyn(tnd.szTip, pszTip, sizeof(tnd.szTip));
	    else
        tnd.szTip[0] = '\0';
    }
   else
    {
        tnd.hIcon = NULL;
        tnd.szTip[0] = '\0';
    }

   return (Shell_NotifyIcon(dwMessage, &tnd));
}

//---------------------------------------------------------------------------
HICON __fastcall TForm1::IconHandle(void)
{
        return (Image1->Picture->Icon->Handle);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ToggleState(void)
{
    TrayMessage(NIM_MODIFY);
}
//---------------------------------------------------------------------------
PSTR __fastcall TForm1::TipText(void)
{
       return(csvpp_version);
}
//---------------------------------------------------------------------------

LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi)
{
	HICON hIcon;

	hIcon = (HICON)LoadImage(g_hinst, MAKEINTRESOURCE(lpdi->CtlID), IMAGE_ICON,
		16, 16, 0);
	if (!hIcon)
		return(FALSE);

	DrawIconEx(lpdi->hDC, lpdi->rcItem.left, lpdi->rcItem.top, hIcon,
		16, 16, 0, NULL, DI_NORMAL);

	return(TRUE);
}



void __fastcall TForm1::Show1Click(TObject *Sender)
{
               SetForegroundWindow(Handle);
               Show();
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Exit1Click(TObject *Sender)
{
exit(0);        
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton9Click(TObject *Sender)
{
  ShellExecute(NULL,NULL,csvpp_work->c_str(),NULL,NULL,SW_SHOWNORMAL);
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
               Hide();
            //   confFileWrite();	
}
//---------------------------------------------------------------------------


void __fastcall TForm1::csvppwork1Click(TObject *Sender)
{
   ShellExecute(NULL,NULL,csvpp_work->c_str(),NULL,NULL,SW_SHOWNORMAL);
	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::menudatadir1Click(TObject *Sender)
{
  ShellExecute(NULL,NULL,own_dir->c_str(),NULL,NULL,SW_SHOWNORMAL);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::excel_call_flgClick(TObject *Sender)
{
 if (excel_call_flg->Checked){excel_call_flg->Checked = false; }
 else                        {excel_call_flg->Checked = true;  }

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
group_name->Width = Form1->Width - 30;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::exceldir1Click(TObject *Sender)
{
group_check();

char *path = mm->srch_cel(list->Items->Strings[list->ItemIndex].c_str());
FileNameSep_T *fn;
fn  = new FileNameSep_T();
sChar *dir = new sChar("");
fn->Set(path);

dir->cat(fn->DrvGet());
dir->cat(fn->DirGet());

ShellExecute(NULL,NULL,dir->c_str(),NULL,NULL,SW_SHOWNORMAL);
delete fn;
delete dir;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::WMCopy(TMessage &Msg)
{
    COPYDATASTRUCT *copydata;
    copydata = (COPYDATASTRUCT*)Msg.LParam;

    AnsiString s = (char *)copydata->lpData;
    csvi->Exec(s.c_str());
    CSV_LOOP(csvi,ustr,SP_PUSH)
      char *str = (char *)ustr;
      if (strcmp(str,"#exec") == 0){remote_exec_rtn(); continue;}
    LOOP_END
}

void TForm1::remote_exec_rtn(){
    char *p0=NULL;
    char *p1=NULL;

    CSV_LOOP(csvi,ustr,SP_PUSH)
      char *str = (char *)ustr;
      if (p0 == NULL) {p0 = str; continue;}
      if (p1 == NULL) {p1 = str; continue;}
    LOOP_END

    if (p0==NULL) {
        return;
    }
    if (p1==NULL) {
      sprintf(cmdLine,"/C \"\"%s\" \"%s\"\"",csvbat_file->c_str(),p0);
      ShellExecute(NULL,NULL,"cmd",cmdLine,NULL,SW_SHOWNORMAL);
    }
    else {
      sprintf(cmdLine,"/C \"\"%s\" \"%s\" \"%s\"\"",csvbat_file->c_str(),p0,p1);
      ShellExecute(NULL,NULL,"cmd",cmdLine,NULL,SW_SHOWNORMAL);
    }




}

void __fastcall TForm1::versionmenu1Click(TObject *Sender)
{
MessageDlg(VERSION, mtInformation	,TMsgDlgButtons() << mbOK, 0);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::console1Click(TObject *Sender)
{
csvpp_con_rtn();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton8aClick(TObject *Sender)
{
csvpp_con_rtn();	
}
//---------------------------------------------------------------------------

void __fastcall TForm1::excelinstall1Click(TObject *Sender)
{
excel_install_rtn();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ResetPosition1Click(TObject *Sender)
{
Top=0;
Left=0;
}
//---------------------------------------------------------------------------

