//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("csvpp_ini.res");
USEFORM("_csvpp_ini.cpp", Form1);
USEUNIT("..\csvpp_xbase\xcsvi_anl.cpp");
USEUNIT("..\csvpp_xbase\xread64.cpp");
USEUNIT("..\csvpp_xbase\xwrite64.cpp");
USEUNIT("..\csvpp_xbase\zschar.cpp");
USEUNIT("..\csvpp_xbase\xexec.cpp");
USEUNIT("..\csvpp_xbase\ztoken.cpp");
USEUNIT("..\csvpp_xbase\zfilename_anl.cpp");
USEUNIT("..\csvpp_xbase\zsjis_anl.cpp");
USEUNIT("..\csvpp_xbase\ztool.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
