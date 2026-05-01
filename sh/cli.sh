main_loop(){

	echo -n "> "
	read command

	stringarr=($command)
	
	if [ -f bin/${stringarr[0]}.out ]; then
		echo "Existe"
	else
		echo "No existe"
	fi

	if [ "$command" != "exit" ]; then
		main_loop
	fi
}

main_loop