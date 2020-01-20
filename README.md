Projekt w C - Karol Machoś
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
https://www.ascii-art-generator.org/


Kompilacja =>

Projekt do kompilacji wymaga gcc 9.2.0, csfml 2.5 oraz sfml 2.5
Aby skompilowac projekt można wykorzystac skrypt w pliku install.sh

Rozgrywka =>

Gra polega na osiągnięciu jak najlepszego wyniku.
Wlecenie w asteroide powoduje koniec rozgrywki.
Wlecenie w powerupy daje nastepujące korzysci:
    
    Skrzynia z podpisem "W" -> Jesli gracz nie ma zadnej amunicji,
    zmienia jej stan na 1. Jest to rakieta ktora niszczy pierwsza asteroide na swojej drodze.

    Skrzynia z podpisem "S" -> Otacza statek polem ochronnym które umożliwia wytrzymanie
    jednej kolizji z asteroidą.

Po zakonczeniu rozgrywki gracz może wpisać swoją nazwę do tabeli wyników.
Nazwa nie może zaczynać ani kończyć się spacją, oraz nie może być dłuższa niż 20 znaków.

Sterowanie =>

Strzałka w górę aby wykonać skok w górę.
Strzałka w dół aby oddać strzał rakietą (o ile aktualny stan amunicji to 1).


