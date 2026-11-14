<!-- CSVPP - Generate C/C++, Verilog-HDL, scripts and text files from Excel data and specifications. -->

<!-- CSVPP (CSV-Preprocessor system) is a code generation system for Windows that automatically generates programs, scripts, batch files, and more based on data and specifications created in Excel. -->
[[japanese]](https://github.com/sky-seeker99/csvpp/blob/main/README_jp.md)

# <img width="272" height="90" alt="csvpp_tag" src="https://github.com/user-attachments/assets/4e7b423a-ee63-4bff-a92e-96e39b48b21e" />

![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)

## Generate Programs from Excel

**CSVPP (CSV-Preprocessor system) is a code generation system for Windows that automatically generates programs, scripts, batch files, and other files from data and specifications created in Excel. A single CSVPP language is all you need to generate code in any target language.**

Describe your data and processing logic in Excel, and CSVPP generates code in the target language and format according to those definitions.

> **Create specifications and data in Excel → Process them with CSVPP → Generate source code**



---

## What CSVPP Can Do

- Automatically generate source code from specifications created in Excel
- Automatically generate large volumes of boilerplate code
- Generate various text files using data from Excel
- Generate C/C++ source code
- Generate Verilog-HDL
- Generate a CPU for verification to greatly reduce verification time.
- Process, compare, merge, and convert CSV data
- Automatically generate scripts, batch files, and more
- Handle specification creation, data preparation, and code generation in a single workflow

---

## Who Should Use CSVPP

### Embedded and C/C++ Development

Automatically generate large volumes of boilerplate source code and data definitions from Excel.

### FPGA / Verilog-HDL Development

Generate Verilog-HDL code from data and specifications managed in Excel.

### People Who Manage Specifications or Data in Excel

Use specifications and data created in Excel directly as input for code generation.

### People Who Want to Automate Repetitive Tasks

Reduce copy-and-paste and manual coding, and automatically generate the files you need from data.

---

# CSVPP Features

## Excel-Based Code Generation

In addition to coding in a conventional text editor, you can use Excel cells to describe data and processing logic in a structured way.

- Edit data cell by cell
- Manage specifications and data in tabular form
- Use familiar Excel workflows
- Manage data and code generation processes in the same Excel environment

---

## Automatically Generate Code from Specifications

Use specifications created in Excel as CSVPP input to generate code in the target language or text files.

For example:

```text
Create specifications in Excel
        ↓
      CSVPP
        ↓
C/C++ / Verilog-HDL / Script / Text ...
```

This workflow automates the process from specification to implementation.

---

## Connect Specifications, Data, and Code Generation

A typical workflow is:

```text
Specification
  ↓
Manual review
  ↓
Write the program
  ↓
Update the specification
  ↓
Update the program
```

This workflow requires these steps.

With CSVPP:

```text
Create specifications and data in Excel
          ↓
        CSVPP
          ↓
   Generate source code
```

CSVPP lets you set up this workflow.

By automatically generating boilerplate code, CSVPP aims to reduce manual errors and rework.

---

# Main Use Cases

## C/C++ Source Code Generation

Generate C/C++ source code from data and specifications in Excel.

A class library for generating C/C++ source code is also included.

## Verilog-HDL Generation

Generate Verilog-HDL from data and specifications managed in Excel.

## Text File Generation

Generate text files in various formats from data, in addition to program source code.

## CSV Data Processing

CSVPP includes a variety of tools for working with CSV data.

Use them for data processing tasks during development, such as editing, comparing, merging, and converting CSV files.

---

# System Requirements

- Microsoft Windows 10 / 11
- Microsoft Excel or Libre Office

---

# Download

Download and use the latest release.

**Latest version: 2026.10.3**

- [csvpp_system_177a_20261003-1.zip](https://github.com/sky-seeker99/csvpp/releases/download/Ver-1.77a-20261003/csvpp_system_177a_20261003-1.zip)

> Extract the ZIP file to use the program.
> 
> CSVPP works with Microsoft Excel or LibreOffice Calc.

---

# Getting Started

Try CSVPP with the sample program.

- [filelist.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/filelist.xls)

The sample demonstrates the basic workflow for generating files from data created in Excel.

---

# Installation and Quick Start (Video)

<img width="640" height="438" alt="csvpp_install_and_exec" src="https://github.com/user-attachments/assets/ca64f838-b8bd-4e49-8b34-5ed9f7977114" />

---

# Manuals

For detailed instructions, see the manuals in the repository.

- [CSVPP Setup and Usage](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Setup_and_Usage.xlsx) 
- [CSVPP Language Manual](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_LanguageManual.xlsx) 
- [CSVPP Language Reference](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_LanguageReferenceGuide.xlsx) 
- [Text File Generation and Processing](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_TextFile_Generation_and_Processing.xlsx) 
- [Binary File Processing](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_BinaryFile_Processing.xlsx) 
- [Verilog-HDL Generation](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Verilog_Generation.xlsx)
- [Generate a Verification CPU (Verilog HDL)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/cpu_maker_2/CSVPP_Verilog_CPU_Generation.xlsx)
- [Excel ⇔ CSV Conversion (LibreOffice Edition](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Converting_LibreCalc_CSV.xlsx) 
- [Excel ⇔ CSV Conversion (Microsoft Excel Edition)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Converting_Excel_CSV.xlsx)
- [Excel ⇔ CSV Utility (Filter Program)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Utility_CSV_tool.xlsx) 

---

# Main Tools Included with CSVPP

CSVPP includes several tools for working with CSV and text data, in addition to code generation.

- [csvmake.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake.exe)  -  Excel to CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake_manual.md)
- [csvmake2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake2.exe)  -  CSV to Excel conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake2_manual.md)
- [csvmake3.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake3.exe)  -  Excel to CSV conversion(for bulk conversion)   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake3_manual.md)
- [csvmake4.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake4.exe)  -  CSV to Excel conversion(for bulk conversion)   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake4_manual.md)
- [csvmake_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake_ooo.exe)  -  Excel to CSV conversion for LibreOffice  
- [csvmake2_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake2_ooo.exe)  -  CSV to Excel conversion for LibreOffice  
- [csvmake3_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake3_ooo.exe)  -  Excel to CSV conversion for LibreOffice(for bulk conversion)  
- [csvmake4_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake4_ooo.exe)  -  CSV to Excel conversion for LibreOffice(for bulk conversion)  
- [bin_catcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bin_catcut.exe)  -  Concatenate and split binary files   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bin_catcut_manual.md)
- [bin_ctl.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bin_ctl.exe)  -  Binary File Processing   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bin_ctl_manual.md)
- [bincsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bincsv.exe)  -  Binary to CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bincsv_manual.md)
- [csvbin.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvbin.exe)  -  CSV to binary conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvbin_manual.md)
- [text_create.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/text_create.exe)  -  Text File Generation   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/text_create_manual.md)
- [text_ctl.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/text_ctl.exe)  -  Process text files   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/text_ctl_manual.md)
- [txt_catcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/txt_catcut.exe)  -  Concatenate and split text files   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/txt_catcut_manual.md)
- [logcat.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/logcat.exe)  -  Concatenate log files   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/logcat_manual.md)
- [retchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retchg.exe)  -  Convert line endings   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retchg_manual.md)
- [csvxml.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvxml.exe)  -  CSV to XML conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvxml_manual.md)
- [csvhtml.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvhtml.exe)  -  CSV to HTML conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvhtml_manual.md)
- [htmlcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/htmlcsv.exe)  -  HTML to CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/htmlcsv_manual.md)
- [eucsjis.csv](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis.csv)  -  Definition file for SJIS-EUC conversion  
- [eucsjis.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis.exe)  -  SJIS-EUC conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/eucsjis_manual.md)
- [eucsjis2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis2.exe)  -  SJIS-EUC conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/eucsjis2_manual.md)
- [nullchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/nullchg.exe)  -  NULL conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/nullchg_manual.md)
- [csvcellretchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcellretchg.exe)  -  Convert line endings within CSV cells   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcellretchg_manual.md)
- [csvcellretchg2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcellretchg2.exe)  -  Convert line endings within CSV cells   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcellretchg2_manual.md)
- [csvmerge.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmerge.exe)  -  Merge CSV files horizontally   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmerge_manual.md)
- [csvcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcut.exe)  -  Extract fields from CSV files   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcut_manual.md)
- [csvdiff.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvdiff.exe)  -  CSV-DIFF   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvdiff_manual.md)
- [c_cmt_del.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/c_cmt_del.exe)  -  Remove C/C++ comments   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/c_cmt_del_manual.md)
- [c_cmt_del2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/c_cmt_del2.exe)  -  Remove C/C++ comments   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/c_cmt_del2_manual.md)
- [jpegcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/jpegcsv.exe)  -  JPEG/BMP to CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/jpegcsv_manual.md)
- [csvjpeg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvjpeg.exe)  -  CSV to JPEG/BMP conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvjpeg_manual.md)
- [csvtab.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvtab.exe)  -  CSV to TAB conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvtab_manual.md)
- [tabcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/tabcsv.exe)  -  TAB to CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/tabcsv_manual.md)
- [csvstrcnv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvstrcnv.exe)  -  Convert CSV numbers to strings   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvstrcnv_manual.md)
- [retconv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv.exe)  -  Convert CSV line endings for Excel   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retconv_manual.md)
- [retconv2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv2.exe)  -  Convert CSV line endings for Excel   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retconv2_manual.md)
- [retconv3.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv3.exe)  -  Convert CSV line endings for FileMaker  
- [retconv4.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv4.exe)  -  Convert CSV line endings for FileMaker  

