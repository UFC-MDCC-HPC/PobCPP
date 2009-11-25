// c.ast.gen.cc
// *** DO NOT EDIT ***
// generated automatically by astgen, from c.ast

#include "c.ast.gen.h"      // this module


// *** DO NOT EDIT ***

  //#include "cc_type.h"       // Type
// ------------------ TranslationUnit -------------------
// *** DO NOT EDIT ***
TranslationUnit::~TranslationUnit()
{
  topForms.deleteAll();
}

void TranslationUnit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TranslationUnit);

  PRINT_LIST(TopForm, topForms);
}

TranslationUnit *TranslationUnit::clone() const
{
  TranslationUnit *ret = new TranslationUnit(
    cloneASTList(topForms)
  );
  return ret;
}


// ------------------ TopForm -------------------
// *** DO NOT EDIT ***
TopForm::~TopForm()
{
}

char const * const TopForm::kindNames[TopForm::NUM_KINDS] = {
  "TF_decl",
  "TF_func",
};

void TopForm::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_GENERIC(loc);
}

DEFN_AST_DOWNCASTS(TopForm, TF_decl, TF_DECL)

TF_decl::~TF_decl()
{
  delete decl;
}

void TF_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TF_decl);

  TopForm::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

TF_decl *TF_decl::clone() const
{
  TF_decl *ret = new TF_decl(
    loc,
    decl? decl->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TopForm, TF_func, TF_FUNC)

TF_func::~TF_func()
{
  delete retspec;
  delete nameParams;
  delete body;
}

void TF_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TF_func);

  TopForm::debugPrint(os, indent, subtreeName);

   printExtras(os, indent); ;
  PRINT_GENERIC(dflags);
  PRINT_SUBTREE(retspec);
  PRINT_SUBTREE(nameParams);
  PRINT_SUBTREE(body);
}

TF_func *TF_func::clone() const
{
  TF_func *ret = new TF_func(
    loc,
    dflags,
    retspec? retspec->clone() : NULL,
    nameParams? nameParams->clone() : NULL,
    body? body->clone() : NULL
  );
  return ret;
}


// *** DO NOT EDIT ***

  // pulled these out of line because Declaration appears lower in .h file
  FunctionType const *TF_func::ftype() const
    { return &( nameParams->var->type->asFunctionTypeC() ); }
  StringRef TF_func::name() const { return nameParams->var->name; }
// ------------------ Declaration -------------------
// *** DO NOT EDIT ***
Declaration::~Declaration()
{
  delete spec;
  decllist.deleteAll();
}

void Declaration::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Declaration);

  PRINT_GENERIC(dflags);
  PRINT_SUBTREE(spec);
  PRINT_LIST(Declarator, decllist);
}

Declaration *Declaration::clone() const
{
  Declaration *ret = new Declaration(
    dflags,
    spec? spec->clone() : NULL,
    cloneASTList(decllist)
  );
  return ret;
}


// ------------------ ASTTypeId -------------------
// *** DO NOT EDIT ***
ASTTypeId::~ASTTypeId()
{
  delete spec;
  delete decl;
}

void ASTTypeId::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ASTTypeId);

  PRINT_SUBTREE(spec);
  PRINT_SUBTREE(decl);
}

ASTTypeId *ASTTypeId::clone() const
{
  ASTTypeId *ret = new ASTTypeId(
    spec? spec->clone() : NULL,
    decl? decl->clone() : NULL
  );
  return ret;
}


// ------------------ TypeSpecifier -------------------
// *** DO NOT EDIT ***
TypeSpecifier::~TypeSpecifier()
{
}

char const * const TypeSpecifier::kindNames[TypeSpecifier::NUM_KINDS] = {
  "TS_name",
  "TS_simple",
  "TS_elaborated",
  "TS_classSpec",
  "TS_enumSpec",
};

void TypeSpecifier::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_name, TS_NAME)

TS_name::~TS_name()
{
}

void TS_name::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_name);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
}

