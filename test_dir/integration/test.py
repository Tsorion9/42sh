#!/usr/bin/env python3

import os
import glob
import subprocess
from termcolor import colored
import signal

os.system("rm -f cases/user_out_* cases/test_out*")

our_shell = "../../21sh"
bash = "/bin/bash"
path_to_cases = "cases"
valgrind_trace = "last_valgrind_output"

offs = 30 #Offset for string succcess or failure
my_timeout = 1# seconds for single test
return_segfault_code = 139

os.system("touch {}".format(valgrind_trace))

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
		return  "  VALGRIND OK"
	return (colored(" VALGRIND_WARNINGS", "red"))

def get_color(diff, timeout, segfault):
	if (timeout == 0 and len(diff) == 0 and segfault == 0):
		return ("green")
	return ("red")

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
	count_tests += 1

	case_name = file[9:-4]
	user_out = path_to_cases + "/user_out_" + case_name + ".txt"
	test_out = path_to_cases + "/test_out_" + case_name + ".txt"

	shell_cmd = " exec 2>>{} && cat {} | {} > {} 2>{}".format(user_out, file,  our_shell, user_out, user_out) 
	shell_cmd += '\nif [[ $? -eq 139 ]]; then exit 139; fi'
	timeout = 0

	#print("Shell command: {}".format(shell_cmd))

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
		shell_cmd = "cat {} | valgrind {} 2>&1 | grep ERROR | cut -f4 -d ' ' > {}".format(file, our_shell, valgrind_trace)
		process = subprocess.Popen(shell_cmd, shell=True, executable="/bin/bash")
		trace = open(valgrind_trace, "r")
		try:
			n_valgrind_errors = int(trace.read())
		except ValueError:
			pass;
		trace.close()



		shell_cmd_leaks = "cat {} | valgrind {} 2>&1 | grep definitely | rev | cut -f5 -d ' ' | rev > {}".format(file, our_shell, valgrind_trace)
		process = subprocess.Popen(shell_cmd, shell=True, executable="/bin/bash")
		trace = open(valgrind_trace, "r")
		n_leaks = trace.read()
		trace.close()
		if (len(n_leaks) > 0):
			n_leaks = int(float(n_leaks[0]))
		

	shell_cmd = " exec 2>>{} && cat {} | {} > {} 2>{}".format(test_out, file,  bash, test_out, test_out) 
	os.system(shell_cmd)
	try:
		diff_cmd = "diff {} {}".format(user_out, test_out)
		diff = subprocess.check_output(diff_cmd, shell=True, executable="/bin/bash")
	except subprocess.CalledProcessError:
		diff = "diff: error occured"
	print(colored("{}{}{}{}{}{}".format(
										count_tests, 
										n_spaces(str(count_tests), 4), 
										case_name, 
										n_spaces(case_name, offs),
										failure_or_success(diff, timeout, segfault),
										valgrind_sumary(n_valgrind_errors, n_leaks)
									  ), 
				  get_color(diff, timeout, segfault)))

	if (timeout == 0 and len(diff) == 0 and segfault == 0 and n_valgrind_errors == 0 and n_leaks == 0):
		good += 1
	else:
		bad += 1

print("")

print(colored("Summary: {} out of {} tests passed!".format(good, good + bad), "magenta"))
print(colored("See traces at {}/user_out_[CASE_NAME].txt and {}/test_out[CASE_NAME].txt".format(path_to_cases, path_to_cases), "green"))

os.system("rm -rf test 1 2 12 trace.txt last_valgrind_output")
#os.killpg(os.getpgid(os.getpid()), signal.SIGILL)
