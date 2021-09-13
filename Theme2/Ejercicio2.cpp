#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<ll> valoresDePrueba{ -1, 0, 1, 2, 3, 5, 15, 20, 100, 409, 500, 593, 1000, 1471, 1500, 2801, 3000, 5000, 10000, 20000 };

ll codigo1(ll n) {
    ll ans = 0, temp;
    vector<int> A(n + 1);
    ans++; //para la primera asignación de i
    for (int i = 1;i < n;i++) {//ans++ por el incremento
        ans++; //comparacion
        ans++; // incremento de i
        ans++; //para la primera asignación de j
        for (int j = n; j > 1; j /= 2) {//ans++ por la division
            ans++;//comparacion
            ans++;
            temp = A[j];
            ans++; // operacion pasada
            A[j] = A[j + 1];
            ans += 2; // operacion pasada
            A[j + 1] = temp;
            ans += 2; // operacion pasada
        }
        ans++;//j>1 falso
    }
    ans++;//i<n falso
    return ans;
}
ll formula1(ll n) {
    return n >= 2 ? 2 + (n - 1) * (4 + (int)log2(n) * 7) : 2;
}

ll codigo2(ll n) {
    int z = 1, ans = 0;
    vector<int> A(n + 1);

    int polinomio = 0;
    ans++;//asignacion de polinomio
    ans++;//asignacion de i
    for (int i = 0; i <= n; i++) {
        ans++;// i<=n verdadero
        ans++;//i++
        polinomio = polinomio * z + A[n - i];
        ans += 4; // operaciones de la linea anterior
    }
    ans++;//i<=n falso
    return ans;
}
ll formula2(ll n) {
    return 3 + (n + 1) * 6;
}
//TODO: chacar hasta cual imprimir y justificar que no se puede imprimir con 20000 pues tarda 22 horas
ll codigo3(ll n) {
    if (n > 1500)return -1;
    vector<vector<ll> > A(n + 1, vector<ll>(n + 1, 0));
    vector<vector<ll> > B(n + 1, vector<ll>(n + 1, 0));
    vector<vector<ll> > C(n + 1, vector<ll>(n + 1));

    ll ans = 0;
    ans++;// asignacion de i
    for (ll i = 1;i <= n;i++) {
        ans++;//i++
        ans++;// i<=n true
        ans++;// asignacion de j
        for (ll j = 1;j <= n;j++) {
            ans++;//j++
            ans++;// j<=n true
            C[i][j] = 0;
            ans++;// asignacion de C[i][j]
            ans++;// asignacion de k
            for (ll k = 1;k <= n;k++) {
                ans++;//k++
                ans++;// k<=n true
                C[i][j] = C[i][j] + A[i][k] * B[k][j];
                ans += 3; // asignacion,suma y mult pasada
            }
            ans++;// k<=n false
        }
        ans++;// j<=n false
    }
    ans++;// i<=n false
    return ans;
}
ll formula3(ll n) {
    if (n > 1500)return -1;
    return n >= 0 ? 2 + n * (4 + n * (5 + n * 5)) : 2;
}

ll codigo4(ll n) {
    int ans = 0, aux;

    int anterior = 1;
    ans++; // asignacion anterior
    int actual = 1;
    ans++; // asignacion anterior
    while (n > 2) {
        ans++;// n > 2 true
        aux = anterior + actual;
        ans += 2; //asignacion y suma
        anterior = actual;
        ans++; // asignacion anterior
        actual = aux;
        ans++; // asignacion anterior
        n = n - 1;
        ans += 2; // asignacion y resta
    }
    ans++; // n>2 false
    return ans;
}
ll formula4(ll n) {
    return n >= 2 ? 3 + (n - 2) * 7 : 3;
}

ll codigo5(ll n) {
    int ans = 0;
    vector<int> s(n + 100), s2(n + 100);
    int i, j = 0;
    ans += 3;//i = n - 1; j = 0;
    for (i = n - 1; i >= 0; i--, j++) {
        ans++;//i>=0 true
        ans++;//i--;
        ans++;//j++;
        s2[j] = s[i];
        ans++;//asignacion anterior
    }
    ans++;//i>=0 false
    ans++;//k=0;
    for (int k = 0; k < n; k++) {
        ans++;//k<n
        ans++;//k++
        s[i] = s2[i];
        ans++;//asignacion anterior
    }
    ans++;//k<n
    return ans;
}
ll formula5(ll n) {
    return n == -1 ? 6 : 6 + 4 * n + 3 * n;
}

ll codigo6(ll n) {
    int ans = 0;
    int l = (a < b) ? a : b;
    ans += 2;//comparacion y asginacion pasada
    r = 1;
    ans++;
    //asignacion de r
    ans++;
    //i=2
    for (int i = 2; i <= l; i++) {
        ans++;
        //i<=l
        ans++;
        //i++;
        //para contar de forma apropiada cambiamos el if
        //ya que si a%i == 0 es falso el compilador ya no revisa b%i == 0
        // if(a%i == 0 and b%i == 0){
        //     r = i;
        //     ans++;
        // }
        bool fir = a % i == 0;
        //no contamos la asignacion solo el modulo y la comparacion
        ans += 2;
        if (first) {
            bool sec = b % i == 0;
            //no contamos la asignacion solo el modulo y la comparacion
            ans += 2;
            ans++;//por el and que omitimos
            if (sec) {
                r = i;
                ans++;// por la asignacion pasada
            }
        }
    }
    ans++;
    //i<=l false
    return ans;
}

string formula6(ll n) {
    return "?";
}

ll codigo7(ll n) {
    vector<int> lista(n + 1);
    int ans = 0;
    ans++;//i=1
    for (int i = 1; i < n; i++) {
        ans++;//i<n true
        ans++;//i++
        ans++;//j=0
        for (int j = 0; j < n - 1; j++) {
            ans++;//j < n-1 true
            ans++;//j++
            ans++;//comparacion siguiente
            if (lista[j] > lista[j + 1]) {
                temp = lista[j];
                ans++; // asignacion pasada
                lista[j] = lista[j + 1];
                ans += 2;//asignacion y suma pasada
                lista[j + 1] = temp;
                ans += 2;//asignacion y suma pasada
            }
        }
        ans++;//j < n-1 false 
    }
    ans++;//i<n false
    return ans;
}

string formula7(ll n) {
    return "?";
}

int main() {

    cout << "Codigo 01: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: " << n << " Simulacion: " << codigo1(n) << " Formula: " << formula1(n) << " ";
        if (codigo1(n) != formula1(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 02: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: " << n << " Simulacion: " << codigo2(n) << " Formula: " << formula2(n) << " ";
        if (codigo2(n) != formula2(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 03: " << endl;
    for (ll n : valoresDePrueba) {
        string ans = codigo3(n) == -1 ? "?" : to_string(formula3(n));
        cout << "Para n: " << n << " Simulacion: " << ans << " Formula: " << formula3(n) << " ";
        if (formula3(n) != formula3(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 04: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: " << n << " Simulacion: " << codigo4(n) << " Formula: " << formula4(n) << " ";
        if (codigo4(n) != formula4(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 05: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: " << n << " Simulacion: " << codigo5(n) << " Formula: " << formula5(n) << " ";
        if (codigo5(n) != formula5(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }
    return 0;
}
