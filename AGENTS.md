# CSVPP Repository Guide

## Project Overview

CSVPP is a Windows code-generation and CSV/text-processing system. It uses Excel or LibreOffice spreadsheets as specifications or data and generates C/C++, Verilog-HDL, scripts, text, and other formats.

The repository contains both legacy C++ source projects and prebuilt Windows executables. Preserve compatibility with this project's Windows/Borland C++ Builder conventions.

## Repository Layout

- `README.md`, `README_jp.md`: English and Japanese project overview.
- `csvpp_src/`: main `csvpp.exe` implementation.
- `csvpp_src_sub/`: supporting front-end, library, and pipe executables.
- `csvpp_xbase/`: shared CSVPP/xbase library and language-processing implementation.
- `csvpp_ini/`, `csvpp_menu/`: configuration and menu applications.
- `csvmake/`, `csvmake_oo/`: Excel/CSV conversion tools for Microsoft Excel and LibreOffice.
- `collect/`: release executables, manuals, installers, and supporting files.
- `csvpp_app/`: Excel/CsvPP example workbooks and automation scripts.
- `csvpp_sample/`: C/C++ and text-generation samples.
- `cpu_maker_2/`, `ChatGPT/verilog*`: Verilog and verification-code generation examples.
- `collect/manual/`: Markdown and workbook manuals.

## Build and Tooling

- Most source projects are legacy Borland C++ Builder projects using `.bdsproj`, `.bpr`, `.bpf`, `.cpp`, and `.h` files.
- Source directories often contain generated `.obj`, `.res`, `.tds`, backup, and `__history` artifacts. Do not treat generated files as source unless the task explicitly concerns them.
- Prefer the matching project file and source directory for changes rather than introducing a modern build system.
- Preserve Windows path and encoding assumptions. Relevant code includes Shift-JIS/EUC-JP, UTF-8, binary, and Excel/CSV handling.
- Do not edit generated executables, XLS/XLSX workbooks, or release ZIPs unless that is the explicit task.

## Working Conventions

- Keep changes minimal and preserve existing public command-line behavior.
- Follow the surrounding C++ style; much of the code is older C++ and Win32-oriented.
- Use Windows-style paths and APIs when changing platform code.
- Update the relevant English or Japanese manual when command behavior or user-facing features change.
- Check both source and corresponding generated/sample output before finalizing code-generation changes.
- Avoid deleting or rebuilding `collect/` binaries unless a requested release process requires it.

## Validation

There is no general modern package-based test runner. When possible:

- Open and build the smallest relevant `.bdsproj` or `.bpr` project with Borland C++ Builder.
- Run the directly affected executable from `collect/` or its project output directory.
- For CSV/text/code-generation changes, compare output against a focused sample workbook or CSV fixture.
- For Verilog changes, use the relevant existing simulation batch files and outputs under `cpu_maker_2/` or `ChatGPT/` where available.
