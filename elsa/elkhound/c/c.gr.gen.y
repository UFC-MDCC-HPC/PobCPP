/* automatically generated grammar */

/* -------- tokens -------- */
%token L2_EOF 0
%token L2_NAME 1
%token L2_TYPE_NAME 2
%token L2_VARIABLE_NAME 3
%token L2_INT_LITERAL 4
%token L2_FLOAT_LITERAL 5
%token L2_STRING_LITERAL 6
%token L2_CHAR_LITERAL 7
%token L2_UDEF_QUAL 8
%token L2_ASM 9
%token L2_AUTO 10
%token L2_BREAK 11
%token L2_BOOL 12
%token L2_CASE 13
%token L2_CATCH 14
%token L2_CDECL 15
%token L2_CHAR 16
%token L2_CLASS 17
%token L2_CONST 18
%token L2_CONST_CAST 19
%token L2_CONTINUE 20
%token L2_DEFAULT 21
%token L2_DELETE 22
%token L2_DO 23
%token L2_DOUBLE 24
%token L2_DYNAMIC_CAST 25
%token L2_ELSE 26
%token L2_ENUM 27
%token L2_EXPLICIT 28
%token L2_EXPORT 29
%token L2_EXTERN 30
%token L2_FALSE 31
%token L2_FLOAT 32
%token L2_FOR 33
%token L2_FRIEND 34
%token L2_GOTO 35
%token L2_IF 36
%token L2_INLINE 37
%token L2_INT 38
%token L2_LONG 39
%token L2_MUTABLE 40
%token L2_NAMESPACE 41
%token L2_NEW 42
%token L2_OPERATOR 43
%token L2_PASCAL 44
%token L2_PRIVATE 45
%token L2_PROTECTED 46
%token L2_PUBLIC 47
%token L2_REGISTER 48
%token L2_REINTERPRET_CAST 49
%token L2_RETURN 50
%token L2_SHORT 51
%token L2_SIGNED 52
%token L2_SIZEOF 53
%token L2_STATIC 54
%token L2_STATIC_CAST 55
%token L2_STRUCT 56
%token L2_SWITCH 57
%token L2_TEMPLATE 58
%token L2_THIS 59
%token L2_THROW 60
%token L2_TRUE 61
%token L2_TRY 62
%token L2_TYPEDEF 63
%token L2_TYPEID 64
%token L2_TYPENAME 65
%token L2_UNION 66
%token L2_UNSIGNED 67
%token L2_USING 68
%token L2_VIRTUAL 69
%token L2_VOID 70
%token L2_VOLATILE 71
%token L2_WCHAR_T 72
%token L2_WHILE 73
%token L2_LPAREN 74
%token L2_RPAREN 75
%token L2_LBRACKET 76
%token L2_RBRACKET 77
%token L2_ARROW 78
%token L2_COLONCOLON 79
%token L2_DOT 80
%token L2_BANG 81
%token L2_TILDE 82
%token L2_PLUS 83
%token L2_MINUS 84
%token L2_PLUSPLUS 85
%token L2_MINUSMINUS 86
%token L2_AND 87
%token L2_STAR 88
%token L2_DOTSTAR 89
%token L2_ARROWSTAR 90
%token L2_SLASH 91
%token L2_PERCENT 92
%token L2_LEFTSHIFT 93
%token L2_RIGHTSHIFT 94
%token L2_LESSTHAN 95
%token L2_LESSEQ 96
%token L2_GREATERTHAN 97
%token L2_GREATEREQ 98
%token L2_EQUALEQUAL 99
%token L2_NOTEQUAL 100
%token L2_XOR 101
%token L2_OR 102
%token L2_ANDAND 103
%token L2_OROR 104
%token L2_QUESTION 105
%token L2_COLON 106
%token L2_EQUAL 107
%token L2_STAREQUAL 108
%token L2_SLASHEQUAL 109
%token L2_PERCENTEQUAL 110
%token L2_PLUSEQUAL 111
%token L2_MINUSEQUAL 112
%token L2_ANDEQUAL 113
%token L2_XOREQUAL 114
%token L2_OREQUAL 115
%token L2_LEFTSHIFTEQUAL 116
%token L2_RIGHTSHIFTEQUAL 117
%token L2_COMMA 118
%token L2_ELLIPSIS 119
%token L2_SEMICOLON 120
%token L2_LBRACE 121
%token L2_RBRACE 122
%token L2___ATTRIBUTE__ 123
%token L2___FUNCTION__ 124
%token L2___LABEL__ 125
%token L2___PRETTY_FUNCTION__ 126
%token L2___TYPEOF__ 127
%token L2_OWNER 128
%token L2_PREFER_REDUCE 129
%token L2_PREFER_SHIFT 130
%token L2_THMPRV_ASSERT 131
%token L2_THMPRV_ASSUME 132
%token L2_THMPRV_INVARIANT 133
%token L2_IMPLIES 134
%token L2_THMPRV_PRE 135
%token L2_THMPRV_POST 136
%token L2_THMPRV_LET 137
%token L2_THMPRV_ATTR 138
%token L2_THMPRV_FORALL 139
%token L2_THMPRV_EXISTS 140
%token L2_THMPRV_PURE_ASSERT 141
%token L2_THMPRV_BIND 142
%token L2_THMPRV_DECL 143
%token L2_THMPRV_PREDICATE 144


