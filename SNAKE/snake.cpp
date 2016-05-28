#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <string>
#include <fstream>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <iomanip>

using namespace std;
class Staty {
    public:
        string nick;
        int liczbapkt;

};
//########################################################################################################################
///ZMIENNE GLOBALNE:
int menu=27,
klawisz,
klawisz2,
szerokosc=40,wysokosc=20,
zaznaczenie=1,
kolorek=10,
poziom;
bool sprawdz;
HANDLE kolor=GetStdHandle(STD_OUTPUT_HANDLE);
///LISTA FUNKCJI:
bool glowna();
void rysuj(int zmienna);
void nazwagry();
void pokazstatystyki();
void ustawienia();
bool snake();
void wyczysc();
void Wyczysc2();
bool Trudnosc();
bool GameOver(int pkt);
//########################################################################################################################
///FUNKCJA GLOWNA:
int main() {
    //ios_base::sync_with_stdio(0);
    srand(time(NULL));
    rysuj(menu);
    glowna();
    return 0;
}
//########################################################################################################################
///FUNKCJE:
//czytajaca klawisze:
bool glowna() {
    for(;;) {
        if (kbhit()) {
            klawisz=getch();
            Wyczysc2();
            switch(menu) {
                case 27:
                    switch(klawisz){
                        case '1':
                            snake();
                            menu=27;
                            break;
                        case '2':
                            menu=2;
                            break;
                        case '3':
                            menu=3;
                            break;
                        case '4':
                            menu=4;
                            break;
                        case 27:
                            return 0;
                    }
                    break;
                case 2:
                    if (klawisz==27) {
                        menu=27;
                    }
                    if (klawisz==8) {
                        cout<<"Wyczyszczono statystyki"<<endl;
                        wyczysc();
                    }
                    break;
                case 3:
                    switch(klawisz) {
                        case 27:
                            menu=27;
                            zaznaczenie=1;
                            break;
                        case 's':
                            if (zaznaczenie<3) {
                                zaznaczenie++;
                            }
                            break;
                        case 'w':
                            if (zaznaczenie>1) {
                                zaznaczenie--;
                            }
                            break;
                        case 'd':
                            switch(zaznaczenie){
                                case 1:if (szerokosc<60) szerokosc++;break;
                                case 2:if (wysokosc<30) wysokosc++;break;
                                case 3:if (kolorek!=15) kolorek++;else  kolorek=1;break;
                            }
                            break;
                        case 'a':
                            switch(zaznaczenie){
                                case 1:if (szerokosc>20) szerokosc--;break;
                                case 2:if (wysokosc>10) wysokosc--;break;
                                case 3:if (kolorek!=1) kolorek--;else kolorek=15;break;
                            }
                            break;
                    }
                    break;
                case 4:
                    if (klawisz==27) {
                        menu=27;
                    }
                    break;
            }
            rysuj(menu);
        }
    }

}
//########################################################################################################################
//rysujaca na ekranie:
void rysuj(int zmienna) {
    switch(zmienna) {
        case 27:
            nazwagry();
            cout<<"     "<<char(26)<<" 1 - Start"<<endl;
            cout<<"     "<<char(26)<<" 2 - Statystyki"<<endl;
            cout<<"     "<<char(26)<<" 3 - Ustawienia"<<endl;
            cout<<"     "<<char(26)<<" 4 - Autor"<<endl;
            cout<<"     "<<char(26)<<" [ESC] - Wyjdz"<<endl;
            for (int e=0;e<50;e++) cout<<char(205);
            break;
        case 2:
            for (int e=0;e<36;e++) cout<<char(205);
            SetConsoleTextAttribute(kolor,9);
            cout<<endl<<endl<<"            Statystyki"<<endl<<endl;
            SetConsoleTextAttribute(kolor,7);
            pokazstatystyki();
            cout<<"[ESC] - Powrot do MENU"<<endl;
            cout<<"[BS] - Resetowanie statystyk"<<endl;
            for (int e=0;e<36;e++) cout<<char(205);
            break;
        case 3:
            ustawienia();
            break;
        case 4:
            for (int e=0;e<37;e++) cout<<char(205);
            cout<<endl<<"Autor gry: ";
            SetConsoleTextAttribute(kolor,3);
            cout<<"Konrad Cielecki"<<endl;
            SetConsoleTextAttribute(kolor,7);
            cout<<"Kontakt z autorem: ";
            SetConsoleTextAttribute(kolor,4);
            cout<<"conrisc@gmail.com"<<endl;
            SetConsoleTextAttribute(kolor,7);
            for (int e=0;e<37;e++) cout<<char(205);
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            for (int e=0;e<37;e++) cout<<char(205);
            break;
    }
}
//########################################################################################################################
//wyswietlajaca napis "snake":
void nazwagry() {
    bool matryca[8][50]={
        {0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0},
        {0,0,1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0},
        {0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,0,0,0,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0},
        {0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0},
        {0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0},
        {0,0,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,1,1,1,0},
        {0,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,1,1,0},
    };
    SetConsoleTextAttribute(kolor,7);
    for (int e=0;e<50;e++) cout<<char(205);
    cout<<endl;
    SetConsoleTextAttribute(kolor,kolorek);
    for (int a=0;a<8;a++) {
        for (int b=0;b<50;b++) {
            if (matryca[a][b]==1) {
                cout<<char(177);
            }
            else {
                cout<<" ";
            }
        }
        cout<<endl;
    }
    SetConsoleTextAttribute(kolor,7);
    cout<<endl;
    for (int e=0;e<50;e++) cout<<char(205);
    cout<<endl;
}
//########################################################################################################################
//funkcja wywolywana w funkcji draw(),czyli rysuje statystyki, czytajac z pliku:
void pokazstatystyki(){
    string nazwa;
    string score;
    ifstream statystyki("statystyki.txt");
    cout<<char(201);
    for (int e=0;e<34;e++) cout<<char(205);
    cout<<char(187)<<endl;
    cout<<char(186)<<" NR "<<char(179)<<" NAZWA                "<<char(179)<<"PUNKTY"<<char(186)<<endl;
    for (int c=1;c<=10;c++) {
        cout<<char(204)<<"----"<<char(197)<<"----------------------"<<char(197)<<"------"<<char(185)<<endl;
        getline(statystyki,nazwa);
        getline(statystyki,score);
        cout<<char(186)<<setw(3)<<c<<" "<<char(179)<<" "<<nazwa;
        for (int d=nazwa.size();d<=20;d++) cout<<" ";
        cout<<char(179)<<setw(4)<<score<<"  "<<char(186)<<endl;
    }
    cout<<char(200);
    for (int e=0;e<34;e++) cout<<char(205);
    cout<<char(188)<<endl;
    statystyki.close();
}
//########################################################################################################################
//funckja wywolywana w funkcji draw(), czyli rysuje menu ustawien:
void ustawienia(){
    Wyczysc2();
    for (int e=0;e<36;e++) cout<<char(205);
    cout<<endl<<endl<<"            Ustawienia"<<endl<<endl;
            switch (zaznaczenie) {
                case 1:
                    SetConsoleTextAttribute(kolor,kolorek);
                    cout<<"       Szerokosc planszy: "<<szerokosc<<endl;
                    SetConsoleTextAttribute(kolor,7);
                    cout<<"        Wysokosc planszy: "<<wysokosc<<endl;
                    cout<<"           Kolor wezyka"<<endl;
                    break;
                case 2:
                    cout<<"       Szerokosc planszy: "<<szerokosc<<endl;
                    SetConsoleTextAttribute(kolor,kolorek);
                    cout<<"        Wysokosc planszy: "<<wysokosc<<endl;
                    SetConsoleTextAttribute(kolor,7);
                    cout<<"           Kolor wezyka"<<endl;
                    break;
                case 3:
                    cout<<"       Szerokosc planszy: "<<szerokosc<<endl;
                    cout<<"        Wysokosc planszy: "<<wysokosc<<endl;
                    SetConsoleTextAttribute(kolor,kolorek);
                    cout<<"           Kolor wezyka"<<endl;
                    break;
            }
            SetConsoleTextAttribute(kolor,7);
            for (int e=0;e<36;e++) cout<<char(205);
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            for (int e=0;e<36;e++) cout<<char(205);
}
//########################################################################################################################
//funkcja gry:
bool snake(){
    Trudnosc();
    if (sprawdz==0) return 0;
    int punkty=0;
        Wyczysc2();
        int x=4,y=4;
        int prawo=1,lewo=0,gora=0,dol=0,dlugosc=3;
        const int wysokosc2=wysokosc;
        const int szerokosc2=szerokosc;
        int eat1=rand()%wysokosc2;
        int eat2=rand()%szerokosc2;
        int plansza[wysokosc2][szerokosc2];
        for (int h=0;h<wysokosc2;h++) {
            for (int g=0;g<szerokosc2;g++) {
                plansza[h][g]=0;
            }
        }
        for(;;){
            if (kbhit()) {
                klawisz2=getch();
                switch(klawisz2) {
                    case 27:
                        GameOver(punkty);
                        return 0;
                    case 'w':
                        if (dol!=1) {
                            prawo=0;
                            lewo=0;
                            dol=0;
                            gora=1;
                        }
                        break;
                    case 's':
                        if (gora!=1) {
                            prawo=0;
                            lewo=0;
                            gora=0;
                            dol=1;
                        }
                        break;
                    case 'a':
                        if (prawo!=1) {
                            prawo=0;
                            gora=0;
                            dol=0;
                            lewo=1;
                        }
                        break;
                    case 'd':
                        if (lewo!=1) {
                            lewo=0;
                            gora=0;
                            dol=0;
                            prawo=1;
                        }
                        break;
                }
            }
            x=x-lewo+prawo;
            y=y-gora+dol;
            if (y>=wysokosc2 || y<0 || x>=szerokosc2 || x<0 || plansza[y][x]>1) {
                GameOver(punkty);
                return 0;
            }
            if (y!=eat1 || x!=eat2) {
                for (int h=0;h<wysokosc2;h++) {
                    for (int g=0;g<szerokosc2;g++) {
                        if (plansza[h][g]>0) {
                            plansza[h][g]--;
                        }
                    }
                }
            }
            else {
                dlugosc++;
                punkty++;
                do {
                    eat1=rand()%wysokosc2;
                    eat2=rand()%szerokosc2;
                } while(plansza[eat1][eat2]!=0);
            }
            plansza[eat1][eat2]=-1;
            Wyczysc2();
            plansza[y][x]=dlugosc;
            for (int f=szerokosc2+2;f>0;f--) {
                cout<<char(205);
            }
            cout<<endl;
            for (int g=0;g<wysokosc2;g++) {
                cout<<char(186);
                for (int h=0;h<szerokosc2;h++) {
                    switch(plansza[g][h]) {
                        case 0:
                            cout<<" ";
                            break;
                        case -1:
                            cout<<char(4);
                            break;
                        default:
                            SetConsoleTextAttribute(kolor,kolorek);
                            cout<<char(219);
                            SetConsoleTextAttribute(kolor,7);
                            break;
                    }
                }
                cout<<char(186)<<endl;
            }
            for (int f=szerokosc2+2;f>0;f--) {
                cout<<char(205);
            }
            cout<<endl<<"Punkty: "<<punkty;
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            for (int f=szerokosc2+2;f>0;f--) {
                cout<<char(205);
            }
            Sleep(poziom);
        }
}
//########################################################################################################################
//funkcja wywolywana przed funkcja snake(), czyli menu wyboru trudnosci:
bool Trudnosc() {
    zaznaczenie=1;
    sprawdz=1;
    for (;klawisz2!=13 && klawisz2!=32;) {
        Wyczysc2();
        for (int e=0;e<36;e++) cout<<char(205);
        cout<<endl<<endl<<"         Poziom trudnosci:"<<endl<<endl;
                switch (zaznaczenie) {
                    case 1:
                        SetConsoleTextAttribute(kolor,kolorek);
                        cout<<"              Latwy"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,7);
                        cout<<"              Sredni"<<endl<<endl;
                        cout<<"              Trudny"<<endl<<endl;
                        poziom=200;
                        break;
                    case 2:
                        cout<<"              Latwy"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,kolorek);
                        cout<<"              Sredni"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,7);
                        cout<<"              Trudny"<<endl<<endl;
                        poziom=100;
                        break;
                    case 3:
                        cout<<"              Latwy"<<endl<<endl;
                        cout<<"              Sredni"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,kolorek);
                        cout<<"              Trudny"<<endl<<endl;
                        SetConsoleTextAttribute(kolor,7);
                        poziom=60;
                        break;
                }
            for (int e=0;e<36;e++) cout<<char(205);
            cout<<endl<<"[ESC] - Powrot do MENU"<<endl;
            for (int e=0;e<37;e++) cout<<char(205);
            klawisz2=getch();
            switch(klawisz2) {
                case 'w':if(zaznaczenie>1)zaznaczenie--;break;
                case 's':if(zaznaczenie<3)zaznaczenie++;break;
                case 27: zaznaczenie=1;Wyczysc2();sprawdz=0; return 0;
            }
    }
    zaznaczenie=1;
    return 0;
}
//########################################################################################################################
//funkcja czyszczenia statystyk:
void wyczysc(){
    ofstream plik("Statystyki.txt");
    for (int i=0;i<10;i++) {
        plik<<"---------------"<<endl;
        plik<<0<<endl;}
    plik.close();
}
//########################################################################################################################
//funkcja czyszczenia okna konsoli:
void Wyczysc2() {
   COORD coordScreen = {0,0};
   DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;
   HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   dwConSize = csbi.dwSize.X*csbi.dwSize.Y;
   FillConsoleOutputCharacter(hConsole,(TCHAR)' ',dwConSize,coordScreen,&cCharsWritten);
   GetConsoleScreenBufferInfo(hConsole,&csbi);
   FillConsoleOutputAttribute(hConsole,csbi.wAttributes,dwConSize,coordScreen,&cCharsWritten);
   SetConsoleCursorPosition(hConsole,coordScreen);
}
//########################################################################################################################
//funkcja uruchamiana po przegranej lub po zakonczeniu snake():
bool GameOver(int pkt) {
    int klawisz3;
    int zap=11;
    string nazwa;
    Staty tablica[10];
    Wyczysc2();
    for (int e=0;e<36;e++) cout<<char(205);
    cout<<endl<<"Liczba uzyskanych pkt.:"<<pkt<<endl;
    for (int e=0;e<36;e++) cout<<char(205);
    cout<<endl<<"Podaj swoj nick: ";
    cin>>nazwa;
    ifstream plik ("statystyki.txt");
    for(int l=0;!plik.eof() || l<10;l++) {
        plik>>tablica[l].nick;
        plik>>tablica[l].liczbapkt;
    }
    plik.close();
    for(int l=0;l<10;l++) {
        if (tablica[l].liczbapkt<pkt) {
            zap=l;
            break;
        }
    }
    if (zap==11) {
        Wyczysc2();
        return 0;
        }
    ofstream pliczek ("statystyki.txt");
    for (int l=0;l<zap;l++) {
        pliczek<<tablica[l].nick<<endl;
        pliczek<<tablica[l].liczbapkt<<endl;
    }
    pliczek<<nazwa<<endl;
    pliczek<<pkt<<endl;
    for (int l=zap;l<9;l++) {
        pliczek<<tablica[l].nick<<endl;
        pliczek<<tablica[l].liczbapkt<<endl;
    }
    pliczek.close();
    Wyczysc2();
}
//########################################################################################################################
