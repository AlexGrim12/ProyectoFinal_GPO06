# Proyecto final: Viajes espaciales y evolución de especies intergalácticas
# Final project: Space travel and the evolution of intergalactic species

Computación Gráfica e Interacción Humano Computadora · Computer Graphics and Human-Computer Interaction
Grupo de teoría / Theory group: 06 · Grupo de laboratorio / Lab group: 13 · Semestre / Semester: 2027-1
Números de cuenta / Account numbers: 318068932, 320282098, 320342330, 320005864

## Español

Ambiente virtual interactivo en C++ con OpenGL 3.3: dos planetas (Halo y Space Park) conectados por una estación espacial, con cohete, tráfico de naves, carrera, seis cámaras e iluminación con ciclo de día y noche.

### Cómo ejecutarlo (Windows 64 bits)
1. Abra la carpeta `Ejecutable/`.
2. Haga doble clic en `ProyectoFinal_GPO06.exe` (tarda unos segundos en cargar los modelos).
3. No mueva `Models`, `Textures`, `shaders` ni las DLL: el programa usa rutas relativas.

### Controles
`W A S D` + ratón: moverse · `M`: cambiar de cámara · `P`: viajar entre planetas · `1`: lanzar el cohete · `2`: paneles solares · `3`: baile de BMO · `C`: carrusel · `L` y `H`: luces · `R`: salida de la carrera · `Esc`: salir.

### Cómo compilarlo
1. Abra `Codigo/ProyectoFinal.sln` en Visual Studio 2022 o posterior (carga de trabajo "Desarrollo de escritorio con C++").
2. Seleccione **Release | x64** y compile. El ejecutable se genera en `Ejecutable/`.
3. Las bibliotecas (GLFW, GLEW, Assimp, GLM) vienen en `Codigo/ThirdParty/`; todas las rutas son relativas.

### Estructura
| Carpeta | Contenido |
|---|---|
| `Ejecutable/` | Programa listo para correr (Release), con sus DLL, modelos, texturas y shaders. Sin código fuente. |
| `Codigo/` | Código fuente (`src/`), proyecto de Visual Studio y bibliotecas (`ThirdParty/`). |
| `Documentacion/` | Documentación individual de cada integrante, por número de cuenta (manual técnico y manual de usuario, en español e inglés). |

## English

Interactive virtual environment in C++ with OpenGL 3.3: two planets (Halo and Space Park) linked by a space station, with a rocket, ship traffic, a race, six cameras and lighting with a day/night cycle.

### How to run it (64-bit Windows)
1. Open the `Ejecutable/` folder.
2. Double-click `ProyectoFinal_GPO06.exe` (loading the models takes a few seconds).
3. Do not move `Models`, `Textures`, `shaders` or the DLLs: the program uses relative paths.

### Controls
`W A S D` + mouse: move · `M`: switch camera · `P`: travel between planets · `1`: launch the rocket · `2`: solar panels · `3`: BMO dance · `C`: carousel · `L` and `H`: lights · `R`: race start · `Esc`: exit.

### How to build it
1. Open `Codigo/ProyectoFinal.sln` in Visual Studio 2022 or later ("Desktop development with C++" workload).
2. Select **Release | x64** and build. The executable is written to `Ejecutable/`.
3. Libraries (GLFW, GLEW, Assimp, GLM) are in `Codigo/ThirdParty/`; all paths are relative.

### Structure
| Folder | Content |
|---|---|
| `Ejecutable/` | Ready-to-run program (Release) with its DLLs, models, textures and shaders. No source code. |
| `Codigo/` | Source code (`src/`), Visual Studio project and libraries (`ThirdParty/`). |
| `Documentacion/` | Each member’s individual documentation, by account number (technical and user manuals, in Spanish and English). |
