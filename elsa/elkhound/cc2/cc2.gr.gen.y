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
/* high precedence */


/* -------- productions ------ */
%%

__EarlyStartSymbol: StartSymbol L2_EOF { $$=0; }
                  ;

StartSymbol: TranslationUnit { $$=1; }
           ;

Identifier: L2_NAME { $$=2; }
          ;

IntegerLiteral: L2_INT_LITERAL { $$=3; }
              ;

CharacterLiteral: L2_CHAR_LITERAL { $$=4; }
                ;

FloatingLiteral: L2_FLOAT_LITERAL { $$=5; }
               ;

StringLiteral: L2_STRING_LITERAL { $$=6; }
             ;

BooleanLiteral: L2_TRUE { $$=7; }
              | L2_FALSE { $$=8; }
              ;

TypedefName: Identifier { $$=9; }
           ;

NamespaceName: OriginalNamespaceName { $$=10; }
             | NamespaceAlias { $$=11; }
             ;

OriginalNamespaceName: Identifier { $$=12; }
                     ;

NamespaceAlias: Identifier { $$=13; }
              ;

ClassName: Identifier { $$=14; }
         | TemplateId { $$=15; }
         ;

EnumName: Identifier { $$=16; }
        ;

TemplateName: Identifier { $$=17; }
            ;

Literal: IntegerLiteral { $$=18; }
       | CharacterLiteral { $$=19; }
       | FloatingLiteral { $$=20; }
       | StringLiteral { $$=21; }
       | BooleanLiteral { $$=22; }
       ;

TranslationUnit: DeclarationSeqOpt { $$=23; }
               ;

PrimaryExpression: Literal { $$=24; }
                 | L2_THIS { $$=25; }
                 | L2_LPAREN Expression L2_RPAREN { $$=26; }
                 | IdExpression { $$=27; }
                 ;

IdExpression: UnqualifiedId { $$=28; }
            | QualifiedId { $$=29; }
            ;

UnqualifiedId: Identifier { $$=30; }
             | OperatorFunctionId { $$=31; }
             | ConversionFunctionId { $$=32; }
             | L2_TILDE ClassName { $$=33; }
             | TemplateId { $$=34; }
             ;

ColonColonOpt: /* empty */ { $$=35; }
             | L2_COLONCOLON { $$=36; }
             ;

TemplateOpt: /* empty */ { $$=37; }
           | L2_TEMPLATE { $$=38; }
           ;

QualifiedId: ColonColonOpt NestedNameSpecifier TemplateOpt UnqualifiedId { $$=39; }
           | L2_COLONCOLON Identifier { $$=40; }
           | L2_COLONCOLON OperatorFunctionId { $$=41; }
           | L2_COLONCOLON TemplateId { $$=42; }
           ;

NestedNameSpecifierOpt: /* empty */ { $$=43; }
                      | NestedNameSpecifier { $$=44; }
                      ;

NestedNameSpecifier: ClassOrNamespaceName L2_COLONCOLON NestedNameSpecifierOpt { $$=45; }
                   | ClassOrNamespaceName L2_COLONCOLON L2_TEMPLATE NestedNameSpecifier { $$=46; }
                   ;

ClassOrNamespaceName: ClassName { $$=47; }
                    | NamespaceName { $$=48; }
                    ;

ExpressionListOpt: /* empty */ { $$=49; }
                 | ExpressionList { $$=50; }
                 ;

PostfixExpression: PrimaryExpression { $$=51; }
                 | PostfixExpression L2_LBRACKET Expression L2_RBRACKET { $$=52; }
                 | PostfixExpression L2_LPAREN ExpressionListOpt L2_RPAREN { $$=53; }
                 | SimpleTypeSpecifier L2_LPAREN ExpressionListOpt L2_RPAREN { $$=54; }
                 | L2_TYPENAME ColonColonOpt NestedNameSpecifier Identifier L2_LPAREN ExpressionListOpt L2_RPAREN { $$=55; }
                 | L2_TYPENAME ColonColonOpt NestedNameSpecifier TemplateOpt TemplateId L2_LPAREN ExpressionListOpt L2_RPAREN { $$=56; }
                 | PostfixExpression L2_DOT TemplateOpt IdExpression { $$=57; }
                 | PostfixExpression L2_ARROW TemplateOpt IdExpression { $$=58; }
                 | PostfixExpression L2_DOT PseudoDestructorName { $$=59; }
                 | PostfixExpression L2_ARROW PseudoDestructorName { $$=60; }
                 | PostfixExpression L2_PLUSPLUS { $$=61; }
                 | PostfixExpression L2_MINUSMINUS { $$=62; }
                 | L2_DYNAMIC_CAST L2_LESSTHAN TypeId L2_GREATERTHAN L2_LPAREN Expression L2_RPAREN { $$=63; }
                 | L2_STATIC_CAST L2_LESSTHAN TypeId L2_GREATERTHAN L2_LPAREN Expression L2_RPAREN { $$=64; }
                 | L2_REINTERPRET_CAST L2_LESSTHAN TypeId L2_GREATERTHAN L2_LPAREN Expression L2_RPAREN { $$=65; }
                 | L2_CONST_CAST L2_LESSTHAN TypeId L2_GREATERTHAN L2_LPAREN Expression L2_RPAREN { $$=66; }
                 | L2_TYPEID L2_LPAREN Expression L2_RPAREN { $$=67; }
                 | L2_TYPEID L2_LPAREN TypeId L2_RPAREN { $$=68; }
                 ;

