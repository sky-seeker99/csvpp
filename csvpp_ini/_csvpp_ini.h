//---------------------------------------------------------------------------

#ifndef _csvpp_iniH
#define _csvpp_iniH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE 管理のコンポーネント
        TPanel *Panel1;
        TSplitter *Splitter1;
        TPanel *Panel2;
        TSplitter *Splitter2;
        TPanel *panel;
        TMemo *batFile;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TLabel *Label1;
        TComboBox *WorkDrv;
        TLabel *Label2;
        TEdit *WorkDir;
        TLabel *Label3;
        TCheckBox *stpp;
        TCheckBox *csvmake_o_p;
        TCheckBox *csvfront;
        TCheckBox *proc;
        TCheckBox *tmp;
        TCheckBox *log;
        TCheckBox *pipe;
        TCheckBox *logWin;
        TLabel *Label4;
        TEdit *logFile;
        TCheckBox *sp_push_flg;
        TLabel *Label5;
        TEdit *filter_prg;
        TLabel *Label6;
        TEdit *filter_ext;
        TLabel *Label7;
        TMemo *env_list;
        TLabel *Label8;
        TMemo *inc_list;
        TTimer *tim;
        void __fastcall WorkDrvChange(TObject *Sender);
        void __fastcall WorkDirChange(TObject *Sender);
        void __fastcall stppClick(TObject *Sender);
        void __fastcall csvmake_o_pClick(TObject *Sender);
        void __fastcall csvfrontClick(TObject *Sender);
        void __fastcall procClick(TObject *Sender);
        void __fastcall tmpClick(TObject *Sender);
        void __fastcall logClick(TObject *Sender);
        void __fastcall pipeClick(TObject *Sender);
        void __fastcall logWinClick(TObject *Sender);
        void __fastcall logFileChange(TObject *Sender);
        void __fastcall sp_push_flgClick(TObject *Sender);
        void __fastcall filter_prgChange(TObject *Sender);
        void __fastcall filter_extChange(TObject *Sender);
        void __fastcall env_listChange(TObject *Sender);
        void __fastcall inc_listChange(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall timTimer(TObject *Sender);
private:	// ユーザー宣言
public:		// ユーザー宣言
		__fastcall TForm1(TComponent* Owner);
		__fastcall ~TForm1();
		char *dir;
        PgExec_C *pg_exec;
		void update();
		void update_file();
		void ppush(char *str);
		bool boolSet(char *str);
		void read_file();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
