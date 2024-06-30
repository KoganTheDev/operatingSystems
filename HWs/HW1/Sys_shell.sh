# C functions under HW1
gcc ./Standard_shell.c  -o Standard_shell
chmod +x Standard_shell

# C functions under Shells
gcc ./Shells/Logic_shell.c -o Logic_shell
gcc ./Shells/Math_shell.c -o Math_shell
gcc ./Shells/String_shell.c -o String_shell
chmod +x Logic_shell
chmod +x Math_shell
chmod +x String_shell

# C functions under ./functions/Standard_Shell_functions
gcc ./functions/Standard_Shell_functions/exit.c -o exit
gcc ./functions/Standard_Shell_functions/Goodbye.c -o Goodbye
gcc ./functions/Standard_Shell_functions/Logic.c -o Logic
gcc ./functions/Standard_Shell_functions/Math.c -o Math
gcc ./functions/Standard_Shell_functions/String.c -o String
chmod +x Standard_shell exit
chmod +x Standard_shell Goodbye
chmod +x Standard_shell Logic
chmod +x Standard_shell Math
chmod +x Standard_shell String


# C functions under ./functions/Logic_Shell_functions
gcc ./functions/Logic_Shell_functions/DectoBin.c -o DectoBin
gcc ./functions/Logic_Shell_functions/DectoHex.c -o DectoHex
gcc ./functions/Logic_Shell_functions/Highbit.c -o Highbit
gcc ./functions/Logic_Shell_functions/History.c -o History
chmod +x Logic_shell DectoBin
chmod +x Logic_shell DectoHex
chmod +x Logic_shell Highbit
chmod +x Logic_shell History

# C functions under ./functions/Math_Shell_functions
gcc ./functions/Math_Shell_functions/Power.c -o Power
gcc ./functions/Math_Shell_functions/Solve.c -o Solve
gcc ./functions/Math_Shell_functions/Sqrt.c -o Sqrt
gcc ./functions/Math_Shell_functions/History.c -o History
chmod +x Math_shell Power
chmod +x Math_shell Solve
chmod +x Math_shell Sqrt
chmod +x Math_shell History

# C functions under ./functions/String_Shell_functions
gcc ./functions/String_Shell_functions/Find.c -o Find
gcc ./functions/String_Shell_functions/PrintFile.c -o PrintFile
gcc ./functions/String_Shell_functions/Replace.c -o Replace
gcc ./functions/String_Shell_functions/History.c -o History
chmod +x String_shell Find
chmod +x String_shell PrintFile
chmod +x String_shell Replace
chmod +x String_shell History

# Run the main shell file.
./Standard_shell