ExpressionList: AssignmentExpression { $$=69; }
              | ExpressionList L2_COMMA AssignmentExpression { $$=70; }
              ;

PseudoDestructorName: ColonColonOpt NestedNameSpecifierOpt TypeName L2_COLONCOLON L2_TILDE TypeName { $$=71; }
                    | ColonColonOpt NestedNameSpecifier L2_TEMPLATE TemplateId L2_COLONCOLON L2_TILDE TypeName { $$=72; }
                    | ColonColonOpt NestedNameSpecifierOpt L2_TILDE TypeName { $$=73; }
                    ;

UnaryExpression: PostfixExpression { $$=74; }
               | L2_PLUSPLUS CastExpression { $$=75; }
               | L2_MINUSMINUS CastExpression { $$=76; }
               | UnaryOperator CastExpression { $$=77; }
               | L2_SIZEOF UnaryExpression { $$=78; }
               | L2_SIZEOF L2_LPAREN TypeId L2_RPAREN { $$=79; }
               | NewExpression { $$=80; }
               | DeleteExpression { $$=81; }
               ;

UnaryOperator: L2_STAR { $$=82; }
             | L2_AND { $$=83; }
             | L2_PLUS { $$=84; }
             | L2_MINUS { $$=85; }
             | L2_BANG { $$=86; }
             | L2_TILDE { $$=87; }
             ;

NewPlacementOpt: /* empty */ { $$=88; }
               | NewPlacement { $$=89; }
               ;

NewInitializerOpt: /* empty */ { $$=90; }
                 | NewInitializer { $$=91; }
                 ;

NewExpression: ColonColonOpt L2_NEW NewPlacementOpt NewTypeId NewInitializerOpt { $$=92; }
             | ColonColonOpt L2_NEW NewPlacementOpt L2_LPAREN TypeId L2_RPAREN NewInitializerOpt { $$=93; }
             ;

NewPlacement: L2_LPAREN ExpressionList L2_RPAREN { $$=94; }
            ;

NewDeclaratorOpt: /* empty */ { $$=95; }
                | NewDeclarator { $$=96; }
                ;

NewTypeId: TypeSpecifierSeq NewDeclaratorOpt { $$=97; }
         ;

NewDeclarator: PtrOperator NewDeclaratorOpt { $$=98; }
             | DirectNewDeclarator { $$=99; }
             ;

DirectNewDeclarator: L2_LBRACKET Expression L2_RBRACKET { $$=100; }
                   | DirectNewDeclarator L2_LBRACKET ConstantExpression L2_RBRACKET { $$=101; }
                   ;

NewInitializer: L2_LPAREN ExpressionListOpt L2_RPAREN { $$=102; }
              ;

DeleteExpression: ColonColonOpt L2_DELETE CastExpression { $$=103; }
                | ColonColonOpt L2_DELETE L2_LBRACKET L2_RBRACKET CastExpression { $$=104; }
                ;

CastExpression: UnaryExpression { $$=105; }
              | L2_LPAREN TypeId L2_RPAREN CastExpression { $$=106; }
              ;

PmExpression: CastExpression { $$=107; }
            | PmExpression L2_DOTSTAR CastExpression { $$=108; }
            | PmExpression L2_ARROWSTAR CastExpression { $$=109; }
            ;

MultiplicativeExpression: PmExpression { $$=110; }
                        | MultiplicativeExpression L2_STAR PmExpression { $$=111; }
                        | MultiplicativeExpression L2_SLASH PmExpression { $$=112; }
                        | MultiplicativeExpression L2_PERCENT PmExpression { $$=113; }
                        ;

AdditiveExpression: MultiplicativeExpression { $$=114; }
                  | AdditiveExpression L2_PLUS MultiplicativeExpression { $$=115; }
                  | AdditiveExpression L2_MINUS MultiplicativeExpression { $$=116; }
                  ;

