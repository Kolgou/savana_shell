public bool print_only_error = false;
public bool print_output = false;
public bool print_status = false;
public bool print_leak = false;
public bool print_bonus = false;
public uint jobs_thread;
public string minishell_emp;
unowned string PWD;

////////////////////////////////////////////////////////////////////////////
// All test is here !
////////////////////////////////////////////////////////////////////////////
async void all_test(string []args) {

	// [NOTE]: triple quote is used to avoid escape character
	


	add_test.begin({"|"});
	add_test.begin({"| echo oi"});
	add_test.begin({"| |"});
	add_test.begin({"| | |"});
	add_test.begin({"| $"});
	add_test.begin({">"});
	add_test.begin({">>"});
	add_test.begin({">>>"});
	add_test.begin({"<"});
	add_test.begin({"<<"});
	add_test.begin({"echo hi <"});
	add_test.begin({"cat    <| ls"});
	add_test.begin({"echo hi | >"});
	add_test.begin({"echo hi | > >>"});
	add_test.begin({"echo hi | < |"});
	add_test.begin({"echo hi |   | "});
	add_test.begin({"echo $EMPYT"});
	add_test.begin({"echo $EMPYT    abc"});
	add_test.begin({"echo $EMPYT abc"});
	add_test.begin({"echo $EMPYT abc   $EMPTY"});
	add_test.begin({"echo $EMPYT abc $EMPTY"});
	add_test.begin({"$EMPTY echo $EMPYT abc"});
	add_test.begin({"expr $? + $?", "expr $? + $?", "expr $? + $?"});
	add_test.begin({"$"});
	add_test.begin({". | . | ."});
	add_test.begin({"./no_permission"});


	/////////////////////////////
	// Test With Simple Command
	/////////////////////////////

	add_test.begin({" /bin/ls "});
	add_test.begin({" /bin/ls -la "});
	add_test.begin({" /bin/ls -l "});
	add_test.begin({" /bin/ls -l -a "});
	add_test.begin({" /bin/ls -l -a -t "});

	add_test.begin({""" printf "Hello World" """});
	add_test.begin({""" printf 'Hello World' """});
	add_test.begin({""" echo "Hello World" """});
	add_test.begin({""" echo 'Hello World' """});

	add_test.begin({""" echo "Hello World" | cat -e """});
	add_test.begin({""" printf 'Hello World' | cat -e """});
	add_test.begin({""" echo "Hello World" | cat -e | cat -e """});

	add_test.begin({""" echo "cat Makefile | cat > $USER"   """});
	add_test.begin({""" echo 'cat Makefile | cat > $USER'   """});
	add_test.begin({""" /bin/ls | /usr/bin/cat -e """});
	add_test.begin({""" echo ' ' """});
	add_test.begin({""" echo '    ' """});
	add_test.begin({""" echo '        ' """});
	add_test.begin({""" echo "        " """});
	add_test.begin({""" echo "    " """});
	add_test.begin({""" echo " " """});
	add_test.begin({"""echo hello'world'"""});
	add_test.begin({"""echo hello""world"""});
	add_test.begin({"""echo ''"""});
	add_test.begin({"""echo "$PWD""""});
	add_test.begin({"""echo '$PWD'"""});
	add_test.begin({"""echo "> >> < * ? [ ] | ; [ ] || && ( }) & # $ \ <<""""});
	add_test.begin({"""echo '> >> < * ? [ ] | ; [ ] || && ( }) & # $ \ <<'"""});
	add_test.begin({"""echo "exit_code ->$? user ->$USER home -> $HOME""""});
	add_test.begin({"""echo 'exit_code ->$? user ->$USER home -> $HOME'"""});
	add_test.begin({"""echo "$""""});
	add_test.begin({"""echo '$'"""});
	add_test.begin({"""echo $"""});
	add_test.begin({"""echo $?"""});
	add_test.begin({"""echo $?HELLO"""});
	add_test.begin({""" printf  $"  $USER  a"  """});


	add_test.begin({" "});
	add_test.begin({"			"});
	add_test.begin({""""""""});
	add_test.begin({" cat -e < Makefile < ../.gitignor  "});
	add_test.begin({" < file_not_found "});
	add_test.begin({" < file_not_found cat"});
	add_test.begin({" < file_not_found > /dev/stdout"});
	add_test.begin({" echo -n salut"});
	add_test.begin({" echo -nnnnnnnnnnnnnn1 salut"});
	add_test.begin({" echo -nnnnnnnnnnnnnn1 salut  nvobwriov wr gow v '$USER>eef>$USER' "});
	add_test.begin({" echo -nnnnnnnnnnnnnnnnnnn1 salut  nvobwriov wr gow v '$USER>eef>$USER'  "});
	add_test.begin({" echo -nnnnnnnnnnnnnnnnnnn1 salut  nvobwriov wr gow v '>p' "});
	add_test.begin({" cat -e < Makefile < ../.gitignore "});
	add_test.begin({" ls -l | cat -e  | ls "});

	/////////////////////////////
	// Test With Echo / printf
	/////////////////////////////

	add_test.begin({""" printf 'Syntax Error!' | | ls """});
	add_test.begin({""" printf 'Syntax Error!' < | ls """});
	add_test.begin({""" printf 'Syntax Error!'  >> | ls """});
	add_test.begin({""" printf 'Syntax Error!' | > file_out """});
	add_test.begin({""" printf 'Syntax Error!' |> file_out """});
	add_test.begin({""" >x printf 'Syntax Error!' | """});
	add_test.begin({""" | >x printf 'Syntax Error!' """});
	add_test.begin({""" >x printf 'Syntax Error!' > """});
	add_test.begin({""" >x printf 'Syntax Error!' << """});
	add_test.begin({""" echo '>' test '<' """});
	add_test.begin({""" echo '>'"""});
	add_test.begin({""" echo '<'"""});
	add_test.begin({""" echo '<<'"""});
	add_test.begin({""" echo '>>'"""});
	add_test.begin({""" echo '>test<' """});
	add_test.begin({""" echo '>test' """});
	add_test.begin({""" echo 'test<' """});
	add_test.begin({""" echo "|" """});
	add_test.begin({""" echo '>test '< """});
	add_test.begin({""" echo ' test <' """});
	add_test.begin({""" echo ">" """});
	add_test.begin({""" echo ">test<" """});
	add_test.begin({""" echo ">test" """});
	add_test.begin({""" echo "test<" """});
	add_test.begin({""" printf 'Syntax Error!' | | ls """});
	add_test.begin({""" printf 'Syntax Error!' < | ls """});
	add_test.begin({""" printf 'Syntax Error!'  >> | ls """});
	add_test.begin({""" printf 'Syntax Error!' | > file_out """});
	add_test.begin({""" printf 'Syntax Error!' |> file_out """});
	add_test.begin({""" >x printf 'Syntax Error!' | """});
	add_test.begin({""" | >x printf 'Syntax Error!' """});
	add_test.begin({""" >x printf 'Syntax Error!' > """});
	add_test.begin({""" >x printf 'Syntax Error!' << """});
	add_test.begin({""" echo '>' test '<' """});
	add_test.begin({""" echo '>'"""});
	add_test.begin({""" echo '>test<' """});
	add_test.begin({""" echo '>test' """});
	add_test.begin({""" echo 'test<' """});
	add_test.begin({""" echo "|" """});
	add_test.begin({""" echo '>test '< """});
	add_test.begin({""" echo ' test <' """});
	add_test.begin({""" echo ">" """});
	add_test.begin({""" echo ">test<" """});
	add_test.begin({""" echo ">test" """});
	add_test.begin({""" echo "test<" """});


	/////////////////////////////
	// Test With Pipes
	/////////////////////////////

	add_test.begin({""" echo hello|cat -e"""});
	add_test.begin({""" echo hello      |cat -e"""});
	add_test.begin({""" echo hello|               cat -e"""});
	add_test.begin({""" echo         hello        |               cat -e"""});
	add_test.begin({""" ls|ls|ls|ls|ls|ls|cat    -e"""});
	add_test.begin({""" ls|ls|ls|ls|ls|ls|ls|ls |ls | ls    | ls | ls | cat    -e"""});
	add_test.begin({""" command_not_found | echo 'abc'"""});
	add_test.begin({""" command_not_found | cat"""});
	add_test.begin({""" cat Makefile | cat /dev/urandom | ls | wc -w """});
	add_test.begin({""" ls | ls |ls | ls| ls |ls| ls|ls | ls | ls | ls | ls"""});
	add_test.begin({""" cat Makefile | md5sum """});
	add_test.begin({""" cat Makefile | grep -o SRC | tr '\n' ' ' """});
	add_test.begin({""" cat /dev/urandom | head -c 15 | wc -c """});
	add_test.begin({""" cat /dev/urandom | strings | grep -o "[A-Z][0-9]" | tr -d '\n' | head -c 15 | wc -c """});

	/////////////////////////////
	// Test With Variable
	/////////////////////////////

	add_test.begin({""" echo $ """});
	add_test.begin({""" echo $ USER """});
	add_test.begin({""" echo $USER """});
	add_test.begin({""" echo $USER$ """});
	add_test.begin({""" echo $USER $ """});
	add_test.begin({""" echo "$USER$" """});
	add_test.begin({""" echo "$USER $" """});
	add_test.begin({""" echo $JENEXISTEPAS """});
	add_test.begin({""" echo $ JENEXISTEPAS """});
	add_test.begin({""" echo $USER_$USER """});
	add_test.begin({""" echo $USER$USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER $USER """});
	add_test.begin({""" printf "$USER\n" """});
	add_test.begin({""" printf $? """});
	add_test.begin({""" printf $?? """});
	add_test.begin({""" printf $??? $?? $? """});
	add_test.begin({""" printf "$USER$USER'' = ' $L ANG '" '' """});
	add_test.begin({""" printf "$USER$USER" """});
	add_test.begin({""" echo $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ | wc -l"""});
	add_test.begin({""" echo $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ | wc -l"""});
	add_test.begin({""" echo $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ | wc -l"""});
	add_test.begin({""" echo $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ | wc -l"""});

	/////////////////////////////
	// Test With Quotes
	/////////////////////////////

	add_test.begin({""" printf "$USER$USER'' = ' $L ANG '" """});
	add_test.begin({""" printf "=  PATH    "  't$USER  ' "" """});
	add_test.begin({""" prin"tf "$USER """});
	add_test.begin({""" pri"tf" $USER """});
	add_test.begin({""" pri"tf $USER" """});
	add_test.begin({""" "printf" $USER """});
	add_test.begin({""" "printf" ""$USER"bj'r'" """});
	add_test.begin({""" "pr'int'f" ""$'USER'"bj'r'" """});
	add_test.begin({""" printf $'hello' """});
	add_test.begin({""" printf $"hello" """});
	add_test.begin({""" ''''''"/bin/ls"'''''' """});
	add_test.begin({""" /b'i"n/ls' -l  """});
	add_test.begin({""" /b''i"n/''ls -"na'"th'an"""});
	add_test.begin({""" /b'i''''''''n/"l's """});
	add_test.begin({""" /b'in/l's -l'a'"""});
	add_test.begin({""" '/'b"in/l"s """});
	add_test.begin({""" echo '$?' """});
	add_test.begin({""" echo ''$USER'' """});
	add_test.begin({""" echo '''$USER''' """});
	add_test.begin({""" echo """});
	add_test.begin({""" echo '' b"""});
	add_test.begin({""" echo '' ''x"""});
	add_test.begin({""" echo '' "''" ''X"""});


	add_test.begin({""" echo$USER """});
	add_test.begin({""" echo -n $USER -n hello supra $USER"""});
	add_test.begin({""" echo -n test"""});
	add_test.begin({""" echo test -n """});
	add_test.begin({""" echo -nnnnnnnnnnnnnn -nns -n test """});
	add_test.begin({""" echo -nnnnnnnnnnnnnn -nnn -n test """});
	add_test.begin({""" echo str1  "" str3"  not finished yet ........ done." """});
	add_test.begin({""" echo  Ichi Ni San Yon Go | cat -e"""});




	///////////////////////////////////
	// Test With Redirection  (Input)
	///////////////////////////////////


	add_test.begin({""" < Makefile cat | md5sum """});
	add_test.begin({""" < file_not_found cat | wc -c """});
	add_test.begin({""" < Makefile cmd_not_found | wc -c """});
	add_test.begin({""" < Makefile | printf 'You see me?' """});
	add_test.begin({""" < Makefile wc -w  < tester.vala """});
	add_test.begin({""" wc -w < tester.vala < Makefile """});
	add_test.begin({""" ls | wc -w < tester.vala < Makefile """});
	add_test.begin({""" < Makefile < tester.vala wc -c """});
	add_test.begin({""" ls | < Makefile < tester.vala wc -c """});


	///////////////////////////////////
	// Test With Redirection  (Output)
	///////////////////////////////////


	add_test.begin({" printf 'Hello World' >trash/$WHOAMI.a.test ", "cat trash/$WHOAMI.a.test -e"});
	add_test.begin({" >trash/$WHOAMI.b.test printf 'Hello World' >trash/$WHOAMI.c.test ", "cat trash/$WHOAMI.b.test -e", "echo A", "cat trash/$WHOAMI.c.test -e"});
	add_test.begin ({"printf 'A' >trash/$WHOAMI.l.test", "echo 'B' >trash/>>trash/$WHOAMI.l.test", "echo 'C' >trash/>trash/$WHOAMI.l.test", "cat trash/$WHOAMI.l.test -e", "cat trash/>trash/$WHOAMI.l.test -e"});
	add_test.begin ({"printf 'A' >trash/$WHOAMI.m.test", " >trash/>trash/$WHOAMI.m.test echo 'B'", ">trash/>trash/$WHOAMI.m.test echo 'C'", "cat $WHOAMI.m.test -e"});

	add_test.begin ({"printf 'hello world' >/dev/null | cat -e"});
	add_test.begin ({"printf 'hello ' >trash/$WHOAMI.test", "printf 'world' >>trash/$WHOAMI.test", "cat trash/$WHOAMI.test -e"});
	add_test.begin ({"printf 'hello ' >trash/$WHOAMI.test2", "printf 'world' >>trash/$WHOAMI.test2", "printf ' ndacunh' >>trash/$WHOAMI.test2", "cat trash/$WHOAMI.test2 -e"});

	add_test.begin ({">/dev/null printf 'hello world' | cat -e"});
	add_test.begin ({">/dev/stdout printf 'hello world' | cat -e"});
	add_test.begin ({" > /dev/stdout"});
	add_test.begin ({" >> /dev/stdout"});
	add_test.begin ({" < /dev/stdout"});

	///////////////////////////////////
	// Extras Test
	///////////////////////////////////


	add_test.begin({"$PWD"});
	add_test.begin({"$EMPTY"});
	add_test.begin({"$EMPTY echo hi"});
	add_test.begin({"./test_files/invalid_permission"});
	add_test.begin({"./missing.out"});
	add_test.begin({"missing.out"});
	add_test.begin({""""aaa""""});
	add_test.begin({"""'aaa'"""});
	add_test.begin({"test_files"});
	add_test.begin({"./test_files"});
	add_test.begin({"/test_files"});
	add_test.begin({"minishell.h"});
	add_test.begin({"$"});
	add_test.begin({"$?"});
	add_test.begin({"README.md"});
	add_test.begin({"edsfdsf" , "echo error: $?"});
	
	///////////////////////////////////
	// Test PWD
	///////////////////////////////////

	add_test.begin({"clear | pwd"});
	add_test.begin({"clear | pwd | cat -e"});
	add_test.begin({"clear | pwd . | cat -e"});
	add_test.begin({"pwd"});
	add_test.begin({"pwd .."});
	add_test.begin({"pwd ."});
	add_test.begin({"pwd . | cat -e"});
	add_test.begin({"pwd | cat -e"});
	add_test.begin({"printf a | pwd | cat -e"});
	
	///////////////////////////////////
	// Test ENV 
	///////////////////////////////////

	add_test.begin({"unset LD_PRELOAD", "unset WHOAMI", "unset PWD", "unset LANG", "unset OLDPWD", "unset ARGS", "unset MAKEFLAGS", "unset MFLAGS", "env | grep -v _ | grep -v SHLVL | grep -v SHELL | sort"});
	add_test.begin({""" env | grep USER | md5sum """});
	add_test.begin({""" env | grep USER """});
	
	add_test.begin({"unset 6_a"});
	add_test.begin({"unset ndacunh"});
	add_test.begin({"unset 0oui"});
	add_test.begin({"unset PWD HERE", "echo $PWD"});


	///////////////////////
	// Test With Export and unset 
	///////////////////////

	add_test.begin({"export ABC", "env | grep ABC -o", "printf hi", "env | grep ABC"});
	add_test.begin({"export NDACUNH=42", "unset NDACUNH | printf hey", "printf : $NDACUNH"});
	add_test.begin({"""export GHOST=123 | env | grep GHOST"""});
	add_test.begin({"""export hello"""});
	add_test.begin({"""export HELLO=123""", "printf : $HELLO"});
	add_test.begin({"""export A-"""});
	add_test.begin({"""export HELLO=123 A"""});
	add_test.begin({"""export HELLO="123 A-""""});
	add_test.begin({"""export hello world"""});
	add_test.begin({"""export HELLO-=123"""});
	add_test.begin({"""export ="""});
	add_test.begin({"""export 123"""});
	add_test.begin({"""export SLS='/bin/ls'""", "printf here:", "$SLS"});
	add_test.begin({"export UNO=1 DOS-2 TRES=3 | env | grep TRES"});
	add_test.begin({"export abcd=abcd", "export abcd+=ndacunh", "env | grep abcd"});
	add_test.begin({"export ABCD=abcd", "export ABCD +=ndacunh", "env | grep ABCD"});
	add_test.begin({"export ABCD=abcd", "export ABCD += ndacunh", "env | grep ABCD"});
	add_test.begin({"export ABCD=abcd", "export ABCD+= ndacunh", "env | grep ABCD"});
	add_test.begin({"export ABCD =abcd", "env | grep ABCD"});
	add_test.begin({"export ABCD= abcd", "env | grep ABCD"});
	add_test.begin({"export ABCD=Hello", "export ABCD =abcd", "env | grep ABCD"});
	add_test.begin({"export ABCD=Hello", "export ABCD= abcd", "env | grep ABCD"});


	add_test.begin({"unset HELLO="});
	add_test.begin({"unset"});
	add_test.begin({"unset HELLO1 HELLO2"});
	add_test.begin({"unset HOME", "echo $HOME"});
	add_test.begin({"unset PATH", "/bin/ls"});
	add_test.begin({"unset PATH", "ls"});
	add_test.begin({"unset PATH", @"export PATH='$PWD'", "ls"});
	add_test.begin({"unset PATH", @"export PATH='$PWD'", "/bin/ls"});
	add_test.begin({"unset PATH", @"export PATH='$PWD'", @"$PWD/ls"});
	add_test.begin({"export A='suprapack'", "echo a $A", "unset A", "echo a $A"});
	add_test.begin({"export HELLO=abc", "unset HELLO"});
	add_test.begin({"export HELLO=abc", "unset HELL", "unset HELLOO", "printf : $HELLO"});

	///////////////////////
	// Test With Exit
	///////////////////////

	add_test.begin({"""exit 123"""});
	add_test.begin({"""exit 298"""});
	add_test.begin({"""exit 256"""});
	add_test.begin({"""exit +100"""});
	add_test.begin({"""exit "+100""""});
	add_test.begin({"""exit +"100""""});
	add_test.begin({"""exit -100"""});
	add_test.begin({"""exit "-100""""});
	add_test.begin({"""exit -"100""""});
	add_test.begin({"""exit hello"""});
	add_test.begin({"""exit 42 world"""});
	add_test.begin({"exit 9223372036854775807"});
	add_test.begin({"exit 9223372036854775808"});
	add_test.begin({"exit -9223372036854775807"});
	add_test.begin({"exit -9223372036854775808"});
	add_test.begin({"exit -9223372036854775809"});

	
	///////////////////////
	// Test With HereDoc 
	///////////////////////

	add_test.begin({"<< end cat -e \nsimple\ntest\nend"});
	add_test.begin({"<< AH cat -e \nsimple\ntest\nend\nAH"});
	add_test.begin({"<< AH cat -e \nsimple\n\n\n\n\n\n\nend\nAH"});
	add_test.begin({"<< AH cat -e | grep -o 'simple' \nsimple\nend\nAH"});
	add_test.begin({"<< \"EOF\" cat -e \n$USER\nEOF"});
	add_test.begin({"<< \'EOF\' cat -e \n$USER\nEOF"});
	add_test.begin({"<< \"EOF\" cat -e \nnda-cunh\nEOF"});
	add_test.begin({"<< \'EOF\' cat -e \nnda-cunh\nEOF"});
	add_test.begin({"cat << here -e\nhello\nhere"});


	if (print_bonus == true) {
		add_test.begin({"cat << here -e\nhello\nhere"});
		add_test.begin({"*"});
		add_test.begin({"*/*"});
		add_test.begin({"*/*"});
		add_test.begin({"echo *"});
		add_test.begin({"echo D*"});
		add_test.begin({"echo *Z"});
		add_test.begin({"echo *t hola"});
		add_test.begin({"echo *t"});
		add_test.begin({"echo $*"});
		add_test.begin({"echo hola*hola *"});
		add_test.begin({"echo $hola*"});
		add_test.begin({"echo $HOME*"});
		add_test.begin({"cd *"});
		add_test.begin({"cd *"});
		add_test.begin({"cd *"});
		add_test.begin({"echo hola || cat"});
		add_test.begin({ "🍒  ||"});
		add_test.begin({"pwd || ls"});
		add_test.begin({"echo hola || echo bonjour"});
		add_test.begin({"echo hola && echo bonjour"});
		add_test.begin({"echo bonjour || echo hola"});
		add_test.begin({"echo bonjour && echo hola"});
		add_test.begin({"echo -n bonjour && echo -n hola"});
		add_test.begin({"pwd && ls && echo hola"});
		add_test.begin({"pwd || ls && echo hola"});
		add_test.begin({"pwd && ls || echo hola"});
		add_test.begin({"pwd || ls || echo hola"});


		add_test.begin({"""ls || export """""});  
		add_test.begin({"""export "" || ls"""});
		add_test.begin({"""ls && export """""});
		add_test.begin({"""export "" && ls"""});
		add_test.begin({"""export "" && unset """""});

		add_test.begin({"ls || ;"});
		add_test.begin({"; || ls"});
		add_test.begin({"ls && ;"});
		add_test.begin({"; && ls"});
		add_test.begin({"ls || <"});
		add_test.begin({"ls && <"});
		add_test.begin({"cat | echo || ls"});
		add_test.begin({"cat | echo && ls"});
		add_test.begin({"ls || cat | echo"});
		add_test.begin({"ls && cat | echo"});
		add_test.begin({"(ls)"});
		add_test.begin({"( ( ls ) )"});
		add_test.begin({"( ( ) ls )"});
		add_test.begin({"ls && (ls)"});
		add_test.begin({"(ls && pwd)"});
		add_test.begin({"( ( ls&&pwd ) )"});
		add_test.begin({"( ( ls ) &&pwd )"});
		add_test.begin({"(ls && ( ( pwd ) ) )"});
		add_test.begin({"(ls && pwd) > hola $> cat hola"});
		add_test.begin({"> hola ls && pwd"});
		add_test.begin({"> hola (ls && pwd)"});
		add_test.begin({"(> pwd) $> ls"});
		add_test.begin({"(< pwd) $> ls"});
		add_test.begin({"(< pwd)"});
		add_test.begin({"( ( ( ( ( pwd) ) ) ) )"});
		add_test.begin({"() pwd"});
		add_test.begin({"> pwd (ls)"});
		add_test.begin({"(ls||pwd)&&(ls||pwd)"});
		add_test.begin({"(lss||pwd)&&(lss||pwd)"});
		add_test.begin({"(lss&&pwd)&&(lss&&pwd)"});
		add_test.begin({"(ls && pwd | wc) > hola $> cat hola"});
		add_test.begin({"(ls && pwd | wc) > hola $> (ls && pwd | wc) > hola $> cat hola"});
		add_test.begin({"(ls && pwd | wc) >> hola $> echo hey&&(ls && pwd | wc) > hola $> cat hola"});
		add_test.begin({"(pwd | wc) < hola"});
		add_test.begin({"(ls && pwd | wc) < hola"});
		add_test.begin({"(ls -z || pwd | wc) < hola"});
		add_test.begin({"echo hey > hola $> (pwd | wc) < hola"});
		add_test.begin({"echo hey > hola $> (ls && pwd | wc) < hola"});
		add_test.begin({"echo hey > hola $> (ls -z || pwd | wc) < hola"});
		add_test.begin({"(ls -z || pwd && ls)"});
		add_test.begin({"ls || (cat Makefile|grep srcs) && (pwd|wc)"});
		add_test.begin({"ls -z && (ls) && (pwd)"});
		add_test.begin({"(ls > Docs/hey && pwd) > hola $> cat hola $> cat Docs/hey"});
		add_test.begin({"ls > Docs/hey && pwd > hola $> cat hola $> cat Docs/hey"});
		add_test.begin({"cd ../.. && pwd && pwd"});
		add_test.begin({"(cd ../.. && pwd) && pwd"});
		add_test.begin({"ls -z || cd ../../..&&pwd $> pwd"});
		add_test.begin({"ls -z || (cd ../../..&&pwd) $> pwd"});
		add_test.begin({"ls *"});
		add_test.begin({"ls *.*"});
		add_test.begin({"ls *.hola"});
		add_test.begin({"cat M*le"});
		add_test.begin({"cat M*ee"});
		add_test.begin({"cat Make*file"});
	}


	// run the loading animation
	loading.begin();
	// Wait for all test to finish
	while (Max_async_test != 0) {
		Idle.add(all_test.callback);
		yield;
	}
	print ("\n\033[35m[Total]: %d / %d\033[0m\n", res, Nb_max_test);
}

/*
 * loading animation
 */
async void loading() {
	const string animation[] = {
		"⠋ Loading .  ",
		"⠙ Loading .. ",
		"⠹ Loading ...",
		"⠸ Loading .. ",
		"⠼ Loading ...",
		"⠴ Loading .. ",
		"⠦ Loading .  ",
		"⠧ Loading .. ",
		"⠇ Loading .  ",
		"⠏ Loading .. "
	};
	int i = 0;
	while (true) {
		Timeout.add(300, loading.callback);
		yield;
		print("%s\r", animation[i]);
		++i;
		if (i == animation.length)
			i = 0;
	}
}

////////////////////////////////////////////////////////////////////////////
// Main  -- options part and start the test
////////////////////////////////////////////////////////////////////////////
[Compact]
class Main {
	public static async void main (string[] args) {
		PWD = Environment.get_variable("PWD");
		Posix.signal(Posix.Signal.PIPE, ()=>{
			warning ("Broken Pipe !");
			error ("Please try run the tester with -v options to see the segfault");
		});
		try {
			minishell_emp = "../minishell";
			jobs_thread = get_num_processors();

			// Enable UTF8 for the terminal
			Intl.setlocale();
			log_hander();

			// Enable Fake Readline it write a fake prompt 'SupraVala: '
			if (" " in PWD)
				Environment.set_variable("LD_PRELOAD", "./fake_readline.so", true);
			else
				Environment.set_variable("LD_PRELOAD", @"$PWD/fake_readline.so", true);

			// Create the trash directory
			DirUtils.create ("trash", 0777);

			// Options Part
			var opt_context = new OptionContext ("- Minishell Tester -");
			opt_context.set_help_enabled (true);
			opt_context.add_main_entries (options, null);
			opt_context.parse (ref args);

			// Check if the minishell is compiled
			if (FileUtils.test (minishell_emp, FileTest.EXISTS) == false) {
				warning ("Please compile the minishell before running the test !");
				warning (@"'$minishell_emp' is not found !");
				return ;
			}

			// Check if the minishell is an executable
			FileUtils.chmod(minishell_emp, 0755);
			if (FileUtils.test (minishell_emp, FileTest.IS_EXECUTABLE) == false) {
				warning ("The minishell is not an executable !");
				return ;
			}

			print_status = !print_status;
			print_output = !print_output;

			yield all_test(args);
		}
		catch (Error e) {
			warning(e.message);
		}
	}

	const OptionEntry[] options = {
		{ "only-error", 'e', OptionFlags.NONE, OptionArg.NONE, ref print_only_error, "Display Error and do not print [OK] test", null },
		{ "no-output", 'o', OptionFlags.NONE, OptionArg.NONE, ref print_output, "Don't Display error-output", null },
		{ "no-status", 's', OptionFlags.NONE, OptionArg.NONE, ref print_status, "Don't Display error-status", null },
		{ "minishell", 'm', OptionFlags.NONE, OptionArg.FILENAME, ref minishell_emp, "the path of minishell default: '../minishell'", "Minishell Path"},
		{ "jobs", 'j', OptionFlags.NONE, OptionArg.INT, ref jobs_thread, "The number of thread jobs by default is number of cpu", "num of jobs"},
		{ "leak", 'v', OptionFlags.NONE, OptionArg.NONE, ref print_leak, "Add Leak test (is too slow)", null },
		{"bonus", 'b', OptionFlags.NONE, OptionArg.NONE, ref print_bonus, "Add Bonus test", null},
		{ null }
	};
}
