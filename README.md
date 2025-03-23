# Proyecto de Mapeo de Adyacencias entre Entidades

Este proyecto está diseñado para analizar y mapear relaciones de adyacencia entre entidades (como países, ciudades, nodos, etc.) utilizando una matriz de adyacencias y un conjunto de mapas hash que relacionan los nombres de las entidades con identificadores numéricos. El proyecto consta de dos archivos principales: `main.cc` y `ObtenerDatos.cc`, que se encargan de la lógica principal y la generación de datos respectivamente.

## Descripción del Proyecto

El proyecto permite:
1. **Generar datos de adyacencia**: A partir de un archivo de texto que contiene las relaciones de adyacencia entre entidades, se generan archivos de mapas hash y una matriz de adyacencias.
2. **Consultar adyacencias**: Dada una entidad, se pueden listar todas las entidades adyacentes.
3. **Verificar si dos entidades son adyacentes**: Se puede verificar si dos entidades específicas son adyacentes.
4. **Encontrar la ruta más corta entre dos entidades**: Se puede encontrar la ruta más corta entre dos entidades, excluyendo ciertas entidades si es necesario.

## Estructura del Proyecto

- **main.cc**: Contiene la lógica principal del programa, incluyendo funciones para leer mapas hash y matrices de adyacencias, verificar adyacencias, y encontrar rutas óptimas entre entidades.
- **ObtenerDatos.cc**: Contiene funciones para generar los archivos de mapas hash y la matriz de adyacencias a partir de un archivo de texto que contiene las relaciones de adyacencia.

## Archivos Generados

El proyecto genera los siguientes archivos en la carpeta `info`:
- **hashMapIntToString.txt**: Mapa que relaciona identificadores numéricos con nombres de entidades.
- **hashMapStringToInt.txt**: Mapa que relaciona nombres de entidades con identificadores numéricos.
- **matriz_de_adyacencia.txt**: Matriz de adyacencias que indica las relaciones entre entidades.

## Uso



