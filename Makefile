make: myShell.c BuiltIn.c
	gcc  -o MyShell myShell.c BuiltIn.c -Werror -Wall -I.