# **Informe**

## **Introducción**

- **Objetivo del Proyecto**: Explorar la eficiencia de diferentes técnicas de organización de archivos para optimizar las operaciones de inserción, búsqueda y eliminación en una base de datos de League of Legends.
 
- **Descripción del Dominio de Datos**: Utilización de datos extraídos de Kaggle, específicamente de los Worlds ocurridos entre el año 2011 al 2022 del juego League of Legends, incluyendo estadísticas de jugadores, equipos y partidos.

- **Resultados Esperados**: Mejorar los tiempos de acceso y la eficiencia del almacenamiento mediante la implementación de técnicas de indexación avanzadas.

## **Técnicas Utilizadas**

### Descripción de las Técnicas de Indexación de Archivos:

- **Sequential/AVL File**: Descripción de cómo estas técnicas pueden beneficiar el acceso secuencial y/o balanceado a los datos.

- **ISAM-Sparse Index**: Utilidad de ISAM para accesos rápidos en bases de datos donde las actualizaciones son menos frecuentes.

- **Extendible Hashing**: Adecuado para situaciones con alta variabilidad en el número de entradas de datos y acceso aleatorio eficiente.

### Algoritmos de Operaciones [Usar gráficos]:

- **Inserción**:
  - Describir cómo se implementa la inserción en cada estructura, con ejemplos de código o pseudocódigo.
- **Eliminación**:
  - Explicar el método para remover entradas y cómo se manejan los espacios vacíos o las reestructuraciones necesarias.
- **Búsqueda**:
  - Detallar la implementación de búsquedas específicas y por rango, subrayando las diferencias entre las técnicas.

### Análisis Comparativo:

- Análisis basado en la cantidad de accesos a memoria secundaria requeridos por cada operación y técnica. **[incluye las dos de abajo]**

- Discutir los accesos a memoria secundaria para cada operación y cada técnica, comparando su eficiencia.

- Optimización en Memoria Secundaria: Explicar cómo se optimizó el manejo de memoria en el código para cada técnica.

### Parser SQL: 

- Explicación detallada del desarrollo y funcionamiento del parser SQL que traduce consultas a operaciones ejecutables.

## **Resultados Experimentales**

- **Cuadro y/o Gráfico Comparativo**:
  - Presentación visual del desempeño de cada técnica en términos de tiempo de ejecución y accesos a disco.

- **Discusión de Resultados**:
  - Interpretación de los resultados experimentales y su implicación en el rendimiento del sistema.

## **Conclusiones**

- Resumen de los aspectos más importantes del proyecto, incluyendo desafíos enfrentados y posibles áreas de mejora. **[incluye las dos de abajo]**

- Resumir los hallazgos principales y comentar cualquier desafío enfrentado durante la implementación.

- Mencionar posibles mejoras o expansiones futuras del proyecto.

## **Apéndices**

- **Código Fuente**:
  - [Repositorio del proyecto](https://github.com/Karu48/LoL_Worlds_2011_-_2022_DB)

- **Documentación Adicional**:
  - Enlaces a documentación de soporte, datos adicionales y recursos utilizados.