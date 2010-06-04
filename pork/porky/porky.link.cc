// License?

#include <cstring>
#include <iostream>
#include <sstream>
#include <map>

#include <stdint.h>

#include "piglet.h"

#include "expr_visitor.h"
#include "patcher.h"

using namespace std;

#define ALEN(arr)    (sizeof(arr) / sizeof(arr[0]))
#define NYI(what)                               \
    do {                                        \
        cerr <<"NYI: "<< what <<endl;           \
        abort();                                \
    } while (0)

#define NYI_NODE(node)                                                  \
    do {                                                                \
        cerr<<__FUNCTION__<<":"<<__LINE__<< ": don't understand node"<<endl; \
        node->debugPrint(cerr, 2);                                      \
        abort();                                                        \
    } while (0)

#define UNREACHED(what)                                                 \
    do {                                                                \
        cerr<<__FUNCTION__<<":"<<__LINE__<< ": shouldn't have reached"  \
            << what << endl;                                            \
        abort();                                                        \
    } while (0)

#define UNREACHED_NODE(node)                                            \
    do {                                                                \
        cerr<<__FUNCTION__<<":"<<__LINE__<< ": shouldn't have reached"<<endl; \
        node->debugPrint(cerr, 2);                                      \
        abort();                                                        \
    } while (0)

//-----------------------------------------------------------------------------

#define declarator_foreach_ideclarator(d, id)           \
    for (const IDeclarator* id = (d)->decl; id; id = (id)->getBaseC())

//-----------------------------------------------------------------------------
// XXX this section needs to be kept in sync with the code that porky.py
// generates.
//
struct TypeRule
{
    const char* const base_name;
    const char* const qualifiers;
    const char* const to_base_name;
    const char* const to_qualifiers;
    
    bool
    match(const sm::string& type_name, const Declarator* decl,
          const D_name** outVarName, const IDeclarator**outLeftmostQual) const
    {
        const D_name* varName = 0;
        const IDeclarator* leftmostQual = 0;

        const char* qp = qualifiers;
        declarator_foreach_ideclarator(decl, idecl) {
            if (!leftmostQual)
                leftmostQual = idecl;

            if (!*qp 
                // can't use ifD_name() because idecl is const.  bug in elsa
                && IDeclarator::D_NAME == idecl->kind()
                && type_name == base_name) {
                // can't use asD_name() because idecl is const.  no bug here
                varName = (const D_name *) idecl;
                goto out;
            } else if (!*qp || IDeclarator::D_NAME == idecl->kind()) {
                goto out;
            }

            switch (*qp) {
            // can't use ifD_*() because idecl is const.  bug in elsa
            case '*':
                if (IDeclarator::D_POINTER != idecl->kind())
                    goto out;
                break;
            case '&':
                if (IDeclarator::D_REFERENCE != idecl->kind())
                    goto out;
                break;
            case '[':
                if (IDeclarator::D_ARRAY != idecl->kind())
                    goto out;
                break;

            default:
                UNREACHED_NODE(idecl);
            }
            ++qp;
        }
out:
        if (outVarName && varName) {
            *outVarName = varName;
            if (outLeftmostQual)
                *outLeftmostQual = leftmostQual;
        }
        return varName;
    }

    string
    makeNewDeclarator(const char* varName) const
    {
        string s = to_qualifiers;
        // STYLE CUSTOMIZATION: is it "Foo* f" or "Foo *f"?
        return s + ((s != "") ? " " : "") + varName;
    }
};
ostream&
operator<<(ostream& os, const TypeRule& rule)
{
    return os <<"<TypeRule match="
              << rule.base_name << rule.qualifiers 
              << " changeto="
              << rule.to_base_name << rule.to_qualifiers
              << ">";
}
ostream&
operator<<(ostream& os, const TypeRule* rule)
{
    return os << *rule;
}

#define foreach_type_rule(r)                                    \
    for (TypeRule* r = &_type_rules[0]; (r)->base_name; ++r)

//-----------------------------------------------------------------------------
// XXX this section needs to be kept in sync with the code that porky.py
// generates.
//

