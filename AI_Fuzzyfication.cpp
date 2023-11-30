#include <iostream>
#include <iomanip>

using namespace std;

void fuzzification(float x, float a, float b, float c, float &u1, float &u2, float &u3)
{
    float uLeft;   // membership value for half trapezoid (left)
    float uCenter; // membership value for trapezoid
    float uRight;  // membership value for half trapezoid (right)

    float left_c, left_d;      // c, d value for left trapezoid
    float ctr_a, ctr_b, ctr_c; // a,b,c, d value for center triangle
    float right_a, right_b;    // a,b value for right trapezoid

    left_c = a;
    left_d = b;
    ctr_a = a;
    ctr_b = b;
    ctr_c = c;
    right_a = b;
    right_b = c;

    // left trapezoid
    if (x <= left_c)
        uLeft = 1;
    if (x > left_c && x < left_d)
    {
        uLeft = (left_d - x) / (left_d - left_c);
    }
    if (x >= left_d)
        uLeft = 0;

    // cout << "uLeft : " << uLeft << endl;   //to be replaced
    u1 = uLeft;

    // center triangle
    if (x <= ctr_a || x >= ctr_c)
        uCenter = 0;
    if (x > ctr_a && x < ctr_b)
    {
        uCenter = (x - ctr_a) / (ctr_b - ctr_a);
    }
    if (x == ctr_b)
        uCenter = 1;
    if (x > ctr_b && x < ctr_c)
    {
        uCenter = (ctr_c - x) / (ctr_c - ctr_b);
    }
    // cout << "uCenter : " << uCenter << endl;//to be replaced
    u2 = uCenter;

    // right trapezoid
    if (x <= right_a)
        uRight = 0;
    if (x > right_a && x < right_b)
    {
        uRight = (x - right_a) / (right_b - right_a);
    }
    if (x >= right_b)
        uRight = 1;
    // cout << "uRight : " << uRight << endl;//to be replaced
    u3 = uRight;
}

void and_rules(float f1, float f2, float temp, float &conclusion) {
    if (f1 >= f2)
        temp = f2;
    else
        temp = f1;

    if(conclusion ==0 ){ // Memilih nilai yang kecil jika ada 2 nilai yang berbeda
        conclusion = temp;
    }

//    if (f1 >= f2) temp = f2; else temp = f1;
//    if (temp >= conclusion) conclusion = temp; // SALAH DIMANA YANG DIPILIH MALAH YANG BESAR JIKA ADA 2 NILAI YANG BERBEDA
//}

}

void determine_sample(float a, float b, float c, float d, float &s1, float &s2, float &s3)
{ // from output fuzzy
    s1 = (a + b) / 2;
    s2 = (b + c) / 2;
    s3 = (c + d) / 2;
}

void defuzzification(float u1, float u2, float u3, float s1, float s2, float s3, float &result)
{
    result = ((u1 * s1) + (u2 * s2) + (u3 * s3)) / (u1 + u2 + u3);
}


void hitungsample(float uu1, float uu2, float uu3, float uu4 , float uu5, float uu6, float uu7 , float uu8, float uu9 , float &ss1, float &ss2, float &ss3)
{
    ss1 = (uu1+uu2+uu3);
    ss2 = (uu4+uu5+uu6);
    ss3 = (uu7+uu8+uu9);
}

void mamdani(float u1, float u2, float u3, float ss1, float ss2, float ss3, float &hasil)
{
    hasil = ((u1 * ss1) + (u2 * ss2) + (u3 * ss3)) / ((u1*3) + (u2*3) + (u3*3));
}

