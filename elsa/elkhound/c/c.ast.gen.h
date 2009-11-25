// c.ast.gen.h
// *** DO NOT EDIT ***
// generated automatically by astgen, from c.ast

#ifndef C_AST_GEN_H
#define C_AST_GEN_H

#include "asthelp.h"        // helpers for generated code

// fwd decls
class TranslationUnit;
class TopForm;
class TF_decl;
class TF_func;
class Declaration;
class ASTTypeId;
class TypeSpecifier;
class TS_name;
class TS_simple;
class TS_elaborated;
class TS_classSpec;
class TS_enumSpec;
class Enumerator;
class Declarator;
class IDeclarator;
class D_name;
class D_func;
class D_array;
class D_bitfield;
class PtrOperator;
class Statement;
class S_skip;
class S_label;
class S_case;
class S_caseRange;
class S_default;
class S_expr;
class S_compound;
class S_if;
class S_switch;
class S_while;
class S_doWhile;
class S_for;
class S_break;
class S_continue;
class S_return;
class S_goto;
class S_decl;
class S_assert;
class S_assume;
class S_invariant;
class S_thmprv;
class Expression;
class E_intLit;
class E_floatLit;
class E_stringLit;
class E_charLit;
class E_variable;
class E_funCall;
class E_fieldAcc;
class E_sizeof;
class E_unary;
class E_effect;
class E_binary;
class E_addrOf;
class E_deref;
class E_cast;
class E_cond;
class E_comma;
class E_sizeofType;
class E_new;
class E_assign;
class E_quantifier;
class Initializer;
class IN_expr;
class IN_compound;
class InitLabel;
class IL_element;
class IL_range;
class IL_field;
class IL_elementField;
class FuncAnnotation;
class FA_precondition;
class FA_postcondition;
class ThmprvAttr;


// *** DO NOT EDIT ***

  #include "sobjlist.h"      // SObjList
  #include "c_variable.h"    // Variable
  #include "cc_flags.h"      // CVFlags, DeclFlags, etc. (r)
  #include "c_type.h"        // Type, FunctonType, CompoundType

  class Env;                 // cc_env.h
  class AEnv;                // aenv.h
  class AbsValue;            // absval.ast
  class Predicate;           // predicate.ast


// *** DO NOT EDIT ***
class TranslationUnit {
public:      // data
  ASTList <TopForm > topForms;

public:      // funcs
  TranslationUnit(ASTList <TopForm > *_topForms) : topForms(_topForms) {
  }
  ~TranslationUnit();

  char const *kindName() const { return "TranslationUnit"; }

  TranslationUnit *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  void tcheck(Env &env);
  public:  void vcgen(AEnv &env) const;
};



// *** DO NOT EDIT ***
class TopForm {
public:      // data
  SourceLoc loc;

public:      // funcs
  TopForm(SourceLoc _loc) : loc(_loc) {
  }
  virtual ~TopForm();

  enum Kind { TF_DECL, TF_FUNC, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TF_decl, TF_DECL)
  DECL_AST_DOWNCASTS(TF_func, TF_FUNC)

  virtual TopForm* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  void tcheck(Env &env);
  public: virtual  void itcheck(Env &env)=0;
  public: virtual  void vcgen(AEnv &env) const=0;
};

class TF_decl : public TopForm {
public:      // data
  Declaration *decl;

public:      // funcs
  TF_decl(SourceLoc _loc, Declaration *_decl) : TopForm(_loc), decl(_decl) {
  }
  virtual ~TF_decl();

  virtual Kind kind() const { return TF_DECL; }
  enum { TYPE_TAG = TF_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TF_decl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(AEnv &env) const;
};

class TF_func : public TopForm {
public:      // data
  DeclFlags dflags;
  TypeSpecifier *retspec;
  Declarator *nameParams;
  S_compound *body;

public:      // funcs
  TF_func(SourceLoc _loc, DeclFlags _dflags, TypeSpecifier *_retspec, Declarator *_nameParams, S_compound *_body) : TopForm(_loc), dflags(_dflags), retspec(_retspec), nameParams(_nameParams), body(_body) {
     numPaths=0;
  }
  virtual ~TF_func();

  virtual Kind kind() const { return TF_FUNC; }
  enum { TYPE_TAG = TF_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TF_func *clone() const;

  public:  FunctionType const *ftype() const;
  public:  StringRef name() const;
  public:  SObjList<Variable> params;
  public:  SObjList<Variable> locals;
  public:  SObjList<Variable> globalRefs;
  public:  SObjList<Statement> roots;
  public:  int numPaths;
  public:  void printExtras(std::ostream &os, int indent) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(AEnv &env) const;
};




// *** DO NOT EDIT ***
class Declaration {
public:      // data
  DeclFlags dflags;
  TypeSpecifier *spec;
  ASTList <Declarator > decllist;

public:      // funcs
  Declaration(DeclFlags _dflags, TypeSpecifier *_spec, ASTList <Declarator > *_decllist) : dflags(_dflags), spec(_spec), decllist(_decllist) {
  }
  ~Declaration();

  char const *kindName() const { return "Declaration"; }

  Declaration *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  void tcheck(Env &env);
  public:  void vcgen(AEnv &env) const;
};



// *** DO NOT EDIT ***
class ASTTypeId {
public:      // data
  TypeSpecifier *spec;
  Declarator *decl;

public:      // funcs
  ASTTypeId(TypeSpecifier *_spec, Declarator *_decl) : spec(_spec), decl(_decl) {
     { type=NULL; };
  }
  ~ASTTypeId();

  char const *kindName() const { return "ASTTypeId"; }