ShiftExpression: AdditiveExpression { $$=117; }
               | ShiftExpression L2_LEFTSHIFT AdditiveExpression { $$=118; }
               | ShiftExpression L2_RIGHTSHIFT AdditiveExpression { $$=119; }
               ;

RelationalExpression: ShiftExpression { $$=120; }
                    | RelationalExpression L2_LESSTHAN ShiftExpression { $$=121; }
                    | RelationalExpression L2_GREATERTHAN ShiftExpression { $$=122; }
                    | RelationalExpression L2_LESSEQ ShiftExpression { $$=123; }
                    | RelationalExpression L2_GREATEREQ ShiftExpression { $$=124; }
                    ;

EqualityExpression: RelationalExpression { $$=125; }
                  | EqualityExpression L2_EQUALEQUAL RelationalExpression { $$=126; }
                  | EqualityExpression L2_NOTEQUAL RelationalExpression { $$=127; }
                  ;

AndExpression: EqualityExpression { $$=128; }
             | AndExpression L2_AND EqualityExpression { $$=129; }
             ;

ExclusiveOrExpression: AndExpression { $$=130; }
                     | ExclusiveOrExpression L2_XOR AndExpression { $$=131; }
                     ;

InclusiveOrExpression: ExclusiveOrExpression { $$=132; }
                     | InclusiveOrExpression L2_OR ExclusiveOrExpression { $$=133; }
                     ;

LogicalAndExpression: InclusiveOrExpression { $$=134; }
                    | LogicalAndExpression L2_ANDAND InclusiveOrExpression { $$=135; }
                    ;

LogicalOrExpression: LogicalAndExpression { $$=136; }
                   | LogicalOrExpression L2_OROR LogicalAndExpression { $$=137; }
                   ;

ConditionalExpression: LogicalOrExpression { $$=138; }
                     | LogicalOrExpression L2_QUESTION Expression L2_COLON AssignmentExpression { $$=139; }
                     ;

AssignmentExpression: ConditionalExpression { $$=140; }
                    | LogicalOrExpression AssignmentOperator AssignmentExpression { $$=141; }
                    | ThrowExpression { $$=142; }
                    ;

AssignmentOperator: L2_EQUAL { $$=143; }
                  | L2_STAREQUAL { $$=144; }
                  | L2_SLASHEQUAL { $$=145; }
                  | L2_PERCENTEQUAL { $$=146; }
                  | L2_PLUSEQUAL { $$=147; }
                  | L2_MINUSEQUAL { $$=148; }
                  | L2_RIGHTSHIFTEQUAL { $$=149; }
                  | L2_LEFTSHIFTEQUAL { $$=150; }
                  | L2_ANDEQUAL { $$=151; }
                  | L2_XOREQUAL { $$=152; }
                  | L2_OREQUAL { $$=153; }
                  ;

Expression: AssignmentExpression { $$=154; }
          | Expression L2_COMMA AssignmentExpression { $$=155; }
          ;

ConstantExpression: ConditionalExpression { $$=156; }
                  ;

Statement: LabeledStatement { $$=157; }
         | ExpressionStatement { $$=158; }
         | CompoundStatement { $$=159; }
         | SelectionStatement { $$=160; }
         | IterationStatement { $$=161; }
         | JumpStatement { $$=162; }
         | DeclarationStatement { $$=163; }
         | TryBlock { $$=164; }
         ;

LabeledStatement: Identifier L2_COLON Statement { $$=165; }
                | L2_CASE ConstantExpression L2_COLON Statement { $$=166; }
                | L2_DEFAULT L2_COLON Statement { $$=167; }
                ;

ExpressionOpt: /* empty */ { $$=168; }
             | Expression { $$=169; }
             ;

ExpressionStatement: ExpressionOpt L2_SEMICOLON { $$=170; }
                   ;

StatementSeqOpt: /* empty */ { $$=171; }
               | StatementSeq { $$=172; }
               ;

CompoundStatement: L2_LBRACE StatementSeqOpt L2_RBRACE { $$=173; }
                 ;

StatementSeq: Statement { $$=174; }
            | StatementSeq Statement { $$=175; }
            ;

SelectionStatement: L2_IF L2_LPAREN Condition L2_RPAREN Statement { $$=176; }
                  | L2_IF L2_LPAREN Condition L2_RPAREN Statement L2_ELSE Statement { $$=177; }
                  | L2_SWITCH L2_LPAREN Condition L2_RPAREN Statement { $$=178; }
                  ;

Condition: Expression { $$=179; }
         | TypeSpecifierSeq Declarator L2_EQUAL AssignmentExpression { $$=180; }
         ;

