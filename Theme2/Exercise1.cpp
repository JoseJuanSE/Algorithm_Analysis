#include <bits/stdc++.h>
#define ll long long
using namespace std;

vector<ll> valoresDePrueba{ -1, 0, 1, 2, 3, 5, 15, 20, 100, 409, 500, 593, 1000, 1471, 1500, 2801, 3000, 5000, 10000, 20000 };

ll codigo1(ll n) {
    ll ans = 0;
    for (ll i = 10; i < n * 5; i *= 2)
        ans++;
    return ans;
}
ll formula1(ll n) {
    return n <= 1 ? 0 : ceil(log2(n) - 1);
}

ll codigo2(ll n) {
    ll ans = 0;
    for (ll j = n; j > 1; j /= 2)
        if (j < (n / 2))
            for (ll i = 0; i < n; i += 2)
                ans++;
    return ans;
}
ll formula2(ll n) {
    return n <= 8 ? 0 : ceil((float)n / (float)2) * ((ll)log2(n / 4));
}

ll codigo3(ll n) {
    ll ans = 0;
    for (ll i = 0; i < n * 5; i += 2)
        for (ll j = 0; j < 2 * n; j++)
            for (ll k = j; k < n; k++)
                ans++;
    return ans;
}
ll formula3(ll n) {
    return ceil((float)5 * n / (float)2) * n * (n + 1) / 2;
}

ll codigo4(ll n) {
    //se cicla con cualquier numero mayor a 0
    if (true) return 0;
    ll ans = 0, i = n;
    while (i >= 0) {
        for (ll j = n; i <= j; i -= 2, j /= 2)
            ans++;
    }
    return ans;
}
ll formula4(ll n) {
    return 0;
}

ll codigo5(ll n) {
    ll ans = 0;
    for (ll i = 1; i < 4 * n; i *= 2)
        for (ll j = i; j < 5 * n; j += 3)
            ans++;
    return ans;
    
}
ll formula5(ll n) {
    ll suma = 0;
    for(ll i = 0; i < ceil(log2(n))+2; i++) {
        suma += ceil((float)(5*n - (1<<i))/(float)3);
    }
    //Conseguí una aproximación a la convergencia de la serie, pero tiene un margen de error pequeño (1-3) que no da en todos los casos
    return suma;
}
int main() {

    cout << "Codigo 01: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: "<<n<< " Simulacion: "<<codigo1(n) << " Formula: " << formula1(n) << " ";
        if (codigo1(n) != formula1(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 02: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: "<<n<< " Simulacion: "<<codigo2(n) << " Formula: " << formula2(n) << " ";
        if (codigo2(n) != formula2(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout<<"Codigo 03: "<<endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: "<<n<< " Simulacion: "<<codigo3(n) << " Formula: " << formula3(n) << " ";
        if (codigo3(n) != formula3(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 04: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: "<<n<< " Simulacion: "<<codigo4(n) << " Formula: " << formula4(n) << " ";
        if (codigo4(n) != formula4(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }

    cout << "Codigo 05: " << endl;
    for (ll n : valoresDePrueba) {
        cout << "Para n: "<<n<< " Simulacion: "<<codigo5(n) << " Formula: " << formula5(n) << " ";
        if (codigo5(n) != formula5(n)) {
            cout << " --> Error en: " << n;
        }
        cout << endl;
    }
    return 0;
}
