Practica 1 de IG
================

Jose Miguel Colella
-------------------

1. Cosas agregadas a la práctica
2. Como interactuar con la práctica 


1. Cosas agregadas a la práctica

Se ha creado un clase denotada 'MallaTVT', que gestiona la lectura de
un fichero ply a dos vectores stl. De estos vectores, usando 'vertex.h', 
creamos un vector de vertex flotantes y de enteros para almacenar los vertices y las caras. Además que dicha clase gestiona el modo de dibujo con
una variable entera. Esta variable entera gestiona el modo en glPolygonMode.
Teniendo esto en cuenta, se ha creado un metodo draw que dibuja el modelo ply, cambiando en base al estado de la variable entera, model.

El uso de una clase reduce el codigo que se tiene que escribir y ayuda a enteder la estructura del programa.

Se ha agregado los ficheros de file_ply_stl, y MallaTVT al makefile.

2. Para interactuar con la practica, primero ejecutamos make.

    -> make 
 
Para ejectutar la practica, hay dos opciones:
    -> ./practica1
    -> ./practica nombre_fichero_ply_sin_extension

Podemos ejecutar la practica sin argumento. Esto carga por defecto la imagen del coche. Si hay un argumento, lee el contenido del fichero ply pasado como parametro.


Al comienzo se puede visualizar un vector de flotantes en modo puntos.

Para moverse usar las flechas del teclado y pg up y pg down para alejarse y acercarse a la imagen.

Ahora para visualizar el modelo ply usamos los numeros 2,3,4,5.

    -> 2: Para visualizar en modo punto.
    -> 3. Para visualizar en modo linea.
    -> 4. Para visualizar en modo solido.
    -> 5. Para visualizar en modo ajedrez.
Ahora si queremos regresar al vector en modo punto usamos 1.

    -> 1: Para visualizar el vector en modo punto.

Si queremos salir de la aplicación podemos usar las siguientes teclas:
    
    -> q: Para salir del programa.
    -> esc: Para salir del programa.

Espero haber clarificado la interacción con los modelos generados en la práctica.
    
