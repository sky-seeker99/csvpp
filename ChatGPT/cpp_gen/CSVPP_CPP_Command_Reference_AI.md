# CSVPP C/C++コード生成命令リファレンス（AI対応版・調査版）

- 対象：`Product_Customer_Order_csvpp(2).xlsx` の **`cpp_C` シート**
- 作成日：2026-10-18
- 範囲：ワークブックに存在するマクロ定義と出力ロジックの整理。**CSVPP実行による全命令の検証ではありません。**

## 1. 構成と利用方法

`cpp_C` は `%class cpp_C`（7行）で定義され、18～69行で `%alias` を登録しています。これらのエイリアスは `#method` 等を `%%do` に接続し、後半の `%st` ブロックで処理します。`usr_C` の `output_src` マクロは `#file_def`、`#header_h`、`#header_cpp`、`#class`、`#member`、`#method`、`#parm` などを呼び、最後に `%output` でファイルを出力します。

**重要：** `#if` は生成対象の C++ の `if` を出力するマクロです。一方 `%if` は CSVPP のマクロ制御命令です。両者を混同しないでください。以下の行番号は **cpp_C シート内のExcel行番号** です。

## 2. 命令一覧（実装位置）

| 分類 | 命令 | `%st` 開始行 | 実装状況 |
|---|---|---:|---|
| ファイル・出力 | `output` | 74 | マクロ定義あり |
| ファイル・出力 | `#file_def` | 244 | マクロ定義あり |
| ファイル・出力 | `#header_cpp` | 250 | マクロ定義あり |
| ファイル・出力 | `#header_h` | 256 | マクロ定義あり |
| ファイル・出力 | `#header_ext` | 262 | マクロ定義あり |
| クラス・宣言 | `#class` | 269 | マクロ定義あり |
| クラス・宣言 | `#kind` | 290 | マクロ定義あり |
| クラス・宣言 | `#public` | 284 | マクロ定義あり |
| クラス・宣言 | `#private` | 286 | マクロ定義あり |
| クラス・宣言 | `#protected` | 288 | マクロ定義あり |
| クラス・宣言 | `#method` | 299 | マクロ定義あり |
| クラス・宣言 | `#member` | 341 | マクロ定義あり |
| クラス・宣言 | `#parm` | 375 | マクロ定義あり |
| クラス・宣言 | `#local` | 532 | マクロ定義あり |
| クラス・宣言 | `#global` | 542 | マクロ定義あり |
| コード・整形 | `#code` | 389 | マクロ定義あり |
| コード・整形 | `#code0` | 393 | マクロ定義あり |
| コード・整形 | `#code_sp` | 408 | マクロ定義あり |
| コード・整形 | `#code_sp++` | 400 | マクロ定義あり |
| コード・整形 | `#code_sp--` | 404 | マクロ定義あり |
| 条件分岐 | `#if` | 413 | マクロ定義あり |
| 条件分岐 | `#elseif` | 428 | マクロ定義あり |
| 条件分岐 | `#else` | 420 | マクロ定義あり |
| 条件分岐 | `#endif` | 438 | マクロ定義あり |
| 条件分岐 | `#switch` | 495 | マクロ定義あり |
| 条件分岐 | `#case` | 509 | マクロ定義あり |
| 条件分岐 | `#default` | 516 | マクロ定義あり |
| 条件分岐 | `#endcase` | 522 | マクロ定義あり |
| 条件分岐 | `#endswitch` | 503 | マクロ定義あり |
| 反復処理 | `#for` | 445 | マクロ定義あり |
| 反復処理 | `#endfor` | 453 | マクロ定義あり |
| 反復処理 | `#while` | 467 | マクロ定義あり |
| 反復処理 | `#endwhile` | 475 | マクロ定義あり |
| 反復処理 | `#do_while` | 481 | マクロ定義あり |
| 反復処理 | `#end_do_while` | 488 | マクロ定義あり |
| 反復処理 | `#break` | 459 | マクロ定義あり |
| 反復処理 | `#continue` | 463 | マクロ定義あり |
| 式・処理 | `#set` | 630 | マクロ定義あり |
| 式・処理 | `#set-` | 636 | マクロ定義あり |
| 式・処理 | `#call` | 642 | マクロ定義あり |
| 式・処理 | `#set_call` | 661 | マクロ定義あり |
| 式・処理 | `#return` | 686 | マクロ定義あり |
| 式・処理 | `#delete` | 697 | マクロ定義あり |
| 式・処理 | `#printf` | 552 | マクロ定義あり |
| 式・処理 | `#fprintf` | 574 | マクロ定義あり |
| 式・処理 | `#sprintf` | 602 | マクロ定義あり |
| その他 | `###` | 708 | マクロ定義あり |
| その他 | `#//` | 714 | マクロ定義あり |

