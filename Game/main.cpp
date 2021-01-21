#include "GameWorld.h"
#include <cctype>

int main() {
    // Declare an object of the type GameWorld
    GameWorld objGameWorld(10, 20, 40);

    // This variable controls the main loop structure
    bool blnContinue = true;

    // This variable stores the player movement as per the user input
    char chDirection = '\0';

    // Menu system
    while (blnContinue) {
        // Display the game to the standard output stream
        objGameWorld.displayGameWorld();

        cout<<"Enter the player movement (w, a, s, d) or enter (q) to quit : ";
        cin>>chDirection;

        chDirection = tolower(chDirection);

        switch (chDirection) {
            case 'w':
            case 'a':
            case 's':
            case 'd':
                objGameWorld.movePlayer(chDirection);
                break;
            case 'q':
                blnContinue = false;
                cout<<"Winners never quit. You lose!!!!!!!!!!!!!!!"<<endl;
                system("pause");
        }

        system("cls");
    }

    return SUCCESS;
}
