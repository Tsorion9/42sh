#!/usr/bin/env python3

import os
import glob
import subprocess
from termcolor import colored
import signal
import sys
import psutil

import argparse

parser = argparse.ArgumentParser()

parser.add_argument('-s', action='store', dest='start', type = int,
                    help='Start test number', default = 0)
parser.add_argument('-e', action='store', dest='end', type=int,
                    help='Start test number', default = 1000000)

parser.add_argument('-v', '--verbose', action='store_true', help="verbose")

args = parser.parse_args()
print(colored("Running tests for cases {}:{}".format(args.start, args.end), "cyan"))

verbose = 0
if (args.verbose):
	verbose = 1;

os.system("rm -f cases/user_out_* cases/test_out*")

our_shell = "../../21sh"
bash = "/bin/bash"
path_to_cases = "cases"
valgrind_trace = "last_valgrind_output"

offs = 30 #Offset for string succcess or failure
my_timeout = 1# seconds for single test
return_segfault_code = 139

os.system("touch {}".format(valgrind_trace))


def wait_for_children():
	procs = psutil.Process(pid = os.getpid()).children(recursive = True)
	if (len(procs) == 0):
		return
	for c in procs:
		try:
			os.waitpid(c.pid, 0)
		except ChildProcessError:
			pass


def	line_count(name):
	count = 0
	with open(name, 'r') as f:
		for line in f:
			count += 1
	return count

def is_err_ok(test_err, user_err):
	err_lines_test = line_count(test_err)
	err_lines_user = line_count(user_err)
	if (err_lines_user == 0 and err_lines_test == 0):
		return (1)
	if (err_lines_user != 0 and err_lines_test != 0):
		return (1)
	return 0;

def failure_or_success(diff, timeout, segfault):
	if (segfault == 1):
		return ("Segfault")
	if (timeout == 1):
		return ("Timeout")
	if (len(diff) > 0):
		return ("Failure")
	return ("Success")

def n_spaces(case_name, offset):
	"""
		Return a string of spaces of offset - len(case_name)
	"""
	return (" " * (offset - len(case_name))) ;

def	valgrind_sumary(n_valgrind_errors, n_leaks):
	if (n_valgrind_errors == 0 and n_leaks == 0):
		return (colored("  VALGRIND_OK ", "green"))
	return (colored("  VALGRIND_KO ", "red"))

def get_color(diff, timeout, segfault, err_ok):
	if (timeout == 0 and len(diff) == 0 and segfault == 0 and err_ok == 1):
		return ("green")
	return ("red")

def stderr_string_message(err_ok):
	if (err_ok == 1):
		return (colored("  STDERR_OK", "green"))
	return (colored("  STDERR_KO", "red"))

def	check_valgrind(file, our_shell, valgrind_trace):
	n_valgrind_errors = 0
	shell_cmd = "exec 2>>{} cat {} | valgrind {} 2>&1 | grep 'ERROR\|definitely' | grep ': [1-9]' | wc -l > {}".format(valgrind_trace, file, our_shell, valgrind_trace)
	process = subprocess.Popen(shell_cmd, shell=True, executable="/bin/bash")
	wait_for_children()
	trace = open(valgrind_trace, "r")
	try:
		n_valgrind_errors = int(trace.read())
	except ValueError:
		pass;
	trace.close()
	return (n_valgrind_errors)

def ignore(signalNumber, frame):
	return

signal.signal(signal.SIGTERM, ignore)
print(colored("Running tests! Path to executable: {}".format(colored(our_shell, "cyan")), "magenta"))
print(colored("Searching for testcases inside: {}".format(colored(path_to_cases + "/in_*.txt", "cyan")), "magenta"))
print("")

count_tests = 0
good = 0
bad = 0

