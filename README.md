<h1>Space Commander Game / Projekt w C - Karol Machoś</h1>

```
     ____
    / ___| _ __   __ _  ___ ___
    \___ \| '_ \ / _` |/ __/ _ \
     ___) | |_) | (_| | (_|  __/
    |____/| .__/ \__,_|\___\___|
          |_|
      ____                                          _           
     / ___|___  _ __ ___  _ __ ___   __ _ _ __   __| | ___ _ __ 
    | |   / _ \| '_ ` _ \| '_ ` _ \ / _` | '_ \ / _` |/ _ \ '__|
    | |__| (_) | | | | | | | | | | | (_| | | | | (_| |  __/ |   
     \____\___/|_| |_| |_|_| |_| |_|\__,_|_| |_|\__,_|\___|_|   
```
Made with: https://www.ascii-art-generator.org/

<h2>PL</h2>

<h3>Kompilacja =></h3>
<p>
Projekt do kompilacji wymaga gcc 9.2.0, csfml 2.5 oraz sfml 2.5
Aby skompilowac projekt można użyć

```
make
```
</p>
<h3>Instalacja CSFML i SFML =></h3>
<p>
SFML => https://github.com/SFML/SFML<br>
CSFML => https://github.com/SFML/CSFML

Ewentualnie można skorzystać z instalacji paczki <b>libcsfml-dev</b> jesli jest on dostępny w odpowiednim dla dystrybucji Linuksa package-managerze.
</p>
<h3>Rozgrywka =></h3>
<p>
Gra polega na osiągnięciu jak najlepszego wyniku.
Wlecenie w asteroide powoduje koniec rozgrywki.
Wlecenie w powerupy daje nastepujące korzysci:
    
Skrzynia z podpisem "W" -> Jesli gracz nie ma zadnej amunicji,
zmienia jej stan na 1. Jest to rakieta ktora niszczy pierwsza asteroide na swojej drodze.

Skrzynia z podpisem "S" -> Otacza statek polem ochronnym które umożliwia wytrzymanie
jednej kolizji z asteroidą.

Po zakonczeniu rozgrywki gracz może wpisać swoją nazwę do tabeli wyników.
Nazwa nie może zaczynać ani kończyć się spacją, oraz nie może być dłuższa niż 20 znaków.
</p>
<h3>Sterowanie =></h3>
<p>
Strzałka w górę aby wykonać skok w górę.<br>
Strzałka w dół aby oddać strzał rakietą (o ile aktualny stan amunicji to 1).
</p>
<h2>ENG</h2>

<h3>Installation =></h3>
<p>
The game requires gcc 9.2.0, CSFML 2.5.0 and SFML 2.5.0 .
To install the game you can use:

```
make
```
</p>
<h3>Installation of CSFML and SFML =></h3>
<p>
SFML => https://github.com/SFML/SFML<br>
CSFML => https://github.com/SFML/CSFML

You can also just use your native package-manager to install any package containing CSFML with all its dependencies (such as for example: <b>libcsfml-dev</b>).
</p>
<h3>Gameplay =></h3>
<p>
The goal of the game is to achieve the highest score posibble, by surviving the longest without crashing your ship against the asteroids.
You can also catch 2 types of power'ups to make surving easier:

The container with "W" on it -> If you crash with the this container and you'll have no rockets on your ship already, it will add one rocket to your ship. You can then fire this rocket on asteroids, in order to destroy them.

The container with "S" on it -> It's a shield. If you crash with this container, your ship whill be surroundend by a blue force field, thus making your ship capable of surviving one crash with an asteroid.

After crashing, you will be prompted to enter your name for the highscores table. If you won't enter any letters, your score won't be saved.
</p>
<h3>Controls =></h3>
<p>
Arrow UP makes your ship jump up.<br>
Arrow DOWN fires your rocket (if you have any stored under your ship)
</p>

<h1>Screenshots<h1>
<img src="https://kamach12.github.io/images/SpaceCommanderScreen1.png">
<img src="https://kamach12.github.io/images/SpaceCommanderScreen2.png">
