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
#   Taras Glek <tglek@mozilla.com>
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

# Launch a series of pork/piglet rewrites and post-process the generated
# patches.
#
# Python version of pork-barrel.cc.
#
# XXX this implementationo makes several assumptions about patches being
# XXX valid; it assumes that piglet's |patcher| is feeding it chunks

import fnmatch, process_manager, re, sys

class ChunkRange:
  def __init__(self, fromline, fromnlines, toline, tonlines):
    self.fromline = fromline
    self.fromnlines = fromnlines
    self.toline = toline
    self.tonlines = tonlines

  def disjoint(self, ro):
    selffromstart = self.fromline
    selffromend = selffromstart + self.fromnlines
    selftostart = self.toline
    selftoend = selftostart + self.tonlines

    rofromstart = ro.fromline
    rofromend = rofromstart + ro.fromnlines
    rotostart = ro.toline
    rotoend = rotostart + ro.tonlines

    if (rofromend >= selffromstart # self|ro
        or rotoend >= selffromstart):
      return True
    elif (selffromend >= rofromstart # ro|self
          or selftoend >= rofromstart):
      return True
    else:
      return False

  def __eq__(self, ro):
    return (self.fromline == ro.fromline and self.fromnlines == ro.fromnlines
            and self.toline == ro.toline and self.tonlines == ro.tonlines)
  def __hash__(self):
    return hash(str(self))
  def __lt__(self, ro):
    # XXX assumes that self and ro don't overlap!!
    return self.fromline < ro.fromline
  def __repr__(self):
    return '@@ -%r,%r +%r,%r @@'% (self.fromline, self.fromnlines,
                                   self.toline, self.tonlines)


class Chunk:
  '''|Chunk|s represent the stuff following "@@ -R, +R @@" in a patch.
|Chunk|s are not associated with files.'''
  def __init__(self, range, text):
    # XXX assumes that the text agrees with the range
    self.range = range
    self.text = text

  def conflictsWith(self, oc):
    # TODO doesn't handle non-conflicting overlaps, e.g.:
    #
    # chunk 1:
    #  @@ -1,1 +1,1 @@
    #  -Bar
    #  +Foo
    # chunk 2:
    #  @@ -1,2 +1,2 @@
    #  -Bar
    #  -Baz
    #  +Foo
    #  +Foo
    #
    # We assume that patcher won't produce them.
    return not (self == oc or self.range.disjoint(oc.range))

  def __eq__(self, oc):
    return self.range == oc.range and self.text == oc.text
  def __hash__(self):
    return hash(self.range) ^ hash(self.text)
  def __lt__(self, oc):
    # XXX assumes that self and oc don't conflict!!
    return self.range < oc.range
  def __repr__(self):
    return '%s\n%s'% (self.range, self.text)


class Patch(object):
  def __init__(self, excludefiles=None, includefiles=None):
    '''If |excludefiles| is not none, no files matching a pattern
in |excludefiles| appear in the patch.
If |includefiles| is not None, only files matching some pattern
in |includefiles| appear in the patch.'''
    self.excludefiles = excludefiles
    self.includefiles = includefiles
    self.filechunks = { }       # : filename -> [ Chunk ]
  
  def addChunk(self, filename, chunk):
    '''Return the pair |wasAdded, badChunk|.
If the chunk was added successfully, return |True, None|.
If the chunk was not added due to a conflict, return |False, conflictingChunk|.
Otherwise, return |False, stringMessage|.'''
    if not self.included(filename) or self.excluded(filename):
      return False, 'excluded'

    chunks = self.filechunks.get(filename, set())
    if chunk in chunks:
      return False, 'dup'
    else:
      for c in chunks:
        if chunk.conflictsWith(c):
          return False, c

    chunks.add(chunk)
    self.filechunks[filename] = chunks

    return True, None

  def included(self, filename):
    if self.includefiles is None: return True
    return any([ fnmatch.fnmatch(filename, pat) for pat in self.includefiles ])

  def excluded(self, filename):
    if self.excludefiles is None: return False
    return any([ fnmatch.fnmatch(filename, pat) for pat in self.excludefiles ])

  def dump(self, out=sys.stdout):
    for filename in sorted(self.filechunks.keys()):
      print >>out, '---', filename
      print >>out, '+++', filename
      for chunk in sorted(self.filechunks[filename]):
        out.write(str(chunk))


