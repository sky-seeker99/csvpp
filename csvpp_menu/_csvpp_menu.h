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
