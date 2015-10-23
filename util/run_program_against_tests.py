""" Simple script that runs a given program against given test cases.

Sample usage that runs the given program against all '.in' files in the
current directory and expects the corresponding outputs to be '.out' files.
  $ python run_program_against_tests.py -r ./a 
  $ python run_program_against_tests.py -r 'java MyClass' 
"""

import filecmp
import os
import time

from argparse import ArgumentParser
from glob import glob
from subprocess import Popen
from tempfile import NamedTemporaryFile
from threading import Thread

INPUT_DIR = './'
INPUT_FILE_EXT = '.in'
OUTPUT_DIR = './'
OUTPUT_FILE_EXT = '.out'
PROGRAM = './a'

class Command(object):
  def __init__(self):
    self.cmd = None
    self.process = None

  def GetOutputFile(self, args, input_file):
    # Returns the filename of the output file for the given input file.
    basename = os.path.basename(input_file)[:-len(args.input_file_ext)]
    return args.output_dir + basename + args.output_file_ext 

  def AreFilesEqual(self, file1, file2):
    return filecmp.cmp(file1, file2, shallow=False)

  def CheckResult(self, thread, out, expected):
    """
    Checks the result of the program execution.
    Kills the thread if the time limit was exceeded.
    Returns the veredict of the outcome: 
      - Accepted, if the output is the same as expected
      - Wrong answer, if the output is different than the expected
      - Time Limit Exceeded, if the program didn't finish within the time limit
      - FAIL with code X, if the program return code is diferent than zero 
    """ 
    if thread.is_alive():
      self.process.terminate()
      thread.join()
      return 'Time Limit Exceeded'
    if self.process.returncode == 0:
      return 'Accepted' if self.AreFilesEqual(out, expected) else 'Wrong Answer'
    else:
      return 'FAIL with code %s' % self.process.returncode

  def Run(self, args, input_file):
    def Target():
      self.process = Popen(self.cmd, shell=True)
      self.process.communicate()

    out_file = NamedTemporaryFile() 
    self.cmd = '%s < %s > %s' % (args.run, input_file, out_file.name)
    
    start_time = time.time()
    thread = Thread(target=Target)
    thread.start()
    thread.join(args.timeout)
    elapsed_time = time.time() - start_time

    expected = self.GetOutputFile(args, input_file)
    result_msg = self.CheckResult(thread, out_file.name, expected)
    return (result_msg, elapsed_time)


def main():
  parser = ArgumentParser(description='Run a program against some test cases.')
  parser.add_argument('--input_dir', default=INPUT_DIR)
  parser.add_argument('--input_file_ext', default=INPUT_FILE_EXT)
  parser.add_argument('--output_dir', default=OUTPUT_DIR)
  parser.add_argument('--output_file_ext', default=OUTPUT_FILE_EXT)
  parser.add_argument('-r', '--run', default=PROGRAM)
  parser.add_argument('-t', '--timeout', type=int, default=1)
  args = parser.parse_args()

  command = Command()
  for input_file in glob(args.input_dir + '*' + args.input_file_ext):
    result, elapsed_time = command.Run(args, input_file)
    print 'Test %8s  Ran for %.3f secs  %s' % (input_file, elapsed_time, result)

if __name__ == "__main__":
  main()

