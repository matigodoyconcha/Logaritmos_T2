
# Tarea 2 CC4102 
## Comparación de  Cola de Fibonacci y Heap utilizando algoritmo de Dijkstra 
Integrantes: 
- Matías Godoy C.
- Damián González G.
- Claudio Morel M.

### Para ejecutar el código:

Debe exitir una carpeta llamada Testing, donde se almacenarán los resultados de la experimentación.

Usando un compilador de c++ como g++ se necesita compilar el archivo main.cpp que contiene la función main junto con las importaciones de todos los otros archivos cpp necesarios. Para esto se puede ejecutar el comando:

```
g++ main.cpp -o ejecutable
```
Para ejecutar ahora el archivo se necesita usar:

```
./ejecutable
```
Este programa, al ejecutarse, correrá 50 veces cada algoritmo con el mismo grafo con los i= [10,12,14] y j=[16,...,22] únicamente si es que la cantida de aristas se pueden realizar en la cantidad de nodos.


### Resultados

Al momento de terminar de ejecutarse el código, se tendrá la carpeta de Testing con archivos de texto, en donde su nombre indica la el tipo de estructura que utilizó (Heap/Fibonacci) y los parametros i,j y en su contenido, está el tiempo de ejecución de cada iteración.

Además se incluye un archivo llamado Promedios.txt, el cual contiene los promedios de las 50 ejecuciones , este viene en el siguiente formato: Estructura;i;j;Time(ms)

