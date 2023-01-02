<h3 align = "center"> Proyecto Arduino </h3>

---
<p align = "center"> En este repositorio se encuentra el código de Arduino capaz de enviar beacons
    <br>
</p>

## 📝 Tabla de contenido

- [Introducción](#Getting_started)
- [Tests](#tests)

## 🏁 Comenzando <a name = "getting_started"> </a>

Estas instrucciones le proporcionarán una copia del proyecto en funcionamiento en su ordenador con fines de desarrollo y prueba

### Requisitos previos

Qué necesita para instalar el software y cómo instalarlo.

Hay que instalar:

```
[Arduino IDE](https://www.arduino.cc/en/software).
```

A su vez hay que instalar dirigiendonos dentro del IDE de Arduino a:
```
Arduino -> Preferencias -> Gestor de Placas Adicionales. 
```
Pegar este enlace

```
https://www.adafruit.com/package_adafruit_index.json
```
Depués hay que buscar nRF52 e instalar “Adafruit nRF52 by Adafruit”, que se encuentra aquí:
```
Herramientas -> Placa -> Gestor de Placas.
```

### Instalación

Tras haber completa la instalación del IDE y haber elegido la placa y el puerto correspondiente, solo queda ubicarnos en la carpeta que contiene el programa y ejecutar el código con nombre:

```
Beacons.ino
```

## 🔧 Ejecutando las pruebas <a name = "tests"> </a>

Para comprobar que funciona, ejecutamos el programa y abrimos en el móvil una aplicación capaz de detectar beacons como podría ser nRF Connect, activamos el bluettoth y buscamos entre la lista de beacons uno con el nombre

```
GTI-3ARoberto
```