  ASTTypeId *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  Type const *tcheck(Env &env);
  public:  Type const *type;
};



// *** DO NOT EDIT ***
class TypeSpecifier {
public:      // data

public:      // funcs
  TypeSpecifier() {
     { cv=CV_NONE; };
  }
  virtual ~TypeSpecifier();

  enum Kind { TS_NAME, TS_SIMPLE, TS_ELABORATED, TS_CLASSSPEC, TS_ENUMSPEC, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(TS_name, TS_NAME)
  DECL_AST_DOWNCASTS(TS_simple, TS_SIMPLE)
  DECL_AST_DOWNCASTS(TS_elaborated, TS_ELABORATED)
  DECL_AST_DOWNCASTS(TS_classSpec, TS_CLASSSPEC)
  DECL_AST_DOWNCASTS(TS_enumSpec, TS_ENUMSPEC)

  virtual TypeSpecifier* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  enum CVFlags cv;
  public: virtual  Type const *tcheck(Env &env)=0;
  protected:  Type const *applyCV(Env &env, Type const *base);
};

class TS_name : public TypeSpecifier {
public:      // data
  StringRef name;

public:      // funcs
  TS_name(StringRef _name) : TypeSpecifier(), name(_name) {
  }
  virtual ~TS_name();

  virtual Kind kind() const { return TS_NAME; }
  enum { TYPE_TAG = TS_NAME };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TS_name *clone() const;

  public: virtual  Type const *tcheck(Env &env);
};

class TS_simple : public TypeSpecifier {
public:      // data
  SimpleTypeId id;

public:      // funcs
  TS_simple(SimpleTypeId _id) : TypeSpecifier(), id(_id) {
  }
  virtual ~TS_simple();

  virtual Kind kind() const { return TS_SIMPLE; }
  enum { TYPE_TAG = TS_SIMPLE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TS_simple *clone() const;

  public: virtual  Type const *tcheck(Env &env);
};

class TS_elaborated : public TypeSpecifier {
public:      // data
  TypeIntr keyword;
  StringRef name;

public:      // funcs
  TS_elaborated(TypeIntr _keyword, StringRef _name) : TypeSpecifier(), keyword(_keyword), name(_name) {
  }
  virtual ~TS_elaborated();

  virtual Kind kind() const { return TS_ELABORATED; }
  enum { TYPE_TAG = TS_ELABORATED };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TS_elaborated *clone() const;

  public: virtual  Type const *tcheck(Env &env);
};

class TS_classSpec : public TypeSpecifier {
public:      // data
  TypeIntr keyword;
  StringRef name;
  ASTList <Declaration > members;

public:      // funcs
  TS_classSpec(TypeIntr _keyword, StringRef _name, ASTList <Declaration > *_members) : TypeSpecifier(), keyword(_keyword), name(_name), members(_members) {
  }
  virtual ~TS_classSpec();

  virtual Kind kind() const { return TS_CLASSSPEC; }
  enum { TYPE_TAG = TS_CLASSSPEC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TS_classSpec *clone() const;

  public: virtual  Type const *tcheck(Env &env);
};

class TS_enumSpec : public TypeSpecifier {
public:      // data
  StringRef name;
  ASTList <Enumerator > elts;

public:      // funcs
  TS_enumSpec(StringRef _name, ASTList <Enumerator > *_elts) : TypeSpecifier(), name(_name), elts(_elts) {
  }
  virtual ~TS_enumSpec();

  virtual Kind kind() const { return TS_ENUMSPEC; }
  enum { TYPE_TAG = TS_ENUMSPEC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual TS_enumSpec *clone() const;

  public: virtual  Type const *tcheck(Env &env);
};



// *** DO NOT EDIT ***
class Enumerator {
public:      // data
  SourceLoc loc;
  StringRef name;
  Expression *expr;

public:      // funcs
  Enumerator(SourceLoc _loc, StringRef _name, Expression *_expr) : loc(_loc), name(_name), expr(_expr) {
     var=NULL;
  }
  ~Enumerator();

  char const *kindName() const { return "Enumerator"; }

  Enumerator *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  Variable *var;
};



// *** DO NOT EDIT ***
class Declarator {
public:      // data
  IDeclarator *decl;
  Initializer *init;

public:      // funcs
  Declarator(IDeclarator *_decl, Initializer *_init) : decl(_decl), init(_init) {
     var=NULL;
  }
  ~Declarator();

  char const *kindName() const { return "Declarator"; }

  Declarator *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  Variable *var;
  public:  Type const *tcheck(Env &env, Type const *base, DeclFlags dflags);
  public:  void vcgen(AEnv &env, AbsValue *initVal) const;
};



// *** DO NOT EDIT ***
class IDeclarator {
public:      // data

public:      // funcs
  IDeclarator() {
  }
  virtual ~IDeclarator();

  enum Kind { D_NAME, D_FUNC, D_ARRAY, D_BITFIELD, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(D_name, D_NAME)
  DECL_AST_DOWNCASTS(D_func, D_FUNC)
  DECL_AST_DOWNCASTS(D_array, D_ARRAY)
  DECL_AST_DOWNCASTS(D_bitfield, D_BITFIELD)

  virtual IDeclarator* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  ASTList<PtrOperator> stars;
  public:  void tcheck(Env &env, Type const *base,
                     DeclFlags dflags, Declarator *declarator);
  public: virtual  void itcheck(Env &env, Type const *base,
                            DeclFlags dflags, Declarator *declarator)=0;
  public: virtual  StringRef getName() const=0;
};

class D_name : public IDeclarator {
public:      // data
  SourceLoc loc;
  StringRef name;
  ThmprvAttr *attr;

public:      // funcs
  D_name(SourceLoc _loc, StringRef _name, ThmprvAttr *_attr) : IDeclarator(), loc(_loc), name(_name), attr(_attr) {
  }
  virtual ~D_name();

