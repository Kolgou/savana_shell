SRC = main.vala core.vala
NAME = tester
NAME_FAKE = fake_readline.so
SRC_FAKE = fake_readline.vala

all: $(NAME) fake_readline.so

$(NAME_FAKE): $(SRC_FAKE) 
	valac $(SRC_FAKE) -X -O2 --profile=posix dlopen.vapi --library=readline -X --shared -o $(NAME_FAKE) -X -fpic -X -w

$(NAME): ${SRC} 
	valac ${SRC} --pkg=posix --pkg=gio-2.0 -X -w -X -O3 -o $(NAME) 

debug: ${SRC} 
	valac ${SRC} --pkg=gio-2.0 -X -w -X -O3 --debug -X -fsanitize=address -o $(NAME) 

re: clean all

clean:
	rm -rf ${NAME} ${NAME_FAKE} trash

run: all
	./tester $(ARGS)

.PHONY: all re clean run debug