`cpp_C` には上記に加えて `%st cpp_C`（エイリアス登録）と `%st ~cpp_C`（終了）、`%st output`（実際の `.h`/`.cpp` 出力）があります。`#output_src` と `#store_member` は **`usr_C` 側**の命令であり、`cpp_C` 固有命令ではありません。

## 3. 実装の詳細（シートのセル内容に基づく）

以下は各 `%st` 定義のセル内容から、CSVPP制御命令を含めて抜粋したものです。列名を併記しているため、AIがExcelのセル配置を再現する際にも利用できます。空セル・コメントのみの行は省略しています。

### ファイル・出力

#### `output`（74行～）

```text
B74=%st | C74=output
B76=#writeln | C76=header_top | D76=#ifndef _$file_name$_h_
B77=#writeln | C77=header_top | D77=#define _$file_name$_h_
B78=#writeln | C78=header_end | D78=#endif  // _$file_name$_h_
B79=#writeln | C79=method_begin | D79=){
B80=#writeln | C80=method_end | D80=}
B81=#writeln | C81=method_define_end | D81=);
B82=#writeln | C82=class_define_end | D82=};
B83=#sp | C83=public | D83=2
B84=#sp | C84=private | D84=2
B85=#sp | C85=protected | D85=2
B86=#writeln | C86=public | D86=public:
B87=#writeln | C87=private | D87=private:
B88=#writeln | C88=protected | D88=protected:
B91=#file | C91=$output_dir$\$file_name$.h
B92=#key | C92=header_h
B93=#key | C93=header_top
B94=#key | C94=header_ext
B97=%for | C97=i | D97=$class_cnt$
C98=%aryrd | D98=class_name | E98=$i$
C99=#key | D99=class_$class_name$
C100=%for | D100=dd | E100=3
D101=%set | E101=ddd | F101=public
D102=%if | E102=dd | F102=0 | G102=%set | H102=ddd | I102=public
D103=%else_if | E103=dd | F103=1 | G103=%set | H103=ddd | I103=private
D104=%else_if | E104=dd | F104=2 | G104=%set | H104=ddd | I104=protected
D105=%endif
D107=%if | E107=class_name | F107=.
E108=%noif | F108=ddd | G108=public
F109=%continue
E110=%endif
D111=%endif
D113=%aryrd | E113=member_cnt | F113=$class_name$_$ddd$
```

※長い定義のため冒頭33行を掲載。詳細は元Excelを参照してください。

#### `#file_def`（244行～）

```text
B244=%st | C244=#file_def
B245=%argsep | C245=p
B247=%set | C247=file_name | D247=$p$
B249=// | C249=cppファイルのヘッダ定義
```

#### `#header_cpp`（250行～）

```text
B250=%st | C250=#header_cpp
B251=%argsep | C251=p
B253=#writeln | C253=header_cpp | D253=$p$
B255=// | C255=hファイルのヘッダ定義
```

#### `#header_h`（256行～）

```text
B256=%st | C256=#header_h
B257=%argsep | C257=p
B259=#writeln | C259=header_h | D259=$p$
B261=// | C261=hファイルのclass外の定義
```