  virtual Kind kind() const { return D_NAME; }
  enum { TYPE_TAG = D_NAME };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual D_name *clone() const;

  public: virtual  void itcheck(Env &env, Type const *base,
                            DeclFlags dflags, Declarator *declarator);
  public: virtual  StringRef getName() const;
};

class D_func : public IDeclarator {
public:      // data
  SourceLoc loc;
  IDeclarator *base;
  ASTList <ASTTypeId > params;
  ASTList <FuncAnnotation > ann;

public:      // funcs
  D_func(SourceLoc _loc, IDeclarator *_base, ASTList <ASTTypeId > *_params, ASTList <FuncAnnotation > *_ann) : IDeclarator(), loc(_loc), base(_base), params(_params), ann(_ann) {
     result=NULL;
  }
  virtual ~D_func();

  virtual Kind kind() const { return D_FUNC; }
  enum { TYPE_TAG = D_FUNC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual D_func *clone() const;

  public:  Variable *result;
  public: virtual  void itcheck(Env &env, Type const *base,
                            DeclFlags dflags, Declarator *declarator);
  public: virtual  StringRef getName() const;
};

class D_array : public IDeclarator {
public:      // data
  IDeclarator *base;
  Expression *size;

public:      // funcs
  D_array(IDeclarator *_base, Expression *_size) : IDeclarator(), base(_base), size(_size) {
  }
  virtual ~D_array();

  virtual Kind kind() const { return D_ARRAY; }
  enum { TYPE_TAG = D_ARRAY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual D_array *clone() const;

  public: virtual  void itcheck(Env &env, Type const *base,
                            DeclFlags dflags, Declarator *declarator);
  public: virtual  StringRef getName() const;
};

class D_bitfield : public IDeclarator {
public:      // data
  StringRef name;
  Expression *bits;

public:      // funcs
  D_bitfield(StringRef _name, Expression *_bits) : IDeclarator(), name(_name), bits(_bits) {
  }
  virtual ~D_bitfield();

  virtual Kind kind() const { return D_BITFIELD; }
  enum { TYPE_TAG = D_BITFIELD };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual D_bitfield *clone() const;

  public: virtual  void itcheck(Env &env, Type const *base,
                            DeclFlags dflags, Declarator *declarator);
  public: virtual  StringRef getName() const;
};



// *** DO NOT EDIT ***
class PtrOperator {
public:      // data
  CVFlags cv;

public:      // funcs
  PtrOperator(CVFlags _cv) : cv(_cv) {
  }
  ~PtrOperator();

  char const *kindName() const { return "PtrOperator"; }

  PtrOperator *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

};



// *** DO NOT EDIT ***

  // arguably premature optimization, I encode 'next' pointers as the
  // pointer itself, bitwise OR'd with 1 if it's a "continue" edge,
  // and use void* as the abstract type; essentially, every Statement
  // is regarded as actually being two distinct CFG nodes, one reached
  // with continue==false and the other with continue==true (except
  // that some nodes don't have a continue==true half)
  typedef void *NextPtr;

  inline NextPtr makeNextPtr(Statement const *next, bool isContinue)
  {
    return (NextPtr)((long)next | !!isContinue);
  }

  inline Statement const *nextPtrStmt(NextPtr np)
  {
    return (Statement const*)((long)np & ~1L);
  }

  // unfortunately I don't have a good way to enforce the flow
  // of constness.. so whatever ("NC" == "non-const")
  inline Statement *nextPtrStmtNC(NextPtr np)
  {
    return (Statement*)nextPtrStmt(np);
  }

  // this is true when the 'next' edge points at a looping construct,
  // but the flow is interpreted as a 'continue', rather than starting
  // the loop from scratch
  inline bool nextPtrContinue(NextPtr np)
  {
    return (bool)((long)np & 1);
  }

  // prints like Statement::kindLocString, with a "(c)" appended
  // if it's the continue==true half
  sm::string nextPtrString(NextPtr np);

  // after working with this system a while, I think it's good, so I
  // want more support for manipulating lists of NextPtrs
  typedef VoidList NextPtrList;
  #define FOREACH_NEXTPTR(list, itervar) \
    for (VoidListIter itervar(list); !itervar.isDone(); itervar.adv())

  // given a function node, return a list of all the CFG nodes,
  // in reverse postorder w.r.t. some spanning tree
  // (implemented in postorder.cc)
  void reversePostorder(NextPtrList &order, TF_func const &func);

// *** DO NOT EDIT ***

  // list of the parameters to Statement::vcgen; abstracted into a
  // macro to make it easier to add/remove/change parameters
  //   env: abstract environment
  //   isContinue: true if we reached this statement on a 'continue' edge
  //   path: which expression path to follow inside the statement
  //   next: which statement will be next; may imply a predicate
  #define STMT_VCGEN_PARAMS AEnv &env, bool isContinue, int path, Statement const *next

// *** DO NOT EDIT ***
class Statement {
public:      // data
  SourceLoc loc;

public:      // funcs
  Statement(SourceLoc _loc) : loc(_loc) {
     next=NULL;
     numPaths=0;
  }
  virtual ~Statement();