/** After we've matched a function, each write_instr tells us how to emit
 * part of the rewritten function.  An instruction is one of 
 *   |  EMIT_STRING  (const char *)|: emit a literal string
 *   |EMIT_CAPT_ARG  (uint)|: emit a captured argument
 *   |         HALT  (xxx)|: done emitting stuff
 * |WriteInstr|'s store a single intptr_t argument, which is interpreted
 * according to the instruction type.
 */
struct WriteInstr
{
    enum { EMIT_STRING, EMIT_CAPT_ARG, HALT } op;
    uintptr_t opnd;

    /** Execute the operation on |out|.  Return true if more instructions
     * remain to be executed.*/
    bool
    exec(ostream& out, const vector<string>& args) const 
    {
        const char* str = 0;

        switch(op) {
        case HALT: return false;
        case EMIT_STRING:
            str = (const char*) opnd;
            xassert(str);
            out << str;
            return true;
        case EMIT_CAPT_ARG:
            xassert(opnd < args.size());
            out << args[opnd];
            return true;
        default:
            UNREACHED(op);
            return false;
        }
    }
};

struct CallRule
{
    const char* callable;
    int nargs;                  // -1 means any number of args
    const WriteInstr* const wprog;
    
    bool
    match(const string& fname, const vector<string>& captArgs) const
    {
        bool m = (fname == callable) 
                 && (0 > nargs || ((int) captArgs.size()) == nargs);
        return m;
    }

    string
    makeNewFuncall(const vector<string>& captArgs) const
    {
        ostringstream out;

        const WriteInstr* i = wprog;
        while (i->exec(out, captArgs))  ++i;

        return out.str();
    }
};
ostream&
operator<<(ostream& os, const CallRule& rule)
{
    return os <<"<CallRule callable="<< rule.callable <<" ...>";
}
ostream&
operator<<(ostream& os, const CallRule* rule)
{
    return os << *rule;
}

#define foreach_call_rule(r)                                    \
    for (CallRule* r = &_call_rules[0]; (r)->callable; ++r)

static const char dot[] = ".";
static const char arrow[] = "->";
static const char lparen[] = "(";
static const char comma[] = ", ";
static const char rparen[] = ")";
static const char star[] = "*";
static const char _new[] = "new ";
static const char _delete[] = "delete ";

//-----------------------------------------------------------------------------
// XXX this section needs to be kept in sync with the code that porky.py
// generates.
//

#include "rules.gen.h"

//-----------------------------------------------------------------------------

class REWRITER : public ExpressionVisitor
{
public:
    REWRITER(Patcher& patcher, ostream& log)
        : patcher(patcher), log(log) {
    }

    void
    warnSkippedPatch(CPPSourceLoc loc)
    {
        log <<"#>>> "<< toString(loc.loc()) <<": "
                     << loc.macroExpansion->name
                     <<" macro prevents rewrite"<< endl;
    }

    void
    tryEdit(const string& str, const UnboxedPairLoc& where,
            CPPSourceLoc loc)
    {
        if (!loc.hasExactPosition()) {
            warnSkippedPatch(loc);
            return;
        }
        patcher.printPatch(str, where);
    }

    void
    tryEdit(const string& str, const UnboxedPairLoc& where,
            CPPSourceLoc loc1, CPPSourceLoc loc2)
    {
        if (!loc2.hasExactPosition()) {
            warnSkippedPatch(loc2);
            return;
        }
        tryEdit(str, where, loc1);
    }

    sm::string
    getBaseName(BaseType* type) const
    {
        if (type->isPointerType())
            return getBaseName(type->asPointerType()->getAtType());
        if (type->isReferenceType())
            return getBaseName(type->asReferenceType()->getAtType());
        if (type->isArrayType())
            return getBaseName(type->asArrayType()->getAtType());

        // this might return something unusual: a FunctionType, 
        // PointerToMemberType, or DependentSizedArrayType.  we don't what
        // the "base" of these are, so we hope the calling code knows what
        // it's doing ...
        return type->toString();
    }