ConditionOpt: /* empty */ { $$=181; }
            | Condition { $$=182; }
            ;

IterationStatement: L2_WHILE L2_LPAREN Condition L2_RPAREN Statement { $$=183; }
                  | L2_DO Statement L2_WHILE L2_LPAREN Expression L2_RPAREN L2_SEMICOLON { $$=184; }
                  | L2_FOR L2_LPAREN ForInitStatement ConditionOpt L2_SEMICOLON ExpressionOpt L2_RPAREN Statement { $$=185; }
                  ;

ForInitStatement: ExpressionStatement { $$=186; }
                | SimpleDeclaration { $$=187; }
                ;

JumpStatement: L2_BREAK L2_SEMICOLON { $$=188; }
             | L2_CONTINUE L2_SEMICOLON { $$=189; }
             | L2_RETURN ExpressionOpt L2_SEMICOLON { $$=190; }
             | L2_GOTO Identifier L2_SEMICOLON { $$=191; }
             ;

DeclarationStatement: BlockDeclaration { $$=192; }
                    ;

DeclarationSeq: Declaration { $$=193; }
              | DeclarationSeq Declaration { $$=194; }
              ;

Declaration: BlockDeclaration { $$=195; }
           | FunctionDefinition { $$=196; }
           | TemplateDeclaration { $$=197; }
           | ExplicitInstantiation { $$=198; }
           | ExplicitSpecialization { $$=199; }
           | LinkageSpecification { $$=200; }
           | NamespaceDefinition { $$=201; }
           ;

BlockDeclaration: SimpleDeclaration { $$=202; }
                | AsmDefinition { $$=203; }
                | NamespaceAliasDefinition { $$=204; }
                | UsingDeclaration { $$=205; }
                | UsingDirective { $$=206; }
                ;

DeclSpecifierSeqOpt: /* empty */ { $$=207; }
                   | DeclSpecifierSeq { $$=208; }
                   ;

InitDeclaratorListOpt: /* empty */ { $$=209; }
                     | InitDeclaratorList { $$=210; }
                     ;

SimpleDeclaration: DeclSpecifierSeqOpt InitDeclaratorListOpt L2_SEMICOLON { $$=211; }
                 ;

DeclSpecifier: StorageClassSpecifier { $$=212; }
             | TypeSpecifier { $$=213; }
             | FunctionSpecifier { $$=214; }
             | L2_FRIEND { $$=215; }
             | L2_TYPEDEF { $$=216; }
             ;

DeclSpecifierSeq: DeclSpecifierSeqOpt DeclSpecifier { $$=217; }
                ;

StorageClassSpecifier: L2_AUTO { $$=218; }
                     | L2_REGISTER { $$=219; }
                     | L2_STATIC { $$=220; }
                     | L2_EXTERN { $$=221; }
                     | L2_MUTABLE { $$=222; }
                     ;

FunctionSpecifier: L2_INLINE { $$=223; }
                 | L2_VIRTUAL { $$=224; }
                 | L2_EXPLICIT { $$=225; }
                 ;

TypeSpecifier: SimpleTypeSpecifier { $$=226; }
             | ClassSpecifier { $$=227; }
             | EnumSpecifier { $$=228; }
             | ElaboratedTypeSpecifier { $$=229; }
             | CvQualifier { $$=230; }
             ;

SimpleTypeSpecifier: ColonColonOpt NestedNameSpecifierOpt TypeName { $$=231; }
                   | ColonColonOpt NestedNameSpecifier L2_TEMPLATE TemplateId { $$=232; }
                   | L2_CHAR { $$=233; }
                   | L2_WCHAR_T { $$=234; }
                   | L2_BOOL { $$=235; }
                   | L2_SHORT { $$=236; }
                   | L2_INT { $$=237; }
                   | L2_LONG { $$=238; }
                   | L2_SIGNED { $$=239; }
                   | L2_UNSIGNED { $$=240; }
                   | L2_FLOAT { $$=241; }
                   | L2_DOUBLE { $$=242; }
                   | L2_VOID { $$=243; }
                   ;

TypeName: ClassName { $$=244; }
        | EnumName { $$=245; }
        | TypedefName { $$=246; }
        ;

ElaboratedTypeSpecifier: ClassKey ColonColonOpt NestedNameSpecifierOpt Identifier { $$=247; }
                       | L2_ENUM ColonColonOpt NestedNameSpecifierOpt Identifier { $$=248; }
                       | L2_TYPENAME ColonColonOpt NestedNameSpecifier Identifier { $$=249; }
                       | L2_TYPENAME ColonColonOpt NestedNameSpecifier TemplateOpt TemplateId { $$=250; }
                       ;

