#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
const double PI = 3.14159265358979323846;


//NAO CUATERNIOS
struct Cuaternion {
    float real;
    float i;
    float j;
    float k;
};


Cuaternion multiplicarC(Cuaternion a, Cuaternion b) {
    Cuaternion res;


    res.real = (a.real * b.real) - (a.i * b.i) - (a.j * b.j) - (a.k * b.k);

    res.i = (a.real * b.i) + (a.i * b.real) + (a.j * b.k) - (a.k * b.j);

    res.j = (a.real * b.j) + (a.j * b.real) + (a.k * b.i) - (a.i * b.k);

    res.k = (a.real * b.k) + (a.k * b.real) + (a.i * b.j) - (a.j * b.i);

    return res;
}
//NAO TRANSFORMACIONES
struct punto {
    float x, y, z;
};

void multiplicarMatrices(float A[4][4], float B[4][4], float C[4][4]) {
    float temp[4][4] = { 0 };
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                temp[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            C[i][j] = temp[i][j];
}


//SOF 
typedef vector<vector<double>> Matriz;


// Función para leer una matriz
Matriz leerMatriz() {
    int filas, cols;
    cout << "Ingrese el numero de filas: "; cin >> filas;
    cout << "Ingrese el numero de columnas: "; cin >> cols;

    // Inicializamos la matriz con el tamaño indicado
    Matriz m(filas, vector<double>(cols));

    cout << "Ingrese los elementos de la matriz (" << filas << "x" << cols << "):" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < cols; j++) {
            cout << "Elemento [" << i << "][" << j << "]: ";
            cin >> m[i][j];
        }
    }
    return m;
}

// Función para imprimir una matriz en consola
void mostrarMatriz(const Matriz& m) {
    if (m.empty()) return;
    for (const auto& fila : m) {
        for (double elemento : fila) {
            cout << setw(10) << elemento << " ";
        }
        cout << endl;
    }
}


// Suma de matrices
Matriz sumar(const Matriz& A, const Matriz& B) {
    int filas = A.size();
    if (filas == 0 || B.size() == 0 || filas != B.size() || A[0].size() != B[0].size()) {
        cout << "Error: Dimensiones incompatibles para suma." << endl;
        return Matriz();
    }
    int cols = A[0].size();
    Matriz resultado(filas, vector<double>(cols));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < cols; ++j) {
            resultado[i][j] = A[i][j] + B[i][j];
        }
    }
    return resultado;
}

// Resta de matrices
Matriz restar(const Matriz& A, const Matriz& B) {
    int filas = A.size();
    if (filas == 0 || B.size() == 0 || filas != B.size() || A[0].size() != B[0].size()) {
        cout << "Error: Dimensiones incompatibles para resta." << endl;
        return Matriz();
    }
    int cols = A[0].size();
    Matriz resultado(filas, vector<double>(cols));

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < cols; ++j) {
            resultado[i][j] = A[i][j] - B[i][j];
        }
    }
    return resultado;
}

