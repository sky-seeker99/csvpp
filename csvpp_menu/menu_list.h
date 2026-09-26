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