IdentifierOpt: /* empty */ { $$=251; }
             | Identifier { $$=252; }
             ;

EnumeratorListOpt: /* empty */ { $$=253; }
                 | EnumeratorList { $$=254; }
                 ;

EnumSpecifier: L2_ENUM IdentifierOpt L2_LBRACE EnumeratorListOpt L2_RBRACE { $$=255; }
             ;

EnumeratorList: EnumeratorDefinition { $$=256; }
              | EnumeratorList L2_COMMA EnumeratorDefinition { $$=257; }
              ;

EnumeratorDefinition: Enumerator { $$=258; }
                    | Enumerator L2_EQUAL ConstantExpression { $$=259; }
                    ;

Enumerator: Identifier { $$=260; }
          ;

NamespaceDefinition: NamedNamespaceDefinition { $$=261; }
                   | UnnamedNamespaceDefinition { $$=262; }
                   ;

NamedNamespaceDefinition: OriginalNamespaceDefinition { $$=263; }
                        | ExtensionNamespaceDefinition { $$=264; }
                        ;

OriginalNamespaceDefinition: L2_NAMESPACE Identifier L2_LBRACE NamespaceBody L2_RBRACE { $$=265; }
                           ;

ExtensionNamespaceDefinition: L2_NAMESPACE OriginalNamespaceName L2_LBRACE NamespaceBody L2_RBRACE { $$=266; }
                            ;

UnnamedNamespaceDefinition: L2_NAMESPACE L2_LBRACE NamespaceBody L2_RBRACE { $$=267; }
                          ;

DeclarationSeqOpt: /* empty */ { $$=268; }
                 | DeclarationSeq { $$=269; }
                 ;

NamespaceBody: DeclarationSeqOpt { $$=270; }
             ;

NamespaceAliasDefinition: L2_NAMESPACE Identifier L2_EQUAL QualifiedNamespaceSpecifier L2_SEMICOLON { $$=271; }
                        ;

QualifiedNamespaceSpecifier: ColonColonOpt NestedNameSpecifierOpt NamespaceName { $$=272; }
                           ;

TypenameOpt: /* empty */ { $$=273; }
           | L2_TYPENAME { $$=274; }
           ;

UsingDeclaration: L2_USING TypenameOpt ColonColonOpt NestedNameSpecifier UnqualifiedId L2_SEMICOLON { $$=275; }
                | L2_USING L2_COLONCOLON UnqualifiedId L2_SEMICOLON { $$=276; }
                ;

UsingDirective: L2_USING L2_NAMESPACE ColonColonOpt NestedNameSpecifierOpt NamespaceName L2_SEMICOLON { $$=277; }
              ;

AsmDefinition: L2_ASM L2_LPAREN StringLiteral L2_RPAREN L2_SEMICOLON { $$=278; }
             ;

LinkageSpecification: L2_EXTERN StringLiteral L2_LBRACE DeclarationSeqOpt L2_RBRACE { $$=279; }
                    | L2_EXTERN StringLiteral Declaration { $$=280; }
                    ;

InitDeclaratorList: InitDeclarator { $$=281; }
                  | InitDeclaratorList L2_COMMA InitDeclarator { $$=282; }
                  ;

InitializerOpt: /* empty */ { $$=283; }
              | Initializer { $$=284; }
              ;

InitDeclarator: Declarator InitializerOpt { $$=285; }
              ;

Declarator: DirectDeclarator { $$=286; }
          | PtrOperator Declarator { $$=287; }
          ;

CvQualifierSeqOpt: /* empty */ { $$=288; }
                 | CvQualifierSeq { $$=289; }
                 ;

ExceptionSpecificationOpt: /* empty */ { $$=290; }
                         | ExceptionSpecification { $$=291; }
                         ;

ConstantExpressionOpt: /* empty */ { $$=292; }
                     | ConstantExpression { $$=293; }
                     ;

DirectDeclarator: DeclaratorId { $$=294; }
                | DirectDeclarator L2_LPAREN ParameterDeclarationClause L2_RPAREN CvQualifierSeqOpt ExceptionSpecificationOpt { $$=295; }
                | DirectDeclarator L2_LBRACKET ConstantExpressionOpt L2_RBRACKET { $$=296; }
                | L2_LPAREN Declarator L2_RPAREN { $$=297; }
                ;

PtrOperator: L2_STAR CvQualifierSeqOpt { $$=298; }
           | L2_AND { $$=299; }
           | ColonColonOpt NestedNameSpecifier L2_STAR CvQualifierSeqOpt { $$=300; }
           ;

CvQualifierSeq: CvQualifier CvQualifierSeqOpt { $$=301; }
              ;