---

# Sample Files

## Samples for Generating Text Files

- [text_file_gen_sample1.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/text_file_gen_sample1.xlsx) 
- [text_file_gen_sample2.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/text_file_gen_sample2.xlsx) 

## Sample for Replacing Source Code Headers

- [replace_license_header.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/replace_license_header.xlsx)

## Sample for Generating Text Files in Bulk

- [json_file_gen_sample.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/json_file_gen_sample.xlsx) 

## Sample for Generating C++ Code

- [cpp_maker.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/cpp_maker.xlsx) 

## Samples for Generating Verilog

- [csvveri_sample_top.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvveri_2_sample/csvveri_sample_top.xlsx) 
- [csvveri_sample.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvveri_2_sample/csvveri_sample.xlsx) 

---

# Tools Written in the CSVPP Language

- [grep_textcut.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/grep_textcut.xlsx)  -  Extended grep and text splitting utility  
- [filelist2xls.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/filelist2xls.xlsx)  -  Directory and file list generator   

---

# Class Library

- [C/C++ Source Code GenerationClass Library](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/cpp_maker_core.xlsx)

---

# Benefits of Using CSVPP

CSVPP can help automate tasks such as:

- Creating boilerplate source code
- Generating code from large datasets
- Turning specifications managed in Excel into code
- Processing CSV data
- Generating text files in bulk
- Updating code when specifications change
- Copy-and-paste tasks

