# Create the compiled files directory
mkdir -p ./Compiled_files

# C functions under HW1
gcc ./Standard_shell.c -o ./Compiled_files/Standard_shell
chmod +x ./Compiled_files/Standard_shell

# C functions under ./functions/Standard_Shell_functions
gcc ./functions/Standard_Shell_functions/exit.c -o ./Compiled_files/exit
gcc ./functions/Standard_Shell_functions/Goodbye.c -o ./Compiled_files/Goodbye
gcc ./functions/Standard_Shell_functions/Logic.c -o ./Compiled_files/Logic
gcc ./functions/Standard_Shell_functions/Math.c -o ./Compiled_files/Math
gcc ./functions/Standard_Shell_functions/String.c -o ./Compiled_files/String
chmod +x ./Compiled_files/exit
chmod +x ./Compiled_files/Goodbye
chmod +x ./Compiled_files/Logic
chmod +x ./Compiled_files/Math
chmod +x ./Compiled_files/String

# C functions under ./functions/Logic_Shell_functions
gcc ./functions/Logic_Shell_functions/DectoBin.c -o ./Compiled_files/DectoBin
gcc ./functions/Logic_Shell_functions/DectoHex.c -o ./Compiled_files/DectoHex
gcc ./functions/Logic_Shell_functions/Highbit.c -o ./Compiled_files/Highbit
gcc ./functions/Logic_Shell_functions/History.c -o ./Compiled_files/Logic_History
chmod +x ./Compiled_files/DectoBin
chmod +x ./Compiled_files/DectoHex
chmod +x ./Compiled_files/Highbit
chmod +x ./Compiled_files/Logic_History

# C functions under ./functions/Math_Shell_functions
gcc ./functions/Math_Shell_functions/Power.c -o ./Compiled_files/Power
gcc ./functions/Math_Shell_functions/Solve.c -o ./Compiled_files/Solve
gcc ./functions/Math_Shell_functions/Sqrt.c -o ./Compiled_files/Sqrt
gcc ./functions/Math_Shell_functions/History.c -o ./Compiled_files/Math_History
chmod +x ./Compiled_files/Power
chmod +x ./Compiled_files/Solve
chmod +x ./Compiled_files/Sqrt
chmod +x ./Compiled_files/Math_History

# C functions under ./functions/String_Shell_functions
gcc ./functions/String_Shell_functions/Find.c -o ./Compiled_files/Find
gcc ./functions/String_Shell_functions/PrintFile.c -o ./Compiled_files/PrintFile
gcc ./functions/String_Shell_functions/Replace.c -o ./Compiled_files/Replace
gcc ./functions/String_Shell_functions/History.c -o ./Compiled_files/String_History
chmod +x ./Compiled_files/Find
chmod +x ./Compiled_files/PrintFile
chmod +x ./Compiled_files/Replace
chmod +x ./Compiled_files/String_History

# Run the main shell file.
./Compiled_files/Standard_shell