TS_name *TS_name::clone() const
{
  TS_name *ret = new TS_name(
    name
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_simple, TS_SIMPLE)

TS_simple::~TS_simple()
{
}

void TS_simple::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_simple);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(id);
}

TS_simple *TS_simple::clone() const
{
  TS_simple *ret = new TS_simple(
    id
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_elaborated, TS_ELABORATED)

TS_elaborated::~TS_elaborated()
{
}

void TS_elaborated::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_elaborated);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(keyword);
  PRINT_CSTRING(name);
}

TS_elaborated *TS_elaborated::clone() const
{
  TS_elaborated *ret = new TS_elaborated(
    keyword,
    name
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_classSpec, TS_CLASSSPEC)

TS_classSpec::~TS_classSpec()
{
  members.deleteAll();
}

void TS_classSpec::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_classSpec);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(keyword);
  PRINT_CSTRING(name);
  PRINT_LIST(Declaration, members);
}

TS_classSpec *TS_classSpec::clone() const
{
  TS_classSpec *ret = new TS_classSpec(
    keyword,
    name,
    cloneASTList(members)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(TypeSpecifier, TS_enumSpec, TS_ENUMSPEC)

TS_enumSpec::~TS_enumSpec()
{
  elts.deleteAll();
}

void TS_enumSpec::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, TS_enumSpec);

  TypeSpecifier::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_LIST(Enumerator, elts);
}

TS_enumSpec *TS_enumSpec::clone() const
{
  TS_enumSpec *ret = new TS_enumSpec(
    name,
    cloneASTList(elts)
  );
  return ret;
}


// ------------------ Enumerator -------------------
// *** DO NOT EDIT ***
Enumerator::~Enumerator()
{
   delete var;
  delete expr;
}

void Enumerator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Enumerator);

  PRINT_GENERIC(loc);
  PRINT_CSTRING(name);
  PRINT_SUBTREE(expr);
}

Enumerator *Enumerator::clone() const
{
  Enumerator *ret = new Enumerator(
    loc,
    name,
    expr? expr->clone() : NULL
  );
  return ret;
}


// ------------------ Declarator -------------------
// *** DO NOT EDIT ***
Declarator::~Declarator()
{
   delete var;
  delete decl;
  delete init;
}

void Declarator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, Declarator);

  PRINT_SUBTREE(decl);
  PRINT_SUBTREE(init);
}

Declarator *Declarator::clone() const
{
  Declarator *ret = new Declarator(
    decl? decl->clone() : NULL,
    init? init->clone() : NULL
  );
  return ret;
}


// ------------------ IDeclarator -------------------
// *** DO NOT EDIT ***
IDeclarator::~IDeclarator()
{
}

char const * const IDeclarator::kindNames[IDeclarator::NUM_KINDS] = {
  "D_name",
  "D_func",
  "D_array",
  "D_bitfield",
};

void IDeclarator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

DEFN_AST_DOWNCASTS(IDeclarator, D_name, D_NAME)

D_name::~D_name()
{
  delete attr;
}

void D_name::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_name);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(loc);
  PRINT_CSTRING(name);
  PRINT_SUBTREE(attr);
}

D_name *D_name::clone() const
{
  D_name *ret = new D_name(
    loc,
    name,
    attr? attr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_func, D_FUNC)

D_func::~D_func()
{
   delete result;
  delete base;
  params.deleteAll();
  ann.deleteAll();
}

void D_func::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_func);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(loc);
  PRINT_SUBTREE(base);
  PRINT_LIST(ASTTypeId, params);
  PRINT_LIST(FuncAnnotation, ann);
}

D_func *D_func::clone() const
{
  D_func *ret = new D_func(
    loc,
    base? base->clone() : NULL,
    cloneASTList(params),
    cloneASTList(ann)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_array, D_ARRAY)

D_array::~D_array()
{
  delete base;
  delete size;
}

void D_array::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_array);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(base);
  PRINT_SUBTREE(size);
}