  enum Kind { S_SKIP, S_LABEL, S_CASE, S_CASERANGE, S_DEFAULT, S_EXPR, S_COMPOUND, S_IF, S_SWITCH, S_WHILE, S_DOWHILE, S_FOR, S_BREAK, S_CONTINUE, S_RETURN, S_GOTO, S_DECL, S_ASSERT, S_ASSUME, S_INVARIANT, S_THMPRV, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(S_skip, S_SKIP)
  DECL_AST_DOWNCASTS(S_label, S_LABEL)
  DECL_AST_DOWNCASTS(S_case, S_CASE)
  DECL_AST_DOWNCASTS(S_caseRange, S_CASERANGE)
  DECL_AST_DOWNCASTS(S_default, S_DEFAULT)
  DECL_AST_DOWNCASTS(S_expr, S_EXPR)
  DECL_AST_DOWNCASTS(S_compound, S_COMPOUND)
  DECL_AST_DOWNCASTS(S_if, S_IF)
  DECL_AST_DOWNCASTS(S_switch, S_SWITCH)
  DECL_AST_DOWNCASTS(S_while, S_WHILE)
  DECL_AST_DOWNCASTS(S_doWhile, S_DOWHILE)
  DECL_AST_DOWNCASTS(S_for, S_FOR)
  DECL_AST_DOWNCASTS(S_break, S_BREAK)
  DECL_AST_DOWNCASTS(S_continue, S_CONTINUE)
  DECL_AST_DOWNCASTS(S_return, S_RETURN)
  DECL_AST_DOWNCASTS(S_goto, S_GOTO)
  DECL_AST_DOWNCASTS(S_decl, S_DECL)
  DECL_AST_DOWNCASTS(S_assert, S_ASSERT)
  DECL_AST_DOWNCASTS(S_assume, S_ASSUME)
  DECL_AST_DOWNCASTS(S_invariant, S_INVARIANT)
  DECL_AST_DOWNCASTS(S_thmprv, S_THMPRV)

  virtual Statement* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  virtual void tcheck(Env &env);
  public: virtual  void itcheck(Env &env)=0;
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const=0;
  public:  void vcgenPath(AEnv &env, SObjList<Statement /*const*/> &path,
                        int index, bool isContinue) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const=0;
  public:  NextPtr next;
  public:  virtual void getSuccessors(NextPtrList &dest, bool isContinue) const;
  public:  sm::string successorsToString() const;
  public:  sm::string kindLocString() const;
  public:  int numPaths;
};

class S_skip : public Statement {
public:      // data

public:      // funcs
  S_skip(SourceLoc _loc) : Statement(_loc) {
  }
  virtual ~S_skip();

  virtual Kind kind() const { return S_SKIP; }
  enum { TYPE_TAG = S_SKIP };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_skip *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_label : public Statement {
public:      // data
  StringRef name;
  Statement *s;

public:      // funcs
  S_label(SourceLoc _loc, StringRef _name, Statement *_s) : Statement(_loc), name(_name), s(_s) {
  }
  virtual ~S_label();

  virtual Kind kind() const { return S_LABEL; }
  enum { TYPE_TAG = S_LABEL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_label *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_case : public Statement {
public:      // data
  Expression *expr;
  Statement *s;

public:      // funcs
  S_case(SourceLoc _loc, Expression *_expr, Statement *_s) : Statement(_loc), expr(_expr), s(_s) {
  }
  virtual ~S_case();

  virtual Kind kind() const { return S_CASE; }
  enum { TYPE_TAG = S_CASE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_case *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_caseRange : public Statement {
public:      // data
  Expression *low;
  Expression *high;
  Statement *s;

public:      // funcs
  S_caseRange(SourceLoc _loc, Expression *_low, Expression *_high, Statement *_s) : Statement(_loc), low(_low), high(_high), s(_s) {
  }
  virtual ~S_caseRange();

  virtual Kind kind() const { return S_CASERANGE; }
  enum { TYPE_TAG = S_CASERANGE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_caseRange *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_default : public Statement {
public:      // data
  Statement *s;

public:      // funcs
  S_default(SourceLoc _loc, Statement *_s) : Statement(_loc), s(_s) {
  }
  virtual ~S_default();

  virtual Kind kind() const { return S_DEFAULT; }
  enum { TYPE_TAG = S_DEFAULT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_default *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_expr : public Statement {
public:      // data
  Expression *expr;

public:      // funcs
  S_expr(SourceLoc _loc, Expression *_expr) : Statement(_loc), expr(_expr) {
  }
  virtual ~S_expr();

  virtual Kind kind() const { return S_EXPR; }
  enum { TYPE_TAG = S_EXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_expr *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_compound : public Statement {
public:      // data
  ASTList <Statement > stmts;

public:      // funcs
  S_compound(SourceLoc _loc, ASTList <Statement > *_stmts) : Statement(_loc), stmts(_stmts) {
  }
  virtual ~S_compound();

  virtual Kind kind() const { return S_COMPOUND; }
  enum { TYPE_TAG = S_COMPOUND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_compound *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_if : public Statement {
public:      // data
  Expression *cond;
  Statement *thenBranch;
  Statement *elseBranch;

public:      // funcs
  S_if(SourceLoc _loc, Expression *_cond, Statement *_thenBranch, Statement *_elseBranch) : Statement(_loc), cond(_cond), thenBranch(_thenBranch), elseBranch(_elseBranch) {
  }
  virtual ~S_if();

  virtual Kind kind() const { return S_IF; }
  enum { TYPE_TAG = S_IF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_if *clone() const;

