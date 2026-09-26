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
__published:	// IDE 管理のコンポーネント
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
private:	// ユーザー宣言
	void confFileRead();
	void confFileWrite();
public:		// ユーザー宣言
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
