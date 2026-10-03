cd C:\hpdata\csvpp_source_tc\csvcompiler_2\cpu_maker_2\verilog
C:\iverilog\bin\iverilog.exe -overi_exe -I. -cverilog.lst.txt
C:\iverilog\bin\vvp.exe -lverilog.log veri_exe -vcd | conoutGet 

pause