/* -------- precedence and associativity ---------*/
/* low precedence */
%nonassoc L2_PREFER_SHIFT








%right L2_IMPLIES









%left L2_OROR









%left L2_ANDAND









%left L2_OR









%left L2_XOR









%left L2_AND









%left L2_EQUALEQUAL L2_NOTEQUAL









%left L2_LESSTHAN L2_LESSEQ L2_GREATERTHAN L2_GREATEREQ









%left L2_LEFTSHIFT L2_RIGHTSHIFT









%left L2_PLUS L2_MINUS









%left L2_STAR L2_SLASH L2_PERCENT









%right L2_DOTSTAR L2_ARROWSTAR





































































%nonassoc L2_CONST L2_ELSE L2_VOLATILE L2___ATTRIBUTE__ L2_OWNER









%nonassoc L2_PREFER_REDUCE
/* high precedence */


/* -------- productions ------ */
%%

__EarlyStartSymbol: File L2_EOF { $$=0; }
                  ;

File: EnterScope TranslationUnit LeaveScope { $$=1; }
    ;

EnterScope: /* empty */ { $$=2; }
          ;

LeaveScope: /* empty */ { $$=3; }
          ;

TypeName: L2_TYPE_NAME { $$=4; }
        ;

VariableName: L2_VARIABLE_NAME { $$=5; }
            ;

AnyName: VariableName { $$=6; }
       | TypeName { $$=7; }
       ;

TranslationUnit: /* empty */ { $$=8; }
               | TranslationUnit Declaration { $$=9; }
               | TranslationUnit GNUAsmStatement { $$=10; }
               | TranslationUnit L2_SEMICOLON { $$=11; }
               ;

PrimaryExpression: Literal { $$=12; }
                 | L2_LPAREN Expression L2_RPAREN { $$=13; }
                 | PQVarName { $$=14; }
                 | TypeName L2_COLONCOLON AnyName { $$=15; }
                 | ThmprvPredicate { $$=16; }
                 ;

Literal: L2_INT_LITERAL { $$=17; }
       | L2_FLOAT_LITERAL { $$=18; }
       | StringLiteral { $$=19; }
       | L2_CHAR_LITERAL { $$=20; }
       | L2_TRUE { $$=21; }
       | L2_FALSE { $$=22; }
       ;

StringLiteral: L2_STRING_LITERAL { $$=23; }
             ;

PQVarName: VariableName { $$=24; }
         ;

PostfixExpression: PrimaryExpression { $$=25; }
                 | PostfixExpression L2_LBRACKET Expression L2_RBRACKET { $$=26; }
                 | PostfixExpression L2_LPAREN ExpressionListOpt L2_RPAREN { $$=27; }
                 | PostfixExpression L2_DOT PQVarName { $$=28; }
                 | PostfixExpression L2_ARROW PQVarName { $$=29; }
                 | PostfixExpression L2_PLUSPLUS { $$=30; }
                 | PostfixExpression L2_MINUSMINUS { $$=31; }
                 ;

ExpressionList: AssignmentExpression { $$=32; }
              | ExpressionList L2_COMMA AssignmentExpression { $$=33; }
              ;

ExpressionListOpt: /* empty */ { $$=34; }
                 | ExpressionList { $$=35; }
                 ;

