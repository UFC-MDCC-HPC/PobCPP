#include <fstream>
#include <iostream>
#include <sstream>

#include "expr_visitor.h"
#include "patcher.h"
#include "piglet.h"

using namespace std;

int failures = 0;

class PatcherTest : public ExpressionVisitor {
public:
    PatcherTest(const string& filename)
        : filename_(filename), 
          pout_(),
          patcher_(pout_) {
    }
    virtual ~PatcherTest() {
    }

    virtual void run() = 0;

    void pass() {
        cout <<"PASS | "<< filename_ <<endl;
    }

    void fail(const char* why) {
        cerr <<"***** FAIL | "<< filename_ <<":"<<endl<<"  "<< why <<endl;
        cerr <<"*****  Test log:"<< endl;
        cerr << log_.str() << endl;
        ++failures;
    }

    bool samePatch(const string& as) {
        patcher_.flush();
        return as == pout_.str();
    }

    ostream& log() {
        return log_;
    }

protected:
    string filename_;
    ostringstream pout_;
    ostringstream log_;
    Patcher patcher_;
    PigletParser parser_;
};


class AdjacentPatchSameLine : public PatcherTest {
public:
    AdjacentPatchSameLine()
        : PatcherTest("patchertest-adjpatchsameline.cc") {
    }
    ~AdjacentPatchSameLine() {
    }

    void run() {
        try {
            TranslationUnit *ast = parser_.getAST(filename_.c_str());
            ast->traverse(*this);
        }  catch (xBase &x) {
            fail(x.why().c_str());
        }

        char const *const patch =
"--- patchertest-adjpatchsameline.cc\n"
"+++ patchertest-adjpatchsameline.cc\n"
"@@ -2,1 +2,1 @@\n"
"-int*x;\n"
"+char*y;\n"
        ;

        if (!samePatch(patch))
            fail("patches were different");
        else
            pass();
    }

    virtual bool
    visitS_decl(S_decl* s)
    {
        Declaration* d = s->decl;
        TypeSpecifier *t = d->spec;
        Declarator* decl = (Declarator*) d->decllist;
        D_pointer* firstQual = (D_pointer*) decl->decl;
        D_name* var = (D_name*) firstQual->getBaseC();

        UnboxedLoc startloc;
        const char *filename = startloc.set(firstQual->loc);
        UnboxedLoc endloc;
        endloc.set(var->name->loc);
        endloc.col += 1;        // "y".length
        UnboxedPairLoc range(filename, startloc, endloc);

        log() <<"  patching " << range << endl;
        patcher_.printPatch ("*y", range);

        startloc.set(t->loc);   // same filename
        endloc.set(t->loc);
        endloc.col += 3;        // "int".length
        UnboxedPairLoc range2(filename, startloc, endloc);

        log() <<"  patching "<< range2 << endl;
        // Patcher shouldn't throw an exception here
        patcher_.printPatch("char", range2);

        return false;
    }

};


int 
main(int argc, char** argv)
{
    { AdjacentPatchSameLine t; t.run(); }
    return failures;
}
