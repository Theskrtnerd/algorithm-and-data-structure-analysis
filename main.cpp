#include <iostream>
#include <string>

std::string school_method_add(std::string l1, std::string l2, int b) {
    if(l1.length() < l2.length()) {
        return school_method_add(l2, l1, b);
    }
    int diff = l1.length() - l2.length();
    for (int i=0;i<diff;i++) {
        l2 = "0" + l2;
    }
    std::string sum = "";
    int curr=0, carry=0;

    for(int i=l1.length()-1;i>-1;i--) {
        curr = carry + (l1[i]-'0') + (l2[i]-'0');
        carry = (int)(curr / b);
        curr = curr % b;
        sum = (char)(curr+'0') + sum;
    }

    if(carry > 0) {
        sum = (char)(carry+'0') + sum;
    }

    return sum;
}

std::string school_method_sub(std::string l1, std::string l2, int b) {
    if(l1.length() < l2.length()) {
        return school_method_sub(l2, l1, b);
    }
    int diff = l1.length() - l2.length();
    for (int i=0;i<diff;i++) {
        l2 = "0" + l2;
    }
    std::string sum = "";
    int curr=0, carry=0;

    for(int i=l1.length()-1;i>-1;i--) {
        curr = (l1[i]-'0') - (l2[i]-'0') - carry;
        if (curr < 0) {
            curr += b;
            carry = 1;
        }
        else {
            carry = 0;
        }
        sum = (char)(curr+'0') + sum;
    }

    if(carry > 0) {
        sum = (char)(carry+'0') + sum;
    }

    return sum;
}

std::string multiply_one_bit(char l1, char l2, int b) {
    if(l1 == '0' || l2 == '0') return "0";
    std::string fc = std::to_string(int((l1 - '0') * (l2 - '0') / b));
    std::string sc = std::to_string(((l1 - '0') * (l2 - '0')) % b);
    if(fc == "0") fc = "";
    return fc+sc;
}

std::string karatsuba_multiply(std::string l1, std::string l2, int b) {
    if(l1.length() < l2.length()) {
        return karatsuba_multiply(l2, l1, b);
    }
    if(l1.length() == 1 && l2.length() == 1) {
        return multiply_one_bit(l1[0], l2[0], b);
    }
    else if(l1.length() == 2 && l2.length() == 1) {
        std::string fh = multiply_one_bit(l1[0], l2[0], b) + "0";
        std::string sh = multiply_one_bit(l1[1], l2[0], b);
        return school_method_add(fh, sh, b);
    }
    int diff = l1.length() - l2.length();
    for (int i=0;i<diff;i++) {
        l2 = "0" + l2;
    }
    int n = l1.length();
    int fh = n/2;
    int sh = n - fh;

    std::string a1 = l1.substr(0,fh);
    std::string a0 = l1.substr(fh,sh);

    std::string b1 = l2.substr(0,fh);
    std::string b0 = l2.substr(fh,sh);

    std::string p2 = karatsuba_multiply(a1, b1, b);
    std::string p1 = karatsuba_multiply(school_method_add(a1, a0, b), school_method_add(b1, b0, b), b);
    std::string p0 = karatsuba_multiply(a0, b0, b);
    std::string p3 = school_method_sub(school_method_sub(p1, p2, b), p0, b);
    
    for(int i=0;i<sh;i++) {
        p2 += "00";
        p3 += "0";
    }
    
    std::string ans = school_method_add(school_method_add(p2, p3, b), p0, b);
    ans.erase(0, ans.find_first_not_of('0'));
    if(ans == "") ans = "0";
    return ans;
}

int main() {
    std::string l1, l2;
    int b;
    std::cin >> l1;
    std::cin >> l2;
    std::cin >> b;

    // School mathod school_method_addition
    std::cout << school_method_add(l1, l2, b) << " ";

    // Karatsuba multiplication
    std::cout << karatsuba_multiply(l1, l2, b) << " ";

    // Division just print 0
    std::cout << 0;
    return 0;
}