UnaryExpression: PostfixExpression { $$=36; }
               | L2_PLUSPLUS CastExpression { $$=37; }
               | L2_MINUSMINUS CastExpression { $$=38; }
               | L2_SIZEOF UnaryExpression { $$=39; }
               | L2_STAR CastExpression %prec L2_STAR { $$=40; }
               | L2_AND CastExpression %prec L2_AND { $$=41; }
               | L2_PLUS CastExpression %prec L2_PLUS { $$=42; }
               | L2_MINUS CastExpression %prec L2_PLUS { $$=43; }
               | L2_BANG CastExpression { $$=44; }
               | L2_TILDE CastExpression { $$=45; }
               | L2_SIZEOF L2_LPAREN TypeId L2_RPAREN { $$=46; }
               | NewExpression { $$=47; }
               ;

NewExpression: L2_NEW TypeSpecifier { $$=48; }
             | L2_NEW L2_LPAREN TypeId L2_RPAREN { $$=49; }
             ;

CastExpression: UnaryExpression { $$=50; }
              | L2_LPAREN TypeId L2_RPAREN CastExpression { $$=51; }
              ;

BinaryExpression: CastExpression { $$=52; }
                | BinaryExpression L2_STAR BinaryExpression %prec L2_STAR { $$=53; }
                | BinaryExpression L2_SLASH BinaryExpression %prec L2_STAR { $$=54; }
                | BinaryExpression L2_PERCENT BinaryExpression %prec L2_STAR { $$=55; }
                | BinaryExpression L2_PLUS BinaryExpression %prec L2_PLUS { $$=56; }
                | BinaryExpression L2_MINUS BinaryExpression %prec L2_PLUS { $$=57; }
                | BinaryExpression L2_LEFTSHIFT BinaryExpression %prec L2_LEFTSHIFT { $$=58; }
                | BinaryExpression L2_RIGHTSHIFT BinaryExpression %prec L2_LEFTSHIFT { $$=59; }
                | BinaryExpression L2_LESSTHAN BinaryExpression %prec L2_LESSTHAN { $$=60; }
                | BinaryExpression L2_GREATERTHAN BinaryExpression %prec L2_LESSTHAN { $$=61; }
                | BinaryExpression L2_LESSEQ BinaryExpression %prec L2_LESSTHAN { $$=62; }
                | BinaryExpression L2_GREATEREQ BinaryExpression %prec L2_LESSTHAN { $$=63; }
                | BinaryExpression L2_EQUALEQUAL BinaryExpression %prec L2_EQUALEQUAL { $$=64; }
                | BinaryExpression L2_NOTEQUAL BinaryExpression %prec L2_EQUALEQUAL { $$=65; }
                | BinaryExpression L2_AND BinaryExpression %prec L2_AND { $$=66; }
                | BinaryExpression L2_XOR BinaryExpression %prec L2_XOR { $$=67; }
                | BinaryExpression L2_OR BinaryExpression %prec L2_OR { $$=68; }
                | BinaryExpression L2_ANDAND BinaryExpression %prec L2_ANDAND { $$=69; }
                | BinaryExpression L2_OROR BinaryExpression %prec L2_OROR { $$=70; }
                | BinaryExpression L2_IMPLIES BinaryExpression %prec L2_IMPLIES { $$=71; }
                ;

ConditionalExpression: BinaryExpression { $$=72; }
                     | BinaryExpression L2_QUESTION Expression L2_COLON AssignmentExpression { $$=73; }
                     ;

AssignmentExpression: ConditionalExpression { $$=74; }
                    | BinaryExpression AssignmentOperator AssignmentExpression { $$=75; }
                    ;

AssignmentOperator: L2_STAREQUAL { $$=76; }
                  | L2_SLASHEQUAL { $$=77; }
                  | L2_PERCENTEQUAL { $$=78; }
                  | L2_PLUSEQUAL { $$=79; }
                  | L2_MINUSEQUAL { $$=80; }
                  | L2_RIGHTSHIFTEQUAL { $$=81; }
                  | L2_LEFTSHIFTEQUAL { $$=82; }
                  | L2_ANDEQUAL { $$=83; }
                  | L2_XOREQUAL { $$=84; }
                  | L2_OREQUAL { $$=85; }
                  | L2_EQUAL { $$=86; }
                  ;

Expression: AssignmentExpression { $$=87; }
          | Expression L2_COMMA AssignmentExpression { $$=88; }
          ;

ExpressionOpt: /* empty */ { $$=89; }
             | Expression { $$=90; }
             ;

ConstantExpression: ConditionalExpression { $$=91; }
                  ;

