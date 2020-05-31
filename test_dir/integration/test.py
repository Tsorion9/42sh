#!/usr/bin/env python3.6

import os
import glob
import subprocess
from termcolor import colored

our_shell = "../../21sh"
path_to_cases = "cases"

def failure_or_success(diff, timeout):
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

def get_color(diff, timeout):
	if (timeout == 0 & len(diff) == 0):
		return ("green")
	return ("red")

offs = 30 #Offset for string succcess or failure
my_timeout = 1 #1 second for single test

print(colored("Running tests! Path to executable: {}".format(colored(our_shell, "cyan")), "magenta"))
print(colored("Searching for testcases inside: {}".format(colored(path_to_cases + "/in_*.txt", "cyan")), "magenta"))
print("")

count_tests = 0
good = 0
bad = 0
for file in glob.glob(path_to_cases + "/in_*.txt"): 
	count_tests += 1

	case_name = file[9:-4]
	user_out = path_to_cases + "/user_out_" + case_name + ".txt"
	test_out = path_to_cases + "/test_out_" + case_name + ".txt"

	shell_cmd ="cat {} | {} > {}".format(file, our_shell, user_out) 
	timeout = 0

	process = subprocess.Popen(shell_cmd, shell=True)
	try:
		process.wait(timeout=my_timeout)
	except subprocess.TimeoutExpired:
		timeout = 1
		process.kill()

	os.system("cat {} | bash > {}".format(file, test_out))
	try:
		diff = subprocess.check_output("diff {} {}".format(user_out, test_out), shell=True)
	except subprocess.CalledProcessError:
		diff = ""
	print(colored("{}{}{}{}{}!".format(
										count_tests, 
										n_spaces(str(count_tests), 4), 
										case_name, 
										n_spaces(case_name, offs),
										failure_or_success(diff, timeout)
									  ), 
				  get_color(diff, timeout)))

	if (timeout == 0 & len(diff) == 0):
		good += 1
	else:
		bad += 1

print("")

print(colored("Summary: {} out of {} tests passed!".format(good, good + bad), "magenta"))
print(colored("See traces at {}/user_out_[CASE_NAME].txt and {}/test_out[CASE_NAME].txt".format(path_to_cases, path_to_cases), "green"))
