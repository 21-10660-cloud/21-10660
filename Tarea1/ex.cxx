#include <vector>
#include <numeric>
#include <cmath>

double mean(const std::vector<double>& v) {
    if (v.empty()) return 0.0;
    return std::accumulate(v.begin(), v.end(), 0.0) / v.size();
}

double variance(const std::vector<double>& v) {
    if (v.size() < 2) return 0.0;
    double m = mean(v);
    double temp = 0;
    for (double x : v) temp += (x - m) * (x - m);
    return temp / v.size();
}

double pearson_r(const std::vector<double>& VA, const std::vector<double>& VB) {
    if (VA.size() != VB.size() || VA.empty()) return 0.0;
    double n = VA.size();
    double sA = std::accumulate(VA.begin(), VA.end(), 0.0);
    double sB = std::accumulate(VB.begin(), VB.end(), 0.0);
    double sAB = 0, sA2 = 0, sB2 = 0;
    for (size_t i = 0; i < n; i++) {
        sAB += VA[i] * VB[i];
        sA2 += VA[i] * VA[i];
        sB2 += VB[i] * VB[i];
    }
    double num = (n * sAB) - (sA * sB);
    double den = std::sqrt(((n * sA2) - (sA * sA)) * ((n * sB2) - (sB * sB)));
    return (den == 0) ? 0.0 : num / den;
}

#include <algorithm>
#include <string>

// --- Funciones Auxiliares para el Ejercicio 5 ---

int char_to_int(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

char int_to_char(int n) {
    if (n >= 0 && n <= 9) return n + '0';
    return n - 10 + 'A';
}

int to_decimal(std::vector<char> v, int base) {
    int decimal = 0;
    int power = 1;
    for (int i = v.size() - 1; i >= 0; i--) {
        decimal += char_to_int(v[i]) * power;
        power *= base;
    }
    return decimal;
}

std::vector<char> from_decimal(int n, int base) {
    if (n == 0) return {'0'};
    std::vector<char> result;
    while (n > 0) {
        result.push_back(int_to_char(n % base));
        n /= base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// --- Implementación de las funciones del Ejercicio 5 ---

std::vector<char> dec_to_septapus(int n) { return from_decimal(n, 7); }
std::vector<char> dec_to_octopus(int n) { return from_decimal(n, 8); }
std::vector<char> dec_to_hexakaidecapus(int n) { return from_decimal(n, 16); }

// Nota: El enunciado pide retornar vector<char>, por lo que convertimos el numero a caracteres
std::vector<char> septapus_to_dec(std::vector<char> s) { 
    std::string s_dec = std::to_string(to_decimal(s, 7));
    return std::vector<char>(s_dec.begin(), s_dec.end());
}
std::vector<char> octopus_to_dec(std::vector<char> s) { 
    std::string s_dec = std::to_string(to_decimal(s, 8));
    return std::vector<char>(s_dec.begin(), s_dec.end());
}
std::vector<char> hexakaidecapus_to_dec(std::vector<char> s) { 
    std::string s_dec = std::to_string(to_decimal(s, 16));
    return std::vector<char>(s_dec.begin(), s_dec.end());
}

std::vector<char> septapus_to_octopus(std::vector<char> s) { return from_decimal(to_decimal(s, 7), 8); }
std::vector<char> septapus_to_hexakaidecapus(std::vector<char> s) { return from_decimal(to_decimal(s, 7), 16); }
std::vector<char> octapus_to_septapus(std::vector<char> s) { return from_decimal(to_decimal(s, 8), 7); }
std::vector<char> octopus_to_hexakaidecapus(std::vector<char> s) { return from_decimal(to_decimal(s, 8), 16); }
std::vector<char> hexakaidecapus_to_septapus(std::vector<char> s) { return from_decimal(to_decimal(s, 16), 7); }
std::vector<char> hexakaidecapus_to_octopus(std::vector<char> s) { return from_decimal(to_decimal(s, 16), 8); }
