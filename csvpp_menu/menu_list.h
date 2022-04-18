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

//
//  menu list control
//
class menu_cel{
  public:
    sChar *key;
    sChar *path;
    menu_cel(char *p_path);
    ~menu_cel();
};

class menu_inf{
  public:
    MemHeader_T *it;
    MEM_FP      *mem_fp;  // cell:menu_cel_T
    
    menu_inf(void);
    ~menu_inf();
    void delete_cel(char *key);
    char *add_cel(char *path);
    char *srch_cel(char *key);
    void file_write(FILE *fp);
    bool file_read(CsvInf_T *csvinf);
    void all_clear();
};



