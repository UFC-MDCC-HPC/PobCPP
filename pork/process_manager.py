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
#   David Mandelin <dmandelin@mozilla.com>
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

# Multiprocess a set of commands, and combine their output into a single file.
#
# Python version of pork-barrel, with some differences:
#   Collects output into one file with delimiters
#   Doesn't assume output is from patches
#   Uses format strings to control command line creation
#   Not as much timing info
#
# It is also intended that this can be extended in other ways by users,
# such as customizing the way output is assembled.  This can be done
# by importing it from another python file and passing a file-like object
# in |process_manager.run(..., outfile, ...)|.  See pork_barrel.py for
# an example that uses this to manage patches.

from __future__ import division

import os, signal, sys, time
from threading import Thread, Lock
from popen2 import Popen4
from Queue import Queue, Empty

tasks = Queue()
output_lock = Lock()

class Worker(object):
  die = False                   # racy access, but makes little difference

  def __init__(self, command, outfile, logfile, verbosity):
    self.thread = None
    self.command = command
    self.outfile = outfile
    self.logfile = logfile
    self.verbosity = verbosity

  def start(self):
    self.thread = Thread(target=self.run)
    self.thread.start()

  def log(self, vbsty, fmt, *args):
    if self.verbosity >= vbsty:
      print >>self.logfile, fmt % args

  def run(self):
    try:
      while not self.die:
        filename = tasks.get(False)
        self.log(1, '%s tasks left', tasks.qsize())
        self.do_task(filename)
        # only in Python 2.5
        #tasks.task_done()
    except KeyboardInterrupt:
      self.log(2, '(Interrupted, attempting fratricide)')
      self.die = True         # try to catch other threads, if we get 
                              # the signal
    except Empty:
      pass
      
    if self.die:
      self.log(2, '(Worker exited abnormally)')

  def do_task(self, filename):
    cmd = self.command % { 'file': filename }

    self.log(2, '>>> %s', cmd)
    pipe = Popen4(cmd)
    pipe.tochild.close()
    output = pipe.fromchild.read()
    pipe.fromchild.close()
    rc = pipe.wait()
    self.log(2, '<<< %s', cmd)
    
    output_lock.acquire()
    self.log(1, '# %s', cmd)
    if os.WIFEXITED(rc):
      ec = os.WEXITSTATUS(rc)
      if ec == 0:
        self.log(2, '#     PORKBAR_OK: rc=0')
      else:
        self.log(0, '#     PORKBAR_FAIL_EXIT: rc=%d, cmd=%s', ec, cmd)
    elif os.WIFSIGNALED(rc):
      sig = os.WTERMSIG(rc)
      self.log(0, '#     PORKBAR_FAIL_SIGNALED_%s, cmd=%s', sig, cmd)
      if sig in (signal.SIGINT, signal.SIGTERM):
        self.log(2, '(Subprocess interrupted, attempting fratricide)')
        self.die = True
    else:
      assert os.WIFSTOPPED(rc)
      self.log(0, '#     PORKBAR_FAIL_STOPPED, cmd=%s', cmd)
      self.log(1, "WARNING: you need to continue or kill this process")

    self.outfile.write(output)
    output_lock.release()
    
def run(filenames, command, outfile=sys.stdout, worker_count=2, logfile=sys.stderr, verbosity=1):
  task_count = 0
  for filename in sorted(filenames):
    tasks.put_nowait(filename)
    task_count += 1

  t0 = time.clock()

  workers = [ Worker(command, outfile, logfile, verbosity) for _ in range(worker_count) ]

  for w in workers:
    w.start()
  for w in workers:
    try:
      w.thread.join()
    except KeyboardInterrupt:
      print >>logfile, '(Interrupted, killing workers)'
      Worker.die = True

  t1 = time.clock()
  dt = t1-t0
  # This time isn't very useful on Unix for this program
  #print "time taken = %.3f (%.3f/task)"%(dt, dt/task_count)

if __name__ == '__main__':
  if len(sys.argv) != 4:
    print 'usage: python process_manager.py <cpu-count> <filename-file> <cmd>'
    print '    by default filename is appended to <cmd>, can also use "%(file)s" in cmd'
    sys.exit(1)

  _, cpu_count, listfile, command = sys.argv
  worker_count = int(cpu_count)
  filenames = [ filename.strip('\r\n') for filename in open(listfile) ]
  if command.find('%(file)') == -1: command += ' %(file)s'
  run(filenames, command, sys.stdout, worker_count)
