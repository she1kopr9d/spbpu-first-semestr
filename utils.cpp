namespace Int{
    int sum_int(int* first_el, int lenght){
        int summa = 0;
        for (int i = 0; i < lenght; i++)
            summa += *(first_el+i);
        return summa;
    }
}

namespace Str{
    char upper(char sym){
        if ((sym >= 'a') && (sym <= 'z')){
            return sym - 0x20;
        }
        return sym;
    }

    char lower(char sym){
        if ((sym >= 'A') && (sym <= 'Z')){
            return sym + 0x20;
        }
        return sym;
    }

    char disRegister(char sym){
        if ((sym >= 'A') && (sym <= 'Z')){
            return lower(sym);
        }
        return upper(sym);
    }
}