CSVPP is especially useful when you have a lot of data and want to convert it into code or files in a specific format.

---

# License

CSVPP software and documentation are licensed under the

**Apache License Version 2.0**

license.

See `LICENSE` for details.

---

# Author

**sky-seeker99**

---

# Updates

For the latest features and manuals, see the GitHub commit history and this repository.

---

# CSVPP-AI Integration (C++ Code Generation)
- [CSVPP AI Integration Specification Ver.1.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v1.0.md)
- [CSVPP AI Integration Specification Ver.2.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v2.0.md) 
- [CSVPP C/C++ Code Generation Command Reference](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_CPP_Command_Reference_AI.md) 
- [CSVPP AI Integration: Excel Generation Rules for Adding Custom Methods](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Custom_Method_Rules_v3_draft.md) 
- [CSVPP AI Integration Specification Ver.3.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v3.0.md) 
- [CSVPP AI Integration Specification Ver.3.1](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/cpp_gen/CSVPP_AI_Integration_Spec_v3.1.md) 

- Excel Files Used
  - [Employee.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Employee.xlsx)
  - [AddressBook.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/AddressBook.xlsx)
  - [Product.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product.xlsx)
  - [Product_Customer_Order_csvpp.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product_Customer_Order_csvpp.xlsx)
  - [BankAccount_csvpp.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/BankAccount_csvpp.xlsx)