#### `#header_ext`（262行～）

```text
B262=%st | C262=#header_ext
B263=%argsep | C263=p
B265=#writeln | C265=header_ext | D265=$p$
B268=// | C268=classの定義
```

### クラス・宣言

#### `#class`（269行～）

```text
B269=%st | C269=#class
B270=%argsep | C270=p
B272=%arywr | C272=class_name | D272=$class_cnt$ | E272=$p$
B273=%calc | C273=class_cnt | D273=class_cnt+1
B274=%set | C274=class_name | D274=$p$
B276=%noif | C276=class_name | D276=.
B277=#writeln | C277=class_$p$ | D277=class $p${
B278=// | C278=class_$p$ | D278=  public:
B279=%endif
B283=// | C283=public/privateの定義
```

#### `#kind`（290行～）

```text
B290=%st | C290=#kind
B291=%argdef | C291=type
B292=%if | C292=type | D292=public | F292=%set | G292=pubKind | H292=$type$
B293=%else_if | C293=type | D293=private | F293=%set | G293=pubKind | H293=$type$
B294=%else_if | C294=type | D294=protected | F294=%set | G294=pubKind | H294=$type$
B295=%else | E295=%printf | F295=public/private/protected error.  (kind=$type$)
B296=%endif
B298=// | C298=methodの定義
```

#### `#public`（284行～）

```text
B284=%st | C284=#public
B285=#kind | C285=public
```

#### `#private`（286行～）

```text
B286=%st | C286=#private
B287=#kind | C287=private
```

#### `#protected`（288行～）

```text
B288=%st | C288=#protected
B289=#kind | C289=protected
```

#### `#method`（299行～）

```text
B299=%st | C299=#method
B300=%argsep | C300=type | D300=p
B302=%aryrd | C302=method_cnt | D302=$class_name$_$pubKind$
B303=%if | C303=method_cnt
C304=%set | D304=method_cnt | E304=0
B305=%endif
B306=%arywr | C306=method_name | D306=$class_name$_$pubKind$_$method_cnt$ | E306=$p$
B307=%set | C307=method_name | D307=$p$
B308=%set | C308=parm_first_flg | D308=1
B310=#sp | D310=method_parm_$class_name$_$pubKind$_$method_name$ | E310=0
B311=#sp | D311=method_define_$class_name$_$pubKind$_$method_name$ | E311=4
B313=%noif | C313=class_name | D313=.
C314=%if | D314=type | E314=.
D315=#write | E315=method_parm_$class_name$_$pubKind$_$method_name$ | F315=$class_name$::$p$(
D316=#write | E316=method_define_$class_name$_$pubKind$_$method_name$ | F316=$p$(
C317=%else
D318=#write | E318=method_parm_$class_name$_$pubKind$_$method_name$ | F318=$type$ $class_name$::$p$(
D319=#write | E319=method_define_$class_name$_$pubKind$_$method_name$ | F319=$type$ $p$(
C320=%endif
B321=%else
C322=%if | D322=type | E322=.
D323=type | E323=void
C324=%endif
C325=#sp | D325=method_parm_$class_name$_$pubKind$_$method_name$ | E325=0
C326=#sp | D326=method_define_$class_name$_$pubKind$_$method_name$ | E326=0
C327=%if | D327=pubKind | E327=public
D328=#write | E328=method_parm_$class_name$_$pubKind$_$method_name$ | F328=$type$ $p$(
D329=#write | E329=method_define_$class_name$_$pubKind$_$method_name$ | F329=$type$ $p$(
C330=%else
D331=#write | E331=method_parm_$class_name$_$pubKind$_$method_name$ | F331=static $type$ $p$(
D332=#write | E332=method_define_$class_name$_$pubKind$_$method_name$ | F332=static $type$ $p$(
C333=%endif
B334=%endif
```

※長い定義のため冒頭33行を掲載。詳細は元Excelを参照してください。

#### `#member`（341行～）

