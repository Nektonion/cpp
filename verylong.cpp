#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

const int sizes = 1000;

class verylong
{
private:
    int *mas;

public:

    string mantissa;
    bool is_negative;

    verylong()
    {
        mas = (int*)malloc(sizeof(int) * sizes);
        memset(mas, 0, sizes * sizeof(int));
        is_negative = false;
        mantissa = "0";
    }

    verylong(long long a)   // its integer
    {
        is_negative = false;
        if (a < 0)
            is_negative = true;
        mas = (int*)malloc(sizeof(int) * sizes);
        memset(mas, 0, sizes * sizeof(int));
        for(int i = 0; a; i++)
        {
            mas[i] = a % 10;
            a /= 10;
        }
        mantissa = "0";
    }

    verylong(int a)
    {
        is_negative = (a < 0? true : false);
        mas = (int*)malloc(sizeof(int) * 10);
        for(int i = 0; a; i++)
        {
            mas[i] = a % 10;
            a /= 10;
        }
        mantissa = "0";
    }

    verylong(string a)
    {
        if (a.length() > sizes)
            abort();

        is_negative = false;
        int finish = 0;
        if (a[0] == '-')
        {
            finish = 1;
            is_negative = true;
        }

        mas = (int*)malloc(sizeof(int) * sizes);
        memset(mas, 0, sizes * sizeof(int));

        int pos = a.find(".");
        if(pos < a.length())
        {
            mantissa = a.substr(pos + 1);
            a = a.substr(0, pos);
        }
        else
            mantissa = "0";

        for(int i = 0; i < a.size() - finish; i++)
        {
            mas[i] = (int(a[a.size() - 1 - i]) - 48);       // 48 ==     ascii('0')
        }
    }

    verylong(const verylong &b)
    {
        is_negative = b.is_negative;
        mantissa = b.mantissa;
        mas = (int*)malloc(sizeof(int) * sizes);
        memcpy(mas, b.mas, sizeof(int) * sizes);
    }

    ~verylong()
    {
        memset(mas, 0, sizes * sizeof(int));
        free(mas);
        mas = NULL;
    }

/*    char* to_pchar()    // cout verylong number from the highest digit
    {
        int p;
        for(p = sizes - 1; p>0 && !mas[p]; p--);
        char* r = (char*)malloc(p+2);
        r[p+1] = 0;
        for(int i = 0; i <= p; i++)
            r[i] = '0' + mas[p-i];
        return r;
    }*/

    string to_string()  // cout c++ style
    {
        int p;
        for(p = sizes - 1; p>0 && !mas[p]; p--);
        string ans = "";
        for(int i = 0; i <= p; i++)
            ans += '0' + mas[p-i];
        ans += ".";
        ans += mantissa;
        return ans;
    }

    void print()
    {
        if (is_negative && (to_string() != "0"))
            cout << "-";
        cout << to_string() << endl;
    }

    /*verylong abs(const verylong &a)
    {
        verylong x(a);
        x.is_negative = false;
        return x;
    }

    void negative(const verylong &a)     // it is like a minus
    {
        is_negative = !a.is_negative;
    }*/

    friend void operator += (verylong &a, const int &b)
    {
        int pb;
        for(pb = 1; pb<=10 && (b / int(pow(10, pb))); pb++);
        for(int i = 0; i < sizes; i++)
                a.mas[i] += int(b / int(pow(10, i))) % 10;
            for(int i = 0; i < pb; i++)
            {
                a.mas[i+1] += a.mas[i] / 10;
                a.mas[i] %= 10;
            }
    }

    friend void operator += (verylong &a, const verylong &b)    // dodelay manticy
    {
        verylong xa(a);
        verylong xb(b);
        xa.is_negative = false;
        xb.is_negative = false;         // abs doesnt work
        if (a.is_negative == b.is_negative)
        {
            for(int i = 0; i < sizes; i++)
                a.mas[i] += b.mas[i];
            for(int i = 0; i < sizes - 1; i++)
            {
                a.mas[i+1] += a.mas[i] / 10;
                a.mas[i] %= 10;
            }
        }
        else if(xb < xa)
        {
            for(int i = 0; i < sizes; i++)
                a.mas[i] -= b.mas[i];
            for(int i = 0; i < sizes - 1; i++)
                if (a.mas[i] < 0)
                {
                    a.mas[i] += 10;
                    a.mas[i+1] -= 1;
                }
        }

        else
        {
            for(int i = 0; i < sizes; i++)
                a.mas[i] = b.mas[i] - a.mas[i];
            for(int i = 0; i < sizes - 1; i++)
                if (a.mas[i] < 0)
                {
                    a.mas[i] += 10;
                    a.mas[i+1] -= 1;
                }
            a.is_negative = !a.is_negative;
        }

        if (a.mas[sizes-1] >= 10)
            abort();
        a.mantissa = "0";
    }

