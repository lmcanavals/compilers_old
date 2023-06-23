# compilers
Good old compiler theory examples

## Instalación de la última versión de llvm-project

```
pacman -Sy archlinux-keyring
pacman -Syu
pacman -S pacman-contrib
pacman -S base-devel git cmake clang llvm
pacman -S python
```

En el siguiente comando hacer `do` a cada cambio importante

```
vindiff /etc/pacman.conf /etc/pacman.conf.pacnew
```

Descargar archivo para actualizar repos

```
curl -O raw.githubusercontent.com/lmcanavals/dotfiles/main/.local/bin/localupdatemirrors
sh localupdatemirrors
```

Crear un usuario e iniciarlo

```
useradd -m <sunombredeusuario>
passwd <sunombredeusuario>
su - <sunombredeusuario>
```

Instalar LLVM, desde el repo

```
git clone --depth 1 https://github.com/llvm/llvm-project.git
cd llvm-project
mkdir build
cd build
cmake ../llvm -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX=~/llvm-project/build/ -DBUILD_SHARED_LIBS=on -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Debug
make -j4
```

En lugar del 4 en `-j4`, ponga número de procesadores disponibles.
Si sale error al final, debe quitar el -jx, para que use menos RAM.
De persistir el error, en Windows crear el archivo `.wslconfig` con esto:

```
[wsl2]

memory=8GB
swap=16GB
swapFile=C:\\Arch\\swap.vhdx
```