```text
B341=%st | C341=#member
B342=%argdef | C342=type | D342=p | E342=cmt
B344=%var | C344=msg
B345=%noif | C345=cmt
C346=%set | D346=msg | E346=// $cmt$
B347=%endif
C350=%aryrd | D350=member_cnt | E350=$class_name$_$pubKind$
B351=%noif | C351=class_name | D351=.
C352=#sp | D352=member_$class_name$_$pubKind$ | E352=4
C354=#writeln | D354=member_$class_name$_$pubKind$ | E354=$type$ $p$; $msg$
B355=%else
C356=#sp | D356=member_$class_name$_$pubKind$ | E356=0
C357=%if | D357=pubKind | E357=public
D358=#writeln | E358=member_$class_name$_$pubKind$ | F358=$type$ $p$; $msg$
C359=%else
D360=#writeln | E360=member_$class_name$_$pubKind$ | F360=static $type$ $p$; $msg$
C361=%endif
B363=%endif
C364=%if | D364=member_cnt
D365=%set | E365=member_cnt | F365=1
C366=%else
D367=%calc | E367=member_cnt | F367=member_cnt + 1
C368=%endif
B370=// | C370=%printf | D370=write member_cnt[$class_name$_$pubKind$] = $member_cnt$  
C372=%arywr | D372=member_cnt | E372=$class_name$_$pubKind$ | G372=$member_cnt$
B374=// | C374=parameterの定義
```

#### `#parm`（375行～）

```text
B375=%st | C375=#parm
B376=%argsep | C376=type | D376=p
B378=%if | C378=parm_first_flg | D378=1
C379=%set | D379=parm_first_flg
B380=%else
C381=#write | D381=method_parm_$class_name$_$pubKind$_$method_name$ | E381=,
C382=#write | D382=method_define_$class_name$_$pubKind$_$method_name$ | E382=,
B383=%endif
C385=#write | D385=method_parm_$class_name$_$pubKind$_$method_name$ | E385=$type$ $p$
C386=#write | D386=method_define_$class_name$_$pubKind$_$method_name$ | E386=$type$ $p$
B388=// | C388=codeの定義
```

#### `#local`（532行～）

```text
B532=%st | C532=#local
B533=%argdef | C533=p0 | D533=p1 | E533=p2
B535=%if | C535=p2
C536=#code | D536=$p0$ $p1$;
B537=%else
C538=#code | D538=$p0$ $p1$ = $p2$;
B539=%endif
B541=// | C541=グローバル変数
```

#### `#global`（542行～）

```text
B542=%st | C542=#global
B543=%argdef | C543=p0 | D543=p1 | E543=p2
B545=%if | C545=p2
C546=#writeln | D546=header_global | E546=$p0$ $p1$;
B547=%else
C548=#writeln | D548=header_global | E548=$p0$ $p1$ = $p2$;
B549=%endif
B551=// | C551=printf
```

### コード・整形

#### `#code`（389行～）

```text
B389=%st | C389=#code
B390=%argsep | C390=p
C391=#writeln | D391=method_body_$class_name$_$pubKind$_$method_name$ | E391=$p$
```

#### `#code0`（393行～）

```text
B393=%st | C393=#code0
B394=%argsep | C394=p
C395=#sp_push | D395=method_body_$class_name$_$pubKind$_$method_name$ | E395=save
C396=#sp | D396=method_body_$class_name$_$pubKind$_$method_name$ | E396=0
C397=#writeln | D397=method_body_$class_name$_$pubKind$_$method_name$ | E397=$p$
C398=#sp_pop | D398=method_body_$class_name$_$pubKind$_$method_name$ | E398=save
```

#### `#code_sp`（408行～）

```text
B408=%st | C408=#code_sp
B409=%argsep | C409=p
C410=#sp | D410=method_body_$class_name$_$pubKind$_$method_name$ | E410=$p$
B412=// | C412=ifの定義
```

#### `#code_sp++`（400行～）

```text
B400=%st | C400=#code_sp++
B401=%argsep | C401=p
C402=#sp++ | D402=method_body_$class_name$_$pubKind$_$method_name$ | E402=$p$
```