- Generated C++ Code Files
  - [Employee.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Employee.cpp)
  - [Employee.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Employee.h)
  - [AddressBook.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/AddressBook.cpp)
  - [AddressBook.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/AddressBook.h)
  - [Product.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product.cpp)
  - [Product.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/Product.h)
  - [BankAccount.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/BankAccount.cpp)
  - [BankAccount.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/cpp_gen/BankAccount.h)

---

# CSVPP-AI Integration (Verilog RTL/Testbench Generation)
- [CSVPP Verilog RTL Generation AI Integration Specification Ver.1.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/verilog_gen/CSVPP_Verilog_RTL_AI_Integration_Spec_Ver1.0.md)
- [CSVPP Verilog RTL, Testbench, and TOP Integration AI Specification Ver.2.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/verilog_gen/CSVPP_Verilog_RTL_Testbench_TOP_AI_Integration_Spec_Ver2.0.md)

- Excel Files Used
  - [csvveri_rtl.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/csvveri_rtl.xlsx)
  - [csvveri_test.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/csvveri_test.xlsx)
  - [csvveri_top.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/csvveri_top.xlsx)

- Generated Verilog Code Files
  - [model.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/model.v)
  - [top.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/top.v)
  - [test.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/test.v)
  - [cover.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/cover.v)
  - [clk.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_gen/clk.v)

# CSVPP-AI Integration (Verilog Verification CPU Generation)
- [CSVPP Verilog Verification CPU Generation and Simulation Environment AI Integration Specification](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/verilog_cpu_gen/CSVPP_Verilog_CPU_AI_Integration_Spec_v1.1.md)

- Excel Files Used (AI-Modified Versions)
  - [cpu_memtest_maker_fixed.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest_maker_fixed.xlsx)
  - [cpu_maker_2_sample_verilog_fixed.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_maker_2_sample_verilog_fixed.xlsx)
 
- Generated Verilog Code Files
  - [cpu_memtest.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest.v)
  - [cpu_memtest.cod](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest.cod)
  - [cpu_memtest_lst.csv](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/cpu_memtest_lst.csv)
  - [top.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/top.v)
  - [target.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/target.v)
  - [rst.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/rst.v)
  - [clk.v](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/clk.v)

- Batch Files
  - [sim_go.sh](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/sim_go.sh)
  - [verilog.lst.txt](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/verilog_cpu_gen/verilog.lst.txt)