    friend void operator -= (verylong &a, const verylong &b) // dodelay manticy
    {
        a.mantissa = "0";
        verylong xa(a);
        verylong xb(b);
        xa.is_negative = false;
        xb.is_negative = false;
        if(a.is_negative != b.is_negative)
        {
            for(int i = 0; i < sizes; i++)
                a.mas[i] += b.mas[i];
            for(int i = 0; i < sizes - 1; i++)
            {
                a.mas[i+1] += a.mas[i] / 10;
                a.mas[i] %= 10;
            }
        }
        else if (xa < xb)
        {
            for(int i = 0; i < sizes; i++)
                a.mas[i] = b.mas[i] - a.mas[i];
            for(int i = 0; i < sizes - 1; i++)
                if (a.mas[i] < 0)
                {
                    a.mas[i] += 10;
                    a.mas[i+1] -= 1;
                }
            a.is_negative = !a.is_negative;
        }

        else
        {
            for(int i = 0; i < sizes; i++)
                a.mas[i] -= b.mas[i];
            for(int i = 0; i < sizes - 1; i++)
                if (a.mas[i] < 0)
                {
                    a.mas[i] += 10;
                    a.mas[i+1] -= 1;
                }
        }


        if (a.mas[sizes-1] >= 10)
            abort();
    }

    friend bool operator < (const verylong &a, const verylong &b)       // dodelay manticy
    {
        if(a.is_negative > b.is_negative)
            return true;
        else if ( (a.is_negative - 0.5) * (b.is_negative - 0.5) > 0 )     // == same signs
        {
            int pa, pb;
            for(pa = sizes - 1; pa>0 && !a.mas[pa]; pa--);        // p_i - number of digits of i num
            for(pb = sizes - 1; pb>0 && !b.mas[pb]; pb--);

            if (pa + pb == 0)   // both are 0
                return false;

            if (pa < pb)
                return (true * !a.is_negative);
            else if (pa > pb)
                return (true * a.is_negative);

            int i;
            for(i = 0; pa==pb && a.mas[pa-i] == b.mas[pb-i] && i<pa; i++);
            if ( (a.mas[pa-i] < b.mas[pb-i] && !a.is_negative) | (a.mas[pa-i] > b.mas[pb-i] && a.is_negative) )
                return true;
        }
        return (false * !a.is_negative);
    }

    //column multiplication
    friend void operator *= (verylong &a, const verylong &b)
    {
        a.mantissa = "0";
        a.is_negative = (b.is_negative? !a.is_negative : a.is_negative);

        int pa, pb;
        for(pa = sizes - 1; pa>0 && !a.mas[pa]; pa--);        // p_i - number of digits of i num
        for(pb = sizes - 1; pb>0 && !b.mas[pb]; pb--);

        if(pa + pb > sizes)
            abort();

        verylong a_res(a);  // a reserved
        memset(a.mas, 0, sizeof(int) * sizes);
        for(int i = 0; i <= pb; i++)
            for(int j = 0; j <= pa; j++)
                a.mas[i+j] += a_res.mas[j] * b.mas[i];
        for(int i = 0; i <= (pa + pb); i++)
        {
            a.mas[i + 1] += a.mas[i] / 10;
            a.mas[i] %= 10;
        }
    }

    friend void operator *= (verylong &a, const int c)
    {
        a.mantissa = "0";
        a.is_negative = ((c < 0) ? !a.is_negative : a.is_negative);
        int b = abs(c);
        int pa, pb;
        for(pa = sizes - 1; pa>0 && !a.mas[pa]; pa--);        // p_i - number of digits of i num
        for(pb = 1; pb<=10 && (b / int(pow(10, pb))); pb++);

        if(pa + pb > sizes)
            abort();

        verylong a_res(a);  // a reserved
        memset(a.mas, 0, sizeof(int) * sizes);

        for(int i = 0; i <= pb; i++)
            for(int j = 0; j <= pa; j++)
                a.mas[i+j] += a_res.mas[j] * ( int(b / int(pow(10, i))) % 10);

        for(int i = 0; i <= (pa + pb); i++)
        {
            a.mas[i + 1] += a.mas[i] / 10;
            a.mas[i] %= 10;
        }
    }

    friend verylong operator *= (const int b, verylong &a)
    {
        a *= b;
        return (a);
    }

