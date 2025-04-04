public delegate string d_readline (string prompt);

Module? module = null;
d_readline func = null;

public string readline (string prompt) {
	if (module == null) {
		module = new Module ("libreadline.so", ModuleFlags.LAZY);
		if (module == null) {
			var fs = FILE.open ("test.log", "w+");
			fs.printf ("Module Error: %s\n", strerror (fs.error ())); 
		}
		func = (d_readline)module.symbol ("readline");
		if (func == null) {
			var fs = FILE.open ("test.log", "w+");
			fs.printf ("Symbol Error: %s\n", strerror (fs.error ())); 
		}
	}
    return func("SupraVala: ");
}
