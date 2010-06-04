# ***** BEGIN LICENSE BLOCK *****
# Version: MPL 1.1/GPL 2.0/LGPL 2.1
#
# The contents of this file are subject to the Mozilla Public License Version
# 1.1 (the "License"); you may not use this file except in compliance with
# the License. You may obtain a copy of the License at
# http://www.mozilla.org/MPL/
#
# Software distributed under the License is distributed on an "AS IS" basis,
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
# for the specific language governing rights and limitations under the
# License.
#
# The Original Code is mozilla.org code.
#
# Contributor(s):
#   Chris Jones <jones.chris.g@gmail.com>
#
# Alternatively, the contents of this file may be used under the terms of
# either of the GNU General Public License Version 2 or later (the "GPL"),
# or the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
# in which case the provisions of the GPL or the LGPL are applicable instead
# of those above. If you wish to allow use of your version of this file only
# under the terms of either the GPL or the LGPL, and not to allow others to
# use your version of this file under the terms of the MPL, indicate your
# decision by deleting the provisions above and replace them with the notice
# and other provisions required by the GPL or the LGPL. If you do not delete
# the provisions above, a recipient may use your version of this file under
# the terms of any one of the MPL, the GPL or the LGPL.
#
# ***** END LICENSE BLOCK *****

import os, sys

from porky.ast import *


def _getcallerpath():
    '''Return the absolute path of the file containing the code that
**CALLED** this function.'''
    return sys._getframe(1).f_code.co_filename

# we want PLY to generate its output in the module directory, not wherever
# the user chooses to run porkyc from
_thisdir, _ = os.path.split(_getcallerpath())

# XXX TESTING
def NYI(what=None):
    what = what or sys._getframe(1).f_code.co_name
    raise NotImplementedError, what

reserved = {
    'call' : 'CALL',
    'class' : 'CLASS',
    'classmethod' : 'CLASSMETHOD',
    'delete' : 'DELETE',
    'function' : 'FUNCTION',
    'global' : 'GLOBAL',
    'member' : 'MEMBER',
    'method' : 'METHOD',
    'new' : 'NEW',
    'rewrite' : 'REWRITE',
    'type' : 'TYPE',
}
tokens = [
    'COLONCOLON', 'EQARROW', 'DASHARROW',
    'COMMA', 'DOT', 'STAR', 'AMPERSAND', 'NL',
    'LBRACKET', 'RBRACKET', 'LBRACE', 'RBRACE', 'LPAREN', 'RPAREN', 
    'ID'
] + list(reserved.values())

t_COLONCOLON = r'\:\:'
t_EQARROW = r'\=>'
t_DASHARROW = r'\->'
t_COMMA = r'\,'
t_DOT = r'\.'
t_STAR = r'\*'
t_AMPERSAND = r'\&'
t_LBRACKET = r'\['
t_RBRACKET = r'\]'
t_LBRACE = r'\{'
t_RBRACE = r'\}'
t_LPAREN = r'\('
t_RPAREN = r'\)'
t_NL = r'(?:\r\n|\r|\n)'

t_ignore = ' \f\t\v'

def t_ID(t):
    r'[a-zA-Z_][a-zA-Z0-9_]*'
    t.type = reserved.get(t.value, 'ID')
    return t

def t_error(t):
    raise Exception, 'bad character '+ str(t)

import ply.lex as lex
lex.lex(debug=0,
        optimize=1,
        lextab="porky_lextab",
        outputdir=_thisdir)

##-----------------------------------------------------------------------------

def p_RewriteSpec(p):
    '''RewriteSpec : REWRITE MaybeNewlines ID MaybeNewlines LBRACE MaybeNewlines RewriteList RBRACE MaybeNewlines'''
    p[0] = Rewriter.create(p[3], p[7])

def p_RewriteList(p):
    '''RewriteList : RewriteList OneRewrite
                   | OneRewrite'''
    if 2 == len(p):
        p[0] = [ p[1] ]
    else:
        p[1].append(p[2])
        p[0] = p[1]
def p_OneRewrite(p):
    '''OneRewrite : ClassRewrite Newlines
                  | FunctionRewrite Newlines
                  | CallRewrite Newlines
                  | TypeRewrite Newlines
                  | GlobalVarRewrite Newlines'''
    p[0] = p[1]

def p_ClassRewrite(p):
    '''ClassRewrite : CLASS ID EQARROW ID
                    | CLASS ID ClassBodyRewrite
                    | CLASS ID EQARROW ID ClassBodyRewrite'''
    NYI()

def p_ClassBodyRewrite(p):
    '''ClassBodyRewrite : LBRACE ClassBodyRewriteList RBRACE'''
    NYI()

def p_ClassBodyRewriteList(p):
    '''ClassBodyRewriteList : ClassBodyRewriteList OneClassBodyRewrite Newlines
                            | OneClassBodyRewrite Newlines'''
    NYI()
