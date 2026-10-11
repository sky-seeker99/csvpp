<!-- CSVPP - Generate C/C++, Verilog-HDL, scripts and text files from Excel data and specifications. -->

<!-- CSVPP (CSV-Preprocessor system) is a code generation system for Windows that automatically generates programs, scripts, batch files, and more based on data and specifications created in Excel. -->

-[japanese](https://github.com/sky-seeker99/csvpp/blob/main/jp/readme.md)

# <img width="272" height="90" alt="csvpp_tag" src="https://github.com/user-attachments/assets/4e7b423a-ee63-4bff-a92e-96e39b48b21e" />

![License](https://img.shields.io/badge/license-Apache--2.0-blue.svg)
![Platform](https://img.shields.io/badge/platform-Windows-lightgrey.svg)
![Language](https://img.shields.io/badge/language-C%2B%2B-orange.svg)

## Generate Programs from Excel

**CSVPP (CSV-Preprocessor system) is a Windows-based code generation system that automatically generates programs, scripts, batch files, and other files based on data and specifications created in Excel.**

By entering data and processing definitions in Excel, CSVPP generates code in the required language and format according to those definitions.

> **Create specifications and data in Excel → Process them with CSVPP → Generate source code**

This workflow can be used to automate the process from specifications and data to source code.

---

## What CSVPP Can Do

- Automatically generate source code from specifications created in Excel
- Automatically generate large amounts of repetitive code
- Generate various types of text files using Excel data
- Generate C/C++ source code
- Generate Verilog-HDL code
- Process, compare, merge, and convert CSV data
- Automatically generate scripts, batch files, and more
- Handle the entire workflow from specification creation to data creation and code generation

---

## Recommended for

### Embedded / C/C++ Development

Automatically generate large amounts of repetitive source code and data definitions from Excel.

### FPGA / Verilog-HDL Development

Generate Verilog-HDL code from data and specifications managed in Excel.

### For People Managing Specifications or Data in Excel

Use specifications and data created in Excel directly as input for code generation.

### For People Who Want to Automate Repetitive Tasks

Reduce manual coding and copy-and-paste work by automatically generating the required files from data.

---

# CSVPP Features

## Excel-Based Code Generation

In addition to conventional text-editor-based coding, CSVPP lets you structure and describe data and processing logic using Excel cells.

- Edit data on a cell-by-cell basis
- Manage specifications and data in tabular form
- Use familiar Excel operations and workflows
- Manage data and code-generation processes in the same Excel environment

---

## Automatically Generate Code from Specifications

Specifications created in Excel can be used as CSVPP input to generate code in the required language or text files.

For example:

```text
Create specifications in Excel
        ↓
      CSVPP
        ↓
C/C++ / Verilog-HDL / Script / Text ...
```

This workflow can automate the process from specifications through implementation.

---

## Connect Specifications, Data, and Code Generation

Normally, the process is:

```text
Specification
  ↓
A person reviews the contents
  ↓
Create the program
  ↓
Change the specifications
  ↓
Modify the program
```

These steps are required.

With CSVPP:

```text
Create specifications and data in Excel
          ↓
        CSVPP
          ↓
   Generate source code
```

This workflow can be established.

By automatically generating repetitive code, CSVPP aims to reduce manual errors and the amount of modification work.

---

# Main Uses

## C/C++ Source Code Generation

It can generate C/C++ source code from Excel-based data and specifications.

A class library for generating C/C++ source code is also provided.

## Verilog-HDL Generation

Generate Verilog-HDL code from data and specifications managed in Excel.

## Text File Generation

Generate various types of text files from data, not just program source code.

## CSV Data Processing

CSVPP includes various tools for handling CSV data.

These tools can be used for various data-processing tasks that arise during development, including CSV processing, comparison, merging, and conversion.

---

# System Requirements

- Microsoft Windows 10 / 11
- Microsoft Excel or LibreOffice

---

# Download

Download and use the latest version of the program.

****Latest version: 2026.9.26****

- [csvpp_system_177a_20260926-1.zip](https://github.com/sky-seeker99/csvpp/releases/download/Ver-1.77a-20260926/csvpp_system_177a_20260926-1.zip)

> Extract the ZIP file before use.
> 
> CSVPP can be used with Microsoft Excel or LibreOffice Calc.

---

# Try It First

You can try CSVPP using the sample programs.

- [filelist.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/filelist.xls)

The samples let you verify the basic workflow for generating files from data created in Excel.

---

# Installation and First Steps (Video)

<img width="640" height="438" alt="csvpp_install_and_exec" src="https://github.com/user-attachments/assets/ca64f838-b8bd-4e49-8b34-5ed9f7977114" />

---

# Manuals

For detailed usage instructions, please refer to the manuals in the repository.

- [CSVPP Setup and Usage](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Setup_and_Usage.xlsx) 
- [CSVPP Language Manual](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_LanguageManual.xlsx) 
- [CSVPP Language Reference](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_LanguageReferenceGuide.xlsx) 
- [Text File Generation and Processing](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_TextFile_Generation_and_Processing.xlsx) 
- [Binary file processing](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_BinaryFile_Processing.xlsx) 
- [Verilog-HDL Generation](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Verilog_Generation.xlsx)
- [Excel ⇔ CSV Conversion (LibreOffice)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Converting_LibreCalc_CSV.xlsx) 
- [Excel ⇔ CSV Conversion (Microsoft Excel)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Converting_Excel_CSV.xlsx)
- [Excel ⇔ CSV Conversion Utility (Filter Program)](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/manual/CSVPP_Utility_CSV_tool.xlsx) 

---

# Main Tools Included in CSVPP

CSVPP includes multiple tools for handling CSV and text data in addition to code generation.

- [csvmake.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake.exe)  -  Excel → CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake_manual.md)
- [csvmake2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake2.exe)  -  CSV → Excel conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake2_manual.md)
- [csvmake3.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake3.exe)  -  Excel → CSV conversion(For Mass Conversion)   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake3_manual.md)
- [csvmake4.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake4.exe)  -  CSV → Excel conversion(For Mass Conversion)   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmake4_manual.md)
- [csvmake_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake_ooo.exe)  -  Excel → CSV conversion for LibreOffice  
- [csvmake2_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake2_ooo.exe)  -  CSV → Excel conversion for LibreOffice  
- [csvmake3_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake3_ooo.exe)  -  Excel → CSV conversion for LibreOffice(For Mass Conversion)  
- [csvmake4_ooo.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmake4_ooo.exe)  -  CSV → Excel conversion for LibreOffice(For Mass Conversion)  
- [bin_catcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bin_catcut.exe)  -  Binary file concatenation and splitting   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bin_catcut_manual.md)
- [bin_ctl.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bin_ctl.exe)  -  Binary file processing   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bin_ctl_manual.md)
- [bincsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/bincsv.exe)  -  Binary → CSV conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/bincsv_manual.md)
- [csvbin.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvbin.exe)  -  CSV → binary conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvbin_manual.md)
- [text_create.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/text_create.exe)  -  Text file generation   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/text_create_manual.md)
- [text_ctl.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/text_ctl.exe)  -  Text file processing   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/text_ctl_manual.md)
- [txt_catcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/txt_catcut.exe)  -  Text file concatenation and splitting   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/txt_catcut_manual.md)
- [logcat.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/logcat.exe)  -  LOG concatenation  
- [retchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retchg.exe)  -  Line-ending conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retchg_manual.md)
- [csvxml.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvxml.exe)  -  CSV → XML conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvxml_manual.md)
- [csvhtml.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvhtml.exe)  -  CSV → HTML conversion  
- [htmlcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/htmlcsv.exe)  -  HTML → CSV conversion  
- [eucsjis.csv](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis.csv)  -  SJIS-EUC conversion  
- [eucsjis.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis.exe)  -  SJIS-EUC conversion  
- [eucsjis2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/eucsjis2.exe)  -  SJIS-EUC conversion  
- [nullchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/nullchg.exe)  -  NULL conversion  
- [csv_textcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csv_textcut.exe)  -  CSV file splitting  
- [csvcellretchg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcellretchg.exe)  -  Inside a CSV File Cell Line-ending conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcellretchg_manual.md)
- [csvcellretchg2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcellretchg2.exe)  -  Inside a CSV File Cell Line-ending conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcellretchg2_manual.md)
- [csvmerge.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvmerge.exe)  -  Horizontal CSV file merge   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvmerge_manual.md)
- [csvcut.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvcut.exe)  -  CSV field extraction   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvcut_manual.md)
- [csvdiff.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvdiff.exe)  -  CSV-DIFF   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvdiff_manual.md)
- [c_cmt_del.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/c_cmt_del.exe)  -  C/C++ comment removal   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/c_cmt_del_manual.md)
- [c_cmt_del2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/c_cmt_del2.exe)  -  C/C++ comment removal   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/c_cmt_del2_manual.md)
- [jpegcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/jpegcsv.exe)  -  JPEG, BMP → CSV file conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/jpegcsv_manual.md)
- [csvjpeg.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvjpeg.exe)  -  CSV file → JPEG, BMP file conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvjpeg_manual.md)
- [csvveri.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvveri.exe)  -  CSV file → Verilog-HDL file conversion  
- [csvtab.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvtab.exe)  -  CSV file → TAB file conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvtab_manual.md)
- [tabcsv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/tabcsv.exe)  -  TAB file → CSV file conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/tabcsv_manual.md)
- [csvstrcnv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/csvstrcnv.exe)  -  CSV numeric value → string conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/csvstrcnv_manual.md)
- [retconv.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv.exe)  -  Excel 用 CSV Line-ending conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retconv_manual.md)
- [retconv2.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv2.exe)  -  Excel 用 CSV Line-ending conversion   ... [manual](https://github.com/sky-seeker99/csvpp/blob/main/collect/manual/retconv2_manual.md)
- [retconv3.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv3.exe)  -  FileMaker 用 CSV Line-ending conversion  
- [retconv4.exe](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/collect/retconv4.exe)  -  FileMaker 用 CSV Line-ending conversion  

---

# Sample Files

## Sample File for Generating Text Files

- [text_file_gen_sample.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/text_file_gen_sample.xlsx) 

## Sample File for Replacing Source Code Headers

- [replace_license_header.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/replace_license_header.xlsx)

## Sample File for Generating Large Numbers of Text Files

- [json_file_gen_sample.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/json_file_gen_sample.xlsx) 

## Sample Files for Generating C++ Code

- [cpp_maker.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/cpp_maker.xlsx) 
-- [CSVPP_C_C++_CodeGenerationSpecification.md](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_sample/CSVPP_C_C++_CodeGenerationSpecification.md)

## Sample Files for Generating Verilog

- [csvveri_sample_top.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvveri_2_sample/csvveri_sample_top.xls) 
- [csvveri_sample.xls](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvveri_2_sample/csvveri_sample.xls) 

---

# Tools Written in the CSVPP Language

- [grep_textcut.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/grep_textcut.xlsx)  -  Extended Grep & Text Splitter  
- [filelist2xls.xlsx](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/filelist2xls.xlsx)  -  Directory & File List Generator   

---

# Class Library

- [C/C++ Source Code Generation Class Library](https://github.com/sky-seeker99/csvpp/raw/refs/heads/main/csvpp_app/cpp_maker_core.xlsx)

---

# Benefits of Using CSVPP

Using CSVPP can help automate tasks such as:

- Creating repetitive source code
- Generating code from large amounts of data
- Converting specifications managed in Excel into code
- Processing CSV data
- Batch generation of text files
- Code modifications associated with changes to the specifications
- Copy-and-paste work

In particular, CSVPP is useful when **"you have a large amount of data and want to convert it into code or files in a predefined format."**

---

# License

The CSVPP programs and documentation are licensed under the

**Apache License Version 2.0**

license.

See `LICENSE` for details.

---

# Author

**sky-seeker99**

---

# Update Information

For the latest feature additions and manual updates, please check the GitHub commit history and this repository.
