#include "vInstructions.h"

/* Visualizza le istruzioni */
void sInstructions(WINDOW *window) {
    /* pulisce il menu */
    werase(window);

    /* Calcola la dimensione del terminale */
    int width, height;
    getmaxyx(window, height, width);

    /* Definisci il testo delle istruzioni */
    const char* instructions[] = {
        "Benvenuto nel mio gioco, seguono le istruzioni.",
        "",
        "A turno l'utente sposterà la propria pedina",
        "attraverso le frecce direzionali, e posizionerà",
        "la medesima cliccando il tasto INVIO, con lo",
        "scopo di allineare quattro pedine in fila",
        "orizzontale, verticale o obliqua.",
        "",
        "Nel frattempo deve stare attento alle mosse",
        "dell'avversario per evitare che anch'esso riesca",
        "a fare quattro impilando le proprie.",
        "",
        "Molto importante è restare sempre concentrati",
        "e studiare bene le mosse del proprio avversario.",
        "",
        "Nel caso nessuno dei due partecipanti al gioco",
        "riuscisse a fare 'quattro', la partita finisce",
        "in parità e se ne comincia un'altra.",
        "",
        "Premere un tasto per tornare al menu..."
    };

    /* Crea una cornice intorno al testo */
    box(window, 0, 0);

    /* Calcola l'altezza e la larghezza del testo */
    constexpr int tHeight = sizeof(instructions) / sizeof(instructions[0]);

    /* Posiziona il testo centrato */
    for (int i = 0; i < tHeight; ++i) {
        constexpr int padding = 1;
        const int sX = (int)(width - strlen(instructions[i])) / 2;
        const int sY = padding + i + 1;  // Lascia un po' di spazio sopra per la cornice
        mvwprintw(window, sY, sX, "%s", instructions[i]);
    }

    /* Aggiorna la finestra */
    wrefresh(window);

    /* Aspetta che l'utente prema un tasto */
    getch();
}