Statement: L2_VARIABLE_NAME L2_COLON Statement { $$=92; }
         | L2_CASE ConstantExpression L2_COLON %prec L2_PREFER_SHIFT { $$=93; }
         | L2_CASE ConstantExpression L2_ELLIPSIS ConstantExpression L2_COLON { $$=94; }
         | L2_DEFAULT L2_COLON Statement { $$=95; }
         | ExpressionStatement { $$=96; }
         | CompoundStatement { $$=97; }
         | L2_IF L2_LPAREN Condition L2_RPAREN Statement %prec L2_PREFER_SHIFT { $$=98; }
         | L2_IF L2_LPAREN Condition L2_RPAREN Statement L2_ELSE Statement %prec L2_CONST { $$=99; }
         | L2_SWITCH L2_LPAREN Condition L2_RPAREN Statement { $$=100; }
         | L2_WHILE L2_LPAREN Condition L2_RPAREN Statement { $$=101; }
         | L2_DO Statement L2_WHILE L2_LPAREN Expression L2_RPAREN L2_SEMICOLON { $$=102; }
         | L2_FOR L2_LPAREN ForInitStatement ConditionOpt L2_SEMICOLON ExpressionOpt L2_RPAREN Statement { $$=103; }
         | L2_BREAK L2_SEMICOLON { $$=104; }
         | L2_CONTINUE L2_SEMICOLON { $$=105; }
         | L2_RETURN Expression L2_SEMICOLON { $$=106; }
         | L2_RETURN L2_SEMICOLON { $$=107; }
         | L2_GOTO L2_VARIABLE_NAME L2_SEMICOLON { $$=108; }
         | BlockDeclaration { $$=109; }
         | GNUAsmStatement { $$=110; }
         | L2_THMPRV_ASSERT Expression L2_SEMICOLON { $$=111; }
         | L2_THMPRV_PURE_ASSERT Expression L2_SEMICOLON { $$=112; }
         | L2_THMPRV_ASSUME Expression L2_SEMICOLON { $$=113; }
         | L2_THMPRV_INVARIANT Expression L2_SEMICOLON { $$=114; }
         | L2_THMPRV_LET Statement { $$=115; }
         ;

ExpressionStatement: L2_SEMICOLON { $$=116; }
                   | Expression L2_SEMICOLON { $$=117; }
                   ;

CompoundStatement: EnterScope L2_LBRACE StatementSeqOpt LeaveScope L2_RBRACE { $$=118; }
                 ;

StatementSeqOpt: /* empty */ { $$=119; }
               | StatementSeqOpt Statement { $$=120; }
               ;

Condition: Expression { $$=121; }
         ;

ConditionOpt: /* empty */ { $$=122; }
            | Condition { $$=123; }
            ;

ForInitStatement: ExpressionStatement { $$=124; }
                ;

Declaration: BlockDeclaration { $$=125; }
           | FunctionDefinition { $$=126; }
           ;

BlockDeclaration: SimpleDeclaration { $$=127; }
                ;

SimpleDeclaration: DeclSpecifier InitDeclaratorListOpt L2_SEMICOLON { $$=128; }
                 | L2_TYPEDEF DeclSpecifier TypedefDeclaratorList L2_SEMICOLON { $$=129; }
                 ;

DeclSpecifier: L2_INLINE DeclModifier TypeSpecifier { $$=130; }
             | DeclModifier L2_INLINE TypeSpecifier { $$=131; }
             | DeclModifier TypeSpecifier { $$=132; }
             | L2_INLINE TypeSpecifier { $$=133; }
             | TypeSpecifier { $$=134; }
             ;

DeclModifier: L2_VIRTUAL { $$=135; }
            | L2_FRIEND { $$=136; }
            | L2_MUTABLE { $$=137; }
            | L2_AUTO { $$=138; }
            | L2_REGISTER { $$=139; }
            | L2_STATIC { $$=140; }
            | L2_EXTERN { $$=141; }
            | L2_THMPRV_PREDICATE { $$=142; }
            ;

TypeSpecifier: PQTypeName { $$=143; }
             | SimpleTypeSpecifier { $$=144; }
             | ElaboratedTypeSpecifier { $$=145; }
             | ClassSpecifier { $$=146; }
             | EnumSpecifier { $$=147; }
             | CVQualifier TypeSpecifier %prec L2_PREFER_REDUCE { $$=148; }
             | TypeSpecifier CVQualifier %prec L2_PREFER_REDUCE { $$=149; }
             | TypeSpecifier GNUAttribute %prec L2_PREFER_REDUCE { $$=150; }
             ;