def p_OneClassBodyRewrite(p):
    '''OneClassBodyRewrite : METHOD ID EQARROW ID
                           | METHOD ID Callargs EQARROW ExprCall
                           | CLASSMETHOD ID EQARROW ID
                           | CLASSMETHOD ID Callargs EQARROW ExprCall
                           | MEMBER ID EQARROW ID'''
    NYI()

def p_FunctionRewrite(p):
    '''FunctionRewrite : FUNCTION QualifiedId EQARROW QualifiedId'''
    NYI()

def p_CallRewrite(p):
    '''CallRewrite : CALL QualifiedId EQARROW QualifiedId
                   | CALL ExprFunCall EQARROW ExprCall'''
    p[0] = CallRewrite.create(p[2], p[4])

def p_ExprCall(p):
    '''ExprCall : ExprFunCall
                | ExprMethodCall
                | ExprNew
                | ExprDelete'''
    p[0] = p[1]

def p_ExprFunCall(p):
    '''ExprFunCall : QualifiedId Callargs'''
    p[0] = CxxExprCall(p[1], p[2])

def p_ExprMethodCall(p):
    '''ExprMethodCall : ExprSelect Callargs'''
    p[0] = CxxExprCall(p[1], p[2], ismethodcall=True)

# TODO ExprNew and ExprDelete assume that they are only used as 'tocall's,
# and not as patterns.  this a rather hacky way of doing things
def p_ExprNew(p):
    '''ExprNew : NEW QualifiedId Callargs'''
    p[0] = CxxExprCall(p[2], p[3], isnew=True);

def p_ExprDelete(p):
    '''ExprDelete : DELETE ExprAtom'''
    p[0] = CxxExprCall(None, [ p[2] ], isdelete=True);

def p_Callargs(p): 
    '''Callargs : LPAREN RPAREN
                | LPAREN ExprList RPAREN
                '''
    if 3 == len(p):
        p[0] = []
    else:
        p[0] = p[2]

# TODO recursive select             
def p_ExprSelect(p):
    '''ExprSelect : ID Selector ID'''
    p[0] = CxxExprSelect(p[1], p[2], p[3])

def p_Selector(p):
    '''Selector : DOT 
                | DASHARROW'''
    if '.' == p[1]:
        p[0] = CxxExprSelect.DOT
    else:
        p[0] = CxxExprSelect.PDOT

def p_TypeRewrite(p):
    '''TypeRewrite : TYPE Type EQARROW Type'''
    p[0] = TypeRewrite(p[2], p[4])

def p_GlobalVarRewrite(p):
    '''GlobalVarRewrite : GLOBAL QualifiedId EQARROW QualifiedId'''
    NYI()

def p_Type(p):
    '''Type : QualifiedId
            | Type STAR
            | Type AMPERSAND
            | Type LBRACKET RBRACKET'''
    # TODO fix ^^^; can't have T&&, e.g.
    # TODO support templates; maybe with wildcard instantiations <*, *>
    if 2 == len(p):
        p[0] = CxxType(p[1])
    elif 3 == len(p):
        if '*' is p[2]:
            p[1].pointer()
        elif '&' is p[2]:
            p[1].reference()
        p[0] = p[1]
    else:
        # TODO handling these in source translation is unnecessarily tricky.
        # thanks, Kernighan and Ritchie.
        NYI('array types')

def p_ExprList(p):
    '''ExprList : ExprList COMMA ExprAtom
                | ExprAtom'''
    if 2 == len(p):
        p[0] = [ p[1] ]
    else:
        p[1].append(p[3])
        p[0] = p[1]

# TODO hack alert: should support more destructuring than just |*foo|
def p_ExprAtom(p):
    '''ExprAtom : ID
                | STAR ID'''
    if 2 == len(p):
        p[0] = CxxExprAtom(p[1])
    else:
        p[0] = CxxExprAtom(p[2], True)

def p_QualifiedId(p):
    '''QualifiedId : ID
                   | COLONCOLON ID
                   | QualifiedId COLONCOLON ID'''
    # TODO support templates
    if 2 == len(p):
        p[0] = CxxQualifiedId(p[1])
    elif 3 == len(p):
        # TODO is this correct? '::Foo' means "Foo in global namespace"?
        p[0] = CxxQualifiedId(p[2])
    else:
        p[1].qualify(p[3])
        p[0] = p[1]

def p_MaybeNewlines(p):
    '''MaybeNewlines : Newlines
                     | '''      # empty
    return

def p_Newlines(p):
    '''Newlines : Newlines NL
                | NL'''
    return

def p_error(t):
    raise Exception, 'syntax error near "%s"'% (t.value)

import ply.yacc as yacc
yacc.yacc(debug=0,
          optimize=1,
          tabmodule="porky_yacctab",
          outputdir=_thisdir)