D_array *D_array::clone() const
{
  D_array *ret = new D_array(
    base? base->clone() : NULL,
    size? size->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(IDeclarator, D_bitfield, D_BITFIELD)

D_bitfield::~D_bitfield()
{
  delete bits;
}

void D_bitfield::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, D_bitfield);

  IDeclarator::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_SUBTREE(bits);
}

D_bitfield *D_bitfield::clone() const
{
  D_bitfield *ret = new D_bitfield(
    name,
    bits? bits->clone() : NULL
  );
  return ret;
}


// ------------------ PtrOperator -------------------
// *** DO NOT EDIT ***
PtrOperator::~PtrOperator()
{
}

void PtrOperator::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, PtrOperator);

  PRINT_GENERIC(cv);
}

PtrOperator *PtrOperator::clone() const
{
  PtrOperator *ret = new PtrOperator(
    cv
  );
  return ret;
}


// ------------------ Statement -------------------
// *** DO NOT EDIT ***
Statement::~Statement()
{
}

char const * const Statement::kindNames[Statement::NUM_KINDS] = {
  "S_skip",
  "S_label",
  "S_case",
  "S_caseRange",
  "S_default",
  "S_expr",
  "S_compound",
  "S_if",
  "S_switch",
  "S_while",
  "S_doWhile",
  "S_for",
  "S_break",
  "S_continue",
  "S_return",
  "S_goto",
  "S_decl",
  "S_assert",
  "S_assume",
  "S_invariant",
  "S_thmprv",
};

void Statement::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    ind(os, indent) << "numPaths=" << numPaths
                    << ", succ=" << successorsToString()
                    << std::endl;
  ;
  PRINT_GENERIC(loc);
}

DEFN_AST_DOWNCASTS(Statement, S_skip, S_SKIP)

S_skip::~S_skip()
{
}

void S_skip::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_skip);

  Statement::debugPrint(os, indent, subtreeName);

}

S_skip *S_skip::clone() const
{
  S_skip *ret = new S_skip(
    loc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_label, S_LABEL)

S_label::~S_label()
{
  delete s;
}

void S_label::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_label);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_SUBTREE(s);
}

S_label *S_label::clone() const
{
  S_label *ret = new S_label(
    loc,
    name,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_case, S_CASE)

S_case::~S_case()
{
  delete expr;
  delete s;
}

void S_case::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_case);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(s);
}

S_case *S_case::clone() const
{
  S_case *ret = new S_case(
    loc,
    expr? expr->clone() : NULL,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_caseRange, S_CASERANGE)

S_caseRange::~S_caseRange()
{
  delete low;
  delete high;
  delete s;
}

void S_caseRange::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_caseRange);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(low);
  PRINT_SUBTREE(high);
  PRINT_SUBTREE(s);
}

S_caseRange *S_caseRange::clone() const
{
  S_caseRange *ret = new S_caseRange(
    loc,
    low? low->clone() : NULL,
    high? high->clone() : NULL,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_default, S_DEFAULT)

S_default::~S_default()
{
  delete s;
}

void S_default::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_default);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(s);
}

S_default *S_default::clone() const
{
  S_default *ret = new S_default(
    loc,
    s? s->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_expr, S_EXPR)

S_expr::~S_expr()
{
  delete expr;
}

void S_expr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_expr);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

S_expr *S_expr::clone() const
{
  S_expr *ret = new S_expr(
    loc,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_compound, S_COMPOUND)

S_compound::~S_compound()
{
  stmts.deleteAll();
}

void S_compound::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_compound);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_LIST(Statement, stmts);
}

S_compound *S_compound::clone() const
{
  S_compound *ret = new S_compound(
    loc,
    cloneASTList(stmts)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_if, S_IF)

S_if::~S_if()
{
  delete cond;
  delete thenBranch;
  delete elseBranch;
}

void S_if::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_if);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(thenBranch);
  PRINT_SUBTREE(elseBranch);
}

