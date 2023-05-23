#include <iostream>
#include <vector>  //trabajar con vectores
#include <cstdlib> //numeros aleatorios
#include <ctime> //para trabajar con tiempo y fechas
#include <algorithm> //algoritmos de manipulacion de datos
//encabezados
#include "Character.h"
#include "Enemy.h"
#include "Boos.h"

//manejar funciones de windows como el clear screen que añadire
#ifdef _WIN32
#include <Windows.h>
#endif

using namespace std;

//cuadricula del tablero
const int WIDTH = 20;
const int HEIGHT = 10;

//para que se limpe la pantalla cuando ejecuto una orden
void clearScreen()
{
    cout << "\033[2J\033[1;1H";
}

//Personalizar color texto
#ifdef _WIN32
void setColor(int color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#endif

class Game
{
private:
    vector<vector<char>> board; //tablero del juego
    Character character;//jugdor en el tablero
    vector<Enemy> enemies; //enemigo en el tablero
    pair<int, int> exit; //para la salida del tablero
    Boos boss; //jefe final

public:
    Game()
        : board(WIDTH, vector<char>(HEIGHT, '.')), boss(7, 7) {} //inizializa el tablero y ek jefe

    void displayBoard() const
    {
        clearScreen();

        for (int i = HEIGHT - 1; i >= 0; i--) //recoro las filas del tablero
        {
            for (int j = 0; j < WIDTH; j++) //recoro las columnas del tablero
            {
                if (j == character.getX() && i == character.getY()) //para que se vea en todo momento donde esta el personaje
                {
                    setColor(14); //doy color al personaje
                    cout << '@' << ' '; //digo que es un @ para identificarlo
                    setColor(7); //cuando se mueva el personaje vuelve al blanco
                }
                else if (j == exit.first && i == exit.second) //la salida
                {
                    cout << 'S' << ' '; //he añadido esto por si se quiere ver la saliuda
                    setColor(7); //la devuelvo de nuevo al color blanco
                }
                else
                {
                    bool enemyPresent = false;
                    for (const Enemy& enemy : enemies) //verifica en todo momento si hay un enemigo en la casilla
                    {
                        if (j == enemy.getX() && i == enemy.getY()) //si concide y hay un enemigo entonces
                        {
                            enemyPresent = true; //vuelvo a tru en enemyPersent
                            setColor(7); //sigo estableciendo que mantenga el color
                            cout << '.' << ' '; // Escondo el enemig en el tablro con un . para que no se vea esto lo tengo para verificar que se crearan
                            break;
                        }
                    }
                    if (!enemyPresent) //si en la casilla no hay enemigo
                    {
                        cout << board[j][i] << ' '; //genero espacios en el tablero
                    }
                }
            }
            cout << endl;
        }

        setColor(12); //doy color a la vida del jugador
        cout << "Vida del jugador: " << character.getHealth() << endl; //muestro en todo momento la vida del jugador
        setColor(13); //doy color a la vida del Boos
        cout << "Vida del jefe final: " << boss.getHealth() << endl; //muestro en todo momento la vida del boos
        setColor(7); //doy color predeterminado
        cout << endl;
    }

    void generateEnemies()
    {
        int numEnemies = rand() % 6 + 7; // creo de forma aleatoria entre 7 y 12 enemigo

        for (int i = 0; i < numEnemies; i++) //genero los enemigos dentro del juego
        {
            int x = rand() % WIDTH; //que sea de forma aleatoria de lado
            int y = rand() % HEIGHT; //que sea de forma aleatoria de alto

            enemies.emplace_back(x, y); //agrago al enemigo a la lista y guardo la posicion
        }
    }

    void generateExit()
    {
        int x = rand() % WIDTH; //estableco de forma aleatoria el ancho de la salida
        int y = rand() % HEIGHT; //establezco de forma aleatoria el alto de la salida

        exit = make_pair(x, y); //guardo donde estara
    }

    void run()
    {
        generateEnemies(); //ejecuto generar enemigos
        generateExit(); //ejecuto generar salida

        displayBoard(); //ejecuto el tablero

        while (true) //ejecuto el bucle de forma infinita
        {
            if (character.getX() == exit.first && character.getY() == exit.second) //si encuentro la salida ...
            {
                cout << "¡Has encontrado la salida! " << endl;
                cout << "Ahora te enfrentaras al jefe final" << endl;
                batalla(); //inicio batalla
                break;
            }

            if (character.getHealth() <= 0) //si el jugador llega a 0
            {
                cout << "¡Tu personaje ha sido derrotado! ¡Has perdido el juego!" << endl;
                break;
            }

            if (boss.getHealth() <= 0) //si el boos llega a 0
            {
                cout << "¡Has derrotado al jefe final! ¡Has ganado el juego!" << endl;
                break;
            }

            char direction; // quiero que solo me des una letra para la direccion
            cout << "Ingresa una direccion (w/a/s/d): "; //ejecute un texto para que se sepa las letras
            cin >> direction; //printeo y recogo la direccion

            int newX = character.getX(); //establezco la posicion
            int newY = character.getY(); //establezco la posicion

            switch (direction) //creacion de un switch con la direccion que hemos recogido anteriormente
            {
            case 'w':
                newY++; //si es w ira para arriba
                break;
            case 'a':
                newX--; //si es a para la izquierda
                break;
            case 's':
                newY--; //si es s para abajo
                break;
            case 'd':
                newX++; //si es d para la derecha
                break;
            default:
                break; //otra opcion no te dejara
            }

            bool validMove = true; // si el movimiento es valido

            if (newX < 0 || newX >= WIDTH || newY < 0 || newY >= HEIGHT)
            {
                validMove = false; // si el movimiento no es valido me devolvera false
            }
            else
            {
                character.setX(newX); //en cambio si esta bien se establece una nueva posicion
                character.setY(newY); //en cambio si esta bien se establece una nueva posicion
            }

            displayBoard(); //y se ejecuta de nuevo el tablero

            if (!validMove) //si llegara a ser falso como he dicho anteriormente saltara el siguiente mesnaje
            {
                cout << "Movimiento no valido. Intentalo de nuevo." << endl;
                continue;
            }

            for (Enemy& enemy : enemies)
            {
                if (newX == enemy.getX() && newY == enemy.getY()) //verifico posiciones del tablero junto a las del jugador
                {
                    fight(enemy); // si es corecta lucharan
                    break;
                }
            }

        }
    }

    void fight(Character& enemy) //lucha contra enemigo
    {
        while (character.getHealth() > 0 && enemy.getHealth() > 0) //lo ejecuto mientras que la vida sea mayor que 0 asi si un enemigo es menos (por lo tanto lo he matado anteriormente) no se iniciara
        {
            int enemyAttack = enemy.getAttack(); //ejecuto el ataque del enemigo
            int characterAttack =character.getAttack(); //despuyes ejecuto el ataque del heroe

            character.setHealth(character.getHealth() - enemyAttack); //resto la vida al enemigo
            enemy.setHealth(enemy.getHealth() - characterAttack); //resto la vida al heroe

            displayBoard(); //vuelvo a cargar el tablero
        }
    }

    void batalla() //batalla contra el jeve
    {
        setColor(11); //doy un color a toda la batalla
        cout << "¡Has encontrado la salida! ¡Te enfrentaras al jefe final!" << endl;
        cout << "¡Preparate para el enfrentamiento!" << endl;
        cout << endl;

        bool isPlayerTurn = true; //establezco el turno del jugador

        while (character.getHealth() > 0 && boss.getHealth() > 0) //mientras que no mueran siga con el bucle
        {
            if (isPlayerTurn)
            {
                cout << "Tu turno. Elige tu ataque (normal[n], fuego[f], magia[m]): "; //digo que ataque va a usar
                char attackChoice; //como solo queria una letra ejecuto la variable con un char
                cin >> attackChoice; //recogo la variable

                int damage;
                switch (attackChoice)
                {
                case 'n':
                    damage = character.getAttack(); //recogera el daño del jugador
                    break;
                case 'f':
                    damage = rand() % 21 + 10; // Daño entre 10 y 30
                    break;
                case 'm':
                    if (character.hasMagicAttackUsed()) //solo lo puedo usar una vez ya que es poderoso
                    {
                       cout << "Ya has usado tu ataque de magia. No puedes usarlo nuevamente." << endl; // si lo he utilizado no me deja
                        continue; //omito las lineas restantes
                    }
                    damage = rand() % 2 == 0 ? 0 : 70; // Daño de 70 o 0
                    character.useMagicAttack(); //cambio el bool del uso de magia para que no lo use mas
                    break;
                default:
                    cout << "Ataque invalido. Intenta nuevamente." << endl; //si pongo otra letra no me dejara
                    continue;
                }

                boss.setHealth(boss.getHealth() - damage); //le ressto la vida al boos
                isPlayerTurn = false; //sera turno del boos
            }
            else
            {
                int bossAttack = boss.getAttack(); //me atacara
                character.setHealth(character.getHealth() - bossAttack); //restara la vida al jugador
                isPlayerTurn = true; //volvera a ser turno del jugador
            }

            displayBoard(); //cargara el tablero de nuevo
        }

        if (character.getHealth() <= 0) // si la vida del jugador es 0 o menos he perdido
        {
            cout << "Tu personaje ha sido derrotado Has perdido el juego" << endl;
        }
        else //si no he ganado
        {
           cout << "Has derrotado al jefe final  Has ganado el juego" << endl;
        }
    }
};

int main() //ejecuto el main
{
    srand(time(0)); //inicializo una semilla aleatoria

    Game game; //llamo al metodo
    game.run();//ahora puedo ejecutar el juego

    return 0; //finalizo el programa
}
