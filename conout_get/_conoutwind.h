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

#ifndef _conoutwindH
#define _conoutwindH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE �Ǘ��̃R���|�[�l���g
    TPanel *Panel1;
    TPanel *Panel2;
    TMemo *memo;
    TButton *Button1;
    TButton *Font;
    TButton *Backcolor;
    TFontDialog *font_diag;
    TColorDialog *color_diag;
    TButton *Button2;
    TSaveDialog *save_di;
    TCheckBox *clrFlg;
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall BackcolorClick(TObject *Sender);
    void __fastcall FontClick(TObject *Sender);
    void __fastcall Button2Click(TObject *Sender);
private:	// ���[�U�[�錾
	void confFileRead();
	void confFileWrite();
public:		// ���[�U�[�錾
    __fastcall TForm1(TComponent* Owner);
    __fastcall ~TForm1();
    void __fastcall WMCopy(TMessage &Msg);
	sChar *config_file;
protected:
	BEGIN_MESSAGE_MAP
        VCL_MESSAGE_HANDLER(WM_COPYDATA, TMessage, WMCopy)
	END_MESSAGE_MAP(TForm)

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