S_if *S_if::clone() const
{
  S_if *ret = new S_if(
    loc,
    cond? cond->clone() : NULL,
    thenBranch? thenBranch->clone() : NULL,
    elseBranch? elseBranch->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_switch, S_SWITCH)

S_switch::~S_switch()
{
  delete expr;
  delete branches;
}

void S_switch::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_switch);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_SUBTREE(branches);
}

S_switch *S_switch::clone() const
{
  S_switch *ret = new S_switch(
    loc,
    expr? expr->clone() : NULL,
    branches? branches->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_while, S_WHILE)

S_while::~S_while()
{
  delete cond;
  delete body;
}

void S_while::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_while);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(body);
}

S_while *S_while::clone() const
{
  S_while *ret = new S_while(
    loc,
    cond? cond->clone() : NULL,
    body? body->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_doWhile, S_DOWHILE)

S_doWhile::~S_doWhile()
{
  delete body;
  delete cond;
}

void S_doWhile::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_doWhile);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(body);
  PRINT_SUBTREE(cond);
}

S_doWhile *S_doWhile::clone() const
{
  S_doWhile *ret = new S_doWhile(
    loc,
    body? body->clone() : NULL,
    cond? cond->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_for, S_FOR)

S_for::~S_for()
{
  delete init;
  delete cond;
  delete after;
  delete body;
}

void S_for::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_for);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(init);
  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(after);
  PRINT_SUBTREE(body);
}

S_for *S_for::clone() const
{
  S_for *ret = new S_for(
    loc,
    init? init->clone() : NULL,
    cond? cond->clone() : NULL,
    after? after->clone() : NULL,
    body? body->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_break, S_BREAK)

S_break::~S_break()
{
}

void S_break::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_break);

  Statement::debugPrint(os, indent, subtreeName);

}

S_break *S_break::clone() const
{
  S_break *ret = new S_break(
    loc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_continue, S_CONTINUE)

S_continue::~S_continue()
{
}

void S_continue::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_continue);

  Statement::debugPrint(os, indent, subtreeName);

}

S_continue *S_continue::clone() const
{
  S_continue *ret = new S_continue(
    loc
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_return, S_RETURN)

S_return::~S_return()
{
  delete expr;
}

void S_return::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_return);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

S_return *S_return::clone() const
{
  S_return *ret = new S_return(
    loc,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_goto, S_GOTO)

S_goto::~S_goto()
{
}

void S_goto::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_goto);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(target);
}

S_goto *S_goto::clone() const
{
  S_goto *ret = new S_goto(
    loc,
    target
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_decl, S_DECL)

S_decl::~S_decl()
{
  delete decl;
}

void S_decl::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_decl);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(decl);
}

S_decl *S_decl::clone() const
{
  S_decl *ret = new S_decl(
    loc,
    decl? decl->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_assert, S_ASSERT)

S_assert::~S_assert()
{
  delete expr;
}

void S_assert::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_assert);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
  PRINT_BOOL(pure);
}

S_assert *S_assert::clone() const
{
  S_assert *ret = new S_assert(
    loc,
    expr? expr->clone() : NULL,
    pure
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_assume, S_ASSUME)

S_assume::~S_assume()
{
  delete expr;
}

void S_assume::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_assume);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

S_assume *S_assume::clone() const
{
  S_assume *ret = new S_assume(
    loc,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_invariant, S_INVARIANT)

S_invariant::~S_invariant()
{
  delete expr;
}

void S_invariant::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_invariant);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

S_invariant *S_invariant::clone() const
{
  S_invariant *ret = new S_invariant(
    loc,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Statement, S_thmprv, S_THMPRV)

S_thmprv::~S_thmprv()
{
  delete s;
}

void S_thmprv::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, S_thmprv);

  Statement::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(s);
}

S_thmprv *S_thmprv::clone() const
{
  S_thmprv *ret = new S_thmprv(
    loc,
    s? s->clone() : NULL
  );
  return ret;
}


// ------------------ Expression -------------------
// *** DO NOT EDIT ***
Expression::~Expression()
{
}

