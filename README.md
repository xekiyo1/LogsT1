# Tarea 1 Diseño y Análisis de Algoritmos "R-Trees" y Bulkloading

El presente archivo muestra como ejecutar el proyecto y armar experimentos de bulkloading

## Requisitos

- Un sistema operativo basado en Unix que cuente con los siguientes comandos/librerias
	+ grep
	+ ls
	+ rm
	+ gcc (version >= 11.4)
	+ xargs (version >= 4.8.0)
	+ chmod
	+ make
	+ test

- Agregar los permisos necesarios para que el archivo bash del cli pueda correr. Esto se logra utilizando chmod para agregar permisos de lectura y ejecución como se ve en el código de a continuación.
	```bash
	chmod +rx ./sh/cli.sh
	```

	Opcionalemte, se puede utilizar el comando "make allow-cli"