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
 
 
class reverse_T{
	public:
	reverse_T(char *p_file);
	~reverse_T();
	bool check(char *p_name);
	void reverseOut(char *p_name);
	void crossWrite(CsvInf_T *csvi,MEM_FP *mem_fp,FILE *out_fp);
      	int 		yoko_max;
	int		tate_max;

};

