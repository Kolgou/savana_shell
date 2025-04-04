////////////////////////////////////////////////////////////////////////////
// Code of the tester
////////////////////////////////////////////////////////////////////////////

errordomain TestError {
	SIGNALED
}

struct ShellInfo {
	string output;
	string errput;
	int status;
}

public int Nb_max_test = 0;
public int Max_async_test = 0;
public int Max_process = 0;
public int res = 0;

async void add_test(string []?av = null) {
	string[] avx = av.copy();

	++Nb_max_test;
	++Max_async_test;
	while (Max_process >= jobs_thread) {
		Idle.add(add_test.callback);
		yield;
	}
	++Max_process;
	try {
		res += yield test(avx);
	}
	catch (Error e) {
		warning(e.message);
	}
	--Max_async_test;
	--Max_process;
}

/**
 * Run Minishell with a command and return the output and the status
 */
async ShellInfo run_minishell (string []?av) throws Error {
	Cancellable timeout = new Cancellable();
	ShellInfo result = {};
	Subprocess process;

	Environment.set_variable ("WHOAMI", "mini", true);
	// Run minishell with valgrind or no
	if (print_leak)
		process = new Subprocess.newv ({"valgrind", "--leak-check=full", "--show-leak-kinds=all", minishell_emp}, STDIN_PIPE | STDERR_PIPE | STDOUT_PIPE);
	else
		process = new Subprocess.newv ({minishell_emp}, STDIN_PIPE | STDOUT_PIPE | SubprocessFlags.STDERR_SILENCE);

	// Add a timeout of 4 seconds
	var uid = Timeout.add (4000, ()=> {
		timeout.cancel();
		process.force_exit ();
		return false;
	});

	// Concat all av in one string
	var command = string.joinv("\n", av);

	yield process.communicate_utf8_async (command, timeout, out result.output, out result.errput);

	// Wait minishell is finished
	yield process.wait_async (timeout);
	// Remove the timeout function
	Source.remove (uid);
	
	// Check if the process is signaled (like segfault)
	if (process.get_if_signaled ()) {
		var sig = process.get_term_sig ();
		throw new TestError.SIGNALED(strsignal(sig));
	}

	// Get the status of the minishell process
	result.status = process.get_exit_status ();

	return result;
}

/**
 * Run Bash with a command and return the output and the status
 */
async ShellInfo run_bash (string []av) throws Error {
	ShellInfo result = {}; 

	// Concat all av in one string
	var command = string.joinv("\n", av);

	Environment.set_variable ("WHOAMI", "bash", true);
	// Run bash
	var process = new Subprocess(STDIN_PIPE | STDERR_PIPE | STDOUT_PIPE, "bash");
	
	yield process.communicate_utf8_async (command, null, out result.output, out result.errput);

	// Wait bash is finished
	yield process.wait_async ();

	// Get the status of the bash process
	result.status = process.get_exit_status ();

	return result;
}


delegate void test_me(string str_test);
/**
 * Check if the output, the status and the memory leak are okay
 */
static bool is_okay (ShellInfo minishell, ShellInfo bash, out string? valgrind) {
	valgrind = null;
	bool ret = true;
	if (print_output && minishell.output != bash.output) {
		ret = false;
	}
	if (print_status && minishell.status != bash.status) {
		ret = false;
	}
	var errbuilder = new StringBuilder ();
	if (print_leak) {
		unowned string tmp = minishell.errput;
		int index = 0;

		// Check if there is a memory leak
		
		test_me func = ((s) => {
			tmp = minishell.errput;
			do {
				int p1;
				int p2;
				index = tmp.index_of(s, 4);
				if (index != -1) {
					tmp = tmp.offset(index);
					tmp = tmp.offset(tmp.index_of_char (':') + 1);
					tmp.scanf (" %d bytes in %d blocks", out p1, out p2);
					if (p1 != 0 || p2 != 0) {
						errbuilder.append(s);
						errbuilder.append(tmp[0: tmp.index_of_char ('\n') + 1]);
					}
				}
			} while (index != -1);
		});
		func ("definitely lost:");
		func ("possibly lost:");
		func ("indirectly lost:");
		// func ("still reachable:");

		func = ((s) => {
			tmp = minishell.errput;
			do {
				index = tmp.index_of(s, 4);
				if (index != -1) {
					tmp = tmp.offset(index);
					errbuilder.append(tmp[0: tmp.index_of_char ('\n') + 1]);
				}
			} while (index != -1);
		});

		func("Conditional jump or move depends on uninitialised value");
		func("Invalid read of size");
		func("Invalid write of size");
		func("Use of uninitialised value of size");

		if (errbuilder.str != "") {
			valgrind = (owned)errbuilder.str;
			ret = false;
		}
	}
	return ret;
}


