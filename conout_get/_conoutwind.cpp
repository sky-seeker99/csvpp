/*

 * Copyright (c) 2009 Shigeru Kasuya (sky_seeker99@users.sourceforge.jp)
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

#include <stdio.h>
#include "..\csvpp_xbase\zcsvfile.h"
#include "..\csvpp_xbase\zfilename_anl.h"
#define VERSION "Console output Get Window Ver 0.93"

#include "_conoutwind.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
AnsiString cmd;
FileNameSep_T *fn;
fn  = new FileNameSep_T();

cmd = ParamStr(0);
fn->Set(cmd.c_str());

config_file = new sChar("");
config_file->cat(fn->DrvGet());
config_file->cat(fn->DirGet());
config_file->cat("conoutwind.csv");

delete fn;
confFileRead();
memo->Lines->Add(VERSION);
memo->Lines->Add("Ready OK.");

}

__fastcall TForm1::~TForm1(){
confFileWrite();
delete config_file;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::WMCopy(TMessage &Msg)
{
    COPYDATASTRUCT *copydata;
    copydata = (COPYDATASTRUCT*)Msg.LParam;

    AnsiString s = (char *)copydata->lpData;
    memo->Lines->Add(s);
    if (clrFlg->Checked) {
      if (s == "-->") {
         memo->Lines->Clear();  
      } 
    }

}

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
      if (strcmp(str,"#height"    ) == 0){Height       = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#width"     ) == 0){Width        = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#top"       ) == 0){Top          = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#left"      ) == 0){Left         = SujiConvEx(w_str); continue;}
      if (strcmp(str,"#font_size" ) == 0)
        {
        memo->Font->Size = SujiConvEx(w_str);
        continue;
        }
      if (strcmp(str,"#font_style" ) == 0)
        {
        memo->Font->Style = (TFontStyles)SujiConvEx(w_str);
        continue;
        }
      if (strcmp(str,"#back_color" ) == 0)
        {
        int ii = SujiConvEx(w_str);
        if (ii < 0){ii = 16777215;}
        memo->Color = (TColor)ii;
        continue;
        }
      if (strcmp(str,"#font_color" ) == 0)
        {
        int ii = SujiConvEx(w_str);
        if (ii < 0){ii = 0;}
        memo->Font->Color = (TColor)ii;
        continue;
        }
      if (strcmp(str,"#font_name") == 0)
        {
        memo->Font->Name = w_str;
        continue;
        }
      if (strcmp(str,"#clear") == 0)
        {
        clrFlg->Checked = SujiConvEx(w_str);
        continue;
        }
	  }
    }
  delete csvinf;


  }

// # config file write #####
void TForm1::confFileWrite()
  {
  FILE *fp = fopen(config_file->c_str(),"wt");

  fprintf(fp,"#height,%d\n",Height);
  fprintf(fp,"#width,%d\n",Width);
  fprintf(fp,"#top,%d\n",Top);
  fprintf(fp,"#left,%d\n",Left);
  fprintf(fp,"#back_color,%d\n",memo->Color );
  fprintf(fp,"#font_color,%d\n",memo->Font->Color );
  fprintf(fp,"#font_style,%d\n",memo->Font->Style );
  fprintf(fp,"#font_size,%d\n",memo->Font->Size );
  fprintf(fp,"#font_name,%s\n",memo->Font->Name.c_str());
  fprintf(fp,"#clear,%d\n",clrFlg->Checked );

  fclose(fp);
  }
void __fastcall TForm1::Button1Click(TObject *Sender)
{
memo->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BackcolorClick(TObject *Sender)
{
color_diag->Color = memo->Color;
if (color_diag->Execute() == false){return;}
memo->Color = color_diag->Color;
Form1->Visible = false;
Form1->Visible = true;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FontClick(TObject *Sender)
{
font_diag->Font = memo->Font;
if (font_diag->Execute() == false){return;}
memo->Font = font_diag->Font;	
Form1->Visible = false;
Form1->Visible = true;    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  if (save_di->Execute() == false){return;}
  memo->Lines->SaveToFile(save_di->FileName.c_str());

}
//---------------------------------------------------------------------------

