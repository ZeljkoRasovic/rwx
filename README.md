Guide:
# Instalacija
Posix (Linux, MacOS, FreeBSD, OpenBSD, NetBSD):
1. Kloniranje repozitorijuma
git clone https://github.com/ZeljkoRasovic/rwx.git
cd rwx
2. Konfigurisanje (detekcija kompajlera)
sh configure.sh
3. Kompajliranje
sh compile.sh rwx.c
4. Pokretanje
./rwx
5. Instalacija
sudo sh install.sh
6. Uklanjanje
sudo sh uninstall.sh

Windows:
1. Kloniranje repozitorijuma
git clone https://github.com/ZeljkoRasovic/rwx.git
cd rwx
2. Konfigurisanje
configure.bat
3. Kompajliranje
compile.bat rwx.c
4. Pokretanje
rwx.exe
5. Instalacija (traziti admin privilegije za dodavanje u Path)
install.bat
6. Uklanjanje
uninstall.bat

# Modifikovanje
Posix (Linux, MacOS, FreeBSD, OpenBSD, NetBSD):
cp rwx.c rwx_modified.c
# edituje rwx_modified.c
# kada sve radi što hoćemo na rwx_modified.c
# radimo sledeće kako bi napravi i primeni patch
sh patch.sh gen rwx_modified.c rwx.c moja_zakrpa.diff
sh patch.sh apply moja_zakrpa.diff rwx.c
sh compile.sh rwx.c

Windows:
cp rwx.c rwx_modified.c
edituje rwx_modified.c
kada sve radi što hoćemo na rwx_modified.c
radimo sledeće kako bi napravi i primeni patch
.\patch.bat gen rwx_modified.c rwx.c moja_zakrpa.diff
.\patch.bat apply moja_zakrpa.diff rwx.c
.\compile.bat rwx.c