char const * const Expression::kindNames[Expression::NUM_KINDS] = {
  "E_intLit",
  "E_floatLit",
  "E_stringLit",
  "E_charLit",
  "E_variable",
  "E_funCall",
  "E_fieldAcc",
  "E_sizeof",
  "E_unary",
  "E_effect",
  "E_binary",
  "E_addrOf",
  "E_deref",
  "E_cast",
  "E_cond",
  "E_comma",
  "E_sizeofType",
  "E_new",
  "E_assign",
  "E_quantifier",
};

void Expression::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  
    ind(os, indent) << extrasToString() << "\n";
  ;
}

DEFN_AST_DOWNCASTS(Expression, E_intLit, E_INTLIT)

E_intLit::~E_intLit()
{
}

void E_intLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_intLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(i);
}

E_intLit *E_intLit::clone() const
{
  E_intLit *ret = new E_intLit(
    i
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_floatLit, E_FLOATLIT)

E_floatLit::~E_floatLit()
{
}

void E_floatLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_floatLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(f);
}

E_floatLit *E_floatLit::clone() const
{
  E_floatLit *ret = new E_floatLit(
    f
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_stringLit, E_STRINGLIT)

E_stringLit::~E_stringLit()
{
}

void E_stringLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_stringLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(s);
}

E_stringLit *E_stringLit::clone() const
{
  E_stringLit *ret = new E_stringLit(
    s
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_charLit, E_CHARLIT)

E_charLit::~E_charLit()
{
}

void E_charLit::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_charLit);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(c);
}

E_charLit *E_charLit::clone() const
{
  E_charLit *ret = new E_charLit(
    c
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_variable, E_VARIABLE)

E_variable::~E_variable()
{
}

void E_variable::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_variable);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
  PRINT_CSTRING(scopeName);
}

E_variable *E_variable::clone() const
{
  E_variable *ret = new E_variable(
    name,
    scopeName
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_funCall, E_FUNCALL)

E_funCall::~E_funCall()
{
  delete func;
  args.deleteAll();
}

void E_funCall::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_funCall);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(func);
  PRINT_LIST(Expression, args);
}

E_funCall *E_funCall::clone() const
{
  E_funCall *ret = new E_funCall(
    func? func->clone() : NULL,
    cloneASTList(args)
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_fieldAcc, E_FIELDACC)

E_fieldAcc::~E_fieldAcc()
{
  delete obj;
}

void E_fieldAcc::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_fieldAcc);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(obj);
  PRINT_CSTRING(fieldName);
}

E_fieldAcc *E_fieldAcc::clone() const
{
  E_fieldAcc *ret = new E_fieldAcc(
    obj? obj->clone() : NULL,
    fieldName
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_sizeof, E_SIZEOF)

E_sizeof::~E_sizeof()
{
  delete expr;
}

void E_sizeof::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_sizeof);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_sizeof *E_sizeof::clone() const
{
  E_sizeof *ret = new E_sizeof(
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_unary, E_UNARY)

E_unary::~E_unary()
{
  delete expr;
}

void E_unary::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_unary);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(op);
  PRINT_SUBTREE(expr);
}

E_unary *E_unary::clone() const
{
  E_unary *ret = new E_unary(
    op,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_effect, E_EFFECT)

E_effect::~E_effect()
{
  delete expr;
}

void E_effect::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_effect);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_GENERIC(op);
  PRINT_SUBTREE(expr);
}

E_effect *E_effect::clone() const
{
  E_effect *ret = new E_effect(
    op,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_binary, E_BINARY)

E_binary::~E_binary()
{
  delete e1;
  delete e2;
}

void E_binary::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_binary);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(e1);
  PRINT_GENERIC(op);
  PRINT_SUBTREE(e2);
}

E_binary *E_binary::clone() const
{
  E_binary *ret = new E_binary(
    e1? e1->clone() : NULL,
    op,
    e2? e2->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_addrOf, E_ADDROF)

E_addrOf::~E_addrOf()
{
  delete expr;
}

void E_addrOf::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_addrOf);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