static void print_test(string []av) {
	print ("\033[36;1mTest\033[0m");
	foreach (unowned var arg in av) {
		print (" [%s]", arg.escape ("\'\""));
	}
}
/**
 * Run Bash and Minishell test (command) and compare it and print the result !
 */
async int test (string []?av = null) throws Error {
	try {
		//////////////////////////
		// Run Minishell
		//////////////////////////
		var minishell = yield run_minishell (av);

		//////////////////////////
		// Parse the output
		//////////////////////////
		
		unowned string output = minishell.output;
		string minishell_output = "";
		int index;

		index = output.index_of("SupraVala: ");
		// If the output doesn't contain "SupraVala: " we just return the output
		if (index == -1)
			minishell_output += output;
		// Get all output between the Prompt and the next Prompt
		while (index != -1) {
			output = output.offset(index + 11);
			output = output.offset(output.index_of_char ('\n') + 1);

			index = output.index_of("SupraVala: ");
			if (index == -1) {
				minishell_output += output;
			}
			else
				minishell_output += output[0: index];
		}

		minishell.output = (owned)minishell_output;


		//////////////////////////
		// Run Bash
		//////////////////////////

		var bash = yield run_bash (av);


		//////////////////////////
		// Print the result
		//////////////////////////
		if (print_only_error == false) {
			print_test(av);
		}

		string? valgrind;
		if (is_okay (minishell, bash, out valgrind)) {
			if (print_only_error == false)
				print ("\033[32;1m[OK]\033[0m");
		}
		else {
			if (print_only_error == true) {
				print_test(av);
			}
			print ("\033[31;1m[KO]\033[0m\n");
			if (print_status && minishell.status != bash.status) {
				printerr("\033[91mStatus mismatch:\033[0m\n");
				printerr("  Minishell: [%d]\n", minishell.status);
				printerr("  Bash: [%d]\n\n", bash.status);
			}
			if (print_output && minishell.output != bash.output) {
				printerr("\033[91mOutput mismatch:\033[0m\n");
				printerr("  Minishell: [%s]\n", minishell.output);
				printerr("  Bash: [%s]\n\n", bash.output);
			}
			if (valgrind != null) {
				printerr("\033[91mMemory leak:\033[0m\n");
				printerr("  %s\n", valgrind.replace ("\n", "\n  "));
			}
			return 0;
		}
		if (print_only_error == false)
			print("\n");
		return 1;
	}
	catch (Error e) {
		if (e is IOError.CANCELLED || e is TestError.SIGNALED) {
			print_test(av);
			print ("\033[31;1m[KO]\033[0m\n");
		}

		if (e is IOError.CANCELLED) {
			print("\033[31;1m[Timeout] %s\n\033[0m", e.message);
			return 0;
		}
		if (e is TestError.SIGNALED) {
			print("\033[31;1m[SEGFAULT] %s\n\033[0m", e.message);
			return 0;
		}
		throw e;
	}
}

////////////////////////////////////////////////////////////////////////////
///	Log handler (Function to print the log like warning, error, etc...)
////////////////////////////////////////////////////////////////////////////

public void log_hander () {
	Log.set_default_handler((type, level, message)=> {
		unowned string real_message;
		var len = message.index_of_char(':') + 1;
		real_message = message.offset(len);
		len += real_message.index_of_char(':') + 2;
		real_message = message.offset(len);

		switch (level) {
			case LogLevelFlags.LEVEL_WARNING:
				print("\033[33m[WARNING]\033[0m: %s \033[35m(", real_message);
				stdout.write(message[0:len - 2].data);
				print(")\033[0m\n");
				break;
			case LogLevelFlags.LEVEL_CRITICAL:
				print("\033[35m[Critical]\033[0m: %s \033[35m(", real_message);
				stdout.write(message[0:len - 2].data);
				print(")\033[0m\n");
				break;
			case LogLevelFlags.LEVEL_MESSAGE:
				print("\033[32m[SupraPack]\033[0m: %s\n", message);
				break;
			case LogLevelFlags.LEVEL_DEBUG:
				if (Environment.get_variable ("G_MESSAGES_DEBUG") != null) {
					print("\033[35m[Debug]\033[0m: %s \033[35m(", real_message);
					stdout.write(message[0:len - 2].data);
					print(")\033[0m\n");
				}
				break;
			case LogLevelFlags.LEVEL_INFO:
				if (type == null)
					print("\033[35m[Info]\033[0m: %s\n", real_message);
				else
					print("%s: %s\n", type, real_message);
				break;
			case LogLevelFlags.FLAG_RECURSION:
			case LogLevelFlags.FLAG_FATAL:
			case LogLevelFlags.LEVEL_ERROR:
			default:
				print("\033[31m[Error]\033[0m: %s \033[35m(", real_message);
				stdout.write(message[0:len - 2].data);
				print(")\033[0m\n");
				Process.exit(-1);
		}
	});
}