ElaboratedTypeSpecifier: ClassKeyword AnyName { $$=151; }
                       | L2_ENUM AnyName { $$=152; }
                       ;

SimpleTypeSpecifier: L2_CHAR { $$=153; }
                   | L2_UNSIGNED L2_CHAR { $$=154; }
                   | L2_SIGNED L2_CHAR { $$=155; }
                   | L2_BOOL { $$=156; }
                   | L2_UNSIGNED { $$=157; }
                   | L2_UNSIGNED L2_INT { $$=158; }
                   | L2_SIGNED { $$=159; }
                   | L2_SIGNED L2_INT { $$=160; }
                   | L2_INT { $$=161; }
                   | L2_UNSIGNED L2_SHORT L2_INT { $$=162; }
                   | L2_UNSIGNED L2_SHORT { $$=163; }
                   | L2_UNSIGNED L2_LONG L2_INT { $$=164; }
                   | L2_UNSIGNED L2_LONG { $$=165; }
                   | L2_SIGNED L2_LONG L2_INT { $$=166; }
                   | L2_SIGNED L2_LONG { $$=167; }
                   | L2_LONG L2_INT { $$=168; }
                   | L2_LONG { $$=169; }
                   | L2_SIGNED L2_LONG L2_LONG { $$=170; }
                   | L2_LONG L2_LONG { $$=171; }
                   | L2_UNSIGNED L2_LONG L2_LONG { $$=172; }
                   | L2_SIGNED L2_SHORT L2_INT { $$=173; }
                   | L2_SIGNED L2_SHORT { $$=174; }
                   | L2_SHORT L2_INT { $$=175; }
                   | L2_SHORT { $$=176; }
                   | L2_WCHAR_T { $$=177; }
                   | L2_FLOAT { $$=178; }
                   | L2_DOUBLE { $$=179; }
                   | L2_LONG L2_DOUBLE { $$=180; }
                   | L2_VOID { $$=181; }
                   ;

PQTypeName: TypeName { $$=182; }
          ;

EnumSpecifier: L2_ENUM L2_LBRACE EnumeratorListOpt L2_RBRACE { $$=183; }
             | L2_ENUM AnyName L2_LBRACE EnumeratorListOpt L2_RBRACE { $$=184; }
             ;

EnumeratorList: EnumeratorDefinition { $$=185; }
              | EnumeratorList L2_COMMA EnumeratorDefinition { $$=186; }
              ;

EnumeratorListOpt: /* empty */ { $$=187; }
                 | EnumeratorList CommaOpt { $$=188; }
                 ;

EnumeratorDefinition: AnyName { $$=189; }
                    | AnyName L2_EQUAL ConstantExpression { $$=190; }
                    ;

InitDeclaratorList: InitDeclarator { $$=191; }
                  | InitDeclaratorList L2_COMMA InitDeclarator { $$=192; }
                  ;

InitDeclaratorListOpt: /* empty */ { $$=193; }
                     | InitDeclaratorList { $$=194; }
                     ;

InitDeclarator: Declarator { $$=195; }
              | Declarator Initializer { $$=196; }
              ;

Initializer: L2_EQUAL InitializerClause { $$=197; }
           ;

InitializerClause: AssignmentExpression { $$=198; }
                 | CompoundInitializer { $$=199; }
                 ;

LabeledInitializerClause: InitializerClause { $$=200; }
                        | L2_LBRACKET ConstantExpression L2_RBRACKET L2_EQUAL InitializerClause { $$=201; }
                        | L2_LBRACKET ConstantExpression L2_ELLIPSIS ConstantExpression L2_RBRACKET L2_EQUAL InitializerClause { $$=202; }
                        | L2_DOT PQVarName L2_EQUAL InitializerClause { $$=203; }
                        | L2_LBRACKET ConstantExpression L2_RBRACKET L2_DOT PQVarName L2_EQUAL InitializerClause { $$=204; }
                        ;

CompoundInitializer: L2_LBRACE InitializerList CommaOpt L2_RBRACE { $$=205; }
                   | L2_LBRACE L2_RBRACE { $$=206; }
                   ;

CommaOpt: /* empty */ { $$=207; }
        | L2_COMMA { $$=208; }
        ;

InitializerList: LabeledInitializerClause { $$=209; }
               | InitializerList L2_COMMA LabeledInitializerClause { $$=210; }
               ;

Declarator: PtrOperator Declarator { $$=211; }
          | DirectDeclarator GNUAttribute { $$=212; }
          | DirectDeclarator { $$=213; }
          ;