# CSVPP-C++ Table-Based Design Language Specification
- ChatGPT was asked to write code in the CSVPP language.
- [CSVPP-C++ Table-Based Design Language Specification Ver.0.1](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP-Cpp_Table_Design_Language_Spec_Ver0.1.md)
- [CSVPP-C++ Table-Based Design Language Specification Ver.1.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP_CPP_Table_Design_Language_Spec_Ver1.0.md)
- [CSVPP-C++ Table-Based Design Language Specification Ver.1.1](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP_CPP_Table_Design_Language_Spec_Ver1.1.md)
- [CSVPP-C++ Table-Based Design Language Specification Ver.2.0](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP_CPP_Table_Design_Language_Spec_Ver2.0.md)
- [CSVPP-C++ Table-Based Design Language Specification Ver.2.7](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Specification_Ver2.7.md)
- [CSVPP-C++ Table-Based Design Language Specification Ver.2.8](https://github.com/sky-seeker99/csvpp/blob/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Specification_Ver2.8.md)

- Excel Files in the CSVPP Language Generated by AI
  - [Product_Design_CSVPP.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP.xlsx)
  - [Product_Design_Ver0.1.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_Ver0.1.xlsx)
  - [Product_Design_CSVPP_Ver0.2.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.2.xlsx)
  - [Product_Design_CSVPP_Ver0.3.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.3.xlsx)
  - [Product_Design_CSVPP_Ver0.4.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.4.xlsx)
  - [Product_Design_CSVPP_Ver0.5.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.5.xlsx)
  - [Product_Design_CSVPP_Ver0.6.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.6.xlsx)
  - [Product_Design_CSVPP_Ver0.7.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.7.xlsx)
  - [Product_Design_CSVPP_Ver0.8.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.8.xlsx)
  - [Product_Design_CSVPP_Ver0.9.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver0.9.xlsx)
  - [Product_Design_CSVPP_Ver1.0.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.0.xlsx)
  - [Product_Design_CSVPP_Ver1.1.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.1.xlsx)
  - [Product_Design_CSVPP_Ver1.2.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.2.xlsx)
  - [Product_Design_CSVPP_Ver1.3.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.3.xlsx)
  - [Product_Design_CSVPP_Ver1.4.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.4.xlsx)
  - [Product_Design_CSVPP_Ver1.5.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.5.xlsx)
  - [Product_Design_CSVPP_Ver1.6.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.6.xlsx)
  - [Product_Design_CSVPP_Ver1.7.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.7.xlsx)
  - [Product_Design_CSVPP_Ver1.8.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.8.xlsx)
  - [Product_Design_CSVPP_Ver1.9.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product_Design_CSVPP_Ver1.9.xlsx)
  - [CSVPP_CPP_Design_Ver2.0_3Classes.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.0_3Classes.xlsx)
  - [CSVPP_CPP_Design_Ver2.1_ArrayAllTables.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.1_ArrayAllTables.xlsx)
  - [CSVPP_CPP_Design_Ver2.2_ArrayLookupFix.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.2_ArrayLookupFix.xlsx)
  - [CSVPP_CPP_Design_Ver2.3_BehaviorCustomCodeFix.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.3_BehaviorCustomCodeFix.xlsx)
  - [CSVPP_CPP_Design_Ver2.4_MethodSimplification.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.4_MethodSimplification.xlsx)
  - [CSVPP_CPP_Design_Ver2.5_MethodKeyFix.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.5_MethodKeyFix.xlsx)
  - [CSVPP_CPP_Design_Ver2.6_CompositeKey.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.6_CompositeKey.xlsx)
  - [CSVPP_CPP_Design_Ver2.7.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.7.xlsx)
  - [CSVPP_CPP_Design_Ver2.8_Unified_Design_Sheet.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.8_Unified_Design_Sheet.xlsx)
  - [CSVPP_CPP_Design_Ver2.8_Unified_Design_Sheet_fix1.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/CSVPP_CPP_Design_Ver2.8_Unified_Design_Sheet_fix1.xlsx)

- Generated C++ Code Files
  - [DesignProduct.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/DesignProduct.h)
  - [DesignProduct.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/DesignProduct.cpp)
  - [Customer.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Customer.h)
  - [Customer.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Customer.cpp)
  - [Product.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product.h)
  - [Product.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Product.cpp)
  - [Order.h](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Oder.h)
  - [Order.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/Oder.cpp)
  - [main.cpp](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/ChatGPT/csvpp-c++/main.cpp)



