#include <bits/stdc++.h>
using namespace std;

class BigInt{
private:
    string num{""};

//some helpful methods

    void remove_leading_zeros(string& n , bool front = false){

        if(front){
            while((int)n.size()>1 and n[0] == '0'){
                n.erase(0,1);
            }

        }else{
            while((int)n.size()>1 and n[n.size()-1] == '0'){
                n.erase(n.size()-1,1);
            }

        }

    }


    void equalize(string& num , const int& diff){
        string res{""};

        for(int i = 0;i<diff;i++){

            res+='0';

        }

        res += num;
        num = res;
    }


    void do_equalize(string& num1 , string& num2){
        int sz = max((int)num1.size() , (int)num2.size());

        if((int)num1.size() != sz){
            equalize(num1 , sz - (int)num1.size());
        }else if((int)num2.size() != sz){
            equalize(num2 , sz - (int)num2.size());
        }

        return;
    }


    bool _greater(string& num1 , string& num2){
        for(int i = 0;i<(int)num1.size();i++){
            if(num1[i]<num2[i])
                return false;
            else if(num1[i]>num2[i])
                break;
        }

        return true;
    }
/***************************************************************************************/

    string add(string num2 , string tmp = ""){
        string num1 = num;

        if(tmp != "")
            num1 = tmp;

        int sz = max((int)num1.size() , (int)num2.size()),sum_of_2_digits{0} , carry{0};
        string res{""};


        do_equalize(num1,num2);


        reverse(num1.begin() , num1.end()) , reverse(num2.begin() , num2.end());


        for(int i = 0;i<sz;i++){

            sum_of_2_digits = carry + (num1[i] - '0') + (num2[i] - '0');

            carry = sum_of_2_digits / 10;

            sum_of_2_digits %= 10;

            res += to_string(sum_of_2_digits);
        }

        if(carry){

            res += to_string(carry);

        }

        remove_leading_zeros(res);

        reverse(res.begin() , res.end());

        return res;
    }

/***************************************************************************************/

    string subtract(string num2){
        string num1 = num;

        int sz = max((int)num1.size() , (int)num2.size()) , sub_of_2_digits{0};
        string res{""};
        bool neg{false} , borrow{false};


        do_equalize(num1,num2);


        if(!_greater(num1,num2)){
            swap(num1,num2);
            neg = true;
        }


        reverse(num1.begin() , num1.end()) , reverse(num2.begin() , num2.end());

        for(int i = 0;i<sz;i++){

            sub_of_2_digits = (num1[i] - '0') - (num2[i] - '0');

            if(borrow){
                sub_of_2_digits--;
                borrow = false;
            }

            if(sub_of_2_digits < 0){
                borrow = true;
                sub_of_2_digits += 10;
            }

            res += to_string(sub_of_2_digits);

        }

        remove_leading_zeros(res);

        if(neg){
            res+='-';
        }

        reverse(res.begin() , res.end());

        return res;
    }

/****************************************************************/

    string multiply(string num2){

        string num1 = num;

        string tmp{""},res {"0"};
        int mul_of_2_digits{0},rem{0};


        for(int i = (int)num1.size()-1;i>=0;--i){

            for(int j = (int)num2.size()-1;j>=0;--j){

                mul_of_2_digits = (num1[i]-'0') * (num2[j]-'0');
                mul_of_2_digits += rem;
                rem = mul_of_2_digits/10;
                mul_of_2_digits%=10;
                tmp+=to_string(mul_of_2_digits);

            }

            if(rem){

                tmp+=to_string(rem);
                rem = 0;

            }

            reverse(tmp.begin(),tmp.end());

            for(int j = 0;j<(int)num1.size()-1-i;j++){

                tmp+='0';

            }

            res = add(tmp,res);
            tmp = "";

        }
        return res;
    }

/****************************************************************/
    string divide(int divisor) {
        string n = num;

        string res{""};
        int digit{0};

        for(int i = 0;i<(int)n.size();i++){
            digit *= 10;
            digit += (n[i] - '0');
            res += (digit / divisor) + '0';
            digit %= divisor;
        }

        remove_leading_zeros(res,true);

        return res;
}

public:
    BigInt(string num):num(num){}

    string getNum() const{
        return num;
    }


    BigInt operator +(const BigInt& B){
        return BigInt(add(B.getNum()));
    }
    BigInt operator +(long long num){
        return BigInt(add(to_string(num)));
    }


    BigInt operator -(const BigInt& B){
        return BigInt(subtract(B.getNum()));
    }
    BigInt operator -(long long num){
        return BigInt(subtract(to_string(num)));
    }



    BigInt operator *(const BigInt& B){
        return BigInt(multiply(B.getNum()));
    }
    BigInt operator *(long long num){
        return BigInt(multiply(to_string(num)));
    }


    BigInt operator /(int num){
        return BigInt(divide(num));
    }
};

ostream &operator<<(ostream &out, BigInt b){
        out<<b.getNum();
        return out;
}

void test1(){
    BigInt b1("123456789012345678901234567890") , b2("113456789011345678901134567890");

    BigInt add = b1 + b2 ;
    BigInt sub = b1 - b2 ;
    BigInt mul = b1 * b2 ;
    BigInt div = b1 / 3 ;

    cout<<"/////////////////////test1\\\\\\\\\\\\\\\\\\\\\ \n";
    cout<<"Addition : "<<add<<"\n"; // 236913578023691357802369135780

    cout<<"Subtraction : "<<sub<<"\n"; // 10000000001000000000100000000

    cout<<"Multiplication : "<<mul<<"\n"; // 14007010862991923172458314525833729651721781743086019052100

    cout<<"Division : "<<div<<"\n\n\n"; // 41152263004115226300411522630
}

void test2(){
    BigInt b1("123456789012345678901234567890") , b2("000000");

    BigInt add = b1 + b2 ;
    BigInt sub = b1 - b2 ;
    BigInt mul = b1 * b2 ;
    BigInt div = b1 / 15 ;

    cout<<"/////////////////////test2\\\\\\\\\\\\\\\\\\\\\ \n";
    cout<<"Addition : "<<add<<"\n";
    cout<<"Subtraction : "<<sub<<"\n";
    cout<<"Multiplication : "<<mul<<"\n";
    cout<<"Division : "<<div<<"\n\n\n";
}


int main(){
    test1();
    test2();
}
