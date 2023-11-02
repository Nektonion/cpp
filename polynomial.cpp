#include <iostream>
#include <string>
#include <vector>
#include <cmath>
//#include <algorithm> // for sort

/*

Class for polynomials
Coefficients are being entered from highest (a_n) to lowest (a_0)
Pn(x) = a_n * x^n + ... + a_0

*/


using namespace std;

const int degree_limit = 10;

template<typename Type>
class polynomial
{
private:
    int high_degree; // actually, it is high degree +1, or just a number of coefficients

public:
    Type* data;

    polynomial()
    {
        high_degree = degree_limit;
        data = new Type[high_degree]{};
    }

    polynomial(int Size)
    {
        high_degree = Size;
        data = new Type[high_degree]{};
    }

    polynomial(vector<Type> vec)
    {
        high_degree = vec.size();
        data = new Type[high_degree]{};
        for(int i = 0; i < vec.size(); i++)
            data[i] = vec[i];
    }

    polynomial(Type *arr, int Size)
    {
        high_degree = Size;
        data = new Type[high_degree]{};

        for(int i = 0; i < Size; i++)
            data[i] = arr[i];
    }

    polynomial(polynomial &other)
    {
        high_degree = other.high_degree;

        if(data != nullptr)
            delete[] data;

        data = new Type[high_degree]{};

        for(int i = 0; i < high_degree; i++)
            data[i] = other.data[i];
    }

    ~polynomial()
    {
        delete[] data;
        data = nullptr;
    }

    void Print()    // output the polynomial
    {
        cout << this <<" polynomial:" << endl;
        for(int i = 0; i < (high_degree - 1); i++)
            cout << data[i] << " x^" << (high_degree - i - 1) << " + ";
        cout << data[high_degree - 1] << endl << endl;
    }

    void GetCoefficients()    // output coefficients
    {
        cout << this <<" coefficients:" << endl;
        for(int i = 0; i < high_degree; i++)
            cout << data[i] << "  ";
        cout << endl << endl;
    }

    void GetValueAt(float x)    // output the polynomial at the point x
    {
        double result = 0.0;
        for(int i = 0; i < high_degree; i++)
            result += data[i] * pow(x, i);

        cout << "The value of the polynomial at the point x = " << x <<  ":\t" << endl;
        cout << result << endl << endl;
    }

    // polynomial assignment
    polynomial & operator = (const polynomial &other)
    {
        high_degree = other.high_degree;
        if(data != nullptr)
            delete[] data;
        data = new Type[high_degree];
        for(int i = 0; i < high_degree; i++)
            data[i] = other.data[i];
        return *this;
    }

    // polynomial addition
    friend polynomial operator + (const polynomial &first, const polynomial &second)
    {
        polynomial<Type> result(first.high_degree);

        if (first.high_degree != second.high_degree)
        {
            cout << "high polynomial degree mismatch, operation '+' denied" << endl;
            return result;
        }
        else
        {
            for(int i = 0; i < result.high_degree; i++)
                result.data[i] = first.data[i] + second.data[i];
            return result;
        }
    }

    // polynomial + number
    friend polynomial operator + (const polynomial &first, const Type &second)
    {
        polynomial<Type> result(first.high_degree);

        for(int i = 0; i < result.high_degree; i++)
            result.data[i] = first.data[i] + second;

        return result;
    }

    //number + polynomial
    friend polynomial operator + (const Type &first, const polynomial &second)
    {
        polynomial<Type> result(second.high_degree);

        for(int i = 0; i < result.high_degree; i++)
            result.data[i] = second.data[i] + first;

        return result;
    }

    // polynomial += polynomial
    polynomial & operator += (const polynomial &other)
    {
        if (this->high_degree != other.high_degree)
        {
            cout << "high polynomial degree mismatch, operation '+=' denied" << endl;
            return *this;
        }
        else
        {
            for(int i = 0; i < high_degree; i++)
                data[i] += other.data[i];
            return *this;
        }
    }

    // polynomial += number
    polynomial & operator += (const Type &other)
    {
        for(int i = 0; i < high_degree; i++)
            data[i] += other;
        return *this;
    }

    // polynomial substraction
    friend polynomial operator - (const polynomial &first, const polynomial &second)
    {
        polynomial<Type> result(first.high_degree);

        if (first.high_degree != second.high_degree)
        {
            cout << "high polynomial degree mismatch, operation '-' denied" << endl;
            return result;
        }
        else
        {
            for(int i = 0; i < result.high_degree; i++)
                result.data[i] = first.data[i] - second.data[i];
            return result;
        }
    }

    // polynomial - number
    friend polynomial operator - (const polynomial &first, const Type &second)
    {
        polynomial<Type> result(first.high_degree);

        for(int i = 0; i < result.high_degree; i++)
            result.data[i] = first.data[i] - second;

        return result;
    }

    // number - polynomial
    friend polynomial operator - (const Type &first, const polynomial &second)
    {
        polynomial<Type> result(second.high_degree);

        for(int i = 0; i < result.high_degree; i++)
            result.data[i] = first - second.data[i];

        return result;
    }

