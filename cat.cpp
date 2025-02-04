#include  <iostream>

int main(){
{  
        std::cout << "Ex 6.0" << std::endl;
        // Ввод текста от пользователя
        std::cout << "Введите строку: ";

        int max_lenght = 40;

        int line_cap = 1;
        char ** lines = new char * [line_cap];
        for (int i = 0; i < line_cap; i++){
            lines[i] = new char[max_lenght];
            lines[i][0] = '\0';
        }
        int size = 0;

        int x = 0;
        int y = 0;
        int b_i = 0;
        int ml = 0;

        char buffer[max_lenght];

        char c = std::cin.get();
        while(c != '\n'){
            if ((x + 2) > line_cap){
                line_cap *= 2;
                char ** temp = new char *[line_cap];
                for (int i = 0; i < (x+1); i++){
                    temp[i] = lines[i];
                }
                delete[] lines;
                for (int i = (x+1); i < line_cap; i++){
                    temp[i] = new char[max_lenght];
                    temp[i][0] = '\0';
                }
                lines = temp;
            }
            if (y >= max_lenght){
                if (b_i >= (max_lenght)){
                    x++;
                    y = 0;
                    b_i = 0;
                    ml = max_lenght;
                }
                else{
                    if (max_lenght-b_i-1 > ml)
                        ml = max_lenght-b_i-1;
                    lines[x][max_lenght-b_i-1] = '\0';
                    x++;
                    y = 0;
                    for (int i = 0; i < b_i; i++){
                        lines[x][y++] = buffer[i];
                    }
                }
            }
            if (((y == 0) && (c == ' ')) == false)
                lines[x][y++] = c;
                buffer[b_i++] = c;
            
            if (c == ' ')
                b_i = 0;
            c = std::cin.get();
        }
        if (y > ml)
            ml = y;
        lines[x][y] = '\0';

        std::cout << line_cap << "\n";
        for (int i = 0; i < 4 + ml; i++)
            std::cout << "-";
        std::cout << '\n';

        for (int i = 0; i < line_cap; i++){
            if (lines[i][0] == '\0')
                break;
            std::cout << "| ";
            int j = 0;
            for (; j < max_lenght; j++){
                if (lines[i][j] == '\0')
                    break;
                std::cout << lines[i][j];
            }
            for(; j < ml; j++)
                std::cout << " ";
            std::cout << " |\n";
        }

        for (int i = 0; i < line_cap; i++)
            delete[] lines[i];
        delete[] lines;

        for (int i = 0; i < 4 + ml; i++)
            std::cout << "-";
        std::cout << '\n';
        
        std::cout <<
            "     \\\n"
            "      \\\n"
            "        /\\_/\\  (\n"
            "       ( o.o ) _)\n"
            "         \\\"/  (\n"
            "       ( | | )\n"
            "      (__d b__)\n";
    }   
}