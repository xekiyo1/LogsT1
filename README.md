# Tarea 1 Diseño y Análisis de Algoritmos "R-Trees" y Bulkloading

El presente programa ejecuta pruebas de rendimiento para dos algoritmos de construcción de R-Trees, en particular, Nearest-X y STR.
El objetivo del proyecto es la comparación en tiempo de construcción y de búsqueda de ambos algoritmos a partir de un
dataset de puntos de Europa y otro aleatorio con valores normalizados.

NOTA: Los datasets deben descargarse a mano, pues git no permite la subida de archivos pesados por defecto. El enlace es el siguiente:


## Requisitos

- Los dataset de puntos en formato binario (europa.bin, random.bin, europa_bonus.bin) deben estar en la carpeta
/bin/data/, se pueden descargar en el siguiente enlace: https://github.com/claugaete/tarea1-cc4102-2026-1
- Se requiere un sistema operativo basado en Unix que cuente con los siguientes comandos/librerias
	+ grep
	+ ls
	+ rm
	+ gcc (version >= 11.4)
	+ xargs (version >= 4.8.0)
	+ chmod
	+ make
	+ test

- Opcional: Agregar los permisos necesarios para que el archivo bash del cli pueda correr. Esto se logra utilizando chmod para agregar permisos de lectura y ejecución como se ve en el código de a continuación si se quieren guardar los logs, aunque esto no fue necesario en el proyecto final.
	```bash
	chmod +rx ./sh/cli.sh
	```

	También, se puede utilizar el comando "make allow-cli"

## Correr el programa
Para correr la tarea, basta con ir al directorio desde una terminal y correr
- **make run** (equivalente a: make run-construct && make run-query)

Esto creará diversos archivos .csv con las métricas obtenidas de la creación de los árboles,
mientras imprime en tiempo real la información que va rescatando.

Si además se quiere realizar la query del bonus, usar:
- **make run-all** (equivalente a: make run && make run-bonus)

Que realiza una consulta predeterminada en los datos de europa_bonus.bin.

A continuación se describe la función de cada comando individual.

### make run-construct
Compila y corre el algoritmo de creación de R-Trees, creando árboles con el dataset de europa y random con ambos algoritmos.

Realiza esto tomando los primeros N puntos, donde N son potencias de dos desde $2^{14}$ a $2^{24}$ y registra los tiempos
creación en _tiemposCreacion.csv_. Los árboles resultantes usando la mayor cantidad de puntos se guardan en _bin/data/trees/_.
### make run-query
Compila y corre las queries de prueba, generando cuadrados aleatorios de distintos tamaños y guardando las lecturas de
disco realizadas en _lecturas_disco.csv_ y la cantidad de puntos encontrados en _puntos_encontrados.csv_.

Esto se realiza para los árboles resultantes de make run-construct.

### make run-bonus
Corre la query del bonus, construyendo el árbol de europa_bonus.bin y realizando una consulta predeterminada en ella.
Los puntos encontrados se guardan en _customQuery.csv_.

## Experimentación personalizada
Se puede observar que '**make run-bonus**' crea los ejecutables /bin/commands/custom_build.out y /bin/commands/custom_query.out,
los cuales son un resultado de **make compile-bonus**. Estos permiten crear RTrees y consultas personalizadas
sin necesidad de modificar el código, por lo que en caso de ser útil, se puede usar:

- ./bin/commands/custom_build.out [nombre] [metodo] [N]

Donde "nombre" es el archivo binario de puntos almacenado en bin/data/ (ejemplo: europa.bin),
"metodo" es NX para usar Nearest-X o STR para usar el mismo STR, y $N$ es la potencia de dos que se
usará como cota máxima al extraer los puntos (ejemplo: $N=7$ significa que se usarán $2^7$ puntos).

- ./bin/commands/custom_query.out [nombre] [x1] [y1] [x2] [y2]

Donde "nombre" es el archivo binario en /bin/trees/ con el RTree a utilizar (ejemplo: EuropaSTR.bin) y
el resto de variables describen el rango de puntos a buscar en el archivo ($x1 < x2$ , $y1 < y2$).