    // polynomial -= polynomial
    polynomial & operator -= (const polynomial &other)
    {
        if (this->high_degree != other.high_degree)
        {
            cout << "high polynomial degree mismatch, operation '-=' denied" << endl;
            return *this;
        }
        else
        {
            for(int i = 0; i < high_degree; i++)
                data[i] -= other.data[i];
            return *this;
        }
    }

    // polynomial -= number
    polynomial & operator -= (const Type &other)
    {
        for(int i = 0; i < high_degree; i++)
            data[i] -= other;
        return *this;
    }

    // number * polynomial
    friend polynomial operator * (const Type &first, const polynomial &second)
    {
        polynomial<Type> result(second.high_degree);

        for(int i = 0; i < result.high_degree; i++)
            result.data[i] = first * second.data[i];

        return result;
    }

    //polynomial * number
    friend polynomial operator * (const polynomial &first, const Type &second)
    {
        polynomial<Type> result(second.high_degree);

        for(int i = 0; i < result.high_degree; i++)
            result.data[i] = first.data[i] * second;

        return result;
    }

    // polynomial multiplication
    friend polynomial operator * (const polynomial &first, const polynomial &second)
    {
        //actually high_degree is a number of coefficients, so there's -1 below ...
        polynomial<Type> result(first.high_degree + second.high_degree - 1);

        // the condition (*) below allows us to deal with polynomials with different high degrees
        for(int i = 0; i < result.high_degree; i++)
            {
                int coeff = 0;

                for(int j = 0; j < first.high_degree; j++)
                    if( (i-j) >= second.high_degree || (i-j) < 0 )  // (*)
                        continue;
                    else
                        coeff += first.data[j] * second.data[i-j];

                result.data[i] = coeff;
            }

        return result;
    }

    // polynomial *= polynomial
    polynomial & operator *= (const polynomial &other)
    {
        polynomial<float> this_copy(*this);

        delete[] data;
        high_degree = this_copy.high_degree + other.high_degree - 1;
        data = new Type[high_degree]{};

        // the condition (*) below allows us to deal with polynomials with different high degrees
        for(int i = 0; i < high_degree; i++)
            {
                int coeff = 0;

                for(int j = 0; j < this_copy.high_degree; j++)
                    if( (i-j) >= other.high_degree || (i-j) < 0 )  // (*)
                        continue;
                    else
                        coeff += this_copy.data[j] * other.data[i-j];

                data[i] = coeff;
            }
        return *this;
    }

    // polynomial *= number
    polynomial & operator *= (const Type &other)
    {
        for(int i = 0; i < high_degree; i++)
            data[i] *= other;
        return *this;
    }

    // polynomial equality
    bool operator == (const polynomial &other)
    {
        if(high_degree == other.high_degree)
        {
            bool match = true;
            for(int i = 0; i < high_degree; i++)
                if(data[i] != other.data[i])
                    match = false;
            return match;
        }
        else
            return false;
    }

    // polynomial inequality
    bool operator != (const polynomial &other)
    {
        return !(*this == other);
    }

    // prefix increment
    void operator ++()
    {
        for(int i = 0; i < this->high_degree; i++)
            this->data[i]++;
    }

    // postfix increment
    void operator ++(int)
    {
        for(int i = 0; i < this->high_degree; i++)
            this->data[i]++;
    }

    // prefix decrement
    void operator --()
    {
        for(int i = 0; i < this->high_degree; i++)
            this->data[i]--;
    }

    // postfix decrement
    void operator --(int)
    {
        for(int i = 0; i < this->high_degree; i++)
            this->data[i]--;
    }

    // index operator. Usage of link (&) here allows us to set a new value of coefficient
    Type & operator [] (int index)
    {
        if(index >= 0 and index < high_degree)
            return data[index];
        else
        {
            cout << "index is out of range" << endl;
            return data[0];
        }
    }

    //friend ostream & operator << (ostream& out, polynomial<float> &P0);
};

/*template<typename Type>
ostream & operator << (ostream& out, polynomial<float> &P0)
{
    out << P0.data[0];
    return out;
}*/

int main()
{
    //vector<float> a{1.1, 2.1, 3.1};
    //vector<float> b{3.1, 2.1, 1.1};

    vector<float> a{3, 2, 1};
    vector<float> b{1, 2, 3, 4};

    polynomial<float> P1(a);
    P1 += 1;
    polynomial<float> P2(b);
    polynomial<float> P3;
    P1.GetCoefficients();
    P2.GetCoefficients();

    P3 = P1 * P2;
    P3.GetCoefficients();
    P1 *= P2;
    P1.GetCoefficients();

    /*polynomial<float> P2(b);
    polynomial<float> P3;

    P3 = P1 + P2;
    P1.Print();
    P2.Print();
    P3.Print();
    --P3;
    P3.Print();
    P3--;
    P3.Print();*/



    return 0;
}
