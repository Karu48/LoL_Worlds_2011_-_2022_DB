# Informe Base de Datos League of Legends

**Link al Github:** 

[https://github.com/Karu48/LoL_Worlds_2011_-_2022_DB](https://github.com/Karu48/LoL_Worlds_2011_-_2022_DB)

**En formato pdf en la repo**

## Introducción

El proyecto tiene como objetivo aplicar técnicas de organización e indexación de archivos a conjuntos de datos del juego League of Legends obtenidos de la plataforma Kaggle. La base de datos consta de tres tablas principales: championStats.csv, matchStats.csv y playerStats.csv.

### Descripción del dominio de datos:

- **championStats.csv:** Esta tabla proporciona estadísticas detalladas sobre los campeones del juego, incluyendo su rendimiento en partidos, ratio de selección/ban, participación en asesinatos, oro obtenido, daño infligido y otras métricas relevantes. (Un campeón a la vez es un jugador)
- **matchStats.csv:** Aquí se almacena información sobre partidos, incluyendo la fecha del evento, los equipos participantes, los resultados del enfrentamiento, las selecciones y los bans de campeones por equipo, y las estadísticas de juego. (Los matches se dan entre 2 equipos)
- **playerStats.csv:** Esta tabla contiene datos sobre los jugadores, incluyendo el equipo al que pertenecen, las estadísticas individuales de juego como asesinatos, muertes, asistencias, oro obtenido, daño infligido, entre otros.

### Resultados Esperados al aplicar técnicas de indexación:

- En primer lugar, se espera una mejora en el rendimiento de consultas,  especialmente en aquellas que se involucra búsquedas, filtrado y ordenamiento, ya que los índices permiten realizar búsquedas más rápidas y eficientes en grandes conjuntos de datos.
- Además, se espera una gran optimización del uso de recursos, ya que al utilizar índices, se puede optimizar el uso de acceso a recursos como la memoria y la CPU al minimizar la cantidad de datos que deben ser procesados durante las consultas.
- Finalmente, esperamos mejorar y garantizar escalabilidad, pues la indexación facilita la escalabilidad de la base de datos al permitir un acceso rápido a los datos tomando en cuenta que la información almacenada irá creciendo en el tiempo.

## Técnicas Utilizadas:

## Sequential File:

- El Sequential File es una estructura de almacenamiento de datos donde los registros se organizan uno tras otro, generalmente en orden de inserción. Para esta implementación utilizaremos el método de eliminación "move the last" el cual implica reemplazar el registro que se desea eliminar con el último registro del archivo y luego reducir el tamaño del archivo en uno. Esta técnica evita la reorganización de los registros restantes después de una eliminación, lo que puede ser eficiente en términos de tiempo y recursos.

- Explique el algoritmo de inserción, eliminación y búsqueda (use gráficos para un mayor entendimiento)

### `Insert`

La inserción de registros en un Sequential File implica agregar nuevos registros al final del archivo. Para ello, primero verificamos la disponibilidad de espacio en el archivo para almacenar el nuevo registro. Si hay suficiente espacio, el registro se escribe en el archivo después del último registro existente, si no, se lleva a un archivo auxiliar y actualizar los punteros existentes.

- Insert en un **archivo auxiliar**:

![Untitled](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Untitled.png)

### `Delete`

Para eliminar registros utilizamos el método “move the last” en el archivo auxiliar, el cual consiste en mover el último registro a la posición del registro que queremos eliminar. Para ello, primero identificamos el registro que deseamos eliminar y luego ubicamos el último registro en el archivo. Luego, copiamos el contenido del último registro en la posición del registro que queremos eliminar y ajustamos los punteros necesarios para reflejar el cambio. Finalmente, reducimos el tamaño del archivo. En el caso del archivo principal, se desplazan todos los registros debajo del registro a eliminar, de forma que se mantiene el orden en el archivo principal.

- Eliminación de un registro

![Untitled](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Untitled%201.png)

![Untitled](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Untitled%202.png)

### `Search`

La función realiza una búsqueda binaria en un archivo binario organizado secuencialmente para encontrar un registro cuyo key coincida con el key proporcionado. Comienza inicializando los índices (comenzando desde la posición 1 y la posición -1), luego realiza iteraciones de búsqueda binaria hasta que el índice low sea menor o igual que el índice high. Además, calcula el índice medio, lee el registro correspondiente desde el archivo y compara las claves. Si encuentra una coincidencia, devuelve el registro. Si no, ajusta los índices low y high según la comparación de claves y continúa el proceso hasta que se encuentre un registro coincidente o se haya explorado completamente el rango de búsqueda. Si no se encuentra, devuelve un registro vacío.

- Buscando un registro sin archivo auxiliar
    
    ![Screen Shot 2024-05-18 at 3.16.58 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_3.16.58_PM.png)
    

### `Range Search`

Aplicamos una búsqueda por rango eficiente, la cual  también realiza una búsqueda binaria para encontrar el rango de registros cuyas claves estén dentro del rango especificado por las claves `key1` y `key2`. Comienza buscando la posición del primer registro que coincide con `key1`. Luego, busca registros adicionales hacia adelante desde esa posición hasta encontrar aquellos cuyas claves superen `key2`. Mientras busca, va agregando los registros que cumplen con la condición al vector de registros registers. Luego, busca registros adicionales en un archivo auxiliar para manejar registros que podrían estar ubicados fuera del rango de búsqueda principal, y los agrega al vector registers si es que también cumplen con la condición del rango. Finalmente, devuelve el vector que contiene todos los registros dentro del rango especificado.

- Buscando un rango de registros con archivo auxiliar (season 1)

Asigna los punteros low, mid y high para realizar la búsqueda binaria como en el search. Una vez que encuentra el key1, recorre todo hasta llegar al key2. En este caso, tuvo que pasar por el archivo auxiliar y añadir el registro al resultado.

![Screen Shot 2024-05-18 at 3.25.02 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_3.25.02_PM.png)

## ISAM:

- El **ISAM (Indexed Sequential Access Method)** es una técnica de indexación de archivos que organiza los datos de manera secuencial en el archivo principal y crea un índice secundario para permitir un acceso aleatorio eficiente a los registros. El índice secundario contiene referencias a las ubicaciones físicas de los registros en el archivo principal, lo que hace más eficiente la recuperación de datos mediante claves de búsqueda (search keys). Esto resulta en tiempos de acceso rápidos y eficientes para las operaciones de inserción, eliminación y búsqueda.
- Explique el algoritmo de inserción, eliminación y búsqueda (use gráficos para un mayor entendimiento)

### `Insert`

La función insert, en primer lugar, busca la posición de inserción del nuevo registro utilizando una búsqueda binaria en el archivo de índice, de modo que los registros estén ordenados por su clave primaria. Después de encontrar la posición adecuada, escribe el nuevo registro en el archivo de datos y actualiza el archivo de índice con la nueva entrada. Si es necesario, reorganiza el archivo de índice para mantener la ordenación por clave primaria.

- Insertamos nuevos registros:

![Screen Shot 2024-05-18 at 6.13.50 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_6.13.50_PM.png)

### `Delete`

El método remove, elimina un registro basándose en su clave primaria. Primero, busca la posición del registro que se va a eliminar utilizando una búsqueda binaria en el archivo de índice. Luego, lee los registros del archivo de datos y del archivo de índice antes y después del registro que se va a eliminar, y los guarda en vectores. Después de eliminar el registro, reescribe los archivos de datos y de índice utilizando los vectores actualizados, eliminando así el registro del almacenamiento del ISAM.

- Hacemos el recorrido desde los overflow pages hasta los primary leaf pages y actualizamos la información luego de la eliminación

![Screen Shot 2024-05-18 at 6.20.55 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_6.20.55_PM.png)

### `Search`

La función search, busca un registro en el  ISAM utilizando su clave primaria. Realiza una búsqueda binaria en el archivo de índice para encontrar la posición del registro correspondiente. Una vez que se encuentra la posición, se lee el registro del archivo de datos en la posición especificada y se devuelve como un valor opcional. Si el registro no se encuentra, se devuelve un valor NULL.

- Aplicamos binary search en cada nodo empezando desde la raíz.
- Seguimos en cada pointer al siguiente nivel hasta encontrar el elemento
    
    ![Screen Shot 2024-05-18 at 6.27.10 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_6.27.10_PM.png)
    

### `Range Search`

El método rangeSearch, es básicamente como la función search, esta busca registros en un rango específico de claves primarias en la estructura ISAM. Utiliza una búsqueda binaria para encontrar la posición del primer registro en el rango y luego lee los registros del archivo de datos y del archivo de índice consecutivamente hasta que se alcance el final del rango. Los registros encontrados se devuelven como un vector de registros.

![Screen Shot 2024-05-18 at 6.30.52 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_6.30.52_PM.png)

## Extendible Hashing:

- El **Extendible Hashing** es una técnica que utiliza una función hash para asignar claves de búsqueda. Ofrece una mayor eficiencia en términos de espacio de almacenamiento, ya que las colisiones de hash se gestionan mediante técnicas de expansión de la tabla hash. Esto resulta en una distribución uniforme de los registros y una menor necesidad de rehashing. Al principio, los datos se dividen en buckets que aumentan de tamaño según sea necesario para evitar los desbordamientos, lo que contribuye a un mejor rendimiento en operaciones de inserción, eliminación y búsqueda.

### `Insert`

En primer lugar, la función calcula el valor hash del registro a insertar y determina la profundidad de búsqueda. Luego, busca el bucket correspondiente utilizando los bits del valor hash y carga el bucket desde el almacenamiento. Si hay una cadena de buckets asociada al bucket encontrado, se sigue la cadena hasta el último overflow bucket. Luego, el registro se inserta en el bucket y se guarda de nuevo en el almacenamiento. Si el bucket está lleno después de la inserción, se realiza una división del bucket para manejar el overflow, ajustando las variables necesarias. 

![Screen Shot 2024-05-18 at 2.00.43 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_2.00.43_PM.png)

### `Delete`

La función remove elimina un registro específico de una estructura de datos, representada aquí como un array llamado records. Comienza iterando sobre todos los elementos del array y compara cada uno con el registro proporcionado. Cuando encuentra una coincidencia, mueve todos los elementos restantes del array una posición hacia atrás para llenar el espacio dejado por el registro eliminado. Luego, asigna NULL al último elemento del array y decrementa su tamaño. Si el tamaño del array se reduce a cero después de eliminar el registro, se elimina el bucket actual de la estructura de datos. 

- **Caso 1:** Eliminar un elemento en un overflow bucket

![Screen Shot 2024-05-18 at 2.01.07 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_2.01.07_PM.png)

- **Caso 2:** Eliminar un elemento en un bucket interno

![Screen Shot 2024-05-18 at 2.02.41 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_2.02.41_PM.png)

### `Search`

En Extendible Hashing, la función search comienza calculando el valor hash del registro objetivo. Utiliza el sufijo del hash correspondiente a la profundidad global para localizar el bucket en el directorio. Una vez identificado el bucket, se carga desde el almacenamiento secundario y se verifica que el registro exista. Si el bucket tiene overflow buckets, estas se recorren hasta encontrar el registro o agotar las referencias. 

![Screen Shot 2024-05-18 at 2.08.20 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_2.08.20_PM.png)

### `Range Search`

Por otro lado, en la búsqueda por rango se calculan los valores hash para los límites inferior y superior del rango. Luego, se identifican y cargan todos los buckets dentro de este rango de valores hash. Cada bucket se examina para encontrar y devolver todos los registros que caen dentro del rango especificado.

![Screen Shot 2024-05-18 at 2.14.07 PM.png](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Screen_Shot_2024-05-18_at_2.14.07_PM.png)

## Análisis Comparativo Teórico:

- En base a los **accesos a memoria secundaria**

| Método/ Técnica | Sequential File | ISAM | Extendible Hashing |
| --- | --- | --- | --- |
| Insert | Acceso frecuente a memoria secundaria debido a la necesidad de encontrar la posición adecuada para la inserción. La técnica de move the last puede ser rápida para la inserción y eliminación, pero requiere buscar y actualizar el registro eliminado. | Menos accesos a memoria secundaria debido a los índices y acceso directo a los bloques de datos. | Acceso a memoria secundaria frecuente debido a la posible necesidad de hacer split y rehashing a los buckets. |
| Delete | Acceso frecuente a memoria secundaria debido a la necesidad de reorganizar el archivo después de la eliminación.  | Menos accesos a memoria secundaria debido a los índices y acceso directo a los bloques de datos. | Acceso a memoria secundaria frecuente debido a la posible necesidad de hacer split y rehashing a los buckets. |
| Search | El acceso a memoria secundaria es dependiente de la estructura del archivo y el método de búsqueda utilizado.  | El acceso a memoria secundaria depende del número de bloques de índice a recorrer. Normalmente es más eficiente que un árbol para volúmenes grandes de datos. | Depende del cálculo del hash y la búsqueda dentro del bucket, generalmente es más eficiente para conjuntos de datos bien distribuidos. |

## Parser SQL

- Explicar claramente cómo se realizó el parser del SQL.

## Resultados Experimentales:

- Cuadro y/o gráfico comparativo de desempeño de las técnicas de indexación de archivos sobre el dominio de datos. **Tanto para inserción como para búsqueda**.
- Considerar dos métricas: total de accesos a disco duro (read & write) y tiempo de ejecución en milisegundos.
- Discusión y análisis de los resultados experimentales.

**EXTENDIBLE**

| Cantidad de Datos | Tiempo de Ejecución | Accessos |
| --- | --- | --- |
| 100 | 82ms | 100 |
| 500 | 544ms | 1000 |
| 1000 | 1319ms | 2000 |

**ISAM** 

| Cantidad de Datos | Tiempo de Ejecución | Read | Write |
| --- | --- | --- | --- |
| 10 | 2ms | 50 | 200 |
| 100 | 49ms | 100 | 400 |
| 1000 | 486ms | 500 | 1500 |

### Extendible Hashing

| Cantidad de Datos | Tiempo de Ejecución | Accessos |
| --- | --- | --- |
| 100 | 196ms | 100 |
| 500 | 1309ms | 500 |
| 1000 | 24194ms | 1000 |

![Untitled](Informe%20Base%20de%20Datos%20League%20of%20Legends%20fb0fa57b5ba34ce197342302b234b783/Untitled%203.png)

Aparenta tener un crecimiento lineal con un $R^2 = 0,998$.

- **Documentación Adicional**:
  - [Documentacion de rapidcsv](https://github.com/d99kris/rapidcsv)
