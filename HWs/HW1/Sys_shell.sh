# Compile main shell program
gcc ./Standard_shell.c -o Standard_shell
chmod +x Standard_shell

# Compile functions under ./functions/Standard_Shell_functions
gcc ./functions/Standard_Shell_functions/exit.c -o ./functions/Standard_Shell_functions/exit
gcc ./functions/Standard_Shell_functions/Goodbye.c -o ./functions/Standard_Shell_functions/Goodbye
gcc ./functions/Standard_Shell_functions/Logic.c -o ./functions/Standard_Shell_functions/Logic
gcc ./functions/Standard_Shell_functions/Math.c -o ./functions/Standard_Shell_functions/Math
gcc ./functions/Standard_Shell_functions/String.c -o ./functions/Standard_Shell_functions/String
chmod +x ./functions/Standard_Shell_functions/exit
chmod +x ./functions/Standard_Shell_functions/Goodbye
chmod +x ./functions/Standard_Shell_functions/Logic
chmod +x ./functions/Standard_Shell_functions/Math
chmod +x ./functions/Standard_Shell_functions/String

# Compile functions under ./functions/Logic_Shell_functions
gcc ./functions/Logic_Shell_functions/DectoBin.c -o ./functions/Logic_Shell_functions/DectoBin
gcc ./functions/Logic_Shell_functions/DectoHex.c -o ./functions/Logic_Shell_functions/DectoHex
gcc ./functions/Logic_Shell_functions/Highbit.c -o ./functions/Logic_Shell_functions/Highbit
gcc ./functions/Logic_Shell_functions/History.c -o ./functions/Logic_Shell_functions/History
chmod +x ./functions/Logic_Shell_functions/DectoBin
chmod +x ./functions/Logic_Shell_functions/DectoHex
chmod +x ./functions/Logic_Shell_functions/Highbit
chmod +x ./functions/Logic_Shell_functions/History

# Compile functions under ./functions/Math_Shell_functions
gcc ./functions/Math_Shell_functions/Power.c -o ./functions/Math_Shell_functions/Power
gcc ./functions/Math_Shell_functions/Solve.c -o ./functions/Math_Shell_functions/Solve
gcc ./functions/Math_Shell_functions/Sqrt.c -o ./functions/Math_Shell_functions/Sqrt
gcc ./functions/Math_Shell_functions/History.c -o ./functions/Math_Shell_functions/History
chmod +x ./functions/Math_Shell_functions/Power
chmod +x ./functions/Math_Shell_functions/Solve
chmod +x ./functions/Math_Shell_functions/Sqrt
chmod +x ./functions/Math_Shell_functions/History

# Compile functions under ./functions/String_Shell_functions
gcc ./functions/String_Shell_functions/Find.c -o ./functions/String_Shell_functions/Find
gcc ./functions/String_Shell_functions/PrintFile.c -o ./functions/String_Shell_functions/PrintFile
gcc ./functions/String_Shell_functions/Replace.c -o ./functions/String_Shell_functions/Replace
gcc ./functions/String_Shell_functions/History.c -o ./functions/String_Shell_functions/History
chmod +x ./functions/String_Shell_functions/Find
chmod +x ./functions/String_Shell_functions/PrintFile
chmod +x ./functions/String_Shell_functions/Replace
chmod +x ./functions/String_Shell_functions/History

# Run the main shell file
./Standard_shell