class ChunkConflictError(Exception):
  def __init__(self, filename, chunk1, chunk2):
    self.filename = filename
    self.chunk1 = chunk1
    self.chunk2 = chunk2

  def __str__(self):
    return 'in file "%s", chunk\n\n%s\n\nconflicts with\n\n%s'% (
      self.filename, self.chunk1, self.chunk2)

class PatchPseudoFile(object):
  '''This file-like class intercepts writes of patch data, parses it, and
passes it to the underlying |Patch| for processing.'''

  chunkRangeRx = re.compile('^@@ \-(\d+),(\d+) \+(\d+),(\d+) @@$')

  def __init__(self, patch, logfile=sys.stdout, verbosity=0):
    self.patch = patch
    self.logfile = logfile
    self.verbosity = verbosity
    self.closed = False
    self.buf = ''
    self.file1 = None
    self.file2 = None
    self.chunkrange = None
    self.chunkbuf = ''

  def log (self, minvbsty, fmt, *args):
    if self.verbosity >= minvbsty:
      print >>self.logfile, fmt % args

  def processChunk(self):
    assert self.file1 == self.file2 # filename changes NYI
    chunk = Chunk(self.chunkrange, self.chunkbuf)
    self.log(2, '  (trying to add chunk %s)', chunk)
    added, whynot = self.patch.addChunk(self.file1, chunk)
    if not added and isinstance(whynot, Chunk):
      raise ChunkConflictError(whynot, chunk)
    elif not added:
      self.log(2, '%s, so not adding %s:%s', 
               whynot, self.file1, self.chunkrange)

  def close(self):
    assert not self.closed

    if (self.file1 is not None and self.file2 is not None
        and self.chunkrange is not None
        and len(self.chunkbuf) > 0):
      self.processChunk()
    elif (self.file1 is not None and self.file2 is not None
          and self.chunkrange is not None
          and len(self.chunkbuf) == ''):
      raise IOError, 'read file and chunk headers, but no chunk text'
    elif (self.file1 is not None and self.file2 is not None
          and self.chunkrange is None):
      raise IOError, 'read file headers, but no chunk header'
    elif (self.file1 is not None and self.file2 is None):
      raise IOError, 'read "--- " file header, but not "+++ " header'

    self.closed = True


  def flush(self):
    assert not self.closed
    lines = self.buf.split('\n')
    if lines[-1] != '':
      self.buf = lines[-1]
    else:
      self.buf = ''
    
    for line in lines[0:-1]:
      if self.file1 is None:
        if not line.startswith('--- '):
          self.log(3, '  (START: eating "%s")', line)
          continue
        self.file1 = line[4:]
        self.log(3, '  (START: got line1 %s)', self.file1)

      elif self.file2 is None:
        if not line.startswith('+++ '):
          self.log(3, '  (FILE2: eating "%s")', line)
          continue
        self.file2 = line[4:]
        self.log(3, '  (FILE2: got %s)', self.file2)
      
      elif self.chunkrange is None:
        m = self.chunkRangeRx.match(line)
        if not m:
          self.log(3, '  (CHUNKRANGE: eating "%s")', line)
          continue
        self.chunkrange = ChunkRange(*[ int(n) for n in m.groups() ])
        self.log(3, '  (CHUNKRANGE: got %s)', self.chunkrange)

      else:
        if '' == line:
          self.log(3, '  (CHUNK: eating "%s")', line)
          continue
        elif line.startswith('--- '):
          # found changes to another file
          self.processChunk()
          self.file1 = line[4:]
          self.file2 = None
          self.chunkrange = None
          self.chunkbuf = ''
          self.log(3, '  (CHUNK: new file1 %s)', self.file1)
        elif line[0] in ('+', '-', ' '):
          self.chunkbuf += line + '\n'
          self.log(3, '  (CHUNK: added line "%s")', line)
        else:
          m = self.chunkRangeRx.match(line)
          if not m:
            self.log(3, '  (CHUNK: eating "%s")', line)
            continue
          # found another chunk for same file
          self.processChunk()
          self.chunkrange = ChunkRange(*[ int(n) for n in m.groups() ])
          self.chunkbuf = ''
          self.log(3, '  (CHUNK: new range %s)', self.chunkrange)

  
  def write(self, str):
    assert not self.closed
    # XXX if serializing writes is a bottleneck, could spawn another thread
    # XXX to do patch processing
    self.buf += str
    if -1 != str.find('\n'):
      self.flush()

  # not implementing reading/seeking methods.  trying to use them will
  # raise an exception.


