






if ( state == 0 ){
    if( !started ){
        WelcomeScreen();
        cout << "\n\n\t\t\t\tPress any key to start";
        cout << "\n\t\t\t\t**********************";
        cout << "\n\n\t\t\t\t Instructions: ";
        cout << "\n\t\t\t\t-----------------------";
        cout << "\n\t\t\t\tW = 'Move Snake up' ";
        cout << "\n\t\t\t\tS = 'Move Snake down' ";
        cout << "\n\t\t\t\tA = 'Move Snake left' ";
        cout << "\n\t\t\t\tD = 'Move Snake right'";
        getch();
        started = 1;
        state = 1;
    } else {
        cout << "\t\t\t\t------------------------------" << endl;
        cout << "\t\t\t\t|--@@@@-- Game Over --@@@@--|" << endl;
        cout << "\t\t\t\t------------------------------" << endl << endl << endl;
        cout << "\t\t\t\t Developed By:" << endl;
        cout << "\t\t\t\t ----------------" << endl;
        cout << "\t\t\t\t Bayzid Simon Sarkar" << endl << endl << endl;
        cout << "\t\t\t\t Press any key to go back to game menu." << endl << endl;
        getch();
        state = 1;
        size = 1;
    }
}