    sm::string
    getBaseName(TypeSpecifier* t) const
    {
        switch (t->kind()) {
        case TypeSpecifier::TS_NAME:
            return t->asTS_name()->name->toString();
        case TypeSpecifier::TS_CLASSSPEC:
            // probably a union
            return (t->asTS_classSpec()->name) ? 
                t->asTS_classSpec()->name->toString()
                : "__anon__.union";
        case TypeSpecifier::TS_SIMPLE:
            return simpleTypeName(t->asTS_simple()->id);
        case TypeSpecifier::TS_TYPE:
            return getBaseName(t->asTS_type()->type);
        case TypeSpecifier::TS_ENUMSPEC:
            return t->asTS_enumSpec()->name ?
                t->asTS_enumSpec()->name
                : "__anon__.enum";
            return t->asTS_enumSpec()->name;
        case TypeSpecifier::TS_ELABORATED: {
            TS_elaborated* tse = t->asTS_elaborated();
            sm::string name = typeIntrNames[tse->keyword];
            // & means concatenation for sm::string
            name &= " ";
            name &= tse->name->toString();
            return name;
        }
        case TypeSpecifier::TS_TYPEOF:
            // TODO not yet supported
            return " __typeof(something)__ ";
        default:
            NYI_NODE(t);
        }
    }

    /** Returns 0 if the declarator was not rewritten, and the new base type
     * name if it was.*/
    const char*
    tryDeclaratorRewrite(const sm::string& type_name, const Declarator* decl)
    {
        const D_name* var;
        const IDeclarator* leftmostQual;

        foreach_type_rule(rule) {
            if (rule->match(type_name, decl, &var, &leftmostQual)) {
                const char* newTypeSpec = rule->to_base_name;

                // XXX it appears that type coercion operators get turned
                // XXX into D_names without PQNames.  so we have to hack 
                // XXX around this below.

                sm::string varName = 
                    var->name ? var->name->toString() : "";
                string newDecl = rule->makeNewDeclarator(varName.c_str());

                CPPSourceLoc leftmostQualLoc = leftmostQual->loc;
                UnboxedLoc startloc;
                const char *filename = startloc.set(leftmostQualLoc.loc());

                CPPSourceLoc varLoc = 
                    var->name ? var->name->loc : var->loc;
                UnboxedLoc endloc;
                endloc.set(varLoc.loc());
                endloc.col += varName.length();

                tryEdit(newDecl, 
                        UnboxedPairLoc(filename, startloc, endloc),
                        leftmostQualLoc.loc(), varLoc.loc());

                return newTypeSpec;
            }
        }
        return 0;
    }

    virtual bool
    visitASTTypeId(ASTTypeId* tid)
    {
        TypeSpecifier* t = tid->spec;
        Declarator* decl = tid->decl;

        sm::string type_name = getBaseName(t);
        const char* newTypeSpec = tryDeclaratorRewrite(type_name, decl);
        // XXX assuming that this is only called from a function spec
        // or something, and that the 'init' is not interesting to visit.

        if (newTypeSpec) {
            CPPSourceLoc tLoc = t->loc;
            UnboxedLoc startloc;
            const char *filename = startloc.set(tLoc.loc());
            UnboxedLoc endloc;
            endloc.set(tLoc.loc());
            endloc.col += type_name.length();

            tryEdit(newTypeSpec, UnboxedPairLoc(filename, startloc, endloc),
                    tLoc.loc());
        }

        return !newTypeSpec;
    }

    // We need to visit Declarations separately from Declarators because
    // there might be more than one declarator per declaration, and we only
    // want to rewrite the base type once.
    virtual bool
    visitDeclaration(Declaration* d) 
    {
        DeclFlags flags = d->dflags;

        // don't (/shouldn't/) care about builtins
        if (DF_BUILTIN & flags)
            return false;

        const char* newTypeSpec = 0;
        TypeSpecifier* t = d->spec;
        sm::string type_name = getBaseName(t);
        FakeList<Declarator>* decls = d->decllist;
        FAKELIST_FOREACH(Declarator, decls, decl) {
            if (decl->init)
                decl->init->traverse(*this);

            const char* tempNewTypeSpec = 
                tryDeclaratorRewrite(type_name, decl);
            if (!newTypeSpec)
                newTypeSpec = tempNewTypeSpec;
        }

        if (newTypeSpec) {
            CPPSourceLoc tLoc = t->loc;
            UnboxedLoc startloc;
            const char *filename = startloc.set(tLoc.loc());
            UnboxedLoc endloc;
            endloc.set(tLoc.loc());
            endloc.col += type_name.length();

            tryEdit(newTypeSpec, UnboxedPairLoc(filename, startloc, endloc),
                    tLoc.loc());
        }

        return !newTypeSpec;
    }