def run(filenames,
        command,
        patchexcludepats=None,
        patchincludepats=None,
        patchoutfile=sys.stdout,
        worker_count=2,
        logfile=sys.stderr,
        verbosity=1):
  pf = PatchPseudoFile(Patch(patchexcludepats, patchincludepats),
                       logfile, verbosity)
  # Nb: we rely on |process_manager| to synchronize writes to |pf|
  process_manager.run(filenames, command, pf, worker_count, logfile, verbosity)
  pf.close()
  pf.patch.dump(patchoutfile)

##-----------------------------------------------------------------------------
## Main
##
import getopt, os

def getncpus():
  if sys.platform.startswith('linux'):
    return len(re.findall('processor\s+\:', open('/proc/cpuinfo').read()))
  elif sys.platform in ('win32', 'cygwin'):
    # XXX teh internets says this; i dunno either way, esp. for cygwin
    return os.getenv('NUMBER_OF_PROCESSORS', 1)
  else:
    # TODO, maybe only for OS X
    return 1

def usage(err):
    if err:
        out, rv = (sys.stderr, 1)
    else:
        out, rv = (sys.stdout, 0)
    print >>out, '''
Usage:  python %s [OPTIONS...] PROGRAM [FILES_TO_REWRITE...]

where OPTIONS are zero or more of
  -j N, --jobs=N
          : use N-way parallelism while rewriting.
            default: -j [best guess at this machine's number of CPU cores]
  -h, --help
          : print this message and exit
  -o PATH, --output=PATH
          : where to save the generated patch.  `-' means stdout.
            default: stdout
  -v N    : be as verbose as N.  set to 0 for no output, and higher for more.
            default: -v 0


COMMAND  [required]
  The first non-option argument is the command to invoke on FILES_TO_REWRITE.
  You can use the pattern `%%(file)s' in the command to reference the file on
  which COMMAND is being invoked.
  Example:  'MyRewriteProgram %%(file)s'

FILES_TO_REWRITE
  If not FILE_TO_REWRITE is specified, the files to rewrite will be read
  from stdin.

  SHELL_PATTERN
          : e.g., `foo/bar.cc', `~/code/*', '$HOME/code'
              CAREFUL: these are expanded relative to the current directory.
              It's best to specify an absolute pattern.
  -x SHELL_PATTERN, --exclude=SHELL_PATTERN
          : don't attempt to rewrite any programs matching `SHELL_PATTERN'
'''% (sys.argv[0])


if __name__ == '__main__':
  try:
    opts, args = getopt.gnu_getopt(
      sys.argv[1:],
      'j:ho:v:x:',
      ['jobs=',
       'help',
       'output=',
       'exclude='])
  except getopt.GetoptError, err:
    print >>sys.stderr, str(err), '\n'
    usage(err=True)

  if 0 == len(args):
    print >>sys.stderr, 'you need to specify a rewrite program\n'
    usage(err=True)

  command = args[0]
  filepats = args[1:]
  exfilepats = [ ]
  ncpus = getncpus()
  patchout = '-'
  verbosity = 1

  for o, a in opts:
    if o in ('-j', '--jobs'):
      ncpus = int(a)
    elif o in ('-x', '--exclude'):
      exfilepats.append(a)
    elif o in ('-o', '--output'):
      patchout = a
    elif o in ('-v', '--verbosity'):
      verbosity = int(a)
    elif o in ('-x', '--exclude'):
      exfilepats.append(a)

  # build list of files to process
  if 0 == len(filepats):
    filepats = sys.stdin.read().split('\n')

  if 0 == len(filepats):
    print >>sys.stderr, 'need some files to rewrite'
    usage(err=True)

  def normalizepath(p):
    return os.path.abspath(
      os.path.expandvars(
        os.path.expanduser(os.path.normpath(p))))

  files = set()
  for fpat in [ normalizepath(f) for f in filepats ]:
    dir = os.path.dirname(fpat)
    def addfiles(a, d, names):
      for name in names:
        fullpath = os.path.join(d, name)
        if fnmatch.fnmatch(fullpath, fpat):
          files.add(fullpath)
    os.path.walk(dir, addfiles, None)

  if 0 == len(files):
    print >>sys.stderr, 'no files matched the provided pattern(s)'
    usage(err=True)

  # figure out where to write patch
  if '-' == patchout:
    patchout = sys.stdout
  else:
    patchout = open(patchout, 'w')

  # kick of process_manager
  run(filenames=files,
      command=command,
      patchexcludepats=exfilepats,
      patchincludepats=None,
      patchoutfile=patchout,
      worker_count=ncpus,
      logfile=sys.stderr,
      verbosity=verbosity)