CvQualifier: L2_CONST { $$=302; }
           | L2_VOLATILE { $$=303; }
           ;

DeclaratorId: IdExpression { $$=304; }
            | ColonColonOpt NestedNameSpecifierOpt TypeName { $$=305; }
            ;

AbstractDeclaratorOpt: /* empty */ { $$=306; }
                     | AbstractDeclarator { $$=307; }
                     ;

TypeId: TypeSpecifierSeq AbstractDeclaratorOpt { $$=308; }
      ;

TypeSpecifierSeqOpt: /* empty */ { $$=309; }
                   | TypeSpecifierSeq { $$=310; }
                   ;

TypeSpecifierSeq: TypeSpecifier TypeSpecifierSeqOpt { $$=311; }
                ;

AbstractDeclarator: PtrOperator AbstractDeclaratorOpt { $$=312; }
                  | DirectAbstractDeclarator { $$=313; }
                  ;

DirectAbstractDeclaratorOpt: /* empty */ { $$=314; }
                           | DirectAbstractDeclarator { $$=315; }
                           ;

DirectAbstractDeclarator: DirectAbstractDeclaratorOpt L2_LPAREN ParameterDeclarationClause L2_RPAREN CvQualifierSeqOpt ExceptionSpecificationOpt { $$=316; }
                        | DirectAbstractDeclaratorOpt L2_LBRACKET ConstantExpressionOpt L2_RBRACKET { $$=317; }
                        | L2_LPAREN AbstractDeclarator L2_RPAREN { $$=318; }
                        ;

ParameterDeclarationListOpt: /* empty */ { $$=319; }
                           | ParameterDeclarationList { $$=320; }
                           ;

EllipsisOpt: /* empty */ { $$=321; }
           | L2_ELLIPSIS { $$=322; }
           ;

ParameterDeclarationClause: ParameterDeclarationListOpt EllipsisOpt { $$=323; }
                          | ParameterDeclarationList L2_COMMA L2_ELLIPSIS { $$=324; }
                          ;

ParameterDeclarationList: ParameterDeclaration { $$=325; }
                        | ParameterDeclarationList L2_COMMA ParameterDeclaration { $$=326; }
                        ;

ParameterDeclaration: DeclSpecifierSeq Declarator { $$=327; }
                    | DeclSpecifierSeq Declarator L2_EQUAL AssignmentExpression { $$=328; }
                    | DeclSpecifierSeq AbstractDeclaratorOpt { $$=329; }
                    | DeclSpecifierSeq AbstractDeclaratorOpt L2_EQUAL AssignmentExpression { $$=330; }
                    ;

CtorInitializerOpt: /* empty */ { $$=331; }
                  | CtorInitializer { $$=332; }
                  ;

FunctionDefinition: DeclSpecifierSeqOpt Declarator CtorInitializerOpt FunctionBody { $$=333; }
                  | DeclSpecifierSeqOpt Declarator FunctionTryBlock { $$=334; }
                  ;

FunctionBody: CompoundStatement { $$=335; }
            ;

Initializer: L2_EQUAL InitializerClause { $$=336; }
           | L2_LPAREN ExpressionList L2_RPAREN { $$=337; }
           ;

CommaOpt: /* empty */ { $$=338; }
        | L2_COMMA { $$=339; }
        ;

InitializerClause: AssignmentExpression { $$=340; }
                 | L2_LBRACE InitializerList CommaOpt L2_RBRACE { $$=341; }
                 | L2_LBRACE L2_RBRACE { $$=342; }
                 ;

InitializerList: InitializerClause { $$=343; }
               | InitializerList L2_COMMA InitializerClause { $$=344; }
               ;

MemberSpecificationOpt: /* empty */ { $$=345; }
                      | MemberSpecification { $$=346; }
                      ;

ClassSpecifier: ClassHead L2_LBRACE MemberSpecificationOpt L2_RBRACE { $$=347; }
              ;

BaseClauseOpt: /* empty */ { $$=348; }
             | BaseClause { $$=349; }
             ;

ClassHead: ClassKey IdentifierOpt BaseClauseOpt { $$=350; }
         | ClassKey NestedNameSpecifier Identifier BaseClauseOpt { $$=351; }
         | ClassKey NestedNameSpecifierOpt TemplateId BaseClauseOpt { $$=352; }
         ;

ClassKey: L2_CLASS { $$=353; }
        | L2_STRUCT { $$=354; }
        | L2_UNION { $$=355; }
        ;

MemberSpecification: MemberDeclaration MemberSpecificationOpt { $$=356; }
                   | AccessSpecifier L2_COLON MemberSpecificationOpt { $$=357; }
                   ;