files = glob.glob(path_to_cases + "/in_*.txt")
for file in sorted(files): 
	os.system("echo 0 >{}".format(valgrind_trace))
	count_tests += 1
	if (count_tests < args.start or count_tests > args.end):
		continue ;

	case_name = file[9:-4]
	user_out = path_to_cases + "/user_out_" + case_name + ".txt"
	test_out = path_to_cases + "/test_out_" + case_name + ".txt"

	user_err = path_to_cases + "/user_err_" + case_name + ".txt" # Write stderror of program to the separate file
	test_err = path_to_cases + "/test_err_" + case_name + ".txt" 
	# We are interested only in number of lines in these files (both zero or both nonzero -> OK)

	shell_cmd = " exec 2>>{} && cat {} | {} > {} 2>{}".format(user_err, file,  our_shell, user_out, user_err) 
	shell_cmd += '\nif [[ $? -eq 139 ]]; then exit 139; fi'
	timeout = 0
	segfault = 0

	process = subprocess.Popen(shell_cmd, shell=True, executable="/bin/bash")
	try:
		process.wait(timeout=my_timeout)
	except subprocess.TimeoutExpired:
		timeout = 1
		os.killpg(os.getpgid(process.pid), signal.SIGTERM)

	process.communicate()
	if (process.returncode == 139): #segfault
		segfault = 1
	else:
		segfault = 0

	n_leaks = 0
	n_valgrind_errors = 0
	if (segfault == 0 and timeout == 0):
		n_valgrind_errors = check_valgrind(file, our_shell, valgrind_trace)

	shell_cmd = " exec 2>>{} && cat {} | {} > {} 2>{}".format(test_err, file,  bash, test_out, test_err) 
	os.system(shell_cmd)
	try:
		diff_cmd = "diff {} {}".format(user_out, test_out)
		diff = subprocess.check_output(diff_cmd, shell=True, executable="/bin/bash")
	except subprocess.CalledProcessError:
		diff = "diff: error occured"
	
	err_ok = is_err_ok(test_err, user_err)
	print(colored("{}{}{}{}{}{}{}".format(
										count_tests, 
										n_spaces(str(count_tests), 4), 
										case_name, 
										n_spaces(case_name, offs),
										failure_or_success(diff, timeout, segfault),
										valgrind_sumary(n_valgrind_errors, n_leaks),
										stderr_string_message(err_ok)
									  ), 
				  get_color(diff, timeout, segfault, err_ok)))

	if (timeout == 0 and len(diff) == 0 and segfault == 0 and n_valgrind_errors == 0 and n_leaks == 0 and err_ok == 1):
		good += 1
	else:
		bad += 1

	wait_for_children()
	if (verbose == 1):
		print("*" * 80)
		print("Input:")
		os.system("cat {}".format(file))
		print("*" * 80)
		print("Expected:")
		os.system("cat {}".format(test_out))
		print("*" * 80)
		print("Got:")
		os.system("cat {}".format(user_out))
		print("*" * 80)
		print("Expected error stream:")
		os.system("cat {}".format(test_err))
		print("*" * 80)
		print("Got error stream:")
		os.system("cat {}".format(user_err))
		print("*" * 80)
		print("Valgrind output:")
		
		shell_cmd_leaks = "cat {} | valgrind {} 2>&1".format(file, our_shell)
		process = subprocess.Popen(shell_cmd_leaks, shell=True, executable="/bin/bash")
		print("*" * 80)

def	green_or_red(n_valgrind_errors):
	if (n_valgrind_errors > 0):
		return ("red")
	return ("green")
print("")

wait_for_children()
print(colored("Summary: {} out of {} tests passed!".format(good, good + bad), "magenta"))
print(colored("See traces at {}/user_out_[CASE_NAME].txt and {}/test_out[CASE_NAME].txt".format(path_to_cases, path_to_cases), "green"))

os.system("rm -rf test 1 2 12 trace.txt last_valgrind_output")

wait_for_children()
#os.killpg(os.getpgid(os.getpid()), signal.SIGILL)
if (args.start == 0 and args.end == 1000000 and verbose == 0):
	print("Nocrash!")
	files = glob.glob(path_to_cases + "/nocrash*.txt")
	for file in sorted(files): 
		os.system("echo 0 >{}".format(valgrind_trace))
		n_valgrind_errors = check_valgrind(file, our_shell, valgrind_trace)
		print(colored("{} {}".format(file, "valgrind"), green_or_red(n_valgrind_errors)))