E_addrOf *E_addrOf::clone() const
{
  E_addrOf *ret = new E_addrOf(
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_deref, E_DEREF)

E_deref::~E_deref()
{
  delete ptr;
}

void E_deref::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_deref);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(ptr);
}

E_deref *E_deref::clone() const
{
  E_deref *ret = new E_deref(
    ptr? ptr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_cast, E_CAST)

E_cast::~E_cast()
{
  delete ctype;
  delete expr;
}

void E_cast::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_cast);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(ctype);
  PRINT_SUBTREE(expr);
}

E_cast *E_cast::clone() const
{
  E_cast *ret = new E_cast(
    ctype? ctype->clone() : NULL,
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_cond, E_COND)

E_cond::~E_cond()
{
  delete cond;
  delete th;
  delete el;
}

void E_cond::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_cond);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(cond);
  PRINT_SUBTREE(th);
  PRINT_SUBTREE(el);
}

E_cond *E_cond::clone() const
{
  E_cond *ret = new E_cond(
    cond? cond->clone() : NULL,
    th? th->clone() : NULL,
    el? el->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_comma, E_COMMA)

E_comma::~E_comma()
{
  delete e1;
  delete e2;
}

void E_comma::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_comma);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(e1);
  PRINT_SUBTREE(e2);
}

E_comma *E_comma::clone() const
{
  E_comma *ret = new E_comma(
    e1? e1->clone() : NULL,
    e2? e2->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_sizeofType, E_SIZEOFTYPE)

E_sizeofType::~E_sizeofType()
{
  delete atype;
}

void E_sizeofType::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_sizeofType);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(atype);
}

E_sizeofType *E_sizeofType::clone() const
{
  E_sizeofType *ret = new E_sizeofType(
    atype? atype->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_new, E_NEW)

E_new::~E_new()
{
  delete atype;
}

void E_new::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_new);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(atype);
}

E_new *E_new::clone() const
{
  E_new *ret = new E_new(
    atype? atype->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_assign, E_ASSIGN)

E_assign::~E_assign()
{
  delete target;
  delete src;
}

void E_assign::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_assign);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(target);
  PRINT_GENERIC(op);
  PRINT_SUBTREE(src);
}

E_assign *E_assign::clone() const
{
  E_assign *ret = new E_assign(
    target? target->clone() : NULL,
    op,
    src? src->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Expression, E_quantifier, E_QUANTIFIER)

E_quantifier::~E_quantifier()
{
  decls.deleteAll();
  delete pred;
}

void E_quantifier::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, E_quantifier);

  Expression::debugPrint(os, indent, subtreeName);

  PRINT_LIST(Declaration, decls);
  PRINT_SUBTREE(pred);
  PRINT_BOOL(forall);
}

E_quantifier *E_quantifier::clone() const
{
  E_quantifier *ret = new E_quantifier(
    cloneASTList(decls),
    pred? pred->clone() : NULL,
    forall
  );
  return ret;
}


// ------------------ Initializer -------------------
// *** DO NOT EDIT ***
Initializer::~Initializer()
{
}

char const * const Initializer::kindNames[Initializer::NUM_KINDS] = {
  "IN_expr",
  "IN_compound",
};

void Initializer::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

DEFN_AST_DOWNCASTS(Initializer, IN_expr, IN_EXPR)

IN_expr::~IN_expr()
{
  delete e;
}

void IN_expr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IN_expr);

  Initializer::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(e);
}

IN_expr *IN_expr::clone() const
{
  IN_expr *ret = new IN_expr(
    e? e->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(Initializer, IN_compound, IN_COMPOUND)

IN_compound::~IN_compound()
{
  inits.deleteAll();
}

void IN_compound::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IN_compound);

  Initializer::debugPrint(os, indent, subtreeName);

  PRINT_LIST(Initializer, inits);
}

IN_compound *IN_compound::clone() const
{
  IN_compound *ret = new IN_compound(
    cloneASTList(inits)
  );
  return ret;
}