#### `#code_sp--`（404行～）

```text
B404=%st | C404=#code_sp--
B405=%argsep | C405=p
C406=#sp-- | D406=method_body_$class_name$_$pubKind$_$method_name$ | E406=$p$
```

### 条件分岐

#### `#if`（413行～）

```text
B413=%st | C413=#if
B414=%argsep | C414=p
B416=#code | C416=if ($p$){
B417=#code_sp++ | C417=2
B419=// | C419=elseの定義
```

#### `#elseif`（428行～）

```text
B428=%st | C428=#elseif
B429=%argsep | C429=p
B431=#code_sp-- | C431=2
B432=#code | C432=}
B433=#code | C433=else if  ($p$){
B434=#code_sp++ | C434=2
B437=// | C437=endifの定義
```

#### `#else`（420行～）

```text
B420=%st | C420=#else
B422=#code_sp-- | C422=2
B423=#code | C423=}
B424=#code | C424=else {
B425=#code_sp++ | C425=2
B427=// | C427=elseifの定義
```

#### `#endif`（438行～）

```text
B438=%st | C438=#endif
B440=#code_sp-- | C440=2
B441=#code | C441=}
B444=// | C444=forの定義
```

#### `#switch`（495行～）

```text
B495=%st | C495=#switch
B496=%argdef | C496=p0
B498=#code | C498=switch($p0$){
B499=#code_sp++ | C499=2
B502=// | C502=endswitchの定義
```

#### `#case`（509行～）

```text
B509=%st | C509=#case
B510=%argdef | C510=p0
B512=#code | C512=case $p0$:
B513=#code_sp++ | C513=2
B515=// | C515=defaultの定義
```

#### `#default`（516行～）

```text
B516=%st | C516=#default
B518=#code | C518=default:
B519=#code_sp++ | C519=2
B521=// | C521=endcaseの定義
```

#### `#endcase`（522行～）

```text
B522=%st | C522=#endcase
B523=%argdef | C523=non_break
B525=%if | C525=non_break
C526=#code | D526=break;
B527=%endif
B528=#code_sp-- | C528=2
B531=// | C531=ローカル変数
```

#### `#endswitch`（503行～）

```text
B503=%st | C503=#endswitch
B505=#code_sp-- | C505=2
B506=#code | C506=}
B508=// | C508=caseの定義
```

### 反復処理

#### `#for`（445行～）

```text
B445=%st | C445=#for
B446=%argdeffix | C446=p0 | D446=p1 | E446=p2
B448=#code | C448=for($p0$;$p1$;$p2$){
B449=#code_sp++ | C449=2
B452=// | C452=endforの定義
```

#### `#endfor`（453行～）

```text
B453=%st | C453=#endfor
B455=#code_sp-- | C455=2
B456=#code | C456=}
B458=// | C458=breakの定義
```

#### `#while`（467行～）

```text
B467=%st | C467=#while
B468=%argdef | C468=p0
B470=#code | C470=while($p0$){
B471=#code_sp++ | C471=2
B474=// | C474=endforの定義
```

#### `#endwhile`（475行～）

```text
B475=%st | C475=#endwhile
B477=#code_sp-- | C477=2
B478=#code | C478=}
B480=// | C480=do_whileの定義
```

#### `#do_while`（481行～）

```text
B481=%st | C481=#do_while
B483=#code | C483=do {
B484=#code_sp++ | C484=2
B487=// | C487=end_do_whileの定義
```

#### `#end_do_while`（488行～）

```text
B488=%st | C488=#end_do_while
B489=%argdef | C489=p0
B491=#code_sp-- | C491=2
B492=#code | C492=} while($p0$);
B494=// | C494=switchの定義
```

#### `#break`（459行～）

```text
B459=%st | C459=#break
B460=#code | C460=break;
B462=// | C462=continueの定義
```

#### `#continue`（463行～）

