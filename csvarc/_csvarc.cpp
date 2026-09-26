/*
 * Copyright 2026 Shigeru Kasuya
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by me or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
//  Archive Command
//

#define MSG_BUFF_LEN 65536
typedef int __stdcall (*_Command_T)(const HWND hWnd,LPCSTR szCmdLine,LPSTR szOutput,const DWORD dwSize);

// interface class -----------------
class Inf_T
{

public:
  HANDLE LhaDll;
  HANDLE ZipDll;
  HANDLE TarDll;
  HANDLE RarDll;
  char msg_buff[MSG_BUFF_LEN+1];
  sChar *string;
  CsvInf_T *csvi;
  FILE     *out_fp;

HANDLE DllLoad(char *file){
  HANDLE hDll;
  hDll   = ::LoadLibrary(file);
  if (hDll == NULL){printf("Unload Archive DLL(%s)\n",file);}
  else             {printf("Load Arcive DLL(%s)\n",file);}
  return(hDll);
  }
  
void DllFree(HANDLE hDll){
  if (hDll != NULL){FreeLibrary(hDll);}
  }

Inf_T(){
  LhaDll   = DllLoad("UNLHA32.DLL");
  ZipDll   = DllLoad("ZIP32J.DLL");
  TarDll   = DllLoad("TAR32.DLL");
  RarDll   = DllLoad("unrar32.dll");
  string   = new sChar("");
  };

~Inf_T(){
  DllFree(LhaDll);
  DllFree(ZipDll);
  DllFree(TarDll);
  DllFree(RarDll);
  delete string;
  }

void Main(char *csv_file,char *log_file);
void unlha_rtn();
void unzip_rtn();
void zip_rtn();
void tar_rtn();
void rar_rtn();
void cd_rtn();
};

// ---------------
// Main
// ---------------
void Inf_T::Main(char *csv_file,char *log_file)
  {
  char *str;

  out_fp = fopen(log_file,"wt");
  csvi   = new CsvInf_T(csv_file);

  if ((out_fp == NULL) || (csvi->CsvError_Rd() != 0))
    {
    if (out_fp != NULL){fclose(out_fp);}
    else               {printf("open error.(file=%s)\n",log_file);}
    delete csvi;
    return;
    }

  printf("archive process execute %s->%s\n",csv_file,log_file);
  csvi->sp_push_set(true); // Ver 1.01
  for(;;)
    {
    if (csvi->CsvFgets() == -1) {break;}
    if (csvi->CsvSelSu_Rd() == 0) {continue;}
    if ((str = csvi->CsvSel_Rd(0)) == MM_NULL) {continue;}
    if (strcmp(str,"#lha"    )==0) {unlha_rtn  ();}
    if (strcmp(str,"#zip"    )==0) {zip_rtn    ();}
    if (strcmp(str,"#unzip"  )==0) {unzip_rtn  ();}
    if (strcmp(str,"#tar"    )==0) {tar_rtn    ();}
    if (strcmp(str,"#unrar"  )==0) {rar_rtn    ();}
    if (strcmp(str,"#cd"     )==0) {cd_rtn     ();}
    }

  delete csvi;
  fclose(out_fp);
  }

// ---------------
// #cd
// ---------------
void Inf_T::cd_rtn()
  {
  int i;
  char *str;

  string->set("");
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    string->cat(str);
    }
  SetCurrentDir (string->c_str());
  printf(">cd %s\n",string->c_str());
  fprintf(out_fp,">cd %s\n",string->c_str());
  }



// ---------------
// #rar
// ---------------
void Inf_T::rar_rtn()
  {
  int i;
  char *str;
  bool first;
  _Command_T _Command;
  bool null_flg;

  if (RarDll == NULL){return;}
  _Command = (_Command_T)::GetProcAddress(RarDll,"Unrar");
  if (_Command == NULL){return;}

  string->set("");
  first = true;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (first == true){first = false;}
    else              {string->cat(" ");}
    string->cat(str);
    }
  fprintf(out_fp,">rar %s\n",string->c_str());
  printf(">rar %s\n",string->c_str());
  _Command(NULL,string->c_str(),msg_buff,MSG_BUFF_LEN);
  null_flg = false;
  for(i=0;i<MSG_BUFF_LEN;++i)
    {
    if (*(msg_buff+i) == 0x00){null_flg = true; break;}
    }
  if (null_flg == false)
    {
    *(msg_buff + MSG_BUFF_LEN -1) = 0x00;
    }
  fprintf(out_fp,"%s\n",msg_buff);
//  printf("%s\n",msg_buff);
  }



// ---------------
// #tar
// ---------------
void Inf_T::tar_rtn()
  {
  int i;
  char *str;
  bool first;
  _Command_T _Command;
  bool null_flg;

  if (TarDll == NULL){return;}
  _Command = (_Command_T)::GetProcAddress(TarDll,"Tar");
  if (_Command == NULL){return;}

  string->set("");
  first = true;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (first == true){first = false;}
    else              {string->cat(" ");}
    string->cat(str);
    }
  fprintf(out_fp,">tar %s\n",string->c_str());
  printf(">tar %s\n",string->c_str());
  _Command(NULL,string->c_str(),msg_buff,MSG_BUFF_LEN);
  null_flg = false;
  for(i=0;i<MSG_BUFF_LEN;++i)
    {
    if (*(msg_buff+i) == 0x00){null_flg = true; break;}
    }
  if (null_flg == false)
    {
    *(msg_buff + MSG_BUFF_LEN -1) = 0x00;
    }
  fprintf(out_fp,"%s\n",msg_buff);
//  printf("%s\n",msg_buff);
  }

// ---------------
// #unzip
// ---------------
void Inf_T::unzip_rtn()
  {
  int i;
  char *str;
  bool first;
  _Command_T _Command;
  bool null_flg;

  if (ZipDll == NULL){return;}
  _Command = (_Command_T)::GetProcAddress(ZipDll,"UnZip");
  if (_Command == NULL){return;}

  string->set("");
  first = true;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (first == true){first = false;}
    else              {string->cat(" ");}
    string->cat(str);
    }
  fprintf(out_fp,">unzip %s\n",string->c_str());
  printf(">unzip %s\n",string->c_str());
  _Command(NULL,string->c_str(),msg_buff,MSG_BUFF_LEN);
  null_flg = false;
  for(i=0;i<MSG_BUFF_LEN;++i)
    {
    if (*(msg_buff+i) == 0x00){null_flg = true; break;}
    }
  if (null_flg == false)
    {
    *(msg_buff + MSG_BUFF_LEN -1) = 0x00;
    }
  fprintf(out_fp,"%s\n",msg_buff);
//  printf("%s\n",msg_buff);
  }


// ---------------
// #zip
// ---------------
void Inf_T::zip_rtn()
  {
  int i;
  char *str;
  bool first;
  _Command_T _Command;
  bool null_flg;

  if (ZipDll == NULL){return;}
  _Command = (_Command_T)::GetProcAddress(ZipDll,"Zip");
  if (_Command == NULL){return;}

  string->set("");
  first = true;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (first == true){first = false;}
    else              {string->cat(" ");}
    string->cat(str);
    }
  fprintf(out_fp,">zip %s\n",string->c_str());
  printf(">zip %s\n",string->c_str());
  _Command(NULL,string->c_str(),msg_buff,MSG_BUFF_LEN);
  null_flg = false;
  for(i=0;i<MSG_BUFF_LEN;++i)
    {
    if (*(msg_buff+i) == 0x00){null_flg = true; break;}
    }
  if (null_flg == false)
    {
    *(msg_buff + MSG_BUFF_LEN -1) = 0x00;
    }
  fprintf(out_fp,"%s\n",msg_buff);
//  printf("%s\n",msg_buff);
  }


// ---------------
// #lha
// ---------------
void Inf_T::unlha_rtn()
  {
  int i;
  char *str;
  bool first;
  _Command_T _Command;
  bool null_flg;

  if (LhaDll == NULL){return;}
  _Command = (_Command_T)::GetProcAddress(LhaDll,"Unlha");
  if (_Command == NULL){return;}

  string->set("");
  first = true;
  for(i=1;i<csvi->CsvSelSu_Rd();++i)
    {
    if ((str = csvi->CsvSel_Rd(i)) == MM_NULL) {continue;}
    if (first == true){first = false;}
    else              {string->cat(" ");}
    string->cat(str);
    }
  fprintf(out_fp,">lha %s\n",string->c_str());
  printf(">lha %s\n",string->c_str());
  _Command(NULL,string->c_str(),msg_buff,MSG_BUFF_LEN);
  null_flg = false;
  for(i=0;i<MSG_BUFF_LEN;++i)
    {
    if (*(msg_buff+i) == 0x00){null_flg = true; break;}
    }
  if (null_flg == false)
    {
    *(msg_buff + MSG_BUFF_LEN -1) = 0x00;
    }
  fprintf(out_fp,"%s\n",msg_buff);
//  printf("%s\n",msg_buff);
  }