// ------------------ InitLabel -------------------
// *** DO NOT EDIT ***
InitLabel::~InitLabel()
{
}

char const * const InitLabel::kindNames[InitLabel::NUM_KINDS] = {
  "IL_element",
  "IL_range",
  "IL_field",
  "IL_elementField",
};

void InitLabel::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

DEFN_AST_DOWNCASTS(InitLabel, IL_element, IL_ELEMENT)

IL_element::~IL_element()
{
  delete index;
}

void IL_element::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IL_element);

  InitLabel::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(index);
}

IL_element *IL_element::clone() const
{
  IL_element *ret = new IL_element(
    index? index->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(InitLabel, IL_range, IL_RANGE)

IL_range::~IL_range()
{
  delete low;
  delete high;
}

void IL_range::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IL_range);

  InitLabel::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(low);
  PRINT_SUBTREE(high);
}

IL_range *IL_range::clone() const
{
  IL_range *ret = new IL_range(
    low? low->clone() : NULL,
    high? high->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(InitLabel, IL_field, IL_FIELD)

IL_field::~IL_field()
{
}

void IL_field::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IL_field);

  InitLabel::debugPrint(os, indent, subtreeName);

  PRINT_CSTRING(name);
}

IL_field *IL_field::clone() const
{
  IL_field *ret = new IL_field(
    name
  );
  return ret;
}

DEFN_AST_DOWNCASTS(InitLabel, IL_elementField, IL_ELEMENTFIELD)

IL_elementField::~IL_elementField()
{
  delete index;
}

void IL_elementField::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, IL_elementField);

  InitLabel::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(index);
  PRINT_CSTRING(name);
}

IL_elementField *IL_elementField::clone() const
{
  IL_elementField *ret = new IL_elementField(
    index? index->clone() : NULL,
    name
  );
  return ret;
}


// ------------------ FuncAnnotation -------------------
// *** DO NOT EDIT ***
FuncAnnotation::~FuncAnnotation()
{
}

char const * const FuncAnnotation::kindNames[FuncAnnotation::NUM_KINDS] = {
  "FA_precondition",
  "FA_postcondition",
};

void FuncAnnotation::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
}

DEFN_AST_DOWNCASTS(FuncAnnotation, FA_precondition, FA_PRECONDITION)

FA_precondition::~FA_precondition()
{
  decls.deleteAll();
  delete expr;
}

void FA_precondition::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, FA_precondition);

  FuncAnnotation::debugPrint(os, indent, subtreeName);

  PRINT_LIST(Declaration, decls);
  PRINT_SUBTREE(expr);
}

FA_precondition *FA_precondition::clone() const
{
  FA_precondition *ret = new FA_precondition(
    cloneASTList(decls),
    expr? expr->clone() : NULL
  );
  return ret;
}

DEFN_AST_DOWNCASTS(FuncAnnotation, FA_postcondition, FA_POSTCONDITION)

FA_postcondition::~FA_postcondition()
{
  delete expr;
}

void FA_postcondition::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, FA_postcondition);

  FuncAnnotation::debugPrint(os, indent, subtreeName);

  PRINT_SUBTREE(expr);
}

FA_postcondition *FA_postcondition::clone() const
{
  FA_postcondition *ret = new FA_postcondition(
    expr? expr->clone() : NULL
  );
  return ret;
}


// ------------------ ThmprvAttr -------------------
// *** DO NOT EDIT ***
ThmprvAttr::~ThmprvAttr()
{
  args.deleteAll();
}

void ThmprvAttr::debugPrint(std::ostream &os, int indent, char const *subtreeName) const
{
  PRINT_HEADER(subtreeName, ThmprvAttr);

  PRINT_CSTRING(name);
  PRINT_LIST(ThmprvAttr, args);
}

ThmprvAttr *ThmprvAttr::clone() const
{
  ThmprvAttr *ret = new ThmprvAttr(
    name,
    cloneASTList(args)
  );
  return ret;
}