MemberDeclaratorListOpt: /* empty */ { $$=358; }
                       | MemberDeclaratorList { $$=359; }
                       ;

SemicolonOpt: /* empty */ { $$=360; }
            | L2_SEMICOLON { $$=361; }
            ;

MemberDeclaration: DeclSpecifierSeqOpt MemberDeclaratorListOpt L2_SEMICOLON { $$=362; }
                 | FunctionDefinition SemicolonOpt { $$=363; }
                 | ColonColonOpt NestedNameSpecifier TemplateOpt UnqualifiedId L2_SEMICOLON { $$=364; }
                 | UsingDeclaration { $$=365; }
                 | TemplateDeclaration { $$=366; }
                 ;

MemberDeclaratorList: MemberDeclarator { $$=367; }
                    | MemberDeclaratorList L2_COMMA MemberDeclarator { $$=368; }
                    ;

PureSpecifierOpt: /* empty */ { $$=369; }
                | PureSpecifier { $$=370; }
                ;

ConstantInitializerOpt: /* empty */ { $$=371; }
                      | ConstantInitializer { $$=372; }
                      ;

MemberDeclarator: Declarator PureSpecifierOpt { $$=373; }
                | Declarator ConstantInitializerOpt { $$=374; }
                | IdentifierOpt L2_COLON ConstantExpression { $$=375; }
                ;

PureSpecifier: L2_EQUAL IntegerLiteral { $$=376; }
             ;

ConstantInitializer: L2_EQUAL ConstantExpression { $$=377; }
                   ;

BaseClause: L2_COLON BaseSpecifierList { $$=378; }
          ;

BaseSpecifierList: BaseSpecifier { $$=379; }
                 | BaseSpecifierList L2_COMMA BaseSpecifier { $$=380; }
                 ;

VirtualOpt: /* empty */ { $$=381; }
          | L2_VIRTUAL { $$=382; }
          ;

AccessSpecifierOpt: /* empty */ { $$=383; }
                  | AccessSpecifier { $$=384; }
                  ;

BaseSpecifier: ColonColonOpt NestedNameSpecifierOpt ClassName { $$=385; }
             | L2_VIRTUAL AccessSpecifierOpt ColonColonOpt NestedNameSpecifierOpt ClassName { $$=386; }
             | AccessSpecifier VirtualOpt ColonColonOpt NestedNameSpecifierOpt ClassName { $$=387; }
             ;

AccessSpecifier: L2_PRIVATE { $$=388; }
               | L2_PROTECTED { $$=389; }
               | L2_PUBLIC { $$=390; }
               ;

ConversionFunctionId: L2_OPERATOR ConversionTypeId { $$=391; }
                    ;

ConversionDeclaratorOpt: /* empty */ { $$=392; }
                       | ConversionDeclarator { $$=393; }
                       ;

ConversionTypeId: TypeSpecifierSeq ConversionDeclaratorOpt { $$=394; }
                ;

ConversionDeclarator: PtrOperator ConversionDeclaratorOpt { $$=395; }
                    ;

CtorInitializer: L2_COLON MemInitializerList { $$=396; }
               ;

MemInitializerList: MemInitializer { $$=397; }
                  | MemInitializer L2_COMMA MemInitializerList { $$=398; }
                  ;

MemInitializer: MemInitializerId L2_LPAREN ExpressionListOpt L2_RPAREN { $$=399; }
              ;

MemInitializerId: ColonColonOpt NestedNameSpecifierOpt ClassName { $$=400; }
                | Identifier { $$=401; }
                ;

OperatorFunctionId: L2_OPERATOR Operator { $$=402; }
                  ;

