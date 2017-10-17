#include<string.h>
#include <iostream>
#include <memory>
#define END_ASCII_CODE 122
#define START_ASCII_CODE 65


size_t getNextState(const std::shared_ptr<std::string> &pattern, size_t patternLength, size_t state, size_t code)
{
    // jezeli znak c jest taki sam jak nastepny znak we wzorcu po prostu inkrementujemy stan
    if (state < pattern->size()) {
        if (state < patternLength && ((char) code) == pattern->at(state))
            return state + 1;
    }

    //back state przechowuje wynik
    size_t backState, i;
    //startujemy od najwiekszej wartosci i konczymy kiedy znajdziemy prefiks ktory jest rowniez suffiksem
    for (backState = state; backState > 0; backState--)
    {
        if (pattern->at(backState-1) == code)
        {
            for (i = 0; i < backState-1; i++)
                if (pattern.get()[i] != pattern.get()[state-backState+1+i])
                    break;
            if (i == backState-1)
                return backState;
        }
    }
    return 0;
}

//tworzymy nasza tablice
void createArrayOfTF(const std::shared_ptr<std::string> &pattern, size_t patternLength, size_t TF[][END_ASCII_CODE])
{
    size_t state, code;

    for (state = 0; state <= patternLength; state++)
        for (code = START_ASCII_CODE; code < END_ASCII_CODE ; code++)
            TF[state][code] = getNextState(pattern, patternLength, state, code);
}

// wyszukujemy wszystkie wystapienia naszego wzroca w tekscie
void search(const std::shared_ptr<std::string> &pattern, const std::shared_ptr<std::string> &text)
{
    size_t patternLength = pattern->size();
    size_t textLength = text->size();
    //dwuwymiarowa tablica <transition function>
    size_t TF[patternLength+1][END_ASCII_CODE];

    createArrayOfTF(pattern, patternLength, TF);

    // po stworzeniu naszej tablicy możemy przeszukac ja w poszukiwaniu wzorca czas O(n)
    size_t i, state=0;
    for (i = 0; i < textLength; i++)
    {
        state = TF[state][text->at(i)];
        if (state == patternLength)
            std::cout << "Pattern found! Start of pattern "<< i-patternLength+1<<"\n";
    }
}

int main()
{
    //std::shared_ptr<std::string> text = std::make_shared<std::string>("aaaBBaCcc DDdAAaBBaCa");
    //std::shared_ptr<std::string> pattern = std::make_shared<std::string>("aBBa");
    std::shared_ptr<std::string> text = std::make_shared<std::string>("abababab");//polskie znaki
    std::shared_ptr<std::string> pattern = std::make_shared<std::string>("abab");//
    search(pattern, text);
    return 0;
}