    friend void operator /= (verylong &a, const int c)
    {
        if (c == 0)
        {
            cout << "dividing by zero, aborted\n";
            abort();
        }
        a.is_negative = ((c < 0) ? !a.is_negative : a.is_negative);
        int b = abs(c);
        int pa;
        for(pa = sizes - 1; pa>0 && !a.mas[pa]; pa--);        // p_i - number of digits of i num
        verylong a_res(a);  // a reserved
        memset(a.mas, 0, sizeof(int) * sizes);

        int k;
        int i = 0;
        int buf = 0;
        for(k = 0; i <= pa; k++)     // i = iterator of a.mas's digits!
        {
            while( (buf < b) && (i<=pa) )
            {
                buf *= 10;
                buf += a_res.mas[pa - i];
                i++;
            }
            a.mas[k] = buf / b;     // we dont know the number of answer's digits. Need to reverse a.mas
            buf -= b *  a.mas[k];
        }

        for(int j = 0; j <= k/2; j++)
            swap(a.mas[j], a.mas[k - 1 - j]);

        double mant = double(buf) / b;
        a.mantissa = (buf? std::to_string(mant).substr(2) : "0");
        //cout<<buf<< " hey bufer \n";
    }

    friend void operator /= (verylong &a, const verylong b)
    {
        int pb;
        for(pb = sizes - 1; pb>0 && !b.mas[pb]; pb--);
        if (pb == 0)
            cout << "dividing by 0\n";
        else if (a < b)
            memset(a.mas, 0, sizeof(int) * sizes);
        else
        {
            a.is_negative = (b.is_negative ? !a.is_negative : a.is_negative);
            int pa;
            for(pa = sizes - 1; pa>0 && !a.mas[pa]; pa--);        // p_i - number of digits of i num
            verylong a_res(a);  // a reserved
            memset(a.mas, 0, sizeof(int) * sizes);

            int k;
            int i = 0;
            verylong buf;
            verylong zero;

            for(k = 0; i <= pa; k++)     // i = iterator of a.mas's digits!
            {                           // k - number of answer's digits
                while( (buf < b) && (i<=pa) )
                {
                    buf *= 10;
                    buf += a_res.mas[pa - i];
                    i++;
                }
                int n = 0;
                while(!buf.is_negative) // or zero < buf. We should check if zero == buf...
                {
                    buf -= b;
                    n++;
                }
                buf += b;
                a.mas[k] = --n;
            }

            for(int j = 0; j <= k/2; j++)
                swap(a.mas[j], a.mas[k - 1 - j]);
        }
        a.mantissa = "0";
    }
};

/*void print(pair<verylong, string> a)
{
    cout << a.first.to_string() << "." << a.second << endl;
}*/

int main()
{
    cout << "=====addition and subtraction=====\n" << endl;
    verylong a("-756432456789087654325678908389289355899407143897843");
    a.print();
    cout << "+" << endl;
    verylong b("123456789087654321234567890987654321345678900987654");
    b.print();
    verylong c(a);
    c += b;
    cout << "=" << endl;
    c.print();
    //  879889245876741975560246799376943677245086044885497
    cout << "- (-756432456789087654325678908389289355899407143897843) =" << endl;
    c -= a;
    c.print();
    cout << "one more time" << endl;
    c -= a;
    c.print();

    cout << "\n=====column multiplication=====\n" << endl;

    verylong d("5831321354342");
    d.print();
    cout << "*" << endl;
    verylong e("20720921239048");
    e.print();
    d *= e;         //verylong *= verylong
    cout << "=" << endl;
    d.print();
    // 120830350502899296094746416

    //d *= -3000;
    cout << "* (-3312) =" << endl;
    -3312 *= d;
    d.print();          // verylong *= int, int *= verylong

    cout << "\n=====dividing by int=====\n" << endl;

    verylong w("5823104");
    w.print();
    cout<<" / 213 ="<<endl;
    w /= 213;
    w.print();
    // 27338.5164319
    cout<<""<<endl;
    verylong g("36779767549938895410480");
    g.print();
    cout<<" / 841290 ="<<endl;
    int h = 841290;
    // 43718298743523512.0

    g /= h;
    g.print();

    cout << "\n=====dividing by verylong=====\n" << endl;

    verylong q("36779767549938895410480");
    q.print();
    cout<<"/"<<endl;
    verylong r("841290");
    r.print();

    q /= r;
    cout<<"="<<endl;        // without reminder
    q.print();

    cout<<endl;
    verylong s("367821938756891230434564832914");
    s.print();
    cout<<"/"<<endl;
    verylong t("7455392348757292819234");
    t.print();
    cout<<"="<<endl;        // reminder is thrown away
    s /= t;
    s.print();

    // 49336362

    cout<<endl;
    t /= 0;
    t.print();
    return 0;
}