DirectDeclarator: AnyName ThmprvAttr { $$=214; }
                | DirectDeclarator L2_LPAREN ParameterDeclarationClause L2_RPAREN FuncAnnotationsOpt { $$=215; }
                | DirectDeclarator L2_LBRACKET ConstantExpression L2_RBRACKET { $$=216; }
                | DirectDeclarator L2_LBRACKET L2_RBRACKET { $$=217; }
                | L2_LPAREN Declarator L2_RPAREN { $$=218; }
                ;

PtrOperator: L2_STAR CVQualifierSeqOpt %prec L2_STAR { $$=219; }
           ;

CVQualifierSeqOpt: /* empty */ { $$=220; }
                 | CVQualifierSeq { $$=221; }
                 ;

CVQualifierSeq: CVQualifier { $$=222; }
              | CVQualifier CVQualifierSeq { $$=223; }
              ;

CVQualifier: L2_CONST %prec L2_CONST { $$=224; }
           | L2_VOLATILE %prec L2_CONST { $$=225; }
           | L2_OWNER %prec L2_CONST { $$=226; }
           ;

TypedefDeclaratorList: TypedefDeclarator { $$=227; }
                     | TypedefDeclaratorList L2_COMMA TypedefDeclarator { $$=228; }
                     ;

TypedefDeclarator: PtrOperator TypedefDeclarator { $$=229; }
                 | DirectTypedefDeclarator { $$=230; }
                 ;

DirectTypedefDeclarator: AnyName { $$=231; }
                       | DirectTypedefDeclarator L2_LPAREN ParameterDeclarationClause L2_RPAREN FuncAnnotationsOpt { $$=232; }
                       | DirectTypedefDeclarator L2_LBRACKET ConstantExpression L2_RBRACKET { $$=233; }
                       | DirectTypedefDeclarator L2_LBRACKET L2_RBRACKET { $$=234; }
                       | L2_LPAREN TypedefDeclarator L2_RPAREN { $$=235; }
                       ;

TypeId: TypeSpecifier AbstractDeclaratorOpt { $$=236; }
      ;

AbstractDeclaratorOpt: /* empty */ { $$=237; }
                     | AbstractDeclarator { $$=238; }
                     ;

AbstractDeclarator: PtrOperator AbstractDeclaratorOpt { $$=239; }
                  | DirectAbstractDeclarator { $$=240; }
                  ;

DirectAbstractDeclaratorOpt: /* empty */ { $$=241; }
                           | DirectAbstractDeclarator { $$=242; }
                           ;

DirectAbstractDeclarator: DirectAbstractDeclarator L2_LPAREN ParameterDeclarationClause L2_RPAREN FuncAnnotationsOpt { $$=243; }
                        | DirectAbstractDeclaratorOpt L2_LBRACKET ConstantExpression L2_RBRACKET { $$=244; }
                        | DirectAbstractDeclaratorOpt L2_LBRACKET L2_RBRACKET { $$=245; }
                        | L2_LPAREN AbstractDeclarator L2_RPAREN { $$=246; }
                        ;

ParameterDeclarationClause: ParameterDeclarationList { $$=247; }
                          | /* empty */ { $$=248; }
                          | L2_ELLIPSIS { $$=249; }
                          | ParameterDeclarationList L2_ELLIPSIS { $$=250; }
                          | ParameterDeclarationList L2_COMMA L2_ELLIPSIS { $$=251; }
                          ;

ParameterDeclarationList: ParameterDeclaration { $$=252; }
                        | ParameterDeclarationList L2_COMMA ParameterDeclaration { $$=253; }
                        ;

ParameterDeclaration: RegisterOpt TypeSpecifier Declarator { $$=254; }
                    | RegisterOpt TypeSpecifier AbstractDeclaratorOpt { $$=255; }
                    ;

RegisterOpt: /* empty */ { $$=256; }
           | L2_REGISTER { $$=257; }
           ;

FunctionDefinition: DeclSpecifier Declarator FunctionBody { $$=258; }
                  ;

FunctionBody: CompoundStatement { $$=259; }
            ;

ClassSpecifier: ClassKeyword ClassNameOpt L2_LBRACE MemberDeclarationSeqOpt L2_RBRACE { $$=260; }
              ;

ClassNameOpt: /* empty */ { $$=261; }
            | AnyName { $$=262; }
            ;

ClassKeyword: L2_CLASS { $$=263; }
            | L2_STRUCT { $$=264; }
            | L2_UNION { $$=265; }
            ;

