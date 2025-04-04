[Compact]
[CCode(cname="void", free_function="dlclose", cheader_filename="dlfcn.h")]
class Module {
	[CCode (cname="dlopen")]
	public Module(string filename, ModuleFlags flags);
	[CCode (cname="dlsym")]
	public void *symbol(string name);
}

[CCode (cprefix="RTLD_", has_type_id=false)]
enum ModuleFlags {
	LAZY,
	NOW,
	GLOBAL,
	LOCAL,
	NODELETE,
	NOLOAD,
	DEEPBIND
}
