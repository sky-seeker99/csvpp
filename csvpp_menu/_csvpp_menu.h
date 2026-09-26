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
//---------------------------------------------------------------------------

#ifndef _csvpp_menuH
#define _csvpp_menuH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>

// tray ---
#define MYWM_NOTIFY         (WM_APP+100)
#define IDC_MYICON                     1006
extern HINSTANCE g_hinst;
LRESULT IconDrawItem(LPDRAWITEMSTRUCT lpdi);
// tray ---


//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
	TPanel *Panel1;
	TPanel *Panel2;
	TPanel *Panel3;
	TPopupMenu *PopupMenu1;
	TPopupMenu *tray_pop;
	TFontDialog *font_diag;
	TColorDialog *color_diag;
	TMenuItem *csvpp1;
	TMenuItem *excel1;
	TMenuItem *csvppini1;
	TMenuItem *stay;
	TMenuItem *excel_call_flg;
	TMenuItem *font1;
	TMenuItem *backcolor1;
	TMenuItem *csvppwork1;
	TMenuItem *menudatadir1;
	TMenuItem *version1;
	TMenuItem *Show1;
	TMenuItem *Exit1;
	TSpeedButton *SpeedButton1;
	TSpeedButton *SpeedButton2;
	TSpeedButton *SpeedButton3;
	TSpeedButton *SpeedButton4;
	TSpeedButton *SpeedButton5;
	TSpeedButton *SpeedButton6;
	TSpeedButton *SpeedButton7;
	TSpeedButton *SpeedButton8a;
	TSpeedButton *SpeedButton9;
	TComboBox *group_name;
	TListBox *list;
	TImage *Image1;
    TMenuItem *exceldir1;
	TMenuItem *versionmenu1;
	TMenuItem *console1;
	TSpeedButton *SpeedButton10;
	TMenuItem *excelinstall1;
	TMenuItem *ResetPosition1;
	void __fastcall SpeedButton5Click(TObject *Sender);
	void __fastcall SpeedButton3Click(TObject *Sender);
	void __fastcall SpeedButton4Click(TObject *Sender);
	void __fastcall listDblClick(TObject *Sender);
	void __fastcall SpeedButton6Click(TObject *Sender);
	void __fastcall SpeedButton1Click(TObject *Sender);
	void __fastcall listClick(TObject *Sender);
	void __fastcall stayClick(TObject *Sender);
	void __fastcall font1Click(TObject *Sender);
	void __fastcall backcolor1Click(TObject *Sender);
	void __fastcall version1Click(TObject *Sender);
	void __fastcall excel1Click(TObject *Sender);
	void __fastcall SpeedButton7Click(TObject *Sender);
	void __fastcall csvpp1Click(TObject *Sender);
	void __fastcall csvppini1Click(TObject *Sender);
	void __fastcall SpeedButton8Click(TObject *Sender);
	void __fastcall Show1Click(TObject *Sender);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall SpeedButton9Click(TObject *Sender);
	void __fastcall SpeedButton2Click(TObject *Sender);
	void __fastcall csvppwork1Click(TObject *Sender);
	void __fastcall menudatadir1Click(TObject *Sender);
	void __fastcall excel_call_flgClick(TObject *Sender);
	void __fastcall FormResize(TObject *Sender);
    void __fastcall exceldir1Click(TObject *Sender);
	void __fastcall versionmenu1Click(TObject *Sender);
	void __fastcall console1Click(TObject *Sender);
	void __fastcall SpeedButton8aClick(TObject *Sender);
	void __fastcall excelinstall1Click(TObject *Sender);
	void __fastcall ResetPosition1Click(TObject *Sender);
private:	// ユーザー宣言
        menu_inf *mm;
		char cmdLine[4096];
		char csvpp_version[4096];
public:		// ユーザー宣言
	__fastcall TForm1(TComponent* Owner);
	__fastcall ~TForm1();
	void __fastcall WMDropFiles(TWMDropFiles & Msg);
	sChar *readme_file;
	sChar *config_file;
	sChar *csvbat_file;
	sChar *csvpp_ini_file;
	sChar *csvpp_con_file;
	sChar *csvpp_ini_csvfile;
	sChar *excel_install_file;
	sChar *excel_install_xla_file;
	sChar *excel_install_xla_org_file;
	sChar *own_dir;
	sChar *group;
	sChar *csvpp_work;
	int list_check(char *key);
	void excel_install_rtn(void);
	void exec_rtn(char *key);
	void exec_repeat_rtn(char *key);
	void excel_rtn(char *key);
	void csvpp_ini_rtn(void);
	void csvpp_con_rtn(void);
	void group_check();
	void file_read();
	void file_write();
	void confFileRead();
	void confFileWrite();
    CsvAnl_C *csvi;
    void remote_exec_rtn();
	void __fastcall WMCopy(TMessage &Msg);
	void getVersion();

	// tray ---
	void __fastcall DrawItem(TMessage& Msg);
	void __fastcall MyNotify(TMessage& Msg);
	bool __fastcall TrayMessage(DWORD dwMessage);
	HICON __fastcall IconHandle(void);
	void __fastcall ToggleState(void);
	PSTR __fastcall TipText(void);
	// tray ---

	// Windows 終了時のルーチン
	void __fastcall	WMQueryEndSession(TWMQueryEndSession &WMQES);	//これがイベントハンドラになる




	protected:
    BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_DROPFILES, TWMDropFiles, WMDropFiles)
        MESSAGE_HANDLER(WM_DRAWITEM,TMessage,DrawItem)
		MESSAGE_HANDLER(MYWM_NOTIFY,TMessage,MyNotify)
		MESSAGE_HANDLER(WM_QUERYENDSESSION,TWMQueryEndSession,WMQueryEndSession)
        VCL_MESSAGE_HANDLER(WM_COPYDATA, TMessage, WMCopy)
    END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
