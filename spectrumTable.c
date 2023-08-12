#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <math.h>
#include <locale.h>
#include <stdlib.h>

#define PI 3.14159265
#define NUM_ELEMENTS 118
#define TABLE_WIDTH 18

#define TALLBAR 9475

typedef struct {
  int r;
  int g;
  int b;
}
RGB;

RGB newRGB(int r, int g, int b) {
  RGB color;
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

typedef struct {
  char symbol[3];
  int group;
  int period;
}
Element;

void calculateQuantityVisibleResults(double Rinf, double me, double massaNucleoAtual, int numeroAtomico, int * resultadosValidos);
void calcularCor(RGB * cores, int totalCores, int indiceAtual, float saturacao, float luminosidade);

// Função para calcular a constante de Rydberg ajustada (R?)
double constanteRydbergAjustada(double Rinf, double me, double M) {
  return Rinf / (1 + me / M);
}
int ascending_int(const void * int_a,
  const void * int_b) {
  int a = * (int * ) int_a;
  int b = * (int * ) int_b;
  return (a > b) - (a < b);
}

int main() {
  setlocale(LC_ALL, "");
  int totalCores = 60;
  RGB cores[totalCores];
  float saturacao = 1.0;
  float luminosidade = 0.3;
  int raio = 0; // raio do círculo
  int centroX, centroY; // coordenadas do centro do círculo
  double angulo = 0.0; // ângulo inicial

  initscr();
  curs_set(0);
  keypad(stdscr, TRUE);
  // Definir cores personalizadas para destaque e não destaque
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_WHITE);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, 211, COLOR_BLACK);
  init_pair(4, 76, COLOR_BLACK);
  init_pair(5, 110, COLOR_BLACK);
  init_pair(6, 208, COLOR_BLACK);
  init_pair(7, 227, COLOR_BLACK);
  init_pair(8, 132, COLOR_BLACK);
  init_pair(9, 132, COLOR_BLACK);
  init_pair(10, 198, COLOR_BLACK);
  init_pair(11, 78, COLOR_BLACK);

  // Habilitar a leitura de teclado não bloqueante
  nodelay(stdscr, TRUE);
  timeout(0);
  // Obter as dimensões da tela
  int maxX, maxY;
  getmaxyx(stdscr, maxY, maxX);

  // Calcular as coordenadas do centro do círculo
  centroX = 17;
  centroY = 17;

  int fim = totalCores - 18;
  int inicio = fim - 42;

  double Rinf = 1.0973731568508E7;
  double me = 9.10938356E-31;

  double massaNucleo[] = {
    1.67262192E-27, // Hidrogênio (Z = 1)
    6.6464764E-27, // Hélio (Z = 2)
    1.675E-27, // Lítio (Z = 3)
    2.466E-27, // Berílio (Z = 4)
    3.74E-27, // Boro (Z = 5)
    5.168E-27, // Carbono (Z = 6)
    6.646E-27, // Nitrogênio (Z = 7)
    9.389E-27, // Oxigênio (Z = 8)
    1.166E-26, // Flúor (Z = 9)
    1.503E-26, // Neônio (Z = 10)
    1.75E-26, // Sódio (Z = 11)
    2.018E-26, // Magnésio (Z = 12)
    2.307E-26, // Alumínio (Z = 13)
    2.617E-26, // Silício (Z = 14)
    2.948E-26, // Fósforo (Z = 15)
    3.301E-26, // Enxofre (Z = 16)
    3.675E-26, // Cloro (Z = 17)
    4.071E-26, // Argônio (Z = 18)
    4.489E-26, // Potássio (Z = 19)
    4.927E-26, // Cálcio (Z = 20)
    5.387E-26, // Escândio (Z = 21)
    5.869E-26, // Titânio (Z = 22)
    6.371E-26, // Vanádio (Z = 23)
    6.895E-26, // Cromo (Z = 24)
    7.44E-26, // Manganês (Z = 25)
    8.006E-26, // Ferro (Z = 26)
    8.593E-26, // Cobalto (Z = 27)
    9.201E-26, // Níquel (Z = 28)
    9.83E-26, // Cobre (Z = 29)
    1.048E-25, // Zinco (Z = 30)
    1.116E-25, // Gálio (Z = 31)
    1.186E-25, // Germânio (Z = 32)
    1.258E-25, // Arsênio (Z = 33)
    1.331E-25, // Selênio (Z = 34)
    1.407E-25, // Bromo (Z = 35)
    1.484E-25, // Criptônio (Z = 36)
    1.564E-25, // Rubídio (Z = 37)
    1.646E-25, // Estrôncio (Z = 38)
    1.73E-25, // Ítrio (Z = 39)
    1.815E-25, // Zircônio (Z = 40)
    1.902E-25, // Nióbio (Z = 41)
    1.991E-25, // Molibdênio (Z = 42)
    2.082E-25, // Tecnécio (Z = 43)
    2.174E-25, // Rutênio (Z = 44)
    2.268E-25, // Ródio (Z = 45)
    2.363E-25, // Paládio (Z = 46)
    2.461E-25, // Prata (Z = 47)
    2.56E-25, // Cádmio (Z = 48)
    2.66E-25, // Índio (Z = 49)
    2.763E-25, // Estanho (Z = 50)
    2.867E-25, // Antimônio (Z = 51)
    2.973E-25, // Telúrio (Z = 52)
    3.08E-25, // Iodo (Z = 53)
    3.189E-25, // Xenônio (Z = 54)
    3.3E-25, // Césio (Z = 55)
    3.413E-25, // Bário (Z = 56)
    3.528E-25, // Lantânio (Z = 57)
    3.645E-25, // Cério (Z = 58)
    3.764E-25, // Praseodímio (Z = 59)
    3.885E-25, // Neodímio (Z = 60)
    4.008E-25, // Promécio (Z = 61)
    4.133E-25, // Samário (Z = 62)
    4.26E-25, // Európio (Z = 63)
    4.389E-25, // Gadolínio (Z = 64)
    4.52E-25, // Térbio (Z = 65)
    4.653E-25, // Disprósio (Z = 66)
    4.788E-25, // Hólmio (Z = 67)
    4.926E-25, // Érbio (Z = 68)
    5.065E-25, // Túlio (Z = 69)
    5.207E-25, // Itérbio (Z = 70)
    5.351E-25, // Lutécio (Z = 71)
    5.496E-25, // Háfnio (Z = 72)
    5.644E-25, // Tântalo (Z = 73)
    5.793E-25, // Tungstênio (Z = 74)
    5.945E-25, // Rênio (Z = 75)
    6.098E-25, // Ósmio (Z = 76)
    6.254E-25, // Irídio (Z = 77)
    6.412E-25, // Platina (Z = 78)
    6.572E-25, // Ouro (Z = 79)
    6.734E-25, // Mercúrio (Z = 80)
    6.898E-25, // Tálio (Z = 81)
    7.065E-25, // Chumbo (Z = 82)
    7.234E-25, // Bismuto (Z = 83)
    7.405E-25, // Polônio (Z = 84)
    7.578E-25, // Astatínio (Z = 85)
    7.754E-25, // Radônio (Z = 86)
    7.931E-25, // Frâncio (Z = 87)
    8.111E-25, // Rádio (Z = 88)
    8.293E-25, // Actínio (Z = 89)
    8.477E-25, // Tório (Z = 90)
    8.663E-25, // Protactínio (Z = 91)
    8.851E-25, // Urânio (Z = 92)
    9.041E-25, // Neptúnio (Z = 93)
    9.233E-25, // Plutônio (Z = 94)
    9.427E-25, // Amerício (Z = 95)
    9.623E-25, // Cúrio (Z = 96)
    9.821E-25, // Berquélio (Z = 97)
    1.002E-24, // Califórnio (Z = 98)
    1.022E-24, // Einstênio (Z = 99)
    1.043E-24, // Férmio (Z = 100)
    1.064E-24, // Mendelévio (Z = 101)
    1.086E-24, // Nobélio (Z = 102)
    1.109E-24, // Laurêncio (Z = 103)
    1.133E-24, // Rutherfórdio (Z = 104)
    1.157E-24, // Dúbnio (Z = 105)
    1.183E-24, // Seabórgio (Z = 106)
    1.209E-24, // Bóhrio (Z = 107)
    1.236E-24, // Hassio (Z = 108)
    1.264E-24, // Meitnério (Z = 109)
    1.293E-24, // Darmstádio (Z = 110)
    1.322E-24, // Roentgênio (Z = 111)
    1.353E-24, // Copernício (Z = 112)
    1.384E-24, // Nihônio (Z = 113)
    1.417E-24, // Fleróvio (Z = 114)
    1.451E-24, // Moscóvio (Z = 115)
    1.485E-24, // Livermório (Z = 116)
    1.521E-24, // Tennessino (Z = 117)
    1.557E-24, // Oganessônio (Z = 118)
  };
  int caracterSorteado[] = {
    TALLBAR
  };
  
  Element elements[] = {
       {"H", 1, 1},  {"He", 18, 1}, {"Li", 1, 2}, {"Be", 2, 2}, {"B", 13, 2},  {"C", 14, 2},  {"N", 15, 2},  {"O", 16, 2},  {"F", 17, 2},  {"Ne", 18, 2},
       {"Na", 1, 3}, {"Mg", 2, 3},  {"Al", 13, 3}, {"Si", 14, 3}, {"P", 15, 3},  {"S", 16, 3},  {"Cl", 17, 3}, {"Ar", 18, 3}, {"K", 1, 4},   {"Ca", 2, 4},
       {"Sc", 3, 4}, {"Ti", 4, 4},  {"V", 5, 4},   {"Cr", 6, 4},  {"Mn", 7, 4},  {"Fe", 8, 4},  {"Co", 9, 4},  {"Ni", 10, 4}, {"Cu", 11, 4}, {"Zn", 12, 4},
       {"Ga", 13, 4}, {"Ge", 14, 4}, {"As", 15, 4}, {"Se", 16, 4}, {"Br", 17, 4}, {"Kr", 18, 4}, {"Rb", 1, 5},  {"Sr", 2, 5},  {"Y", 3, 5},   {"Zr", 4, 5},
       {"Nb", 5, 5},  {"Mo", 6, 5},  {"Tc", 7, 5},  {"Ru", 8, 5},  {"Rh", 9, 5},  {"Pd", 10, 5}, {"Ag", 11, 5}, {"Cd", 12, 5}, {"In", 13, 5}, {"Sn", 14, 5},
       {"Sb", 15, 5}, {"Te", 16, 5}, {"I", 17, 5},  {"Xe", 18, 5}, {"Cs", 1, 6},  {"Ba", 2, 6},  {"La", 4, 9},  {"Ce", 5, 9},  {"Pr", 6, 9},  {"Nd", 7, 9},
       {"Pm", 8, 9},  {"Sm", 9, 9},  {"Eu", 10, 9},  {"Gd", 11, 9}, {"Tb", 12, 9}, {"Dy", 13, 9}, {"Ho", 14, 9}, {"Er", 15, 9}, {"Tm", 16, 9}, {"Yb", 17, 9},
       {"Lu", 18, 9}, {"Hf", 4, 6},  {"Ta", 5, 6},  {"W", 6, 6},   {"Re", 7, 6},  {"Os", 8, 6},  {"Ir", 9, 6},  {"Pt", 10, 6}, {"Au", 11, 6}, {"Hg", 12, 6},
       {"Tl", 13, 6}, {"Pb", 14, 6}, {"Bi", 15, 6}, {"Po", 16, 6}, {"At", 17, 6}, {"Rn", 18, 6}, {"Fr", 1, 7},  {"Ra", 2, 7},  {"Ac", 4, 10},  {"Th", 5, 10},
       {"Pa", 6, 10},  {"U", 7, 10},   {"Np", 8, 10},  {"Pu", 9, 10},  {"Am", 10, 10},  {"Cm", 11, 10}, {"Bk", 12, 10}, {"Cf", 13, 10}, {"Es", 14, 10}, {"Fm", 15, 10},
       {"Md", 16, 10}, {"No", 17, 10}, {"Lr", 18, 10}, {"Rf", 4, 7},  {"Db", 5, 7},  {"Sg", 6, 7},  {"Bh", 7, 7},  {"Hs", 8, 7},  {"Mt", 9, 7},  {"Ds", 10, 7},
       {"Rg", 11, 7}, {"Cn", 12, 7}, {"Nh", 13, 7}, {"Fl", 14, 7}, {"Mc", 15, 7}, {"Lv", 16, 7}, {"Ts", 17, 7}, {"Og", 18, 7}
  };
  int position = 0;

  while (1) {
    // Criar um plano para desenho
    char plano[maxY][maxX];
    memset(plano, ' ', sizeof(plano));

    int numcaracterSorteado = position + 1;
    double ASPECT_RATIO = 2;
    double R = 2, R2 = 4, R3 = 6;
    double anguloK = angulo, anguloL2 = -angulo, anguloM3 = angulo;
    const char * elementoSelecionado = elements[position].symbol;
    // Desenhar caracterSorteado no plano
    if (numcaracterSorteado >= 1) {
      int xK = (int)(ASPECT_RATIO * R * sin(anguloK) + centroX);
      int yK = (int)(R * cos(anguloK) + centroY);
      if (xK >= 0 && xK < maxX && yK >= 0 && yK < maxY) {
        plano[yK][xK] = '#';
      }
    }
    if (numcaracterSorteado >= 2) {
      int xK2 = (int)(ASPECT_RATIO * R * sin(anguloK + PI) + centroX);
      int yK2 = (int)(R * cos(anguloK + PI) + centroY);
      if (xK2 >= 0 && xK2 < maxX && yK2 >= 0 && yK2 < maxY) {
        plano[yK2][xK2] = '#';
      }
    }
    if (numcaracterSorteado >= 3) {
      int xL = (int)(ASPECT_RATIO * R2 * sin(anguloL2) + centroX);
      int yL = (int)(R2 * cos(anguloL2) + centroY);
      if (xL >= 0 && xL < maxX && yL >= 0 && yL < maxY) {
        plano[yL][xL] = '*';
      }
    }
    if (numcaracterSorteado >= 4) {
      int xL2 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + PI) + centroX);
      int yL2 = (int)(R2 * cos(anguloL2 + PI) + centroY);
      if (xL2 >= 0 && xL2 < maxX && yL2 >= 0 && yL2 < maxY) {
        plano[yL2][xL2] = '*';
      }
    }
    if (numcaracterSorteado >= 5) {
      int xL3 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + 3 * PI / 2) + centroX);
      int yL3 = (int)(R2 * cos(anguloL2 + 3 * PI / 2) + centroY);
      if (xL3 >= 0 && xL3 < maxX && yL3 >= 0 && yL3 < maxY) {
        plano[yL3][xL3] = '*';
      }
    }
    if (numcaracterSorteado >= 6) {
      int xL4 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + PI / 4) + centroX);
      int yL4 = (int)(R2 * cos(anguloL2 + PI / 4) + centroY);
      if (xL4 >= 0 && xL4 < maxX && yL4 >= 0 && yL4 < maxY) {
        plano[yL4][xL4] = '*';
      }
    }
    if (numcaracterSorteado >= 7) {
      int xL5 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + 5 * PI / 4) + centroX);
      int yL5 = (int)(R2 * cos(anguloL2 + 5 * PI / 4) + centroY);
      if (xL5 >= 0 && xL5 < maxX && yL5 >= 0 && yL5 < maxY) {
        plano[yL5][xL5] = '*';
      }
    }
    if (numcaracterSorteado >= 8) {
      int xL6 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + 3 * PI / 4) + centroX);
      int yL6 = (int)(R2 * cos(anguloL2 + 3 * PI / 4) + centroY);
      if (xL6 >= 0 && xL6 < maxX && yL6 >= 0 && yL6 < maxY) {
        plano[yL6][xL6] = '*';
      }
    }
    if (numcaracterSorteado >= 9) {
      int xL7 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + PI / 2) + centroX);
      int yL7 = (int)(R2 * cos(anguloL2 + PI / 2) + centroY);
      if (xL7 >= 0 && xL7 < maxX && yL7 >= 0 && yL7 < maxY) {
        plano[yL7][xL7] = '*';
      }
    }
    if (numcaracterSorteado >= 10) {
      int xL8 = (int)(ASPECT_RATIO * R2 * sin(anguloL2 + 7 * M_PI / 4) + centroX);
      int yL8 = (int)(R2 * cos(anguloL2 + 7 * M_PI / 4) + centroY);
      if (xL8 >= 0 && xL8 < maxX && yL8 >= 0 && yL8 < maxY) {
        plano[yL8][xL8] = '*';
      }
    }
    if (numcaracterSorteado >= 11) {
      int xM1 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + M_PI / 4) + centroX);
      int yM1 = (int)(R3 * cos(anguloM3 + M_PI + M_PI / 4) + centroY);
      if (xM1 >= 0 && xM1 < maxX && yM1 >= 0 && yM1 < maxY) {
        plano[yM1][xM1] = 'd';
      }
    }

    if (numcaracterSorteado >= 12) {
      int xM2 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 5 * M_PI / 4) + centroX);
      int yM2 = (int)(R3 * cos(anguloM3 + M_PI + 5 * M_PI / 4) + centroY);
      if (xM2 >= 0 && xM2 < maxX && yM2 >= 0 && yM2 < maxY) {
        plano[yM2][xM2] = 'e';
      }
    }

    if (numcaracterSorteado >= 13) {
      int xM3 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 3 * M_PI / 4) + centroX);
      int yM3 = (int)(R3 * cos(anguloM3 + M_PI + 3 * M_PI / 4) + centroY);
      if (xM3 >= 0 && xM3 < maxX && yM3 >= 0 && yM3 < maxY) {
        plano[yM3][xM3] = 'f';
      }
    }

    if (numcaracterSorteado >= 14) {
      int xM4 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI) + centroX);
      int yM4 = (int)(R3 * cos(anguloM3 + M_PI) + centroY);
      if (xM4 >= 0 && xM4 < maxX && yM4 >= 0 && yM4 < maxY) {
        plano[yM4][xM4] = 'g';
      }
    }

    if (numcaracterSorteado >= 15) {
      int xM5 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 3 * M_PI / 2) + centroX);
      int yM5 = (int)(R3 * cos(anguloM3 + M_PI + 3 * M_PI / 2) + centroY);
      if (xM5 >= 0 && xM5 < maxX && yM5 >= 0 && yM5 < maxY) {
        plano[yM5][xM5] = 'h';
      }
    }

    if (numcaracterSorteado >= 16) {
      int xM6 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + M_PI) + centroX);
      int yM6 = (int)(R3 * cos(anguloM3 + M_PI + M_PI) + centroY);
      if (xM6 >= 0 && xM6 < maxX && yM6 >= 0 && yM6 < maxY) {
        plano[yM6][xM6] = 'n';
      }
    }
    if (numcaracterSorteado >= 17) {
      int xM7 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 5 * M_PI / 4) + centroX);
      int yM7 = (int)(R3 * cos(anguloM3 + M_PI + 5 * M_PI / 4) + centroY);
      if (xM7 >= 0 && xM7 < maxX && yM7 >= 0 && yM7 < maxY) {
        plano[yM7][xM7] = 'o';
      }
    }

    if (numcaracterSorteado >= 18) {
      int xM8 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 3 * M_PI / 2) + centroX);
      int yM8 = (int)(R3 * cos(anguloM3 + M_PI + 3 * M_PI / 2) + centroY);
      if (xM8 >= 0 && xM8 < maxX && yM8 >= 0 && yM8 < maxY) {
        plano[yM8][xM8] = 'h';
      }
    }

    if (numcaracterSorteado >= 19) {
      int xM9 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 7 * M_PI / 4) + centroX);
      int yM9 = (int)(R3 * cos(anguloM3 + M_PI + 7 * M_PI / 4) + centroY);
      if (xM9 >= 0 && xM9 < maxX && yM9 >= 0 && yM9 < maxY) {
        plano[yM9][xM9] = 'f';
      }
    }

    if (numcaracterSorteado >= 20) {
      int xM10 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 2 * M_PI) + centroX);
      int yM10 = (int)(R3 * cos(anguloM3 + M_PI + 2 * M_PI) + centroY);
      if (xM10 >= 0 && xM10 < maxX && yM10 >= 0 && yM10 < maxY) {
        plano[yM10][xM10] = 'n';
      }
    }

    if (numcaracterSorteado >= 21) {
      int xM11 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 9 * M_PI / 4) + centroX);
      int yM11 = (int)(R3 * cos(anguloM3 + M_PI + 9 * M_PI / 4) + centroY);
      if (xM11 >= 0 && xM11 < maxX && yM11 >= 0 && yM11 < maxY) {
        plano[yM11][xM11] = 'i';
      }
    }

    if (numcaracterSorteado >= 22) {
      int xM12 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 5 * M_PI / 2) + centroX);
      int yM12 = (int)(R3 * cos(anguloM3 + M_PI + 5 * M_PI / 2) + centroY);
      if (xM12 >= 0 && xM12 < maxX && yM12 >= 0 && yM12 < maxY) {
        plano[yM12][xM12] = 'e';
      }
    }

    if (numcaracterSorteado >= 23) {
      int xM13 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 11 * M_PI / 4) + centroX);
      int yM13 = (int)(R3 * cos(anguloM3 + M_PI + 11 * M_PI / 4) + centroY);
      if (xM13 >= 0 && xM13 < maxX && yM13 >= 0 && yM13 < maxY) {
        plano[yM13][xM13] = 'r';
      }
    }
    if (numcaracterSorteado >= 24) {
      int xM14 = (int)(ASPECT_RATIO * R3 * sin(anguloM3 + M_PI + 6 * M_PI) + centroX);
      int yM14 = (int)(R3 * cos(anguloM3 + M_PI + 6 * M_PI) + centroY);
      if (xM14 >= 0 && xM14 < maxX && yM14 >= 0 && yM14 < maxY) {
        plano[yM14][xM14] = 'p';
      }
    }
    if (numcaracterSorteado >= 25) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM15 = (int)(a * cos(anguloM3 + M_PI + 11 * M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM15 = (int)(a * cos(anguloM3 + M_PI + 11 * M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM15 >= 0 && xM15 < maxX && yM15 >= 0 && yM15 < maxY) {
        plano[yM15][xM15] = '$';
      }
    }
    if (numcaracterSorteado >= 26) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM16 = (int)(a * cos(anguloM3 + M_PI + 6 * M_PI) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM16 = (int)(a * cos(anguloM3 + M_PI + 6 * M_PI) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM16 >= 0 && xM16 < maxX && yM16 >= 0 && yM16 < maxY) {
        plano[yM16][xM16] = '$';
      }
    }
    if (numcaracterSorteado >= 27) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM17 = (int)(a * cos(anguloM3 + M_PI + 5 * M_PI / 2) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM17 = (int)(a * cos(anguloM3 + M_PI + 5 * M_PI / 2) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM17 >= 0 && xM17 < maxX && yM17 >= 0 && yM17 < maxY) {
        plano[yM17][xM17] = 'l';
      }
    }
    if (numcaracterSorteado >= 28) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM18 = (int)(a * cos(anguloM3 + M_PI + 9 * M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM18 = (int)(a * cos(anguloM3 + M_PI + 9 * M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM18 >= 0 && xM18 < maxX && yM18 >= 0 && yM18 < maxY) {
        plano[yM18][xM18] = 'h';
      }
    }
    if (numcaracterSorteado >= 29) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM19 = (int)(a * cos(anguloM3 + M_PI + 2 * M_PI) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM19 = (int)(a * cos(anguloM3 + M_PI + 2 * M_PI) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM19 >= 0 && xM19 < maxX && yM19 >= 0 && yM19 < maxY) {
        plano[yM19][xM19] = 'z';
      }
    }
    if (numcaracterSorteado >= 30) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 75;
      double theta = inclinacao * (M_PI / 180.0);
      int xM20 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM20 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM20 >= 0 && xM20 < maxX && yM20 >= 0 && yM20 < maxY) {
        plano[yM20][xM20] = 'x';
      }
    }
    if (numcaracterSorteado >= 31) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM21 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI / 2) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM21 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI / 2) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM21 >= 0 && xM21 < maxX && yM21 >= 0 && yM21 < maxY) {
        plano[yM21][xM21] = '-';
      }
    }
    if (numcaracterSorteado >= 32) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM22 = (int)(a * cos(anguloM3 + M_PI + 5 * M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM22 = (int)(a * cos(anguloM3 + M_PI + 5 * M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM22 >= 0 && xM22 < maxX && yM22 >= 0 && yM22 < maxY) {
        plano[yM22][xM22] = '0';
      }
    }
    if (numcaracterSorteado >= 33) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM23 = (int)(a * cos(anguloM3 + M_PI + M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM23 = (int)(a * cos(anguloM3 + M_PI + M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM23 >= 0 && xM23 < maxX && yM23 >= 0 && yM23 < maxY) {
        plano[yM23][xM23] = '$';
      }
    }
    if (numcaracterSorteado >= 34) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM24 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI / 2) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM24 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI / 2) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM24 >= 0 && xM24 < maxX && yM24 >= 0 && yM24 < maxY) {
        plano[yM24][xM24] = '+';
      }
    }
    if (numcaracterSorteado >= 35) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM25 = (int)(a * cos(anguloM3 + M_PI) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM25 = (int)(a * cos(anguloM3 + M_PI) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM25 >= 0 && xM25 < maxX && yM25 >= 0 && yM25 < maxY) {
        plano[yM25][xM25] = ',';
      }
    }
    if (numcaracterSorteado >= 36) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM26 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM26 = (int)(a * cos(anguloM3 + M_PI + 3 * M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM26 >= 0 && xM26 < maxX && yM26 >= 0 && yM26 < maxY) {
        plano[yM26][xM26] = '.';
      }
    }
    if (numcaracterSorteado >= 37) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM27 = (int)(a * cos(anguloM3 + M_PI + 5 * M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM27 = (int)(a * cos(anguloM3 + M_PI + 5 * M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM27 >= 0 && xM27 < maxX && yM27 >= 0 && yM27 < maxY) {
        plano[yM27][xM27] = '@';
      }
    }
    if (numcaracterSorteado >= 38) {
      double a = R3 * 1.5;
      double b = R2 * 0.25;
      double inclinacao = 45;
      double theta = inclinacao * (M_PI / 180.0);
      int xM28 = (int)(a * cos(anguloM3 + M_PI + M_PI / 4) * cos(theta) - b * sin(anguloM3) * sin(theta) + centroX);
      int yM28 = (int)(a * cos(anguloM3 + M_PI + M_PI / 4) * sin(theta) + b * sin(anguloM3) * cos(theta) + centroY);

      if (xM28 >= 0 && xM28 < maxX && yM28 >= 0 && yM28 < maxY) {
        plano[yM28][xM28] = '%';
      }
    }

    // Imprimir o plano na tela
    for (int i = 0; i < maxY; i++) {
      mvprintw(i, 0, "%.*s", maxX, plano[i]);
    }

    for (int i = 0; i < NUM_ELEMENTS; i++) {
      int x = elements[i].group + 10;
      int y = elements[i].period - 1;

      if ((i >= 20 && i <= 29) || (i >= 38 && i <= 47) || (i >= 71 && i <= 79) || (i >= 103 && i <= 107)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(3)); 
        }
      } else if ((i == 0) || (i >= 5 && i <= 8) || (i >= 14 && i <= 16) || (i >= 33 && i <= 34) || (i == 52)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(4)); // Usa a cor personalizada 1
        }
      } else if ((i == 12) || (i == 30) || (i >= 48 && i <= 50) || (i >= 80 && i <= 83)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(5)); // Usa a cor personalizada 2
        }
      } else if ((i == 3 || i == 11) || (i == 19 || i == 37) || (i == 55 || i == 87)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(7)); // Usa a cor personalizada 4
        }
      } else if ((i == 2 || i == 10) || (i == 36 || i == 54) || (i == 18 || i == 86)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(6)); 
        }
      } else if ((i >= 88 && i <= 102)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(8)); 
        }
      } else if ((i >= 56 && i <= 70)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(9)); 
        }
      } else if ((i == 1 || i == 9) || (i == 17 || i == 35) || (i == 53 || i == 85)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(10)); 
        }
      } else if ((i == 4 || i == 13) || (i == 31 || i == 32) || (i == 50 || i == 51 || i == 84)) {
        if (i == position) {
          attron(COLOR_PAIR(1)); 
        } else {
          attron(COLOR_PAIR(11)); 
        }
      } else if (i == position) {
        attron(COLOR_PAIR(1));
      } else {
        attron(COLOR_PAIR(2));
      }

      move(y, x * 3);
      printw("%-2s", elements[i].symbol);
      attroff(COLOR_PAIR(1));
      attroff(COLOR_PAIR(2));
    }
    int xCentro = centroX;
    int yCentro = centroY;

    if (elementoSelecionado != NULL) {
      int tamanhoElemento = strlen(elementoSelecionado);

      xCentro -= tamanhoElemento / 2;
      yCentro -= 0.01;

      mvprintw(yCentro, xCentro, "%s", elementoSelecionado);
    }
    mvprintw(20, 55, "(W)\n\t\t\t\t\t\t    (A)(S)(D)");
    mvprintw(1, 0, "Número atômico: %d", position + 1);
    int vNumAtomico = position + 1;
    mvprintw(0, 0, "Distribuição eletrônica:");
    for (int i = 0; i < 4; i++) {
      mvprintw(2 + i, 0, "[%c]", i + 75);
      int limit = 2;

      for (int j = 0; j < i + 1; j++) {
        mvprintw(2 + i, j * 3 + 3, "%d ", (limit <= vNumAtomico ? limit : vNumAtomico));
        vNumAtomico -= limit;

        if (vNumAtomico <= 0)
          break;

        limit += 4;
      }
      if (vNumAtomico <= 0)
        break;
    }
    if (vNumAtomico > 0) {
      for (int i = 3; i > 0; i--) {
        int c = 'R' - i;
        int limit = 2;
        int E = (limit <= vNumAtomico ? limit : vNumAtomico);

        for (int j = 0; j < i + 1 && E > 0; j++) {
          if (c != 0) {
            mvprintw(6 + (3 - i), 0, "[%c]", 82 - i);
            c = 0;
          }
          mvprintw(6 + (3 - i), j * 3 + 3, "%d ", E);
          vNumAtomico -= E;
          E = (limit += 4) <= vNumAtomico ? limit : vNumAtomico;
        }
      }
    }
    angulo += 0.3;
    napms(100);
    int key = getch();

    switch (key) {
    case KEY_LEFT:
      position--;
      break;
    case KEY_RIGHT:
      position++;
      break;
    case KEY_UP:
      position -= TABLE_WIDTH;
      if (position < 0) {
        position += NUM_ELEMENTS;
      }
      break;
    case KEY_DOWN:
      position += TABLE_WIDTH;
      if (position >= NUM_ELEMENTS) {
        position -= NUM_ELEMENTS;
      }
      break;
          case 'a':
      position--;
      break;
    case 'd':
      position++;
      break;
    case 'w':
      position -= TABLE_WIDTH;
      if (position < 0) {
        position += NUM_ELEMENTS;
      }
      break;
    case 's':
      position += TABLE_WIDTH;
      if (position >= NUM_ELEMENTS) {
        position -= NUM_ELEMENTS;
      }
      break;
    case 'q':
    case 'Q':
      endwin();
      return 0;
    }

    if (position < 0) {
      position = NUM_ELEMENTS - 1;
    } else if (position >= NUM_ELEMENTS) {
      position = NUM_ELEMENTS - 1;
    }

    double massaNucleoAtual = massaNucleo[position + 1];
    int resultadosValidos;
    int numeroAtomico = position + 1;
    calculateQuantityVisibleResults(Rinf, me, massaNucleoAtual, numeroAtomico, & resultadosValidos);
    int n1 = 1, n2 = 2;
    int line_idxs[resultadosValidos];
    double lambda_a = 0;

    for (size_t i = 0; i < resultadosValidos;) {
      double lambda_a = 0;
      lambda_a = (1.0 / (constanteRydbergAjustada(Rinf, me, massaNucleoAtual) * numeroAtomico * numeroAtomico * ((1.0 / (n1 * n1)) - (1.0 / (n2 * n2)))));
      if (lambda_a >= 400E-9 && lambda_a <= 700E-9) {
        line_idxs[i] = inicio + (700 - lambda_a * 1e9) * (totalCores - 10.5) / (750 - 380);
        i++;
      }
      n2++;
      if (n2 <= 6) continue;
      n1++;
      n2 = n1 + 1;
    }
    WINDOW * offscreenWin = newwin(3, 87, 28, 0); // Cria uma nova janela
    for (int i = fim; i >= inicio; i--) {
      calcularCor( & cores[i], totalCores, i, saturacao, luminosidade);
      int r = cores[i].r * 1000 / 255;
      int g = cores[i].g * 1000 / 255;
      int b = cores[i].b * 1000 / 255;
      init_color(i + 16, r, g, b);
      init_pair(i + 16, COLOR_BLACK, i + 16);
      wattron(offscreenWin, COLOR_PAIR(i + 16)); // Ativa a cor na janela
      wprintw(offscreenWin, "  ");
      wattroff(offscreenWin, COLOR_PAIR(i + 16)); // Desativa a cor na janela
    }

    qsort(line_idxs, resultadosValidos, sizeof * line_idxs, ascending_int);
    for (size_t m = 0; m < 3; m++) {

      if (m == 2) {
        wprintw(offscreenWin, "\n");
        for (int i = fim, line_idx = resultadosValidos - 1; i >= inicio; i--) {
          wattron(offscreenWin, COLOR_PAIR(i + 16)); // Ativa a cor na janela
          if (line_idx >= 0 && i == line_idxs[line_idx]) {
            wprintw(offscreenWin, "%lc ", TALLBAR);
            --line_idx;
          } else {
            wprintw(offscreenWin, "  ");
          }
          wattroff(offscreenWin, COLOR_PAIR(i + 16)); // Desativa a cor na janela
        }
      } else if (m == 1) {
        wprintw(offscreenWin, "\n");
        for (int i = fim, line_idx = resultadosValidos - 1; i >= inicio; i--) {
          wattron(offscreenWin, COLOR_PAIR(i + 16) | A_REVERSE); // Ativa a cor de fundo na janela
          if (line_idx >= 0 && i == line_idxs[line_idx]) {
            wprintw(offscreenWin, "%lc ", TALLBAR);
            wattroff(offscreenWin, A_REVERSE); // Desativa a cor de fundo na janela
            --line_idx;
          } else {
            wprintw(offscreenWin, "  ");
          }
          wattroff(offscreenWin, COLOR_PAIR(i + 16) | A_REVERSE); // Desativa a cor na janela
        }
      }
    }

    wrefresh(offscreenWin); // Atualiza a janela
  }
  endwin();
  return 0;
}
void calcularCor(RGB * cores, int totalCores, int indiceAtual, float saturacao, float luminosidade) {
  float matiz = indiceAtual * (360.0 / totalCores);
  float croma = (1 - fabs(2 * luminosidade - 1)) * saturacao;
  float x = croma * (1 - fabs(fmod(matiz / 60, 2) - 1));
  float m = luminosidade - croma / 2;

  float r, g, b;
  if (matiz >= 0 && matiz < 60) {
    r = croma;
    g = x;
    b = 0;
  } else if (matiz >= 60 && matiz < 120) {
    r = x;
    g = croma;
    b = 0;
  } else if (matiz >= 120 && matiz < 180) {
    r = 0;
    g = croma;
    b = x;
  } else if (matiz >= 180 && matiz < 240) {
    r = 0;
    g = x;
    b = croma;
  } else if (matiz >= 240 && matiz < 300) {
    r = x;
    g = 0;
    b = croma;
  } else {
    r = croma;
    g = 0;
    b = x;
  }
  cores -> r = (r + m) * 255;
  cores -> g = (g + m) * 255;
  cores -> b = (b + m) * 255;
}

void calculateQuantityVisibleResults(double Rinf, double me, double massaNucleoAtual, int numeroAtomico, int * resultadosValidos) {
  int n1 = 1, n2 = 2;
  * resultadosValidos = 0; // Initialize the counter for valid results within the visible range

  // Loop to find spectral lines within the visible range
  while ( * resultadosValidos < 118) { // Assume a maximum of 4 valid results within the visible range
    // Calculate the wavelength (lambda_a) for the spectral line
    double lambda_a = 1.0 / (constanteRydbergAjustada(Rinf, me, massaNucleoAtual) * numeroAtomico * numeroAtomico * ((1.0 / (n1 * n1)) - (1.0 / (n2 * n2))));

    if (lambda_a >= 400E-9 && lambda_a <= 700E-9) {
      ( * resultadosValidos) ++; // Increment the counter for valid results within the visible range
    }

    if (lambda_a > 700E-9) {
      break; // Wavelength exceeded the visible range, exit the loop
    }

    n2++; // Increment the value of 2n
    if (n2 <= 6) {
      continue;
    }

    n1++; // Increment the value of 1n and redefine 2n to a value greater than 1n
    n2 = n1 + 1;
  }
}
       