MemberDeclarationSeqOpt: /* empty */ { $$=266; }
                       | MemberDeclarationSeqOpt MemberDeclaration { $$=267; }
                       ;

MemberDeclaration: DeclSpecifier MemberDeclaratorList L2_SEMICOLON { $$=268; }
                 ;

MemberDeclaratorList: MemberDeclarator { $$=269; }
                    | MemberDeclaratorList L2_COMMA MemberDeclarator { $$=270; }
                    ;

MemberDeclarator: Declarator { $$=271; }
                | L2_COLON ConstantExpression { $$=272; }
                | L2_COLON ConstantExpression GNUAttribute { $$=273; }
                | AnyName L2_COLON ConstantExpression GNUAttribute { $$=274; }
                | AnyName L2_COLON ConstantExpression { $$=275; }
                ;

GNUExprOp: L2_LBRACKET { $$=276; }
         | L2_RBRACKET { $$=277; }
         | L2_ARROW { $$=278; }
         | L2_COLONCOLON { $$=279; }
         | L2_DOT { $$=280; }
         | L2_BANG { $$=281; }
         | L2_TILDE { $$=282; }
         | L2_PLUS %prec L2_PLUS { $$=283; }
         | L2_MINUS %prec L2_PLUS { $$=284; }
         | L2_PLUSPLUS { $$=285; }
         | L2_MINUSMINUS { $$=286; }
         | L2_AND %prec L2_AND { $$=287; }
         | L2_STAR %prec L2_STAR { $$=288; }
         | L2_DOTSTAR %prec L2_DOTSTAR { $$=289; }
         | L2_ARROWSTAR %prec L2_DOTSTAR { $$=290; }
         | L2_SLASH %prec L2_STAR { $$=291; }
         | L2_PERCENT %prec L2_STAR { $$=292; }
         | L2_LEFTSHIFT %prec L2_LEFTSHIFT { $$=293; }
         | L2_RIGHTSHIFT %prec L2_LEFTSHIFT { $$=294; }
         | L2_LESSTHAN %prec L2_LESSTHAN { $$=295; }
         | L2_LESSEQ %prec L2_LESSTHAN { $$=296; }
         | L2_GREATERTHAN %prec L2_LESSTHAN { $$=297; }
         | L2_GREATEREQ %prec L2_LESSTHAN { $$=298; }
         | L2_EQUALEQUAL %prec L2_EQUALEQUAL { $$=299; }
         | L2_NOTEQUAL %prec L2_EQUALEQUAL { $$=300; }
         | L2_XOR %prec L2_XOR { $$=301; }
         | L2_OR %prec L2_OR { $$=302; }
         | L2_ANDAND %prec L2_ANDAND { $$=303; }
         | L2_OROR %prec L2_OROR { $$=304; }
         | L2_QUESTION { $$=305; }
         | L2_COLON { $$=306; }
         | L2_EQUAL { $$=307; }
         | L2_STAREQUAL { $$=308; }
         | L2_SLASHEQUAL { $$=309; }
         | L2_PERCENTEQUAL { $$=310; }
         | L2_PLUSEQUAL { $$=311; }
         | L2_MINUSEQUAL { $$=312; }
         | L2_ANDEQUAL { $$=313; }
         | L2_XOREQUAL { $$=314; }
         | L2_OREQUAL { $$=315; }
         | L2_LEFTSHIFTEQUAL { $$=316; }
         | L2_RIGHTSHIFTEQUAL { $$=317; }
         | L2_COMMA { $$=318; }
         | L2_ELLIPSIS { $$=319; }
         | L2_SEMICOLON { $$=320; }
         | L2_LBRACE { $$=321; }
         | L2_RBRACE { $$=322; }
         ;