```text
B463=%st | C463=#continue
B464=#code | C464=continue;
B466=// | C466=whileの定義
```

### 式・処理

#### `#set`（630行～）

```text
B630=%st | C630=#set
B631=%argdef | C631=v | D631=val
B633=#code | C633=$v$ = $val$;
B635=// | C635=set-
```

#### `#set-`（636行～）

```text
B636=%st | C636=#set-
B637=%argdef | C637=v | D637=val
B639=#code | C639=$v$ -= $val$;
B641=// | C641=call
```

#### `#call`（642行～）

```text
B642=%st | C642=#call
B644=%set | C644=func
B645=%set | C645=w
B646=%for | C646=ii | D646=$argc$
C647=%aryrd | D647=argv | E647=$ii$
C648=%if | D648=argv | E648=%continue | F648=%endif
C649=%if | D649=func
D650=%set | E650=func | F650=$argv$
D651=%continue
C652=%endif
C653=%noif | D653=w
D654=%set | E654=w | F654=$w$,
C655=%endif
C656=%set | D656=w | E656=$w$$argv$
B657=%endfor
B658=#code | C658=$func$($w$);
B660=// | C660=set_call
```

#### `#set_call`（661行～）

```text
B661=%st | C661=#set_call
B663=%set | C663=v
B664=%set | C664=func
B665=%set | C665=w
B666=%for | C666=ii | D666=$argc$
C667=%aryrd | D667=argv | E667=$ii$
C668=%if | D668=argv | E668=%continue | F668=%endif
C669=%if | D669=v
D670=%set | E670=v | F670=$argv$
D671=%continue
C672=%endif
C673=%if | D673=func
D674=%set | E674=func | F674=$argv$
D675=%continue
C676=%endif
C677=%noif | D677=w
D678=%set | E678=w | F678=$w$,
C679=%endif
C680=%set | D680=w | E680=$w$$argv$
B681=%endfor
B682=#code | C682=$v$ = $func$($w$);
B685=// | C685=return
```

#### `#return`（686行～）

```text
B686=%st | C686=#return
B687=%argdef | C687=ret
B689=%if | C689=ret
C690=#code | D690=return;
B691=%else
C692=#code | D692=return($ret$);
B693=%endif
B696=// | C696=delete
```

#### `#delete`（697行～）

```text
B697=%st | C697=#delete
B698=%argdef | C698=var1 | D698=var2
B700=%if | C700=var2
C701=#code | D701=delete $var1$;
B702=%else
C703=#code | D703=delete $var1$ $var2$;
B704=%endif
B707=// | C707=comment
```

#### `#printf`（552行～）

```text
B552=%st | C552=#printf
B554=%set | C554=frm
B555=%set | C555=w
B556=%for | C556=ii | D556=$argc$
C557=%aryrd | D557=argv | E557=$ii$
C558=%if | D558=argv | E558=%continue | F558=%endif
C559=%if | D559=frm
D560=%set | E560=frm | F560=$argv$
D561=%continue
C562=%endif
C563=%noif | D563=w
D564=%set | E564=w | F564=$w$,
C565=%endif
C566=%set | D566=w | E566=$w$$argv$
B567=%endfor
B568=%if | C568=w
C569=#code | D569=printf("$frm$");
B570=%else
C571=#code | D571=printf("$frm$",$w$);
B572=%endif
B573=// | C573=fprintf
```

#### `#fprintf`（574行～）

```text
B574=%st | C574=#fprintf
B576=%set | C576=fp
B577=%set | C577=frm
B578=%set | C578=w
B579=%for | C579=ii | D579=$argc$
C580=%aryrd | D580=argv | E580=$ii$
C581=%if | D581=argv | E581=%continue | F581=%endif
C582=%if | D582=fp
D583=%set | E583=fp | F583=$argv$
D584=%continue
C585=%endif
C586=%if | D586=frm
D587=%set | E587=frm | F587=$argv$
D588=%continue
C589=%endif
C590=%noif | D590=w
D591=%set | E591=w | F591=$w$,
C592=%endif
C593=%set | D593=w | E593=$w$$argv$
B594=%endfor
B596=%if | C596=w
C597=#code | D597=fprintf($fp$,"$frm$");
B598=%else
C599=#code | D599=fprintf($fp$,"$frm$",$w$);
B600=%endif
B601=// | C601=sprintf
```