  public:  virtual void getSuccessors(VoidList &dest, bool isContinue) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_switch : public Statement {
public:      // data
  Expression *expr;
  Statement *branches;

public:      // funcs
  S_switch(SourceLoc _loc, Expression *_expr, Statement *_branches) : Statement(_loc), expr(_expr), branches(_branches) {
  }
  virtual ~S_switch();

  virtual Kind kind() const { return S_SWITCH; }
  enum { TYPE_TAG = S_SWITCH };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_switch *clone() const;

  public:  SObjList<Statement> cases;
  public:  virtual void getSuccessors(VoidList &dest, bool isContinue) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_while : public Statement {
public:      // data
  Expression *cond;
  Statement *body;

public:      // funcs
  S_while(SourceLoc _loc, Expression *_cond, Statement *_body) : Statement(_loc), cond(_cond), body(_body) {
  }
  virtual ~S_while();

  virtual Kind kind() const { return S_WHILE; }
  enum { TYPE_TAG = S_WHILE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_while *clone() const;

  public:  virtual void getSuccessors(VoidList &dest, bool isContinue) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_doWhile : public Statement {
public:      // data
  Statement *body;
  Expression *cond;

public:      // funcs
  S_doWhile(SourceLoc _loc, Statement *_body, Expression *_cond) : Statement(_loc), body(_body), cond(_cond) {
  }
  virtual ~S_doWhile();

  virtual Kind kind() const { return S_DOWHILE; }
  enum { TYPE_TAG = S_DOWHILE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_doWhile *clone() const;

  public:  virtual void getSuccessors(VoidList &dest, bool isContinue) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_for : public Statement {
public:      // data
  Statement *init;
  Expression *cond;
  Expression *after;
  Statement *body;

public:      // funcs
  S_for(SourceLoc _loc, Statement *_init, Expression *_cond, Expression *_after, Statement *_body) : Statement(_loc), init(_init), cond(_cond), after(_after), body(_body) {
  }
  virtual ~S_for();

  virtual Kind kind() const { return S_FOR; }
  enum { TYPE_TAG = S_FOR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_for *clone() const;

  public:  virtual void tcheck(Env &env);
  public:  virtual void getSuccessors(VoidList &dest, bool isContinue) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_break : public Statement {
public:      // data

public:      // funcs
  S_break(SourceLoc _loc) : Statement(_loc) {
  }
  virtual ~S_break();

  virtual Kind kind() const { return S_BREAK; }
  enum { TYPE_TAG = S_BREAK };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_break *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_continue : public Statement {
public:      // data

public:      // funcs
  S_continue(SourceLoc _loc) : Statement(_loc) {
  }
  virtual ~S_continue();

  virtual Kind kind() const { return S_CONTINUE; }
  enum { TYPE_TAG = S_CONTINUE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_continue *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_return : public Statement {
public:      // data
  Expression *expr;

public:      // funcs
  S_return(SourceLoc _loc, Expression *_expr) : Statement(_loc), expr(_expr) {
  }
  virtual ~S_return();

  virtual Kind kind() const { return S_RETURN; }
  enum { TYPE_TAG = S_RETURN };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_return *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_goto : public Statement {
public:      // data
  StringRef target;

public:      // funcs
  S_goto(SourceLoc _loc, StringRef _target) : Statement(_loc), target(_target) {
  }
  virtual ~S_goto();

  virtual Kind kind() const { return S_GOTO; }
  enum { TYPE_TAG = S_GOTO };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_goto *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_decl : public Statement {
public:      // data
  Declaration *decl;

public:      // funcs
  S_decl(SourceLoc _loc, Declaration *_decl) : Statement(_loc), decl(_decl) {
  }
  virtual ~S_decl();

  virtual Kind kind() const { return S_DECL; }
  enum { TYPE_TAG = S_DECL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_decl *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_assert : public Statement {
public:      // data
  Expression *expr;
  bool pure;

public:      // funcs
  S_assert(SourceLoc _loc, Expression *_expr, bool _pure) : Statement(_loc), expr(_expr), pure(_pure) {
  }
  virtual ~S_assert();

  virtual Kind kind() const { return S_ASSERT; }
  enum { TYPE_TAG = S_ASSERT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_assert *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_assume : public Statement {
public:      // data
  Expression *expr;

public:      // funcs
  S_assume(SourceLoc _loc, Expression *_expr) : Statement(_loc), expr(_expr) {
  }
  virtual ~S_assume();

  virtual Kind kind() const { return S_ASSUME; }
  enum { TYPE_TAG = S_ASSUME };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_assume *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_invariant : public Statement {
public:      // data
  Expression *expr;

public:      // funcs
  S_invariant(SourceLoc _loc, Expression *_expr) : Statement(_loc), expr(_expr) {
  }
  virtual ~S_invariant();

  virtual Kind kind() const { return S_INVARIANT; }
  enum { TYPE_TAG = S_INVARIANT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_invariant *clone() const;

  public:  SObjList<Expression> inferFacts;
  public:  Predicate *vcgenPredicate(AEnv &env) const;
  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};

class S_thmprv : public Statement {
public:      // data
  Statement *s;

public:      // funcs
  S_thmprv(SourceLoc _loc, Statement *_s) : Statement(_loc), s(_s) {
  }
  virtual ~S_thmprv();

  virtual Kind kind() const { return S_THMPRV; }
  enum { TYPE_TAG = S_THMPRV };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual S_thmprv *clone() const;

  public: virtual  void itcheck(Env &env);
  public: virtual  void vcgen(STMT_VCGEN_PARAMS) const;
  public: virtual  void factFlow(SObjList<Expression> &facts, bool isContinue,
                             NextPtr succPtr) const;
};



// *** DO NOT EDIT ***
class Expression {
public:      // data

public:      // funcs
  Expression() {
     type=NULL;
     numPaths=0;
  }
  virtual ~Expression();

  enum Kind { E_INTLIT, E_FLOATLIT, E_STRINGLIT, E_CHARLIT, E_VARIABLE, E_FUNCALL, E_FIELDACC, E_SIZEOF, E_UNARY, E_EFFECT, E_BINARY, E_ADDROF, E_DEREF, E_CAST, E_COND, E_COMMA, E_SIZEOFTYPE, E_NEW, E_ASSIGN, E_QUANTIFIER, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(E_intLit, E_INTLIT)
  DECL_AST_DOWNCASTS(E_floatLit, E_FLOATLIT)
  DECL_AST_DOWNCASTS(E_stringLit, E_STRINGLIT)
  DECL_AST_DOWNCASTS(E_charLit, E_CHARLIT)
  DECL_AST_DOWNCASTS(E_variable, E_VARIABLE)
  DECL_AST_DOWNCASTS(E_funCall, E_FUNCALL)
  DECL_AST_DOWNCASTS(E_fieldAcc, E_FIELDACC)
  DECL_AST_DOWNCASTS(E_sizeof, E_SIZEOF)
  DECL_AST_DOWNCASTS(E_unary, E_UNARY)
  DECL_AST_DOWNCASTS(E_effect, E_EFFECT)
  DECL_AST_DOWNCASTS(E_binary, E_BINARY)
  DECL_AST_DOWNCASTS(E_addrOf, E_ADDROF)
  DECL_AST_DOWNCASTS(E_deref, E_DEREF)
  DECL_AST_DOWNCASTS(E_cast, E_CAST)
  DECL_AST_DOWNCASTS(E_cond, E_COND)
  DECL_AST_DOWNCASTS(E_comma, E_COMMA)
  DECL_AST_DOWNCASTS(E_sizeofType, E_SIZEOFTYPE)
  DECL_AST_DOWNCASTS(E_new, E_NEW)
  DECL_AST_DOWNCASTS(E_assign, E_ASSIGN)
  DECL_AST_DOWNCASTS(E_quantifier, E_QUANTIFIER)

  virtual Expression* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  Type const *tcheck(Env &env);
  public: virtual  Type const *itcheck(Env &env)=0;
  public:  Type const *type;
  public:  int numPaths;
  public:  void recordSideEffect()
    { numPaths = std::max(numPaths, 1); };
  public:  int numPaths1() const
    { return std::max(numPaths, 1); };
  public:  sm::string extrasToString() const;
  public: virtual  int constEval(Env &env) const=0;
  protected:  int xnonconst() const;
  public: virtual  sm::string toString() const=0;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const=0;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const=0;
  public:  Predicate *vcgenPredDefault(AEnv &env, int path) const;
};

class E_intLit : public Expression {
public:      // data
  int i;

public:      // funcs
  E_intLit(int _i) : Expression(), i(_i) {
  }
  virtual ~E_intLit();

  virtual Kind kind() const { return E_INTLIT; }
  enum { TYPE_TAG = E_INTLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_intLit *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_floatLit : public Expression {
public:      // data
  float f;

public:      // funcs
  E_floatLit(float _f) : Expression(), f(_f) {
  }
  virtual ~E_floatLit();

  virtual Kind kind() const { return E_FLOATLIT; }
  enum { TYPE_TAG = E_FLOATLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_floatLit *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_stringLit : public Expression {
public:      // data
  StringRef s;

public:      // funcs
  E_stringLit(StringRef _s) : Expression(), s(_s) {
  }
  virtual ~E_stringLit();

  virtual Kind kind() const { return E_STRINGLIT; }
  enum { TYPE_TAG = E_STRINGLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_stringLit *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_charLit : public Expression {
public:      // data
  char c;

public:      // funcs
  E_charLit(char _c) : Expression(), c(_c) {
  }
  virtual ~E_charLit();

  virtual Kind kind() const { return E_CHARLIT; }
  enum { TYPE_TAG = E_CHARLIT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_charLit *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_variable : public Expression {
public:      // data
  StringRef name;
  StringRef scopeName;

public:      // funcs
  E_variable(StringRef _name, StringRef _scopeName) : Expression(), name(_name), scopeName(_scopeName) {
     var=NULL;
  }
  virtual ~E_variable();

  virtual Kind kind() const { return E_VARIABLE; }
  enum { TYPE_TAG = E_VARIABLE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_variable *clone() const;

  public:  Variable *var;
  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_funCall : public Expression {
public:      // data
  Expression *func;
  ASTList <Expression > args;

public:      // funcs
  E_funCall(Expression *_func, ASTList <Expression > *_args) : Expression(), func(_func), args(_args) {
  }
  virtual ~E_funCall();

  virtual Kind kind() const { return E_FUNCALL; }
  enum { TYPE_TAG = E_FUNCALL };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_funCall *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_fieldAcc : public Expression {
public:      // data
  Expression *obj;
  StringRef fieldName;

public:      // funcs
  E_fieldAcc(Expression *_obj, StringRef _fieldName) : Expression(), obj(_obj), fieldName(_fieldName) {
     field = NULL;
  }
  virtual ~E_fieldAcc();

  virtual Kind kind() const { return E_FIELDACC; }
  enum { TYPE_TAG = E_FIELDACC };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_fieldAcc *clone() const;

  public:  CompoundType::Field const *field;
  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_sizeof : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_sizeof(Expression *_expr) : Expression(), expr(_expr) {
     size=-1;
  }
  virtual ~E_sizeof();

  virtual Kind kind() const { return E_SIZEOF; }
  enum { TYPE_TAG = E_SIZEOF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_sizeof *clone() const;

  public:  int size;
  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_unary : public Expression {
public:      // data
  UnaryOp op;
  Expression *expr;

public:      // funcs
  E_unary(UnaryOp _op, Expression *_expr) : Expression(), op(_op), expr(_expr) {
  }
  virtual ~E_unary();

  virtual Kind kind() const { return E_UNARY; }
  enum { TYPE_TAG = E_UNARY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_unary *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_effect : public Expression {
public:      // data
  EffectOp op;
  Expression *expr;

public:      // funcs
  E_effect(EffectOp _op, Expression *_expr) : Expression(), op(_op), expr(_expr) {
  }
  virtual ~E_effect();

  virtual Kind kind() const { return E_EFFECT; }
  enum { TYPE_TAG = E_EFFECT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_effect *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_binary : public Expression {
public:      // data
  Expression *e1;
  BinaryOp op;
  Expression *e2;

public:      // funcs
  E_binary(Expression *_e1, BinaryOp _op, Expression *_e2) : Expression(), e1(_e1), op(_op), e2(_e2) {
  }
  virtual ~E_binary();

  virtual Kind kind() const { return E_BINARY; }
  enum { TYPE_TAG = E_BINARY };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_binary *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_addrOf : public Expression {
public:      // data
  Expression *expr;

public:      // funcs
  E_addrOf(Expression *_expr) : Expression(), expr(_expr) {
  }
  virtual ~E_addrOf();

  virtual Kind kind() const { return E_ADDROF; }
  enum { TYPE_TAG = E_ADDROF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_addrOf *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_deref : public Expression {
public:      // data
  Expression *ptr;

public:      // funcs
  E_deref(Expression *_ptr) : Expression(), ptr(_ptr) {
  }
  virtual ~E_deref();

  virtual Kind kind() const { return E_DEREF; }
  enum { TYPE_TAG = E_DEREF };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_deref *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_cast : public Expression {
public:      // data
  ASTTypeId *ctype;
  Expression *expr;

public:      // funcs
  E_cast(ASTTypeId *_ctype, Expression *_expr) : Expression(), ctype(_ctype), expr(_expr) {
  }
  virtual ~E_cast();

  virtual Kind kind() const { return E_CAST; }
  enum { TYPE_TAG = E_CAST };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_cast *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_cond : public Expression {
public:      // data
  Expression *cond;
  Expression *th;
  Expression *el;

public:      // funcs
  E_cond(Expression *_cond, Expression *_th, Expression *_el) : Expression(), cond(_cond), th(_th), el(_el) {
  }
  virtual ~E_cond();

  virtual Kind kind() const { return E_COND; }
  enum { TYPE_TAG = E_COND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_cond *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_comma : public Expression {
public:      // data
  Expression *e1;
  Expression *e2;

public:      // funcs
  E_comma(Expression *_e1, Expression *_e2) : Expression(), e1(_e1), e2(_e2) {
  }
  virtual ~E_comma();

  virtual Kind kind() const { return E_COMMA; }
  enum { TYPE_TAG = E_COMMA };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_comma *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_sizeofType : public Expression {
public:      // data
  ASTTypeId *atype;

public:      // funcs
  E_sizeofType(ASTTypeId *_atype) : Expression(), atype(_atype) {
     size=-1;
  }
  virtual ~E_sizeofType();

  virtual Kind kind() const { return E_SIZEOFTYPE; }
  enum { TYPE_TAG = E_SIZEOFTYPE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_sizeofType *clone() const;

  public:  int size;
  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_new : public Expression {
public:      // data
  ASTTypeId *atype;

public:      // funcs
  E_new(ASTTypeId *_atype) : Expression(), atype(_atype) {
  }
  virtual ~E_new();

  virtual Kind kind() const { return E_NEW; }
  enum { TYPE_TAG = E_NEW };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_new *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_assign : public Expression {
public:      // data
  Expression *target;
  BinaryOp op;
  Expression *src;

public:      // funcs
  E_assign(Expression *_target, BinaryOp _op, Expression *_src) : Expression(), target(_target), op(_op), src(_src) {
  }
  virtual ~E_assign();

  virtual Kind kind() const { return E_ASSIGN; }
  enum { TYPE_TAG = E_ASSIGN };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_assign *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};

class E_quantifier : public Expression {
public:      // data
  ASTList <Declaration > decls;
  Expression *pred;
  bool forall;

public:      // funcs
  E_quantifier(ASTList <Declaration > *_decls, Expression *_pred, bool _forall) : Expression(), decls(_decls), pred(_pred), forall(_forall) {
  }
  virtual ~E_quantifier();

  virtual Kind kind() const { return E_QUANTIFIER; }
  enum { TYPE_TAG = E_QUANTIFIER };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual E_quantifier *clone() const;

  public: virtual  Type const *itcheck(Env &env);
  public: virtual  int constEval(Env &env) const;
  public: virtual  sm::string toString() const;
  public: virtual  AbsValue *vcgen(AEnv &env, int path) const;
  public: virtual  Predicate *vcgenPred(AEnv &env, int path) const;
};



// *** DO NOT EDIT ***
class Initializer {
public:      // data

public:      // funcs
  Initializer() {
     { label = NULL; };
  }
  virtual ~Initializer();

  enum Kind { IN_EXPR, IN_COMPOUND, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(IN_expr, IN_EXPR)
  DECL_AST_DOWNCASTS(IN_compound, IN_COMPOUND)

  virtual Initializer* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  public:  InitLabel *label;
  public: virtual  void tcheck(Env &env, Type const *type)=0;
  public: virtual  AbsValue *vcgen(AEnv &env, Type const *type, int path) const=0;
};

class IN_expr : public Initializer {
public:      // data
  Expression *e;

public:      // funcs
  IN_expr(Expression *_e) : Initializer(), e(_e) {
  }
  virtual ~IN_expr();

  virtual Kind kind() const { return IN_EXPR; }
  enum { TYPE_TAG = IN_EXPR };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual IN_expr *clone() const;

  public: virtual  void tcheck(Env &env, Type const *type);
  public: virtual  AbsValue *vcgen(AEnv &env, Type const *type, int path) const;
};

class IN_compound : public Initializer {
public:      // data
  ASTList <Initializer > inits;

public:      // funcs
  IN_compound(ASTList <Initializer > *_inits) : Initializer(), inits(_inits) {
  }
  virtual ~IN_compound();

  virtual Kind kind() const { return IN_COMPOUND; }
  enum { TYPE_TAG = IN_COMPOUND };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual IN_compound *clone() const;

  public: virtual  void tcheck(Env &env, Type const *type);
  public: virtual  AbsValue *vcgen(AEnv &env, Type const *type, int path) const;
};



// *** DO NOT EDIT ***
class InitLabel {
public:      // data

public:      // funcs
  InitLabel() {
  }
  virtual ~InitLabel();

  enum Kind { IL_ELEMENT, IL_RANGE, IL_FIELD, IL_ELEMENTFIELD, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(IL_element, IL_ELEMENT)
  DECL_AST_DOWNCASTS(IL_range, IL_RANGE)
  DECL_AST_DOWNCASTS(IL_field, IL_FIELD)
  DECL_AST_DOWNCASTS(IL_elementField, IL_ELEMENTFIELD)

  virtual InitLabel* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

};

class IL_element : public InitLabel {
public:      // data
  Expression *index;

public:      // funcs
  IL_element(Expression *_index) : InitLabel(), index(_index) {
  }
  virtual ~IL_element();

  virtual Kind kind() const { return IL_ELEMENT; }
  enum { TYPE_TAG = IL_ELEMENT };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual IL_element *clone() const;

};

class IL_range : public InitLabel {
public:      // data
  Expression *low;
  Expression *high;

public:      // funcs
  IL_range(Expression *_low, Expression *_high) : InitLabel(), low(_low), high(_high) {
  }
  virtual ~IL_range();

  virtual Kind kind() const { return IL_RANGE; }
  enum { TYPE_TAG = IL_RANGE };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual IL_range *clone() const;

};

class IL_field : public InitLabel {
public:      // data
  StringRef name;

public:      // funcs
  IL_field(StringRef _name) : InitLabel(), name(_name) {
  }
  virtual ~IL_field();

  virtual Kind kind() const { return IL_FIELD; }
  enum { TYPE_TAG = IL_FIELD };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual IL_field *clone() const;

};

class IL_elementField : public InitLabel {
public:      // data
  Expression *index;
  StringRef name;

public:      // funcs
  IL_elementField(Expression *_index, StringRef _name) : InitLabel(), index(_index), name(_name) {
  }
  virtual ~IL_elementField();

  virtual Kind kind() const { return IL_ELEMENTFIELD; }
  enum { TYPE_TAG = IL_ELEMENTFIELD };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual IL_elementField *clone() const;

};



// *** DO NOT EDIT ***
class FuncAnnotation {
public:      // data

public:      // funcs
  FuncAnnotation() {
  }
  virtual ~FuncAnnotation();

  enum Kind { FA_PRECONDITION, FA_POSTCONDITION, NUM_KINDS };
  virtual Kind kind() const = 0;

  static char const * const kindNames[NUM_KINDS];
  char const *kindName() const { return kindNames[kind()]; }

  DECL_AST_DOWNCASTS(FA_precondition, FA_PRECONDITION)
  DECL_AST_DOWNCASTS(FA_postcondition, FA_POSTCONDITION)

  virtual FuncAnnotation* clone() const=0;

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

};

class FA_precondition : public FuncAnnotation {
public:      // data
  ASTList <Declaration > decls;
  Expression *expr;

public:      // funcs
  FA_precondition(ASTList <Declaration > *_decls, Expression *_expr) : FuncAnnotation(), decls(_decls), expr(_expr) {
  }
  virtual ~FA_precondition();

  virtual Kind kind() const { return FA_PRECONDITION; }
  enum { TYPE_TAG = FA_PRECONDITION };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual FA_precondition *clone() const;

};

class FA_postcondition : public FuncAnnotation {
public:      // data
  Expression *expr;

public:      // funcs
  FA_postcondition(Expression *_expr) : FuncAnnotation(), expr(_expr) {
  }
  virtual ~FA_postcondition();

  virtual Kind kind() const { return FA_POSTCONDITION; }
  enum { TYPE_TAG = FA_POSTCONDITION };

  virtual void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

  virtual FA_postcondition *clone() const;

};



// *** DO NOT EDIT ***
class ThmprvAttr {
public:      // data
  StringRef name;
  ASTList <ThmprvAttr > args;

public:      // funcs
  ThmprvAttr(StringRef _name, ASTList <ThmprvAttr > *_args) : name(_name), args(_args) {
  }
  ~ThmprvAttr();

  char const *kindName() const { return "ThmprvAttr"; }

  ThmprvAttr *clone() const;

  void debugPrint(std::ostream &os, int indent, char const *subtreeName = "tree") const;

};



#endif // C_AST_GEN_H