Operator: L2_NEW { $$=403; }
        | L2_DELETE { $$=404; }
        | L2_NEW L2_LBRACKET L2_RBRACKET { $$=405; }
        | L2_DELETE L2_LBRACKET L2_RBRACKET { $$=406; }
        | L2_PLUS { $$=407; }
        | L2_MINUS { $$=408; }
        | L2_STAR { $$=409; }
        | L2_SLASH { $$=410; }
        | L2_PERCENT { $$=411; }
        | L2_XOR { $$=412; }
        | L2_AND { $$=413; }
        | L2_OR { $$=414; }
        | L2_TILDE { $$=415; }
        | L2_BANG { $$=416; }
        | L2_EQUAL { $$=417; }
        | L2_LESSTHAN { $$=418; }
        | L2_GREATERTHAN { $$=419; }
        | L2_PLUSEQUAL { $$=420; }
        | L2_MINUSEQUAL { $$=421; }
        | L2_STAREQUAL { $$=422; }
        | L2_SLASHEQUAL { $$=423; }
        | L2_PERCENTEQUAL { $$=424; }
        | L2_XOREQUAL { $$=425; }
        | L2_ANDEQUAL { $$=426; }
        | L2_OREQUAL { $$=427; }
        | L2_LEFTSHIFT { $$=428; }
        | L2_RIGHTSHIFT { $$=429; }
        | L2_RIGHTSHIFTEQUAL { $$=430; }
        | L2_LEFTSHIFTEQUAL { $$=431; }
        | L2_EQUALEQUAL { $$=432; }
        | L2_NOTEQUAL { $$=433; }
        | L2_LESSEQ { $$=434; }
        | L2_GREATEREQ { $$=435; }
        | L2_ANDAND { $$=436; }
        | L2_OROR { $$=437; }
        | L2_PLUSPLUS { $$=438; }
        | L2_MINUSMINUS { $$=439; }
        | L2_COMMA { $$=440; }
        | L2_ARROWSTAR { $$=441; }
        | L2_ARROW { $$=442; }
        | L2_LPAREN L2_RPAREN { $$=443; }
        | L2_LBRACKET L2_RBRACKET { $$=444; }
        ;

ExportOpt: /* empty */ { $$=445; }
         | L2_EXPORT { $$=446; }
         ;

TemplateDeclaration: ExportOpt L2_TEMPLATE L2_LESSTHAN TemplateParameterList L2_GREATERTHAN Declaration { $$=447; }
                   ;

TemplateParameterList: TemplateParameter { $$=448; }
                     | TemplateParameterList L2_COMMA TemplateParameter { $$=449; }
                     ;

TemplateParameter: TypeParameter { $$=450; }
                 | ParameterDeclaration { $$=451; }
                 ;

TypeParameter: L2_CLASS IdentifierOpt { $$=452; }
             | L2_CLASS IdentifierOpt L2_EQUAL TypeId { $$=453; }
             | L2_TYPENAME IdentifierOpt { $$=454; }
             | L2_TYPENAME IdentifierOpt L2_EQUAL TypeId { $$=455; }
             | L2_TEMPLATE L2_LESSTHAN TemplateParameterList L2_GREATERTHAN L2_CLASS IdentifierOpt { $$=456; }
             | L2_TEMPLATE L2_LESSTHAN TemplateParameterList L2_GREATERTHAN L2_CLASS IdentifierOpt L2_EQUAL IdExpression { $$=457; }
             ;

TemplateArgumentListOpt: /* empty */ { $$=458; }
                       | TemplateArgumentList { $$=459; }
                       ;

TemplateId: TemplateName L2_LESSTHAN TemplateArgumentListOpt L2_GREATERTHAN { $$=460; }
          ;

TemplateArgumentList: TemplateArgument { $$=461; }
                    | TemplateArgumentList L2_COMMA TemplateArgument { $$=462; }
                    ;

TemplateArgument: AssignmentExpression { $$=463; }
                | TypeId { $$=464; }
                | IdExpression { $$=465; }
                ;

ExplicitInstantiation: L2_TEMPLATE Declaration { $$=466; }
                     ;

ExplicitSpecialization: L2_TEMPLATE L2_LESSTHAN L2_GREATERTHAN Declaration { $$=467; }
                      ;

TryBlock: L2_TRY CompoundStatement HandlerSeq { $$=468; }
        ;

FunctionTryBlock: L2_TRY CtorInitializerOpt FunctionBody HandlerSeq { $$=469; }
                ;

HandlerSeqOpt: /* empty */ { $$=470; }
             | HandlerSeq { $$=471; }
             ;

HandlerSeq: Handler HandlerSeqOpt { $$=472; }
          ;

Handler: L2_CATCH L2_LPAREN ExceptionDeclaration L2_RPAREN CompoundStatement { $$=473; }
       ;

ExceptionDeclaration: TypeSpecifierSeq Declarator { $$=474; }
                    | TypeSpecifierSeq AbstractDeclarator { $$=475; }
                    | TypeSpecifierSeq { $$=476; }
                    | L2_ELLIPSIS { $$=477; }
                    ;

AssignmentExpressionOpt: /* empty */ { $$=478; }
                       | AssignmentExpression { $$=479; }
                       ;

ThrowExpression: L2_THROW AssignmentExpressionOpt { $$=480; }
               ;

TypeIdListOpt: /* empty */ { $$=481; }
             | TypeIdList { $$=482; }
             ;

ExceptionSpecification: L2_THROW L2_LPAREN TypeIdListOpt L2_RPAREN { $$=483; }
                      ;

TypeIdList: TypeId { $$=484; }
          | TypeIdList L2_COMMA TypeId { $$=485; }
          ;

