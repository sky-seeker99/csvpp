c:
cd \
mkdir csv
del c:\csv\*.csv
csvmake %1 c:\csv 
C:\hpdata\csvpp_source_tc\csvpp_src\Release_Build\csvpp.exe c:\csv\cmd.csv -ic:\csv -down_xls=%1 -s -f | conoutGet 
pause

