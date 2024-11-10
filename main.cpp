#include<fstream>
#include<sstream>
#include"tokenizer.cpp"

int main(int argc,char* argv[]){
    if(argc<2){
        std::cerr << "errored\n";
        exit(EXIT_FAILURE);
    }
    std::string source,path=argv[1];
    {
    std::stringstream contents_stream;
    std::fstream input(path, std::ios::in);
    contents_stream << input.rdbuf();
    source = contents_stream.str();
    }
    source.push_back('\0');
    Tokenizer tokenizer(source);
    std::vector<Token> tokens=tokenizer.tokenize();
    for(const Token& token:tokens){
        debug(token.type);
        std::cout<< " " << token.val << std::endl;
    }
    exit(EXIT_SUCCESS);
}