GNUExprKeyword: L2_ASM { $$=323; }
              | L2_AUTO { $$=324; }
              | L2_BREAK { $$=325; }
              | L2_BOOL { $$=326; }
              | L2_CASE { $$=327; }
              | L2_CATCH { $$=328; }
              | L2_CDECL { $$=329; }
              | L2_CHAR { $$=330; }
              | L2_CLASS { $$=331; }
              | L2_CONST %prec L2_CONST { $$=332; }
              | L2_CONST_CAST { $$=333; }
              | L2_CONTINUE { $$=334; }
              | L2_DEFAULT { $$=335; }
              | L2_DELETE { $$=336; }
              | L2_DO { $$=337; }
              | L2_DOUBLE { $$=338; }
              | L2_DYNAMIC_CAST { $$=339; }
              | L2_ELSE %prec L2_CONST { $$=340; }
              | L2_ENUM { $$=341; }
              | L2_EXPLICIT { $$=342; }
              | L2_EXTERN { $$=343; }
              | L2_FLOAT { $$=344; }
              | L2_FOR { $$=345; }
              | L2_FRIEND { $$=346; }
              | L2_GOTO { $$=347; }
              | L2_IF { $$=348; }
              | L2_INLINE { $$=349; }
              | L2_INT { $$=350; }
              | L2_LONG { $$=351; }
              | L2_MUTABLE { $$=352; }
              | L2_NEW { $$=353; }
              | L2_OPERATOR { $$=354; }
              | L2_PASCAL { $$=355; }
              | L2_PRIVATE { $$=356; }
              | L2_PROTECTED { $$=357; }
              | L2_PUBLIC { $$=358; }
              | L2_REGISTER { $$=359; }
              | L2_REINTERPRET_CAST { $$=360; }
              | L2_RETURN { $$=361; }
              | L2_SHORT { $$=362; }
              | L2_SIGNED { $$=363; }
              | L2_SIZEOF { $$=364; }
              | L2_STATIC { $$=365; }
              | L2_STATIC_CAST { $$=366; }
              | L2_STRUCT { $$=367; }
              | L2_SWITCH { $$=368; }
              | L2_TEMPLATE { $$=369; }
              | L2_THIS { $$=370; }
              | L2_THROW { $$=371; }
              | L2_TRY { $$=372; }
              | L2_TYPEDEF { $$=373; }
              | L2_TYPEID { $$=374; }
              | L2_UNION { $$=375; }
              | L2_UNSIGNED { $$=376; }
              | L2_VIRTUAL { $$=377; }
              | L2_VOID { $$=378; }
              | L2_VOLATILE %prec L2_CONST { $$=379; }
              | L2_WCHAR_T { $$=380; }
              | L2_WHILE { $$=381; }
              | L2___TYPEOF__ { $$=382; }
              ;

GNUAttribute: L2___ATTRIBUTE__ L2_LPAREN L2_LPAREN GNUExprSeq L2_RPAREN L2_RPAREN { $$=383; }
            ;

GNUExprSeq: /* empty */ { $$=384; }
          | GNUExpr GNUExprSeq { $$=385; }
          ;

GNUExpr: L2_LPAREN GNUExprSeq L2_RPAREN { $$=386; }
       | AnyName { $$=387; }
       | GNUExprOp { $$=388; }
       | GNUExprKeyword { $$=389; }
       | L2_INT_LITERAL { $$=390; }
       | L2_STRING_LITERAL { $$=391; }
       ;

GNUAsmStatement: L2_ASM L2_LPAREN GNUExprSeq L2_RPAREN L2_SEMICOLON { $$=392; }
               | L2_ASM L2_VOLATILE L2_LPAREN GNUExprSeq L2_RPAREN L2_SEMICOLON { $$=393; }
               ;

FuncAnnotationsOpt: /* empty */ { $$=394; }
                  | FuncAnnotationsOpt FuncAnnotation { $$=395; }
                  ;

FuncAnnotation: L2_THMPRV_PRE L2_LPAREN FADeclListOpt Expression L2_RPAREN { $$=396; }
              | L2_THMPRV_POST L2_LPAREN Expression L2_RPAREN { $$=397; }
              ;

FADeclListOpt: /* empty */ { $$=398; }
             | FADeclList { $$=399; }
             ;

FADeclList: SimpleDeclaration { $$=400; }
          | FADeclList SimpleDeclaration { $$=401; }
          ;

ThmprvAttr: /* empty */ { $$=402; }
          | L2_THMPRV_ATTR L2_LPAREN ThmprvAttrList L2_RPAREN { $$=403; }
          ;

ThmprvAttrList: OneThmprvAttr { $$=404; }
              | ThmprvAttrList L2_COMMA OneThmprvAttr { $$=405; }
              ;

OneThmprvAttr: AnyName { $$=406; }
             | AnyName L2_LPAREN ThmprvAttrList L2_RPAREN { $$=407; }
             ;

ThmprvPredicate: L2_THMPRV_FORALL L2_LPAREN FADeclList Expression L2_RPAREN { $$=408; }
               | L2_THMPRV_EXISTS L2_LPAREN FADeclList Expression L2_RPAREN { $$=409; }
               ;

