# Proyecto-Progra-3-CNN

instrucciones para conseguir el mnist dataset:

(si estas en windows el tutorial de abajo no funciona. solo si estas en linux. si estas en windows aqui esta el link de drive con los archivos)

https://drive.google.com/drive/folders/1XqO0I2Rn7bwNorV7KZh8o73m22BYl3-e?usp=share_link

(extrae los archivos en la carpeta "dataset")

1. entra a tu ide (vscode, clion, etc) y entra al terminal
![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/1499d0ca-38f1-40f6-956b-343ef299b8e7)

2. navega a la carpeta "dataset" usando el comando ```cd dataset```
![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/1bb469f6-a5be-4cc7-b38e-580b467ae7a2)

3. ejecuta los siguientes comandos para descargar el dataset:
```
wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
wget http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz
```
![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/851a617f-fc50-4c69-ae30-1649c0550cf6)

4. la carpeta deberia ahora verse asi

![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/df82415f-fb0a-4549-9024-53221c34625d)

5. extrae los archivos .gz usando los siguientes comandos
```
gzip -d train-images-idx3-ubyte.gz
gzip -d train-labels-idx1-ubyte.gz
gzip -d t10k-images-idx3-ubyte.gz
gzip -d t10k-labels-idx1-ubyte.gz
```
![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/08c23c2a-138c-4d06-8192-515e44ffa814)

6. la carpeta ahora deberia verse asi
 
![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/8750b9a6-af85-4d64-90af-dd1caf70d1a4)


7. en main cambia el string directory a tu direccion donde se encuentra ubicada la carpeta datasets q sino por algun motivo no funciona
![image](https://github.com/alejandro-ore/Proyecto-Progra-3-CNN/assets/104222679/08883219-fff2-42ba-98d7-8f14f8376536)

y bueno eso es todo, cualquier duda avisen
