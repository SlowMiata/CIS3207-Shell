make: myShell.c BuiltIn.c Special.c
	gcc  -o MyShell myShell.c BuiltIn.c Special.c -Wall -Werror -I.