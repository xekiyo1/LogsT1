main_loop(){

	echo -n "> "
	read command

	stringarr=($command)
	echo $command
	

	if [ "$command" == "list" ]; then
		files=$(eval "ls ./bin/*.out")

		echo "Lista de Comandos":
		for i in $files; do
			no_ext=${i/.out}
			echo ">	${no_ext:6}"
		done
	elif [ "$command" == "exit" ]; then
		echo "Bye-Bye"
	elif [ -f bin/${stringarr[0]}.out ]; then
		bin/${stringarr[0]}.out ${stringarr[@]:1}
	else
		echo "El comando ${stringarr[0]} no existe. ¿Compilaste los archivos?"
	fi

	
	#if false; then
	if [ "$command" != "exit" ]; then
		echo "Comando \"$command\" finalizado"
		main_loop
	fi
}

main_loop