#### `#sprintf`（602行～）

```text
B602=%st | C602=#sprintf
B604=%set | C604=fp
B605=%set | C605=frm
B606=%set | C606=w
B607=%for | C607=ii | D607=$argc$
C608=%aryrd | D608=argv | E608=$ii$
C609=%if | D609=argv | E609=%continue | F609=%endif
C610=%if | D610=fp
D611=%set | E611=fp | F611=$argv$
D612=%continue
C613=%endif
C614=%if | D614=frm
D615=%set | E615=frm | F615=$argv$
D616=%continue
C617=%endif
C618=%noif | D618=w
D619=%set | E619=w | F619=$w$,
C620=%endif
C621=%set | D621=w | E621=$w$$argv$
B622=%endfor
B624=%if | C624=w
C625=#code | D625=sprintf($fp$,"$frm$");
B626=%else
C627=#code | D627=sprintf($fp$,"$frm$",$w$);
B628=%endif
B629=// | C629=set
```

### その他

#### `###`（708行～）

```text
B708=%st | C708=###
B709=%argdef | C709=p
B711=#writeln | C711=method_cmt_$class_name$_$pubKind$_$method_name$ | E711=$p$
B713=// | C713=comment
```

#### `#//`（714行～）

```text
B714=%st | C714=#//
B715=%argdef | C715=p
B717=#code | C717=// $p$

```

## 4. 出力処理の流れ

`output`（74行～）は、`#writeln` でヘッダーガードや閉じ括弧を定義し、`#file` で `$output_dir$\$file_name$.h`（91行）と `$output_dir$\$file_name$.cpp`（159行）を開きます。`#key` で、クラス定義、メンバ、関数宣言、関数本体など、蓄積した断片を順に書き出します。クラス情報・メンバ情報・メソッド情報の配列は出力後にリセットされます（236～240行）。

## 5. 動作確認済みの使用例

直近の `Product` の実行結果で確認できた出力例：

```cpp
bool Product::isInStock(){
  return(stock > 0);
}

double Product::getTotalPrice(int quantity){
  return(price * quantity);
}

bool Product::reduceStock(int quantity){
  if (quantity <= 0 || quantity > stock){
    return(false);
  }
  stock -= quantity;
  return(true);
}
```

対応する命令は `#method`、`#parm`、`#if`、`#endif`、`#set-`、`#return` です。実際のC++生成ファイルで確認されています。ただし、**全命令の実行確認やC++コンパイル検証を済ませたという意味ではありません**。

## 6. AIによるExcel編集時の注意

1. 実績のあるワークブックを複製し、`cpp_C` のマクロ本体は原則変更しない。
2. `cmd` にクラス・メンバを記述し、独自メソッドは `usr_C` の専用マクロに定義する。
3. `#` 系はC++出力用マクロ、`%` 系はCSVPP制御命令として区別する。
4. `#method` の後に `#parm`、本文命令を配置する。字下げはExcelの**列位置**と `#code_sp++` / `#code_sp--` の両方に依存しうるため、実績あるセル配置をコピーする。
5. `#local`、`#global`、`#set_call`、`#delete` 等の複雑な命令は、元Excelの定義を参照し、小さなテストで検証してから自動生成に採用する。
6. 出力後は `.h` と `.cpp` の宣言・定義一致、`#include`、括弧の対応、コンパイル可否を確認する。

## 7. 未確認事項

全命令の引数制約、特殊文字・引用符・複数行引数の扱い、エラー時挙動、複雑なネスト、コンパイラでの検証はこの資料だけでは確定できません。元の `reference` シートやCSVPP本体の仕様との照合が必要です。
