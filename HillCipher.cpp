#include <iostream>
#include <vector>

using namespace std;

int determinant(int a, int b, int c, int d) {
    return a * d - b * c;
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

string hillCipherEncrypt(string message, vector<vector<int>> key) {
    string ciphertext = "";
    int n = key.size();

    for (int i = 0; i < message.length(); i += 2) {
        int char1 = message[i] - 'A';
        int char2 = (i + 1 < message.length()) ? message[i + 1] - 'A' : 0;

        int encryptedChar1 = (key[0][0] * char1 + key[0][1] * char2) % 26;
        int encryptedChar2 = (key[1][0] * char1 + key[1][1] * char2) % 26;

        ciphertext += (char)(encryptedChar1 + 'A');
        ciphertext += (char)(encryptedChar2 + 'A');
    }

    return ciphertext;
}

string hillCipherDecrypt(string ciphertext, vector<vector<int>> key) {
    string plaintext = "";
    int n = key.size();

    int det = determinant(key[0][0], key[0][1], key[1][0], key[1][1]);
    int modInv = modInverse(det, 26);

    if (modInv == -1) {
        cout << "The modular inverse does not exist for the given key matrix. Decryption is not possible." << endl;
        return "";
    }

    int adj00 = key[1][1];
    int adj01 = -key[0][1];
    int adj10 = -key[1][0];
    int adj11 = key[0][0];

    adj00 = (adj00 % 26 + 26) % 26;
    adj01 = (adj01 % 26 + 26) % 26;
    adj10 = (adj10 % 26 + 26) % 26;
    adj11 = (adj11 % 26 + 26) % 26;

    key[0][0] = (modInv * adj00) % 26;
    key[0][1] = (modInv * adj01) % 26;
    key[1][0] = (modInv * adj10) % 26;
    key[1][1] = (modInv * adj11) % 26;

    for (int i = 0; i < ciphertext.length(); i += 2) {
        int char1 = ciphertext[i] - 'A';
        int char2 = (i + 1 < ciphertext.length()) ? ciphertext[i + 1] - 'A' : 0;

        int decryptedChar1 = (key[0][0] * char1 + key[0][1] * char2) % 26;
        int decryptedChar2 = (key[1][0] * char1 + key[1][1] * char2) % 26;

        plaintext += (char)(decryptedChar1 + 'A');
        plaintext += (char)(decryptedChar2 + 'A');
    }

    return plaintext;
}

int main() {
    vector<vector<int>> key = {{3, 5}, {2, 7}};
    string message = "HELLO";

    string ciphertext = hillCipherEncrypt(message, key);
    cout << "Encrypted: " << ciphertext << endl;

    string decryptedMessage = hillCipherDecrypt(ciphertext, key);
    cout << "Decrypted: " << decryptedMessage << endl;

    return 0;
}