// Producto de matrices
Matriz multiplicar(const Matriz& A, const Matriz& B) {
    int filasA = A.size();
    if (filasA == 0 || B.size() == 0 || A[0].size() != B.size()) {
        // Validación básica de dimensiones
        cout << "Error: Dimensiones incompatibles para producto." << endl;
        return Matriz();
    }
    int colsA = A[0].size();
    int colsB = B[0].size();
    Matriz resultado(filasA, vector<double>(colsB, 0.0));

    for (int i = 0; i < filasA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            for (int k = 0; k < colsA; ++k) {
                resultado[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return resultado;
}


// Matriz Compuesta
// Función para crear una matriz identidad de 4x4
Matriz identidad() {
    Matriz m(4, vector<double>(4, 0.0));
    for (int i = 0; i < 4; i++) m[i][i] = 1.0;
    return m;
}

// Matriz de Traslación
Matriz traslacion(double tx, double ty, double tz) {
    Matriz m = identidad();
    m[0][3] = tx; m[1][3] = ty; m[2][3] = tz;
    return m;
}

// Matriz de Rotación en X
Matriz rotX(double rad) {
    Matriz m = identidad();
    m[1][1] = cos(rad);  m[1][2] = -sin(rad);
    m[2][1] = sin(rad);  m[2][2] = cos(rad);
    return m;
}

// Matriz de Rotación en Y
Matriz rotY(double rad) {
    Matriz m = identidad();
    m[0][0] = cos(rad);  m[0][2] = sin(rad);
    m[2][0] = -sin(rad); m[2][2] = cos(rad);
    return m;
}

// Matriz de Rotación en Z
Matriz rotZ(double rad) {
    Matriz m = identidad();
    m[0][0] = cos(rad);  m[0][1] = -sin(rad);
    m[1][0] = sin(rad);  m[1][1] = cos(rad);
    return m;
}


//VANOYE 
struct Point {
    int x;
    int y;
};

// --- LINEA BRESENHAM ---
void CalculateLineBresenham(Point p0, Point p1) {
    int dx = abs(p1.x - p0.x);
    int dy = abs(p1.y - p0.y);
    int p = 2 * dy - dx;
    int x = p0.x;
    int y = p0.y;

    cout << "\n========================================" << endl;
    cout << "       BRESENHAM LINEA (POR PASOS)      " << endl;
    cout << "========================================" << endl;
    cout << "Parametros: dx=" << dx << " dy=" << dy << endl;
    cout << "Constantes: 2dy=" << 2 * dy << " | 2dy-2dx=" << 2 * dy - 2 * dx << endl;

    cout << "PASO K: 0 | Punto Inicial: (" << x << ", " << y << ")" << endl;

    for (int k = 0; k < dx; ++k) {
        string cond = (p < 0) ? "pk < 0" : "pk >= 0";
        int pk_usado = p;

        x++;
        if (p < 0) {
            p = p + 2 * dy;
        }
        else {
            y++;
            p = p + 2 * dy - 2 * dx;
        }

        cout << "----------------------------------------" << endl;
        cout << "PASO K: " << k + 1 << " | Usando " << cond << " (" << pk_usado << ")" << endl;
        cout << "Nuevo Punto: (" << x << ", " << y << ")" << endl;
        cout << "Siguiente pk: " << p << endl;
    }
}

// --- CIRCULO PUNTO MEDIO ---
void CalculateCircleMidpoint(int radius, Point center) {
    double x = 0;
    double y = radius;
    double p = 1 - (double)radius;
    vector<Point> octante;

    cout << fixed << setprecision(4);
    cout << "\n========================================" << endl;
    cout << "      CIRCULO PUNTO MEDIO (POR PASOS)    " << endl;
    cout << "========================================" << endl;

    octante.push_back({ (int)x, (int)y });
    int k = 0;

    cout << "PASO K: 0 | Punto Inicial: (" << (int)x << ", " << (int)y << ")" << endl;
    cout << "Trasladado: (" << (int)x + center.x << ", " << (int)y + center.y << ")" << endl;
    cout << "p Inicial: " << p << endl;

    while (x < y) {
        k++;
        string cond = (p < 0) ? "pk < 0" : "pk >= 0";
        double pk_usado = p;
        double inc;

        x++;
        if (p < 0) {
            inc = (2.0 * x) + 1.0;
            p = p + inc;
        }
        else {
            y--;
            inc = (2.0 * x) + 1.0 - (2.0 * y);
            p = p + inc;
        }
        octante.push_back({ (int)x, (int)y });

        cout << "----------------------------------------" << endl;
        cout << "PASO K: " << k << " | Usando " << cond << " (" << pk_usado << ")" << endl;
        cout << "Operacion: p + inc = " << pk_usado << " + " << inc << endl;
        cout << "Punto Actual: (" << (int)x << ", " << (int)y << ")" << endl;
        cout << "Trasladado:   (" << (int)x + center.x << ", " << (int)y + center.y << ")" << endl;
        cout << "Siguiente pk: " << p << endl;
    }

    cout << "\n--- REFLEXION PARA COMPLETAR CUADRANTE ---" << endl;
    for (int i = (int)octante.size() - 2; i >= 0; --i) {
        k++;
        int xr = octante[i].y;
        int yr = octante[i].x;
        cout << "----------------------------------------" << endl;
        cout << "PASO K: " << k << " | REFLEXION SIMETRICA" << endl;
        cout << "Punto: (" << xr << ", " << yr << ")" << endl;
        cout << "Trasladado: (" << xr + center.x << ", " << yr + center.y << ")" << endl;
    }
}

// --- ELIPSE PUNTO MEDIO ---
void CalculateEllipseMidpoint(int rx, int ry, Point center) {
    double x = 0;
    double y = (double)ry;
    double rx2 = (double)rx * rx;
    double ry2 = (double)ry * ry;
    double px = 0;
    double py = 2.0 * rx2 * y;

    cout << fixed << setprecision(4);
    cout << "\n========================================" << endl;
    cout << "      ELIPSE PUNTO MEDIO (POR PASOS)     " << endl;
    cout << "========================================" << endl;

    double p1 = ry2 - (rx2 * ry) + (0.25 * rx2);
    int k = 0;

    cout << ">>> REGION 1 <<<" << endl;
    cout << "PASO K: 0 | Punto Inicial: (" << (int)x << ", " << (int)y << ")" << endl;
    cout << "Trasladado:  (" << (int)x + center.x << ", " << (int)y + center.y << ")" << endl;
    cout << "p1 Inicial: " << p1 << endl;

    while (px < py) {
        k++;
        string cond = (p1 < 0) ? "p1k < 0" : "p1k >= 0";
        double pk_usado = p1;
        x++;
        px += 2.0 * ry2;
        if (p1 < 0) {
            p1 += ry2 + px;
        }
        else {
            y--;
            py -= 2.0 * rx2;
            p1 += ry2 + px - py;
        }
        cout << "----------------------------------------" << endl;
        cout << "PASO K: " << k << " | Usando " << cond << " (" << pk_usado << ")" << endl;
        cout << "Punto Actual: (" << (int)x << ", " << (int)y << ")" << endl;
        cout << "Trasladado:   (" << (int)x + center.x << ", " << (int)y + center.y << ")" << endl;
        cout << "2ry2x: " << px << " | 2rx2y: " << py << endl;
        cout << "Siguiente pk: " << p1 << endl;
    }

    cout << "\n>>> REGION 2 (EMPALME) <<<" << endl;
    double p2 = (ry2 * (x + 0.5) * (x + 0.5)) + (rx2 * (y - 1.0) * (y - 1.0)) - (rx2 * ry2);
    cout << "p2 Inicial: " << p2 << endl;
    cout << "----------------------------------------" << endl;

    while (y > 0) {
        k++;
        string cond = (p2 > 0) ? "p2k > 0" : "p2k <= 0";
        double pk_usado = p2;
        y--;
        py -= 2.0 * rx2;
        if (p2 > 0) {
            p2 += rx2 - py;
        }
        else {
            x++;
            px += 2.0 * ry2;
            p2 += rx2 - py + px;
        }
        cout << "PASO K: " << k << " | Usando " << cond << " (" << pk_usado << ")" << endl;
        cout << "Punto Actual: (" << (int)x << ", " << (int)y << ")" << endl;
        cout << "Trasladado:   (" << (int)x + center.x << ", " << (int)y + center.y << ")" << endl;
        cout << "2ry2x: " << px << " | 2rx2y: " << py << endl;
        cout << "Siguiente pk: " << p2 << endl;
        cout << "----------------------------------------" << endl;
    }
}

int main() {
    int op;
    do {
        cout << "\n\t\n MENU PRINCIPAL" << endl;
        cout << "1. Suma, Resta y Producto (Matrices)" << endl;
        cout << "2. Matriz Compuesta" << endl;
        cout << "3. Cuaterniones" << endl;
        cout << "4. Transformaciones y Perspectiva" << endl;
        cout << "5. Trazo de curvas" << endl;
        cout << "====================================" << endl;
        cout << "Seleccione: "; cin >> op;

        switch (op) {
        case 1: {
            int operacionInicial;
            cout << "\n¿Que operacion desea realizar primero?" << endl;
            cout << "1. Suma (+)\n2. Resta (-)\n3. Producto (*)" << endl;
            cout << "Opcion: ";
            cin >> operacionInicial;

            // Pedimos las dos matrices iniciales
            cout << "\n--- Ingrese Matriz A ---" << endl;
            Matriz resultado = leerMatriz();
            cout << "\n--- Ingrese Matriz B ---" << endl;
            Matriz B = leerMatriz();

            // Ejecutamos la primera operacion
            if (operacionInicial == 1) resultado = sumar(resultado, B);
            else if (operacionInicial == 2) resultado = restar(resultado, B);
            else if (operacionInicial == 3) resultado = multiplicar(resultado, B);

            // Submenú para seguir operando
            bool terminarSub = false;
            while (!terminarSub) {
                if (resultado.empty()) {
                    cout << "La operacion fallo. Reiniciando operacion..." << endl;
                    break;
                }
                cout << "\n>>> Matriz Actual:" << endl;
                mostrarMatriz(resultado);

                cout << "\n¿Desea hacer algo mas con este resultado?" << endl;
                cout << "1. Sumar (+)  2. Restar (-)  3. Multiplicar (*)  4. Terminar" << endl;
                cout << "Opcion: ";
                int opSub; cin >> opSub;

                if (opSub == 4) {
                    terminarSub = true;
                }
                else {
                    cout << "\nIngrese la siguiente matriz: " << endl;
                    Matriz nueva = leerMatriz();

                    if (opSub == 1) resultado = sumar(resultado, nueva);
                    else if (opSub == 2) resultado = restar(resultado, nueva);
                    else if (opSub == 3) resultado = multiplicar(resultado, nueva);
                }
            }

         
            break;
        }
        case 2: {
            // Matriz Compuesta
            double x1, y1, z1, x2, y2, z2, angulo;
            int numPuntos;
            cout << "--- Datos del Vector Eje ---" << endl;
            cout << "Punto V1 (x y z): "; cin >> x1 >> y1 >> z1;
            cout << "Punto V2 (x y z): "; cin >> x2 >> y2 >> z2;
            cout << "Angulo de rotacion (grados): "; cin >> angulo;

            cout << "\n¿Cuantos puntos desea transformar? ";
            cin >> numPuntos;

            vector<vector<double>> puntos(numPuntos, vector<double>(4, 1.0));
            for (int i = 0; i < numPuntos; i++) {
                cout << "Ingrese punto " << i + 1 << " (x y z): ";
                cin >> puntos[i][0] >> puntos[i][1] >> puntos[i][2];
                puntos[i][3] = 1.0; // Coordenada homogénea
            }

            double dx = x2 - x1;
            double dy = y2 - y1;
            double dz = z2 - z1;

            Matriz M_Resultante = identidad();
            Matriz T = traslacion(-x1, -y1, -z1);
            Matriz Ti = traslacion(x1, y1, z1);
            double rad = angulo * PI / 180.0;

            cout << "\n[Analizando vector...]" << endl;

            if (dy == 0 && dz == 0) {
                cout << "Resultado: Paralelo al eje X." << endl;
                M_Resultante = multiplicar(Ti, multiplicar(rotX(rad), T));
            }
            else if (dx == 0 && dz == 0) {
                cout << "Resultado: Paralelo al eje Y." << endl;
                M_Resultante = multiplicar(Ti, multiplicar(rotY(rad), T));
            }
            else if (dx == 0 && dy == 0) {
                cout << "Resultado: Paralelo al eje Z." << endl;
                M_Resultante = multiplicar(Ti, multiplicar(rotZ(rad), T));
            }
            else {
                cout << "Resultado: Eje Arbitrario (7 matrices)." << endl;
                double L = sqrt(dx * dx + dy * dy + dz * dz);
                double a = dx / L, b = dy / L, c = dz / L;
                double d = sqrt(b * b + c * c);
                double cosAlpha = c / d; double sinAlpha = b / d;
                double cosBeta = d; double sinBeta = -a;

                Matriz Rx = identidad();
                Rx[1][1] = cosAlpha; Rx[1][2] = -sinAlpha; Rx[2][1] = sinAlpha; Rx[2][2] = cosAlpha;
                Matriz Rxi = identidad();
                Rxi[1][1] = cosAlpha; Rxi[1][2] = sinAlpha; Rxi[2][1] = -sinAlpha; Rxi[2][2] = cosAlpha;
                Matriz Ry = identidad();
                Ry[0][0] = cosBeta; Ry[0][2] = sinBeta; Ry[2][0] = -sinBeta; Ry[2][2] = cosBeta;
                Matriz Ryi = identidad();
                Ryi[0][0] = cosBeta; Ryi[0][2] = -sinBeta; Ryi[2][0] = sinBeta; Ryi[2][2] = cosBeta;
                Matriz Rz = rotZ(rad);

                M_Resultante = T;
                M_Resultante = multiplicar(Rx, M_Resultante);
                M_Resultante = multiplicar(Ry, M_Resultante);
                M_Resultante = multiplicar(Rz, M_Resultante);
                M_Resultante = multiplicar(Ryi, M_Resultante);
                M_Resultante = multiplicar(Rxi, M_Resultante);
                M_Resultante = multiplicar(Ti, M_Resultante);
            }

            cout << "\n--- RESULTADOS DE LA TRANSFORMACION ---" << endl;
            cout << fixed << setprecision(4);
            cout << "-------------------------------------------" << endl;

            for (int k = 0; k < numPuntos; k++) {
                vector<double> Pf(4, 0.0);
                for (int i = 0; i < 4; i++) {
                    for (int j = 0; j < 4; j++) {
                        Pf[i] += M_Resultante[i][j] * puntos[k][j];
                    }
                }
                cout << "Punto " << k + 1 << " transformado: (" << Pf[0] << ", " << Pf[1] << ", " << Pf[2] << ")" << endl;
            }
            cout << "-------------------------------------------" << endl;

            
            break;
        }
        case 3: {
            double grados, vx, vy, vz, px, py, pz;

            cout << "Rotacion con Cuaterniones" << endl;
            cout << "Grados: "; cin >> grados;
            cout << "Vector eje (x y z): "; cin >> vx >> vy >> vz;
            cout << "Punto a rotar (x y z): "; cin >> px >> py >> pz;

            double radianes = (grados * PI) / 180.0;
            double normaEje = sqrt(vx * vx + vy * vy + vz * vz);

            double ux = vx / normaEje;
            double uy = vy / normaEje;
            double uz = vz / normaEje;

            Cuaternion q;
            q.real = cos(radianes / 2.0);
            q.i = ux * sin(radianes / 2.0);
            q.j = uy * sin(radianes / 2.0);
            q.k = uz * sin(radianes / 2.0);

            Cuaternion qInv = { q.real, -q.i, -q.j, -q.k };

            Cuaternion p = { 0, px, py, pz };

            Cuaternion primeromult = multiplicarC(q, p);
            Cuaternion RQ = multiplicarC(primeromult, qInv);


            cout << fixed << setprecision(4);
            cout << "\nResultados" << endl;
            cout << "Cuaternion q: " << q.real << " + " << q.i << "i + " << q.j << "j + " << q.k << "k" << endl;
            cout << "Cuaternion q^-1:  " << qInv.real << " + (" << qInv.i << "i + " << qInv.j << "j + " << qInv.k << "k)" << endl;
            cout << "Resultado final RQ:" << RQ.i << "i + " << RQ.j << "j + " << RQ.k << "k" << endl;


            break;
        }
        case 4: {
            int numPuntos;
            cout << "INGRESAR DATOS\n";
            cout << "Cuantos puntos tiene su figura? ";
            while (!(cin >> numPuntos)) {
                cout << "Error. Por favor, ingresa un numero entero: ";

                cin.clear();
            }

            vector<punto> figura(numPuntos);
            for (int i = 0; i < numPuntos; i++) {
                cout << "Punto " << i + 1 << " (x y z): ";
                cin >> figura[i].x >> figura[i].y >> figura[i].z;
            }

            float zprp;
            cout << "\nIngrese Zprp: "; cin >> zprp;

            float matrizglobal[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };
            int opcion;

            do {
                cout << "\n MENU DE TRANSFORMACIONES\n";
                cout << "1. Trasladar\n2. Escalar\n3. Rotar X\n4. Rotar Y\n5. Rotar Z\n6. Resultado\n";
                cout << "Seleccione: "; cin >> opcion;

                if (opcion == 6) break;

                
                float M[4][4] = { {1,0,0,0}, {0,1,0,0}, {0,0,1,0}, {0,0,0,1} };

                switch (opcion) {
                case 1: { // TRASLACIÓN
                    float dx, dy, dz;
                    cout << "Ingrese dx, dy, dz: "; cin >> dx >> dy >> dz;
                    M[0][3] = dx; M[1][3] = dy; M[2][3] = dz;
                    break;
                }
                case 2: { // ESCALACIÓN
                    float sx, sy, sz;
                    cout << "Ingrese factores sx, sy, sz: "; cin >> sx >> sy >> sz;
                    M[0][0] = sx; M[1][1] = sy; M[2][2] = sz;
                    break;
                }
                case 3: case 4: case 5: { // ROTACIONES
                    float ang, rad;
                    cout << "Angulo en grados: "; cin >> ang;
                    rad = ang * (float)PI / 180.0f;
                    float c = cos(rad);
                    float s = sin(rad);

                    if (opcion == 3) { // RX
                        M[1][1] = c; M[1][2] = -s;
                        M[2][1] = s; M[2][2] = c;
                    }
                    else if (opcion == 4) { // RY 
                        M[0][0] = c;  M[0][2] = s;
                        M[2][0] = -s; M[2][2] = c;
                    }
                    else { // RZ
                        M[0][0] = c; M[0][1] = -s;
                        M[1][0] = s; M[1][1] = c;
                    }
                    break;
                }
                }

               
                float temp[4][4];
                multiplicarMatrices(matrizglobal, M, temp);

                for (int i = 0; i < 4; i++)
                    for (int j = 0; j < 4; j++)
                        matrizglobal[i][j] = temp[i][j];

            } while (true);

            cout << "\n" << setfill('=') << setw(40) << "" << endl;
            cout << "\t RESULTADOS" << endl;
            cout << setfill('=') << setw(40) << "" << endl;
            cout << fixed << setprecision(2);

            for (int i = 0; i < numPuntos; i++) {
                punto p = figura[i];

                float nx = matrizglobal[0][0] * p.x + matrizglobal[0][1] * p.y + matrizglobal[0][2] * p.z + matrizglobal[0][3];
                float ny = matrizglobal[1][0] * p.x + matrizglobal[1][1] * p.y + matrizglobal[1][2] * p.z + matrizglobal[1][3];
                float nz = matrizglobal[2][0] * p.x + matrizglobal[2][1] * p.y + matrizglobal[2][2] * p.z + matrizglobal[2][3];

                float xy = zprp / (zprp - nz);
                float xp = nx * xy;
                float yp = ny * xy;

                cout << "Punto " << i + 1 << " Original: (" << p.x << ", " << p.y << ", " << p.z << ")\n";
                cout << "\tTransformado: (" << nx << ", " << ny << ", " << nz << ")\n";
                cout << "\tCierta perspectiva: (" << xp << ", " << yp << ")\n\n";



            }
            break;
        }
        case 5: {

            int opcion;
            do {
                cout << "\n========================================" << endl;
                cout << "      MENU DE ALGORITMOS GRAFICOS      " << endl;
                cout << "========================================" << endl;
                cout << "1. Linea (Bresenham)" << endl;
                cout << "2. Circulo (Punto Medio)" << endl;
                cout << "3. Elipse (Punto Medio)" << endl;
                cout << "4. Salir" << endl;
                cout << "Seleccione una opcion: ";

                if (!(cin >> opcion)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                switch (opcion) {
                case 1: {
                    Point p0, p1;
                    cout << "\n--- Datos de la Linea ---" << endl;
                    cout << "Ingrese x0: "; cin >> p0.x;
                    cout << "Ingrese y0: "; cin >> p0.y;
                    cout << "Ingrese x1: "; cin >> p1.x;
                    cout << "Ingrese y1: "; cin >> p1.y;
                    CalculateLineBresenham(p0, p1);
                    break;
                }
                case 2: {
                    int r; Point c;
                    cout << "\n--- Datos del Circulo ---" << endl;
                    cout << "Ingrese el Radio: "; cin >> r;
                    cout << "Ingrese Centro X: "; cin >> c.x;
                    cout << "Ingrese Centro Y: "; cin >> c.y;
                    CalculateCircleMidpoint(r, c);
                    break;
                }
                case 3: {
                    int rx, ry; Point c;
                    cout << "\n--- Datos de la Elipse ---" << endl;
                    cout << "Ingrese Radio X (rx): "; cin >> rx;
                    cout << "Ingrese Radio Y (ry): "; cin >> ry;
                    cout << "Ingrese Centro X: "; cin >> c.x;
                    cout << "Ingrese Centro Y: "; cin >> c.y;
                    CalculateEllipseMidpoint(rx, ry, c);
                    break;
                }
                case 4:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opcion no valida, intente de nuevo." << endl;
                }
            } while (opcion != 4);
            break;
        }
        case 6:
            cout << "Saliendo del programa principal..." << endl;
            break;

        default:
            cout << "Opcion de menu principal no valida." << endl;
            break;
       
        }
    } while (op != 6);
   return 0;
}