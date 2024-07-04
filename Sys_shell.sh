#standard files
cc Standard_shell.c -o Standard_shell
cc Math_shell.c -o Math_shell
cc Logic_shell.c -o Logic_shell
cc String_shell.c -o String_shell
cc exit.c -o exit
#math files
#needed to add -lm so that the program compiles properly
cc Sqrt.c -o Sqrt -lm
cc Power.c -o Power -lm
cc Solve.c -o Solve -lm
#logic files
cc Highbit.c -o Highbit
cc DectoBin.c -o DectoBin
cc DectoHex.c -o DectoHex
#string files
cc PrintFile.c -o PrintFile
cc Find.c -o Find
cc Replace.c -o Replace
#common history
cc History.c -o History
#create commands folder if it dosent exist
if [ ! -d "Commands" ]; then
	mkdir "Commands"
fi
./Standard_shell