    virtual bool
    visitE_funCall(E_funCall* fc)
    {
        string fname;
        int nargs = 0;
        vector<string> captArgs;

        if (fc->func->ifE_variable()) {
            fname = fc->func->asE_variable()->name->toString().c_str();
        } else if (fc->func->ifE_fieldAcc()) {
            // TODO oy vey iz mir.  I would expect a lowering pass to remove
            // method call crap and convert to something like 
            // Base::foo(this, ...), but elsa doesn't do this.  
            // so here we hack in the fully-qualified function name and
            // |this| argument, if they exist.
            // TODO doesn't consider inheritance
            E_fieldAcc* efa = fc->func->asE_fieldAcc();
            fname = getBaseName(efa->obj->getType()).c_str();
            fname += "::";
            fname += efa->fieldName->toString().c_str();

            // capture the "this" argument we just located
            try {
                captArgs.push_back(patcher.getRange(
                                       PairLoc(efa->obj->loc,
                                               efa->obj->endloc)));
            } catch (x_assert& ae) {
                // whoops --- no precise source location.  skip it.
                //warning("imprecise source loc, skipping");
                return false;
            }
            nargs = 1;
        } else if (fc->func->ifE_arrow()) {
            // TODO sigh.  almost exactly the same code as above, and no
            // good way to share it.
            E_arrow* ea = fc->func->ifE_arrow();
            fname = getBaseName(ea->obj->getType()).c_str();
            fname += "::";
            fname += ea->fieldName->toString().c_str();

            // capture the "this" argument we just located
            try {
                captArgs.push_back(patcher.getRange(
                                       PairLoc(ea->obj->loc,
                                               ea->obj->endloc)));
            } catch (x_assert& ae) {
                // whoops --- no precise source location.  skip it.
                //warning("imprecise source loc, skipping");
                return false;
            }
            nargs = 1;
        } else if (fc->func->ifE_binary()) {
            // TODO sometime this is a pointer-to-method expression.
            // not yet implemented.  just visit the children and see if 
            // we can do anything
            return true;
        } else if (fc->func->ifE_deref()) {
            // TODO this shows up with hash table enumerators, where we 
            // have *(nsTHashtable<EntryType>::s_EnumArgs * -> userFunc)(...).
            // not yet implemented.  just visit the children and see if
            // can do anything.
            return true;
        } else if (fc->func->ifE_constructor()) {
            // TODO not implemented
            return true;
        } else if (fc->func->ifE_cond()) {
            // TODO not implemented
            return true;
        } else if (fc->func->ifE_cast()) {
            // TODO not implemented
            return true;
        } else {
            UNREACHED_NODE(fc->func);
            return true;
        }

        FAKELIST_FOREACH(ArgExpression, fc->args, arg) {
            try {
                captArgs.push_back(
                    patcher.getRange(
                        PairLoc(arg->expr->loc, arg->expr->endloc)));
                ++nargs;
            } catch (x_assert& ae) {
                // whoops --- no precise source location.  skip it.
                //warning("imprecise source loc, skipping");
                return false;
            }
        }

        foreach_call_rule(c) {
            if (c->match(fname, captArgs)) {
                string newFuncall = c->makeNewFuncall(captArgs);

                if (0 <= fc->args)
                    tryEdit(newFuncall, PairLoc(fc->loc, fc->endloc),
                            fc->loc, fc->endloc);
                else
                    // special case when we want to replace a function's
                    // name only, i.e., we don't care what the args are
                    tryEdit(newFuncall,
                            PairLoc(fc->func->loc, fc->func->endloc),
                            fc->func->loc, fc->func->loc);

                return false;
            }
        }

        return true;
    }

private:
    Patcher patcher;
    ostream& log;
};

//-----------------------------------------------------------------------------

int
main(int argc, char **argv)
{
    xassert(argc > 1);

    PigletParser parser;
    Patcher p;
    ofstream log;
//    log.open("/dev/null");
//    REWRITER visitor(p, log);
    REWRITER visitor(p, cout);

    for (int i = 1; i < argc; ++i) {
        TranslationUnit *unit = parser.getASTNoExc(argv[i]);
        unit->traverse(visitor);
    }
    return 0;
}