int main()
{
    float x_jmldownload, uSedikit, uLumayan, uBanyak;  // Jumlah Download
    float x_rating, uJelek, uSedang, uBagus; // Rating
    float kurang, lumayanrekomendasi, rekomendasi;         // Kesimpulan
    float sample1, sample2, sample3;      // untuk defuzzification
    float samp1, samp2, samp3; // untuk hitung sample untuk mamdani
    float aplikasirekomendasi;                         // Aplikasi Rekomendasi outcome
    float apkrekomendasi; // Aplikasi Rekomendasi Outcome untuk Mamdani
    cout << fixed << setprecision(2); //mengatur presisi desimal untuk nilai floating-point. agar yang tampil hanya 2 bilangan di belkaang koma
    cout << "================================================" << endl;
    cout << "   Fuzifikasi menentukan Aplikasi Rekomendasi " << endl;
    cout << "================================================" << endl;
    cout <<endl;
    cout << "  Masukkan X untuk jumlah download \t : ";
    cin >> x_jmldownload;
    cout << endl;
    cout << "  Masukkan X untuk rating \t\t : ";
    cin >> x_rating;
    cout << endl;
    fuzzification(x_jmldownload, 10, 30, 50, uSedikit, uLumayan, uBanyak);  // Jumlah Download
    fuzzification(x_rating, 2.5, 3.5, 4.5 , uJelek, uSedang, uBagus); // Rating

    cout << "================================================" << endl;
    cout << endl;
    cout << "  Fuzzification of Jumlah Download  : " << endl;
    cout << "  uSedikit = " << uSedikit << endl;
    cout << "  uLumayan = " << uLumayan << endl;
    cout << "  uBanyak = " << uBanyak << endl;
    cout << endl;
    cout << "================================================" << endl;
    cout << endl;
    cout << "  Fuzzification of Rating Pengguna : " << endl;
    cout << "  uJelek = " << uJelek << endl;
    cout << "  uSedang = " << uSedang << endl;
    cout << "  uBagus = " << uBagus << endl;
    cout << endl;

    // rules
    and_rules(uSedikit, uJelek, kurang, kurang);
    and_rules(uSedikit, uSedang, kurang, kurang);
    and_rules(uSedikit, uBagus, lumayanrekomendasi, lumayanrekomendasi);
    and_rules(uLumayan, uJelek, kurang, kurang);
    and_rules(uLumayan, uSedang, lumayanrekomendasi, lumayanrekomendasi);
    and_rules(uLumayan, uBagus, rekomendasi, rekomendasi);
    and_rules(uBanyak, uJelek, lumayanrekomendasi, lumayanrekomendasi);
    and_rules(uBanyak, uSedang, rekomendasi, rekomendasi);
    and_rules(uBanyak, uBagus, rekomendasi, rekomendasi);

    cout << "================================================" << endl;
    cout << endl;
    cout << "  Conclusion : " << endl;
    cout << "  uKurang = " << kurang << endl;
    cout << "  uLumayanRekomendasi = " << lumayanrekomendasi << endl;
    cout << "  uRekomendasi = " << rekomendasi << endl;
    cout << endl;

    // sample for defuzzification
    determine_sample(0, 50, 70 , 100, sample1, sample2, sample3);
    cout << "================================================" << endl;
    cout << endl;
    cout << "  Sample value for defuzzification : " << endl;
    cout << "  Sample 1 = " << sample1 << endl;
    cout << "  Sample 2 = " << sample2 << endl;
    cout << "  Sample 3 = " << sample3 << endl;
    cout << endl;

    // defuzzification
    defuzzification(kurang, lumayanrekomendasi, rekomendasi, sample1, sample2, sample3, aplikasirekomendasi);
    cout << "================================================" << endl;
    cout << endl;
    cout << "  Aplikasi Rekomendasi : " << aplikasirekomendasi << endl;
    cout << endl;

    mamdani(kurang, lumayanrekomendasi, rekomendasi, samp1, samp2, samp3, apkrekomendasi);
    hitungsample(10, 20, 30, 60, 65, 70 ,80 ,90 ,95 ,samp1 ,samp2 ,samp3);
    cout << "================================================" << endl;
    cout << endl;
    cout << "  Defuzzifikasi Mamdani " << endl << endl;
    cout << "  Aplikasi Rekomendasi : " << apkrekomendasi << endl;

    return 0;
}
